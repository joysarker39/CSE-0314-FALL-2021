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

        /// horizontal Line
        drawLineDDA(0,355,294,355);
        drawLineDDA(1133,355,1422,355);

        /// Base
        drawLineDDA(294,493,120,517);
        drawLineDDA(120,517,658,843); //2nd window up
        drawLineDDA(658,843,1315,659);

        drawLineDDA(1315,659,1316,682);
        drawLineDDA(1316,682,656,874);

        drawLineDDA(656,874,120,542);
        drawLineDDA(120,542,120,517);

        drawLineDDA(658,843,657,874);
        drawLineDDA(1315,659,1119,586);

        ///front Door side
        drawLineDDA(663,436,663,754);
        drawLineDDA(663,754,1118,639);
        drawLineDDA(1118,639,1119,367);

        drawLineDDA(980,672,981,454); // door right
        drawLineDDA(981,454,854,482);
        drawLineDDA(854,482,853,706);
        drawLineDDA(853,705,863,702);
        drawLineDDA(863,702,863,489);
        drawLineDDA(863,489,974,466);
        drawLineDDA(974,466,973,675);

        drawLineDDA(980,673,853,705);

        /// window line
        drawLineDDA(295,324,294,554);
        drawLineDDA(294,554,662,753); // side

        drawLineDDA(574,629,574,488);
        drawLineDDA(574,488,364,399);
        drawLineDDA(364,399,364,524);
        drawLineDDA(364,524,574,629); //outer window

        drawLineDDA(561,610,560,492);
        drawLineDDA(560,492,370,411);
        drawLineDDA(370,411,370,516);
        drawLineDDA(370,516,561,610); // inner window

        drawLineDDA(469,565,468,453);
        drawLineDDA(457,448,457,557);

        drawLineDDA(378,503,430,450); // window line
        drawLineDDA(388,508,427,468);
        drawLineDDA(487,551,537,501);
        drawLineDDA(504,557,543,517);

        /// upper base
        drawLineDDA(265,303,416,186);
        //drawLineDDA(265,303,516,110);
        drawLineDDA(502,120,516,110);
        drawLineDDA(516,110,909,175); // topmost 909, 175
        drawLineDDA(909,175,625,447);
        drawLineDDA(625,447,266,305);
        drawLineDDA(265,303,281,320);
        drawLineDDA(281,320,634,463);
        drawLineDDA(634,463,909,203);
        drawLineDDA(909,203,1148,390);
        drawLineDDA(1148,390,1161,377);
        drawLineDDA(1161,377,909,175);
        drawLineDDA(909,175,909,203);
        drawLineDDA(625,447,634,463); //mid line
        drawLineDDA(1119,387,1148,390);

        /// Upper fire base
        drawLineDDA(416,215,371,253);
        drawLineDDA(371,253,474,296);
        drawLineDDA(474,296,560,217);
        drawLineDDA(560,217,510,207); /// lower

        drawLineDDA(418,132,473,151);
        drawLineDDA(473,151,511,123);
        drawLineDDA(511,123,460,110);
        drawLineDDA(460,110,416,131); ///outer

        drawLineDDA(416,131,417,249);
        drawLineDDA(417,249,472,269);
        drawLineDDA(472,269,510,237);
        drawLineDDA(510,237,511,123);
        drawLineDDA(472,269,473,151);

        drawLineDDA(472,140,494,123);
        drawLineDDA(494,123,461,115);
        drawLineDDA(461,115,434,129);
        drawLineDDA(434,129,471,140);



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
