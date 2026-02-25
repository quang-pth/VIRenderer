#include<Windows.h>
#include<tchar.h>
#ifdef _DEBUG
#include<iostream>
#endif
#include<d3d12.h>
#include<dxgi1_6.h>
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
    printf(format, valist);
    va_end(valist);
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

	RECT wrc = { 0, 0, 1280, 720 }; // ウィンドウのクライアント領域のサイズを指定
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

	HRESULT result = CreateDXGIFactory1(IID_PPV_ARGS(&_dxgiFactory)); // DXGIファクトリーを作成
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
		DebugOutputFormatString("DirectX 12に対応したデバイスが見つかりませんでした。\n");
		return -1;
	}

	MSG msg = {};

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
	}

	UnregisterClass(w.lpszClassName, w.hInstance); // ウィンドウクラスの登録を解除

	DebugOutputFormatString("ウィンドウを閉じました。\n");
	getchar();

	return 0;
}