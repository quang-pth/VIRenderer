#include<Windows.h>
#include<tchar.h>
#ifdef _DEBUG
#include<iostream>
#endif
#include<d3d12.h>
#include<d3dx12.h>
#include<dxgi1_6.h>
#include<d3dcompiler.h>
#include<DirectXMath.h>
#include<vector>
#include<xstring>
#include<DirectXTex.h>

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

size_t AlignmentSize(size_t size, size_t alignment) {
	return size + alignment - size % alignment;
}

struct Vertex {
	DirectX::XMFLOAT3 pos;	
	DirectX::XMFLOAT2 uv;
};

struct TexRGBA {
	unsigned char R, G, B, A;
};

#if _DEBUG
int main() {
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
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

	D3D12_RENDER_TARGET_VIEW_DESC _rtvDesc = {};
	_rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	_rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

	DXGI_SWAP_CHAIN_DESC desc = {};
	_swapChain->GetDesc(&desc);
	std::vector<ID3D12Resource*> backBuffers(desc.BufferCount);
	D3D12_CPU_DESCRIPTOR_HANDLE heapHandle = _rtvHeap->GetCPUDescriptorHandleForHeapStart(); // デスクリプタヒープの先頭のハンドルを取得
	UINT descHeapSize = _dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV); // デスクリプタヒープのタイプに応じたハンドルのサイズを取得
	// バックバッファの数だけループして、バックバッファを取得して、レンダーターゲットビューを作成する
	for (uint8_t i = 0; i < desc.BufferCount; ++i) {
		_swapChain->GetBuffer(i, IID_PPV_ARGS(&backBuffers[i])); // バックバッファを取得
		heapHandle.ptr += i * descHeapSize; // デスクリプタヒープのハンドルをバックバッファの数だけ進める
		_dev->CreateRenderTargetView(backBuffers[i], &_rtvDesc, heapHandle); // レンダーターゲットビューを作成。今回はシンプルにするために、ビューの設定はnullptrを指定
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

	Vertex vertices[] = {
		{{-0.4f,  -0.7f,  0.0f}, {0.0f, 1.0f}},	// 左下
		{{-0.4f,   0.7f,  0.0f}, {0.0f, 0.0f}},	// 左上
		{{ 0.4f,  -0.7f,  0.0f}, {1.0f, 1.0f}},	// 右下
		{{ 0.4f,   0.7f,  0.0f}, {1.0f, 0.0f}}	// 右上
	};

	D3D12_HEAP_PROPERTIES heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	D3D12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(vertices));

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

	Vertex* _vertexBufferAddress = nullptr;
	_vertexBuffer->Map(
		0, // サブリソースインデックスを指定。バッファリソースの場合は0を指定
		nullptr, // サブリソースの範囲を指定。バッファリソースの場合はnullptrを指定して、全体をマップする
		(void**)&_vertexBufferAddress // マップされたアドレスを受け取る変数のアドレスを指定
	);
	std::copy(std::begin(vertices), std::end(vertices), _vertexBufferAddress);
	_vertexBuffer->Unmap(
		0, // サブリソースインデックスを指定。バッファリソースの場合は0を指定 
		nullptr // サブリソースの範囲を指定。バッファリソースの場合はnullptrを指定して、全体をアンマップする
	);

	D3D12_VERTEX_BUFFER_VIEW _vertexBufferView;
	_vertexBufferView.BufferLocation = _vertexBuffer->GetGPUVirtualAddress();
	_vertexBufferView.SizeInBytes = sizeof(vertices);
	_vertexBufferView.StrideInBytes = sizeof(vertices[0]);

	unsigned short indices[] = {
		0, 1, 2,
		1, 3, 2
	};

	D3D12_RESOURCE_DESC idxBufferResource = CD3DX12_RESOURCE_DESC::Buffer(sizeof(indices));

	ID3D12Resource* _indexBuffer = nullptr;
	if (_dev->CreateCommittedResource(
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&idxBufferResource,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&_indexBuffer)
	) != S_OK) 
	{
		DebugOutputFormatString("Failed to create index buffer");
		return -1;
	}

	unsigned short* _indexBufferAddress = nullptr;
	_indexBuffer->Map(
		0, // サブリソースインデックスを指定。バッファリソースの場合は0を指定
		nullptr, // サブリソースの範囲を指定。バッファリソースの場合はnullptrを指定して、全体をマップする
		(void**)&_indexBufferAddress // マップされたアドレスを受け取る変数のアドレスを指定
	);
	std::copy(std::begin(indices), std::end(indices), _indexBufferAddress);
	_indexBuffer->Unmap(
		0, // サブリソースインデックスを指定。バッファリソースの場合は0を指定 
		nullptr // サブリソースの範囲を指定。バッファリソースの場合はnullptrを指定して、全体をアンマップする
	);

	D3D12_INDEX_BUFFER_VIEW _indexBufferView;
	_indexBufferView.BufferLocation = _indexBuffer->GetGPUVirtualAddress();
	_indexBufferView.SizeInBytes = sizeof(indices);
	_indexBufferView.Format = DXGI_FORMAT_R16_UINT;

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
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
	};

	DirectX::TexMetadata metaData = {};
	DirectX::ScratchImage scratchImage = {};
	if (DirectX::LoadFromWICFile(
		L"Assets/Texture/phrolova-8.png",
		DirectX::WIC_FLAGS_NONE,
		&metaData, 
		scratchImage
	) != S_OK ) {
		DebugOutputFormatString("Failed to load image");
		return -1;
	}

	const DirectX::Image* image = scratchImage.GetImage(0, 0, 0);
	D3D12_HEAP_PROPERTIES _uploadHeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	D3D12_RESOURCE_DESC _uploadResourceDesc = CD3DX12_RESOURCE_DESC::Buffer(AlignmentSize(image->rowPitch, D3D12_TEXTURE_DATA_PITCH_ALIGNMENT) * image->height);

	// アップロード用のリソース作成
	ID3D12Resource* _uploadBuffer = nullptr;
	if (_dev->CreateCommittedResource(
		&_uploadHeapProperties,
		D3D12_HEAP_FLAG_NONE,
		&_uploadResourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&_uploadBuffer)
	) != S_OK) {
		DebugOutputFormatString("Failed to create upload resource buffer");
		return -1;
	}

	D3D12_HEAP_PROPERTIES _textureHeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	D3D12_RESOURCE_DESC _textureResourceDesc = CD3DX12_RESOURCE_DESC::Buffer(metaData.width);
	_textureResourceDesc.Format = metaData.format;
	_textureResourceDesc.Dimension = static_cast<D3D12_RESOURCE_DIMENSION>(metaData.dimension);
	_textureResourceDesc.Width = metaData.width;
	_textureResourceDesc.Height = metaData.height;
	_textureResourceDesc.DepthOrArraySize = metaData.arraySize;
	_textureResourceDesc.MipLevels = metaData.mipLevels;
	_textureResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;

	// コピー先用のリソース作成
	ID3D12Resource* _textureBuffer = nullptr;
	if (_dev->CreateCommittedResource(
		&_textureHeapProperties,
		D3D12_HEAP_FLAG_NONE,
		&_textureResourceDesc,
		D3D12_RESOURCE_STATE_COPY_DEST,
		nullptr,
		IID_PPV_ARGS(&_textureBuffer)
	) != S_OK) {
		DebugOutputFormatString("Failed to create copy-to texture buffer");
		return -1;
	}

	auto srcAddress = image->pixels;
	auto alignedRowPitch = AlignmentSize(image->rowPitch, D3D12_TEXTURE_DATA_PITCH_ALIGNMENT);
	uint8_t* _mapForImage = nullptr;
	_uploadBuffer->Map(0, nullptr, (void**)&_mapForImage);
	for (int y = 0; y < image->height; ++y) {
		std::copy_n(srcAddress, image->rowPitch, _mapForImage);
		srcAddress += image->rowPitch;
		_mapForImage += alignedRowPitch;
	}
	_uploadBuffer->Unmap(0, nullptr);

	D3D12_TEXTURE_COPY_LOCATION _copySrcLocation = {};
	_copySrcLocation.pResource = _uploadBuffer;
	_copySrcLocation.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
	_copySrcLocation.PlacedFootprint.Offset = 0;
	_copySrcLocation.PlacedFootprint.Footprint.Width = metaData.width;
	_copySrcLocation.PlacedFootprint.Footprint.Height = metaData.height;
	_copySrcLocation.PlacedFootprint.Footprint.Depth = metaData.depth;
	_copySrcLocation.PlacedFootprint.Footprint.RowPitch = AlignmentSize(image->rowPitch, D3D12_TEXTURE_DATA_PITCH_ALIGNMENT);
	_copySrcLocation.PlacedFootprint.Footprint.Format = image->format;

	D3D12_TEXTURE_COPY_LOCATION _copyDstLocation = CD3DX12_TEXTURE_COPY_LOCATION(_textureBuffer, 0);

	{
		_cmdList->CopyTextureRegion(&_copyDstLocation, 0, 0, 0, &_copySrcLocation, nullptr);
		_cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(
			_textureBuffer,
			D3D12_RESOURCE_STATE_COPY_DEST,
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE
		));
		_cmdList->Close();
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
	}

	ID3D12DescriptorHeap* _textureDescHeap = nullptr;
	D3D12_DESCRIPTOR_HEAP_DESC _textureDescHeapDesc = {};
	_textureDescHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	_textureDescHeapDesc.NodeMask = 0;
	_textureDescHeapDesc.NumDescriptors = 1;
	_textureDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	if (_dev->CreateDescriptorHeap(
		&_textureDescHeapDesc,
		IID_PPV_ARGS(&_textureDescHeap)
	) != S_OK) {
		DebugOutputFormatString("Failed to create texture descriptor heap!");
		return -1;
	}

	D3D12_SHADER_RESOURCE_VIEW_DESC _textureResourceView = {};
	_textureResourceView.Format = metaData.format;
	_textureResourceView.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	_textureResourceView.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	_textureResourceView.Texture2D.MipLevels = 1;
	_dev->CreateShaderResourceView(
		_textureBuffer,
		&_textureResourceView,
		_textureDescHeap->GetCPUDescriptorHandleForHeapStart()
	);

	D3D12_ROOT_PARAMETER _rootParameter = {};
	_rootParameter.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	_rootParameter.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	
	D3D12_DESCRIPTOR_RANGE _descTableRange = {};
	_descTableRange.NumDescriptors = 1;
	_descTableRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	_descTableRange.BaseShaderRegister = 0;
	_descTableRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
	
	_rootParameter.DescriptorTable.NumDescriptorRanges = 1;
	_rootParameter.DescriptorTable.pDescriptorRanges = &_descTableRange;

	// D3D12_ROOT_PARAMETER _constRootParameter = {};
	// _constRootParameter.ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
	// _constRootParameter.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	// _constRootParameter.Constants.ShaderRegister = 0;
	// _constRootParameter.Constants.RegisterSpace = 0;
	// _constRootParameter.Constants.Num32BitValues = 8;

	// D3D12_ROOT_PARAMETER _rootParams[2] = {_rootParameter, _constRootParameter};

	D3D12_STATIC_SAMPLER_DESC _samplerDesc = {};
	_samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	_samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	_samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	_samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
	_samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
	_samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
	_samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	_samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;

	D3D12_ROOT_SIGNATURE_DESC _rootSignatureDesc = {};
	_rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	_rootSignatureDesc.NumParameters = 1;
	_rootSignatureDesc.pParameters = &_rootParameter;
	_rootSignatureDesc.NumStaticSamplers = 1;
	_rootSignatureDesc.pStaticSamplers = &_samplerDesc;

	ID3DBlob* rootSignatureBlob = nullptr;
	result = D3D12SerializeRootSignature(
		&_rootSignatureDesc,
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

	pipelineDesc.pRootSignature = _rootSignature; // パイプラインステートのルートシグネチャを指定

	if (_dev->CreateGraphicsPipelineState(
		&pipelineDesc,
		IID_PPV_ARGS(&_pipelineState)
	) != S_OK) {
		DebugOutputFormatString("Failed to create graphics pipeline state");
		return -1;
	}

	D3D12_VIEWPORT _viewport = {};
	_viewport.Width = windowWidth; // ビューポートの幅を指定。今回はウィンドウの幅と同じにする
	_viewport.Height = windowHeight; // ビューポートの高さを指定。今回はウィンドウの高さと同じにする
	_viewport.TopLeftX = 0.0f; // ビューポートの左上のX座標を指定。今回は0にする
	_viewport.TopLeftY = 0.0f; // ビューポートの左上のY座標を指定。今回は0にする
	_viewport.MinDepth = 0.0f; // ビューポートの最小深度を指定。通常は0にする
	_viewport.MaxDepth = 1.0f; // ビューポートの最大深度を指定。通常は1にする

	D3D12_RECT _scissorRect = {};
	_scissorRect.top = 0; // シザー矩形の上端のY座標を指定。今回は0にする
	_scissorRect.left = 0; // シザー矩形の左端のX座標を指定。今回は0にする
	_scissorRect.right = _scissorRect.left + windowWidth; // シザー矩形の右端のX座標を指定。今回は左端からウィンドウの幅だけ進める
	_scissorRect.bottom = _scissorRect.top + windowHeight; // シザー矩形の下端のY座標を指定。今回は上端からウィンドウの高さだけ進める

	D3D12_RESOURCE_BARRIER resourceBarrier = CD3DX12_RESOURCE_BARRIER::Transition(
		nullptr,
		D3D12_RESOURCE_STATE_PRESENT,
		D3D12_RESOURCE_STATE_RENDER_TARGET,
		0
	);

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
		
		float clearColor[] = {1.0f, 1.0f, 0.0f, 1.0f};
		resourceBarrier.Transition.pResource = backBuffers[backBufferIdx];
		resourceBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
		resourceBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
		_cmdList->ResourceBarrier(1, &resourceBarrier);
		_cmdList->ClearRenderTargetView(descHandle, clearColor, 0, nullptr);

		_cmdList->RSSetViewports(1, &_viewport);
		_cmdList->RSSetScissorRects(1, &_scissorRect);

		_cmdList->SetPipelineState(_pipelineState);
		_cmdList->SetGraphicsRootSignature(_rootSignature);
		_cmdList->SetDescriptorHeaps(1, &_textureDescHeap);
		_cmdList->SetGraphicsRootDescriptorTable(0, _textureDescHeap->GetGPUDescriptorHandleForHeapStart());
		
		// float color[] = {
		// 	1.0f, 0.0f, 0.0f, 1.0f,
		// 	0.0f, 1.0f, 0.0f, 1.0f
		// };
		// _cmdList->SetGraphicsRoot32BitConstants(1, 8, &color, 0);

		_cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		_cmdList->IASetVertexBuffers(0, 1, &_vertexBufferView);
		_cmdList->IASetIndexBuffer(&_indexBufferView);
		_cmdList->DrawIndexedInstanced(6, 1, 0, 0, 0);

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
	
	return 0;
}