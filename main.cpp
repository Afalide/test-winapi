
#include <windows.h>
#include <windowsx.h>
#include <iostream>



//////////////////////////////////////////////////
LRESULT CALLBACK MyWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



//////////////////////////////////////////////////
COLORREF 	g_bg_color;
HBRUSH		g_bg_brush;
HWND		g_window;
WNDCLASS 	g_window_class;
HCURSOR		g_hand_cursor;
int			g_xpos;
int			g_ypos;


//////////////////////////////////////////////////
int main()
{
	g_bg_color = RGB(30,30,30)/*RGB(68,150,101)*/;
	g_bg_brush = CreateSolidBrush(g_bg_color);
	g_hand_cursor = LoadCursor(NULL, IDC_HAND);
	
	g_window_class.style      		= 0;
	g_window_class.lpfnWndProc		= MyWindowProc;
	g_window_class.cbClsExtra 		= 0;
	g_window_class.cbWndExtra 		= 0;
	g_window_class.hInstance  		= NULL;
	g_window_class.hIcon			= NULL;
	g_window_class.hCursor			= NULL;
	g_window_class.hbrBackground	= g_bg_brush;
	g_window_class.lpszMenuName		= NULL;
	g_window_class.lpszClassName	= "MyWindowClass";
	
	if(0 == RegisterClass(&g_window_class))
	{
		std::cout << "Class registration failed with error code "
				  << GetLastError() << "\n";
		return 1;
	}
	
	g_window = CreateWindowEx(
		 0 //exstyles
		,"MyWindowClass"
		,"MyWindowTitle"
		,0 //styles
		,50
		,50
		,150
		,150
		,NULL
		,NULL
		,NULL
		,NULL
	);
	
	if(NULL == g_window)
	{
		std::cout << "Window creation failed with error code " 
				  << GetLastError() << "\n";
		return 1;
	}
	
	SetWindowLong(g_window, GWL_EXSTYLE, 0);
	SetWindowLong(g_window, GWL_STYLE, WS_CAPTION|WS_SYSMENU);
	
	ShowWindow(g_window, SW_SHOW);
	// UpdateWindow(g_window);
	
	// HDC main_window_dc = CreateCompatibleDC(NULL);
	// if(0 == UpdateLayeredWindow(g_window, NULL, NULL, NULL, main_window_dc, NULL, g_bg_color, NULL, 0))
		// std::cout << "UpdateLayeredWindow failed with code " << GetLastError() << "\n";
	
	MSG msg;
    while (GetMessage (&msg, NULL, 0, 0))
    {
        TranslateMessage (&msg); 
        DispatchMessage  (&msg);
    }
	
	return 0;
}



//////////////////////////////////////////////////
LRESULT CALLBACK MyWindowProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	
	switch(message)
	{
		case WM_NCCREATE:
			std::cout << "WM_NCCREATE\n";
			break;
			
		case WM_LBUTTONDOWN:
			int x,y;
			x = GET_X_LPARAM(lparam); 
			y = GET_Y_LPARAM(lparam); 
			std::cout << "WM_LBUTTONDOWN at " << x << " " << y << "\n";
			
			// hdc = GetDC(g_window);
			// hdc = GetDCEx(g_window,NULL,DCX_WINDOW);
			hdc = GetWindowDC(g_window);
			if(NULL == hdc)
				std::cout << "GetWindowDC failed with code " << GetLastError() << "\n"; 
			
			if(0 == Rectangle(hdc, x-10, y-10, x, y))
				std::cout << "Rectangle failed with code " << GetLastError() << "\n"; 
				
			ReleaseDC(g_window,hdc);
			
			break;
		
		case WM_PAINT:
			std::cout << "WM_PAINT\n";
			hdc = BeginPaint(window, &ps);
			Rectangle(hdc, 10, 10, 30, 30);
			EndPaint(window, &ps);
			break;
			
		case WM_DESTROY:
			std::cout << "WM_DESTROY\n";
			PostQuitMessage(0);
			break;
	}

	return DefWindowProc(window, message, wparam, lparam);
}







