#include<Windows.h>
#include<tchar.h>
#ifdef _DEBUG
#include<iostream>
#endif

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