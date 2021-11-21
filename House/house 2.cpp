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
        drawLineDDA(296,493,120,517);
        drawLineDDA(120,517,658,843);
        drawLineDDA(658,843,1315,659);
        drawLineDDA(1315,659,1316,682);
        drawLineDDA(1316,682,656,874);
        drawLineDDA(656,874,118,542);
        drawLineDDA(118,542,121,517);
        drawLineDDA(657,871,656,842);
        drawLineDDA(1313,656,1119,586);

        ///front Door side
        drawLineDDA(663,438,663,754);
        drawLineDDA(663,754,1118,639);
        drawLineDDA(1118,639,1119,369);
        drawLineDDA(980,671,981,454);
        drawLineDDA(981,454,854,482);
        drawLineDDA(854,482,853,705);
        drawLineDDA(853,705,863,702);
        drawLineDDA(863,702,863,489);
        drawLineDDA(863,489,974,466);
        drawLineDDA(974,466,972,675);

        /// window line
        drawLineDDA(296,324,294,554);
        drawLineDDA(294,554,662,753);
        drawLineDDA(574,629,574,488);
        drawLineDDA(574,488,364,399);
        drawLineDDA(364,399,361,524);
        drawLineDDA(361,524,574,629);
        drawLineDDA(561,610,560,492);
        drawLineDDA(560,492,370,411);
        drawLineDDA(370,411,367,516);
        drawLineDDA(367,516,562,610);
        drawLineDDA(469,565,468,453);
        drawLineDDA(457,448,453,557);

        drawLineDDA(377,503,428,450);
        drawLineDDA(389,508,427,468);
        drawLineDDA(487,551,537,501);
        drawLineDDA(504,557,543,517);

        /// upper base
        drawLineDDA(265,303,418,186);
        drawLineDDA(507,120,516,110);
        drawLineDDA(515,111,907,178);
        drawLineDDA(907,178,625,447);
        drawLineDDA(625,447,266,305);
        drawLineDDA(266,305,281,320);
        drawLineDDA(281,320,634,463);
        drawLineDDA(634,463,906,203);
        drawLineDDA(906,203,1148,390);
        drawLineDDA(1148,390,1161,377);
        drawLineDDA(1161,377,907,176);
        drawLineDDA(907,176,906,201);
        drawLineDDA(636,464,626,445);
        drawLineDDA(1119,391,1148,392);

        /// Upper fire base
        drawLineDDA(419,215,371,253);
        drawLineDDA(371,253,474,296);
        drawLineDDA(474,296,560,217);
        drawLineDDA(560,217,510,207);

        drawLineDDA(418,132,473,151);
        drawLineDDA(473,151,511,123);
        drawLineDDA(511,123,460,110);
        drawLineDDA(460,110,416,131);
        drawLineDDA(416,131,417,249);
        drawLineDDA(417,249,472,269);
        drawLineDDA(472,269,510,237);
        drawLineDDA(510,237,510,124);
        drawLineDDA(473,269,472,147);

        drawLineDDA(472,140,494,123);
        drawLineDDA(494,123,461,115);
        drawLineDDA(461,115,434,129);
        drawLineDDA(434,129,471,140);

        /// horizontal Line
        drawLineDDA(11,355,296,354);
        drawLineDDA(1133,354,1422,355);

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
