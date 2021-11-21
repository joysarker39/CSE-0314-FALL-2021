#include <windows.h>

#include <cmath>

#define ROUND(a) ((int) (a + 0.5))

/* set window handle */

static HWND sHwnd;

static COLORREF redColor=RGB(255,0,0);

static COLORREF blueColor=RGB(0,0,255);

static COLORREF greenColor=RGB(0,255,0);

static COLORREF colorID = RGB(47,18,003);


void SetWindowHandle(HWND hwnd) {

    sHwnd=hwnd;

}

/* SetPixel */

void setPixel(int x,int y,COLORREF& color=colorID) {

    if(sHwnd==NULL) {

        MessageBox(NULL,"sHwnd was not initialized !","Error",MB_OK|MB_ICONERROR);

        exit(0);

    }

    HDC hdc=GetDC(sHwnd);

    SetPixel(hdc,x,y,color);

    ReleaseDC(sHwnd,hdc);

    return;

// NEVERREACH //

}


void drawLineDDA(int xa, int ya, int xb, int yb) {

    int dx = xb - xa, dy = yb - ya, steps, k;

    float xIncrement, yIncrement, x = xa, y = ya;

    if(abs(dx) > abs(dy)) steps = abs(dx);

    else steps = abs(dy);

    xIncrement = dx / (float) steps;

    yIncrement = dy / (float) steps;

    setPixel(ROUND(x), ROUND(y));

    for(int k = 0; k < steps; k++) {

        x += xIncrement;

        y += yIncrement;

        setPixel(x, y);

    }

}

/* Window Procedure WndProc */

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam) {

    switch(message) {

    case WM_PAINT:

        SetWindowHandle(hwnd);

        /// Base
        drawLineDDA(123,164,53,174);
        drawLineDDA(53,174,268,304);
        drawLineDDA(268,304,530,229);
        drawLineDDA(530,229,531,239);
        drawLineDDA(531,239,268,316);
        drawLineDDA(268,316,53,184);
        drawLineDDA(53,184,54,174);
        drawLineDDA(268,304,268,316); /// mid line
        drawLineDDA(531,229,452,201); /// last Line

        ///front Door side
        drawLineDDA(270,205,270,332);
        drawLineDDA(270,332,452,286);
        drawLineDDA(452,286,452,178);
        drawLineDDA(346,312,346,223);
        drawLineDDA(346,223,398,212);
        drawLineDDA(398,212,396,299);
        drawLineDDA(396,299,394,299);
        drawLineDDA(394,299,395,216);
        drawLineDDA(395,216,351,226);
        drawLineDDA(351,226,350,310); /// door line

        /// window line
        drawLineDDA(124,118,123,210);
        drawLineDDA(123,210,270,288);
        drawLineDDA(234,239,235,183);
        drawLineDDA(235,183,150,148);
        drawLineDDA(150,148,150,197);
        drawLineDDA(150,197,234,240);
        drawLineDDA(229,232,229,185);
        drawLineDDA(229,185,152,153);
        drawLineDDA(152,153,152,195);
        drawLineDDA(152,195,229,232);
        drawLineDDA(192,214,192,169);
        drawLineDDA(187,167,186,210);
        drawLineDDA(156,189,176,170);
        drawLineDDA(160,191,176,175);
        drawLineDDA(200,208,220,189);
        drawLineDDA(206,211,222,194);

        /// upper base
        drawLineDDA(453,187,464,186);
        drawLineDDA(464,186,470,181);
        drawLineDDA(470,181,368,101);
        drawLineDDA(368,101,255,209);
        drawLineDDA(255,209,111,152);
        drawLineDDA(111,152,116,156);
        drawLineDDA(116,156,259,215);
        drawLineDDA(259,215,367,111);
        drawLineDDA(367,111,464,186);
        drawLineDDA(367,102,367,111);
        drawLineDDA(254,209,258,214);
        drawLineDDA(111,151,172,105);
        drawLineDDA(207,78,210,74);
        drawLineDDA(210,74,367,101);

        /// Upper fire base
        drawLineDDA(172,82,188,74);
        drawLineDDA(188,74,209,79);
        drawLineDDA(209,79,194,89);
        drawLineDDA(194,89,172,82);
        drawLineDDA(172,82,172,130);
        drawLineDDA(172,130,194,138);
        drawLineDDA(194,138,208,125);
        drawLineDDA(208,125,209,80);
        drawLineDDA(194,89,194,138);
        drawLineDDA(178,82,189,76);
        drawLineDDA(189,76,203,79);
        drawLineDDA(203,79,194,86);
        drawLineDDA(194,86,178,81);
        drawLineDDA(172,116,153,131);
        drawLineDDA(153,131,195,147);
        drawLineDDA(195,147,227,118);
        drawLineDDA(227,118,208,114);

        /// horizontal Line
        drawLineDDA(10,172,123,172);
        drawLineDDA(458,172,574,172);

        break;

    case WM_CLOSE: // FAIL THROUGH to call DefWindowProc

        break;

    case WM_DESTROY:

        PostQuitMessage(0);

        return 0;

    default:

        break; // FAIL to call DefWindowProc //

    }

    return DefWindowProc(hwnd,message,wParam,lParam);

}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int iCmdShow) {

    static TCHAR szAppName[] = TEXT("Straight Line");

    WNDCLASS wndclass;

    wndclass.style         = CS_HREDRAW|CS_VREDRAW ;

    wndclass.lpfnWndProc   = WndProc ;

    wndclass.cbClsExtra    = 0 ;

    wndclass.cbWndExtra    = 0 ;

    wndclass.hInstance     = hInstance ;

    wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;

    wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;

    wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;

    wndclass.lpszMenuName  = NULL ;

    wndclass.lpszClassName = szAppName ;

// Register the window //

    if(!RegisterClass(&wndclass)) {

        MessageBox(NULL,"Registering the class failled","Error",MB_OK|MB_ICONERROR);

        exit(0);

    }

// CreateWindow //

    HWND hwnd=CreateWindow(szAppName,"DDA - Programming Techniques",

                           WS_OVERLAPPEDWINDOW,

                           CW_USEDEFAULT,

                           CW_USEDEFAULT,

                           CW_USEDEFAULT,

                           CW_USEDEFAULT,

                           NULL,

                           NULL,

                           hInstance,

                           NULL);

    if(!hwnd) {

        MessageBox(NULL,"Window Creation Failed!","Error",MB_OK);

        exit(0);

    }

// ShowWindow and UpdateWindow //

    ShowWindow(hwnd,iCmdShow);

    UpdateWindow(hwnd);

// Message Loop //

    MSG msg;

    while(GetMessage(&msg,NULL,0,0)) {

        TranslateMessage(&msg);

        DispatchMessage(&msg);

    }

    /* return no error to the operating system */

    return 0;

}
