
#include <iostream>
#include <windows.h>
#include <wingdi.h>
#include <windowsx.h>
// #include <gdiplus.h>

//Some globals
COLORREF 	g_bg_color = RGB(68,150,101);
HBRUSH		g_bg_brush = CreateSolidBrush(g_bg_color);

//The window procedure. It is a function designed to process window events (=messages).
//It will be called each time the window recieves an event
LRESULT CALLBACK MyWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//Definition for the window procedure
LRESULT CALLBACK MyWindowProc(
	HWND hWnd,        // handle to window
    UINT uMsg,        // message identifier
    WPARAM wParam,    // first message parameter
    LPARAM lParam)    // second message parameter
{
	std::cout << "Got an event: ";
	
	switch(uMsg)
	{
		case WM_NCCREATE:
			std::cout << "WM_NCCREATE\n";
			return 1;
			
		case WM_LBUTTONDOWN:
			std::cout << "WM_LBUTTONDOWN";
			int x,y;
			x = GET_X_LPARAM(lParam); 
			y = GET_Y_LPARAM(lParam); 
			return 0;
		
		case WM_PAINT:
			std::cout << "WM_PAINT\n";
			PAINTSTRUCT ps; 
			HDC hdc; 
			hdc = BeginPaint(hWnd, &ps);
			
			//TextOut(hdc, 0, 0, "Hello, Windows!", 15);
			Rectangle(hdc, 10, 10, 30, 30);
			
			EndPaint(hWnd, &ps);
			return 0;
			
		case WM_DESTROY:
			std::cout << "WM_DESTROY\n"; 
			PostQuitMessage(0);
			return 0;
			
		default:
			//We call the default window procedure
			std::cout << "other\n";
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	
	std::cout << "This part should not be called\n";
	return 0;
}

int main()
{
	std::cout << "Start\n";

	//Create the window class (aka the pattern of the window)
	WNDCLASS winClass;
	winClass.style      	= 0 /*CS_DBLCLKS | CS_VREDRAW*/;
	winClass.lpfnWndProc	= MyWindowProc;
	winClass.cbClsExtra 	= 0;
	winClass.cbWndExtra 	= 0;
	winClass.hInstance  	= NULL;
	winClass.hIcon			= NULL;
	winClass.hCursor		= NULL;
	winClass.hbrBackground	= g_bg_brush;
	winClass.lpszMenuName	= NULL;
	winClass.lpszClassName	= "MyClass";
	
	//Try to register the window class
	if(0 == RegisterClass(&winClass))
	{
		std::cout << "Class registration failed. "
				  << "Error code is " << GetLastError() << "\n";
		return 1;
	}
	
	//Try to create a window with this class
	HWND window;
	window = CreateWindow(
		"MyClass",
		"MyWindow",
		0/*WS_OVERLAPPED*/,
		50,50,   //Coordinates
		200,200, //Size
		NULL,
		NULL,
		NULL,
		NULL
	);
	
	if(NULL == window)
	{
		std::cout << "Window creation failed. "
				  << "Error code is " << GetLastError() << "\n";
		return 1;
	}
	
	//Remove every style (borders, titlebar...)
	SetWindowLong(window, GWL_STYLE,   0);
	SetWindowLong(window, GWL_EXSTYLE, 0);
	
	//Add basic window decoration
	SetWindowLong(window, GWL_STYLE,
		WS_CAPTION     // title bar + borders
	   |WS_SYSMENU     // icon X (close window, requires CAPTION)
	   |WS_MAXIMIZEBOX // icon □ (maximize window, requires SYSMENU)
	   |WS_MINIMIZEBOX // icon _ (minimize window, requires SYSMENU)
	);
	
	//Show the created window
	ShowWindow(window, SW_SHOW);
    UpdateWindow(window);

	//Prepare the GDI+ API
	// Gdiplus::GdiplusStartupInput 	gdiStartupInput;
	// Gdiplus::GdiplusStartupOutput	gdiStartupOuput;
	// ULONG_PTR                    	gdiToken;
	
	//Start the GDI+ API
	// gdiStartupInput.SuppressBackgroundThread = true;
	// Gdiplus::GdiplusStartup(&gdiToken, &gdiStartupInput, &gdiStartupOuput);
	
	//Get the hook procedures. We are responsible to call them
	//before and after the main loop
	//This is to avoid a background thread created by the system
	// ULONG_PTR 							hookProcToken;
	// Gdiplus::NotificationHookProc	 	notificationHookProc;
	
	// Gdiplus::NotificationUnhookProc 	notificationUnhookProc;
	// notificationHookProc   = gdiStartupOuput.NotificationHook;
	// notificationUnhookProc = gdiStartupOuput.NotificationUnhook;
	
	//Basic event loop
    // notificationHookProc(&hookProcToken);
	MSG msg;
    while (GetMessage (&msg, NULL, 0, 0))
    {
        TranslateMessage (&msg);  //Reads keyboard messages
        DispatchMessage  (&msg);  //Sends msg to the appropriate window
    }
	// notificationUnhookProc(hookProcToken);
	// Gdiplus::GdiplusShutdown(gdiToken);
	
	std::cout << "End\n";
	return 0;
}











