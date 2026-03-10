#include<Windows.h>
#include<tchar.h>
#ifdef _DEBUG
#include<iostream>
#endif
#include<d3d12.h>
#include<dxgi1_6.h>
#include<d3dcompiler.h>
#include<DirectXMath.h>
#include<vector>

LRESULT WindowProcedure(HWND wind, UINT msg, WPARAM wparam, LPARAM lparam) {
    if (msg == WM_DESTROY) {
		PostQuitMessage(0); // OSに「このウィンドウは閉じるよ」と伝える
        return 0;
    }
	return DefWindowProcW(wind, msg, wparam, lparam);
}

// @brief コンソールにフォーマット付き文字列を表示
// @param format フォーマット（%dとか%fとかの）
// @param 可変長引数
// @remark この関数はデバッグ用です。デバッグ時にしか動作しません。
void DebugOutputFormatString(const char* format, ...) {
#if _DEBUG
    va_list valist;
    va_start(valist, format);
	vprintf(format, valist);
    va_end(valist);
#endif
}

void EnableDebugLayer() {
#if _DEBUG
	ID3D12Debug* debugLayer = nullptr;
	if (D3D12GetDebugInterface(IID_PPV_ARGS(&debugLayer)) != S_OK) {
		DebugOutputFormatString("Failed to get DirectX Debug Interface");
		return;
	}

	debugLayer->EnableDebugLayer();
	debugLayer->Release();
#endif
}

#if _DEBUG
int main() {
#else
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
#endif
	WNDCLASSEX w = {}; // ウィンドウクラスの構造体
	w.cbSize = sizeof(WNDCLASSEX); // 構造体のサイズを指定
	w.lpfnWndProc = (WNDPROC)WindowProcedure; // ウィンドウプロシージャを指定
	w.lpszClassName = _T("VIRenderer"); // ウィンドウクラスの名前を指定
	w.hInstance = GetModuleHandleA(NULL); // インスタンスハンドルを指定
	
	RegisterClassEx(&w); // ウィンドウクラスをOSに登録

	const uint16_t windowWidth = 1280;
	const uint16_t windowHeight = 720;
	const uint16_t backBuffersCount = 2;

	RECT wrc = { 0, 0, windowWidth, windowHeight }; // ウィンドウのクライアント領域のサイズを指定
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, FALSE); // ウィンドウサイズをクライアント領域のサイズから計算
	// ウィンドウを作成
	HWND hwnd = CreateWindow(
		w.lpszClassName, // ウィンドウクラスの名前を指定
		_T("VIRenderer DX12"), // ウィンドウタイトルを指定 
		WS_OVERLAPPEDWINDOW, // ウィンドウスタイルを指定
		CW_USEDEFAULT, // ウィンドウの表示位置をOSに任せる
		CW_USEDEFAULT, // ウィンドウの表示位置をOSに任せる
		wrc.right - wrc.left, // ウィンドウの幅を指定
		wrc.bottom - wrc.top, // ウィンドウの高さを指定
		NULL, // 親ウィンドウハンドル
		NULL, // メニューハンドル
		w.hInstance, // インスタンスハンドル
		NULL // 追加パラメータ
	);
	
	ShowWindow(hwnd, SW_SHOW); // ウィンドウを表示する

	ID3D12Device* _dev = nullptr;
	IDXGIFactory6* _dxgiFactory = nullptr;
	IDXGISwapChain4* _swapChain = nullptr;
	ID3D12CommandAllocator* _cmdAllocator = nullptr;
	ID3D12GraphicsCommandList* _cmdList = nullptr;
	ID3D12CommandQueue* _cmdQueue = nullptr;
	ID3D12DescriptorHeap* _rtvHeap = nullptr;
	ID3D12Fence* _fence = nullptr;
	UINT64 _fenceVal = 0;
	ID3D12Resource* _vertexBuffer = nullptr;

	EnableDebugLayer();

#if _DEBUG
	CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(&_dxgiFactory)); // デバッグモードでDXGIファクトリーを作成
#else
	CreateDXGIFactory1(IID_PPV_ARGS(&_dxgiFactory)); // DXGIファクトリーを作成
#endif

	IDXGIAdapter* tmpAdapter = nullptr;
	std::vector<IDXGIAdapter*> adapters; // 利用可能なアダプターを保存するベクター
	for (int i = 0; _dxgiFactory->EnumAdapters(i, &tmpAdapter) != DXGI_ERROR_NOT_FOUND; ++i) {
		adapters.push_back(tmpAdapter); // アダプターをベクターに追加
	}
	for (auto adapter : adapters) {
		DXGI_ADAPTER_DESC desc;
		adapter->GetDesc(&desc);
		std::wstring wdesc(desc.Description);

		if (wdesc.find(L"NVIDIA") != std::wstring::npos) {
			tmpAdapter = adapter;
			break; // NVIDIA製のアダプターが見つかったらループを抜ける
		}

	}

	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};

	D3D_FEATURE_LEVEL supportedFeatureLevel; // 最低限必要な機能レベルを指定
	for (auto level : featureLevels) {
		if (D3D12CreateDevice(
			tmpAdapter, // 物理デバイスを指定。nullptrだとOSが最適なものを選ぶ
			level, // DirectXの機能レベルを指定
			IID_PPV_ARGS(&_dev) // デバイスのポインタを受け取る変数のアドレスを指定
			) == S_OK) 
		{
			supportedFeatureLevel = level;
			break; // 対応した機能レベルが見つかったらループを抜ける
		}
	}
	if (_dev == nullptr) {
		DebugOutputFormatString("Failed to create DirectX Device\n");
		return -1;
	}

	if (_dev->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT, // コマンドリストのタイプを指定
		IID_PPV_ARGS(&_cmdAllocator) // コマンドアロケーターのポインタを受け取る変数のアドレスを指定
	) != S_OK) {
		DebugOutputFormatString("Failed to create command allocator \n");
		return -1;
	}

	if (_dev->CreateCommandList(
		0, // ノードマスク。シングルGPUの場合は0で問題ない
		D3D12_COMMAND_LIST_TYPE_DIRECT, // コマンドリストのタイプを指定
		_cmdAllocator, // コマンドアロケーターを指定
		nullptr, // 初期パイプラインステートオブジェクト。今はまだ必要ないのでnullptrを指定
		IID_PPV_ARGS(&_cmdList) // コマンドリストのポインタを受け取る変数のアドレスを指定
	) != S_OK) {
		DebugOutputFormatString("Failed to create command list\n");
		return -1;
	}

	D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};
	cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	cmdQueueDesc.NodeMask = 0; // シングルGPUの場合は0で問題ない
	cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	if (_dev->CreateCommandQueue(
		&cmdQueueDesc,
		IID_PPV_ARGS(&_cmdQueue)
	) != S_OK) {
		DebugOutputFormatString("Failed to create command queue\n");
		return -1;
	}

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
	swapChainDesc.Width = windowWidth;
	swapChainDesc.Height = windowHeight;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.Stereo = false; // ステレオ3D表示をするかどうか
	swapChainDesc.SampleDesc.Count = 1; // マルチサンプリングのサンプル数を指定。1ならマルチサンプリングなし
	swapChainDesc.SampleDesc.Quality = 0; // マルチサンプリングの品質レベルを指定。0が最も高品質
	swapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER; // バックバッファの用途を指定。
	swapChainDesc.BufferCount = backBuffersCount;
	swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	if (_dxgiFactory->CreateSwapChainForHwnd(
		_cmdQueue, 
		hwnd,
		&swapChainDesc,
		nullptr, // フルスクリーンモードの設定。今はまだ必要ないのでnullptrを指定
		nullptr, // 出力を制限する場合はその出力を指定。今はまだ必要ないのでnullptrを指定
		(IDXGISwapChain1**)&_swapChain
	) != S_OK) {
		DebugOutputFormatString("Failed to create swapchain\n");
		return -1;
	}

	D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc = {};
	descriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	descriptorHeapDesc.NodeMask = 0; // シングルGPUの場合は0で問題ない
	descriptorHeapDesc.NumDescriptors = backBuffersCount; // デスクリプタの数を指定。今回はバックバッファの数と同じにする
	descriptorHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	if (_dev->CreateDescriptorHeap(
		&descriptorHeapDesc,
		IID_PPV_ARGS(&_rtvHeap)
	) != S_OK) {
		DebugOutputFormatString("Failed to create descriptor heap\n");
		return -1;
	}

	DXGI_SWAP_CHAIN_DESC desc = {};
	_swapChain->GetDesc(&desc);
	std::vector<ID3D12Resource*> backBuffers(desc.BufferCount);
	D3D12_CPU_DESCRIPTOR_HANDLE heapHandle = _rtvHeap->GetCPUDescriptorHandleForHeapStart(); // デスクリプタヒープの先頭のハンドルを取得
	UINT descHeapSize = _dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV); // デスクリプタヒープのタイプに応じたハンドルのサイズを取得
	// バックバッファの数だけループして、バックバッファを取得して、レンダーターゲットビューを作成する
	for (uint8_t i = 0; i < desc.BufferCount; ++i) {
		_swapChain->GetBuffer(i, IID_PPV_ARGS(&backBuffers[i])); // バックバッファを取得
		heapHandle.ptr += i * descHeapSize; // デスクリプタヒープのハンドルをバックバッファの数だけ進める
		_dev->CreateRenderTargetView(backBuffers[i], nullptr, heapHandle); // レンダーターゲットビューを作成。今回はシンプルにするために、ビューの設定はnullptrを指定
	}

	if (_dev->CreateFence(
		_fenceVal, // フェンスの初期値を指定, 今回は0から始めるので_fenceValを指定
		D3D12_FENCE_FLAG_NONE, // フェンスのフラグを指定, 今回は特に必要ないのでD3D12_FENCE_FLAG_NONEを指定
		IID_PPV_ARGS(&_fence) // フェンスのポインタを受け取る変数のアドレスを指定
	) != S_OK) {
		DebugOutputFormatString("Failed to create fence");
		return -1;
	}

	MSG msg = {};

	DirectX::XMFLOAT3 vertices[3] = {
		{-1.0f,  -1.0f,  0.0f},	// 左下
		{-1.0f,   1.0f,  0.0f},	// 左上
		{ 1.0f,  -1.0f,  0.0f}	// 右下
	};

	D3D12_HEAP_PROPERTIES heapProperties;
	heapProperties.Type = D3D12_HEAP_TYPE_UPLOAD; // ヒープのタイプを指定。CPUからGPUにデータを転送するためのヒープなのでD3D12_HEAP_TYPE_UPLOADを指定
	heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN; // CPUのページプロパティ。D3D12_HEAP_TYPE_DEFAULTを使用する場合はD3D12_CPU_PAGE_PROPERTY_UNKNOWNを指定する必要がある
	heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN; // メモリプールの優先順位。D3D12_HEAP_TYPE_DEFAULTを使用する場合はD3D12_MEMORY_POOL_UNKNOWNを指定する必要がある
	heapProperties.CreationNodeMask = 0; // マルチGPU環境で使用するノードマスク。シングルGPUの場合は0で問題ない
	heapProperties.VisibleNodeMask = 0; // マルチGPU環境で使用するノードマスク。シングルGPUの場合は0で問題ない

	D3D12_RESOURCE_DESC resourceDesc;
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER; // リソースの次元を指定。今回は頂点バッファなのでD3D12_RESOURCE_DIMENSION_BUFFERを指定
	resourceDesc.Width = sizeof(vertices); // リソースの幅を指定。今回は頂点データ全体のサイズを指定
	resourceDesc.Height = 1; // リソースの高さを指定。バッファリソースの場合は1を指定
	resourceDesc.Alignment = 0; // リソースのアライメントを指定。0ならデフォルトのアライメントが使用される
	resourceDesc.DepthOrArraySize = 1; // リソースの深さまたは配列サイズを指定。バッファリソースの場合は1を指定
	resourceDesc.MipLevels = 1; // ミップレベルの数を指定。バッファリソースの場合は1を指定
	resourceDesc.Format = DXGI_FORMAT_UNKNOWN; // リソースのフォーマットを指定。バッファリソースの場合はDXGI_FORMAT_UNKNOWNを指定
	resourceDesc.SampleDesc.Count = 1; // マルチサンプリングのサンプル数を指定。バッファリソースの場合は1を指定
	resourceDesc.SampleDesc.Quality = 0; // マルチサンプリングの品質レベルを指定。バッファリソースの場合は0を指定
	resourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE; // リソースのフラグを指定。今回は特に必要ないのでD3D12_RESOURCE_FLAG_NONEを指定
	resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR; // リソースのレイアウトを指定。バッファリソースの場合はD3D12_TEXTURE_LAYOUT_ROW_MAJORを指定

	if (_dev->CreateCommittedResource(
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&resourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&_vertexBuffer)
	) != S_OK) 
	{
		DebugOutputFormatString("Failed to create vertex buffer");
		return -1;
	}

	DirectX::XMFLOAT3* vertexBufferAddress = nullptr;
	_vertexBuffer->Map(
		0, // サブリソースインデックスを指定。バッファリソースの場合は0を指定
		nullptr, // サブリソースの範囲を指定。バッファリソースの場合はnullptrを指定して、全体をマップする
		(void**)&vertexBufferAddress // マップされたアドレスを受け取る変数のアドレスを指定
	);
	std::copy(std::begin(vertices), std::end(vertices), vertexBufferAddress);
	_vertexBuffer->Unmap(
		0, // サブリソースインデックスを指定。バッファリソースの場合は0を指定 
		nullptr // サブリソースの範囲を指定。バッファリソースの場合はnullptrを指定して、全体をアンマップする
	);

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
	vertexBufferView.BufferLocation = _vertexBuffer->GetGPUVirtualAddress();
	vertexBufferView.SizeInBytes = sizeof(vertices);
	vertexBufferView.StrideInBytes = sizeof(vertices[0]);

	ID3DBlob* _vsBlob = nullptr;
	ID3DBlob* _psBlob = nullptr;
	ID3DBlob* _errorBlob = nullptr;
	HRESULT result = D3DCompileFromFile(
		L"Assets/Shader/BasicVertexShader.vs.hlsl",
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"BasicVS",
		"vs_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		&_vsBlob,
		&_errorBlob);
	if (FAILED(result)) {
		if (result == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND)) {
			::OutputDebugStringA("Assets/Shader/BasicVertexShader.vs.hlsl is not found");
		}
		else {
			std::string errorMsg;
			errorMsg.resize(_errorBlob->GetBufferSize());
			std::copy_n((char*)_errorBlob->GetBufferPointer(), _errorBlob->GetBufferSize(), errorMsg.begin());
			errorMsg += "\n";
			::OutputDebugStringA(errorMsg.c_str());
		}
		return -1;
	}

	result = D3DCompileFromFile(
		L"Assets/Shader/BasicPixelShader.ps.hlsl",
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"BasicPS",
		"ps_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		&_psBlob,
		&_errorBlob);
	if (FAILED(result)) {
		if (result == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND)) {
			::OutputDebugStringA("Assets/Shader/BasicPixelShader.ps.hlsl is not found");
		}
		else {
			std::string errorMsg;
			errorMsg.resize(_errorBlob->GetBufferSize());
			std::copy_n((char*)_errorBlob->GetBufferPointer(), _errorBlob->GetBufferSize(), errorMsg.begin());
			errorMsg += "\n";
			::OutputDebugStringA(errorMsg.c_str());
		}
		return -1;
	}

	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0}
	};

	ID3D12PipelineState* _pipelineState = nullptr;
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc = {};
	pipelineDesc.VS.pShaderBytecode = _vsBlob->GetBufferPointer();
	pipelineDesc.VS.BytecodeLength = _vsBlob->GetBufferSize();
	pipelineDesc.PS.pShaderBytecode = _psBlob->GetBufferPointer();
	pipelineDesc.PS.BytecodeLength = _psBlob->GetBufferSize();
	pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // サンプルマスクを指定。0xffffffffならすべてのサンプルが有効
	pipelineDesc.RasterizerState.MultisampleEnable = false; // マルチサンプリングを有効にするかどうか。今回はマルチサンプリングを使用しないのでfalseを指定
	pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE; // カリングモードを指定。今回は三角形の表も裏も両方表示したいのでD3D12_CULL_MODE_NONEを指定
	pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID; // 塗りつぶしモードを指定。D3D12_FILL_MODE_WIREFRAMEならワイヤーフレーム表示になるが、今回は通常の塗りつぶし表示にしたいのでD3D12_FILL_MODE_SOLIDを指定
	pipelineDesc.RasterizerState.DepthClipEnable = true; // 深度クリッピングを有効にするかどうか。これをtrueにしておくと、深度が0以下のピクセルがクリップされる。今回は有効にしておく
	pipelineDesc.BlendState.AlphaToCoverageEnable = false; // アルファトゥカバレッジを有効にするかどうか。マルチサンプリングのみで意味がある機能なので、今回はマルチサンプリングを使用しないためfalseを指定
	pipelineDesc.BlendState.IndependentBlendEnable = false; // 独立ブレンドを有効にするかどうか。複数のレンダーターゲットを使用する場合に、レンダーターゲットごとに異なるブレンド設定を使用できるようになるが、今回はレンダーターゲットは1つだけなのでfalseを指定

	D3D12_RENDER_TARGET_BLEND_DESC defaultRenderTargetBlendDesc = {};
	defaultRenderTargetBlendDesc.BlendEnable = false; // ブレンドを有効にするかどうか。今回はブレンドを使用しないのでfalseを指定
	defaultRenderTargetBlendDesc.LogicOpEnable = false; // ロジックオペレーションを有効にするかどうか。今回はロジックオペレーションを使用しないのでfalseを指定
	defaultRenderTargetBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL; // レンダーターゲットの書き込みマスクを指定。今回はすべてのチャンネルを書き込み可能にするのでD3D12_COLOR_WRITE_ENABLE_ALLを指定
	
	pipelineDesc.BlendState.RenderTarget[0] = defaultRenderTargetBlendDesc;

	pipelineDesc.InputLayout.pInputElementDescs = inputLayout; // 入力レイアウトの配列を指定
	pipelineDesc.InputLayout.NumElements = _countof(inputLayout); // 入力レイアウトの要素数を指定。_countofは配列の要素数を取得するマクロ
	pipelineDesc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED; // ストリップカット値を指定。インデックスバッファを使用しない場合はD3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLEDを指定
	pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE; // プリミティブトポロジー型を指定。今回は三角形を描画するのでD3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLEを指定
	pipelineDesc.NumRenderTargets = 1; // レンダーターゲットの数を指定。今回は1つだけなので1を指定
	pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM; // レンダーターゲットのフォーマットを指定。今回はRGBA8の不透明度付きフォーマットを指定
	pipelineDesc.SampleDesc.Count = 1; // マルチサンプリングのサンプル数を指定。バッファリソースの場合は1を指定
	pipelineDesc.SampleDesc.Quality = 0; // マルチサンプリングの品質レベルを指定。バッファリソースの場合は0を指定

	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc = {};
	rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT; //今回は頂点情報だけをルートパラメータとして使用するので、D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUTを指定して、入力アセンブラの入力レイアウトを使用できるようにする

	ID3DBlob* rootSignatureBlob = nullptr;
	result = D3D12SerializeRootSignature(
		&rootSignatureDesc,
		D3D_ROOT_SIGNATURE_VERSION_1, // ルートシグネチャのバージョンを指定。今回は1.0を指定
		&rootSignatureBlob,
		&_errorBlob
	);
	if (FAILED(result)) {
		std::string errorMsg;
		errorMsg.resize(_errorBlob->GetBufferSize());
		std::copy_n((char*)_errorBlob->GetBufferPointer(), _errorBlob->GetBufferSize(), errorMsg.begin());
		errorMsg += "\n";
		::OutputDebugStringA(errorMsg.c_str());
		return -1;
	}

	ID3D12RootSignature* _rootSignature = nullptr;
	if (_dev->CreateRootSignature(
		0, // ノードマスク。シングルGPUの場合は0で問題ない
		rootSignatureBlob->GetBufferPointer(), // ルートシグネチャのバイナリデータを指定
		rootSignatureBlob->GetBufferSize(), // ルートシグネチャのバイナリデータのサイズを指定
		IID_PPV_ARGS(&_rootSignature) // ルートシグネチャのポインタを受け取る変数のアドレスを指定
	) != S_OK) {
		DebugOutputFormatString("Failed to create root signature");
		rootSignatureBlob->Release(); // ルートシグネチャのバイナリデータはもう必要ないので解放する
		return -1;
	}
	rootSignatureBlob->Release(); // ルートシグネチャのバイナリデータはもう必要ないので解放する
	
	pipelineDesc.pRootSignature = _rootSignature; // パイプラインステートのルートシグネチャを指定

	if (_dev->CreateGraphicsPipelineState(
		&pipelineDesc,
		IID_PPV_ARGS(&_pipelineState)
	) != S_OK) {
		DebugOutputFormatString("Failed to create graphics pipeline state");
		return -1;
	}

	D3D12_VIEWPORT _viewport = {};
	_viewport.Width = windowWidth;
	_viewport.Height = windowHeight;
	_viewport.TopLeftX = 0.0f;
	_viewport.TopLeftY = 0.0f;
	_viewport.MinDepth = 0.0f;
	_viewport.MaxDepth = 1.0f;

	D3D12_RECT _scissorRect = {};
	_scissorRect.top = 0;
	_scissorRect.left = 0;
	_scissorRect.right = _scissorRect.left + windowWidth;
	_scissorRect.bottom = _scissorRect.top + windowHeight;

	while (true) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) { // メッセージがあるか確認
			if (msg.message == WM_QUIT) { // WM_QUITメッセージならループを抜ける
				break;
			}
			TranslateMessage(&msg); // キーボード入力などのメッセージを変換
			DispatchMessage(&msg); // ウィンドウプロシージャにメッセージを送る
		}

		if (msg.message == WM_QUIT) { // WM_QUITメッセージならループを抜ける
			break;
		}

		UINT backBufferIdx = _swapChain->GetCurrentBackBufferIndex();
		D3D12_CPU_DESCRIPTOR_HANDLE descHandle = _rtvHeap->GetCPUDescriptorHandleForHeapStart();
		descHandle.ptr += backBufferIdx * descHeapSize;
		_cmdList->OMSetRenderTargets(
			1, // レンダーターゲットの数を指定。今回は1つだけなので1を指定 
			&descHandle, // レンダーターゲットのハンドルを指定
			true, // レンダーターゲットのハンドルは配列で渡す必要があるが、今回は1つだけなのでtrueを指定して、配列ではなく単一のハンドルを渡す
			nullptr // デプスステンシルビューのハンドルを指定。今回はデプスステンシルバッファを使わないのでnullptrを指定
		);
		
		D3D12_RESOURCE_BARRIER resourceBarrier = {};
		resourceBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		resourceBarrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		resourceBarrier.Transition.pResource = backBuffers[backBufferIdx];
		resourceBarrier.Transition.Subresource = 0;
		resourceBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
		resourceBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
		
		float clearColor[] = {1.0f, 1.0f, 0.0f, 1.0f};
		_cmdList->ResourceBarrier(1, &resourceBarrier);
		_cmdList->ClearRenderTargetView(descHandle, clearColor, 0, nullptr);

		_cmdList->SetPipelineState(_pipelineState);
		_cmdList->SetGraphicsRootSignature(_rootSignature);
		_cmdList->RSSetViewports(1, &_viewport);
		_cmdList->RSSetScissorRects(1, &_scissorRect);
		_cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		_cmdList->IASetVertexBuffers(0, 1, &vertexBufferView);
		_cmdList->DrawInstanced(3, 1, 0, 0);

		resourceBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
		resourceBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
		_cmdList->ResourceBarrier(1, &resourceBarrier);

		_cmdList->Close(); // コマンドリストをクローズして、コマンドの記録を終了する
		ID3D12CommandList* cmdLists[] = { _cmdList };
		_cmdQueue->ExecuteCommandLists(1, cmdLists);
		_cmdQueue->Signal(_fence, ++_fenceVal);
		if (_fence->GetCompletedValue() != _fenceVal) {
			HANDLE completeEvent = CreateEvent(
				nullptr, // セキュリティ属性。nullptrならデフォルトのセキュリティ設定
				false, // マニュアルリセットイベントかオートリセットイベントか。
				false, // イベントの初期状態。trueならシグナル状態、falseなら非シグナル状態
				nullptr // イベントの名前。nullptrなら名前なしイベント
			);
			_fence->SetEventOnCompletion(_fenceVal, completeEvent);
			WaitForSingleObject(completeEvent, INFINITE); // イベントがシグナル状態になるまで待つ。これにより、GPUがコマンドの実行を完了するまで次のコマンドを送らないようにする
			CloseHandle(completeEvent); // イベントハンドルを閉じる
		}
		_cmdAllocator->Reset(); // コマンドアロケーターをリセットして、コマンドリストが使用したコマンドアロケーターのメモリを再利用できるようにする
		_cmdList->Reset(_cmdAllocator, nullptr); // コマンドリストをリセットして、再びコマンドを記録できるようにする

		_swapChain->Present(
			1, // 垂直同期ありで表示。0なら垂直同期なし
			0
		);
	}

	UnregisterClass(w.lpszClassName, w.hInstance); // ウィンドウクラスの登録を解除

	DebugOutputFormatString("Window Closed\n");
	getchar();

	return 0;
}