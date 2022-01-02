#include <windows.h>
#include <cmath>
#define ROUND(a) ((int) (a + 0.5))

#define LEFT_EDGE 0x1
#define RIGHT_EDGE 0x2
#define BOTTOM_EDGE 0x4
#define TOP_EDGE 0x8

#define INSIDE(a) (!a)
#define REJECT(a,b) (a&b)
#define ACCEPT(a,b) (!(a|b))
/* set window handle */

static HWND sHwnd;

static COLORREF redColor=RGB(255,0,0);
static COLORREF blueColor=RGB(0,0,255);
static COLORREF greenColor=RGB(0,255,0);

typedef struct Point
{
    int x;
    int y;
}pt;

pt winMin = {10, 10};
pt winMax = {519,312};
pt p1;
pt p2;

void SetWindowHandle(HWND hwnd){
    sHwnd=hwnd;
}

/* SetPixel */
void setPixel(int x,int y,COLORREF& color=redColor){
    if(sHwnd==NULL){
        MessageBox(NULL,"sHwnd was not initialized !","Error",MB_OK|MB_ICONERROR);
        exit(0);
    }
    HDC hdc=GetDC(sHwnd);
    SetPixel(hdc,x,y,color);
    ReleaseDC(sHwnd,hdc);
    return;

}

void drawLineDDA(int xa, int ya, int xb, int yb){

int dx = xb - xa, dy = yb - ya, steps, k;

float xIncrement, yIncrement, x = xa, y = ya;

if(abs(dx) > abs(dy)) steps = abs(dx);

else steps = abs(dy);

xIncrement = dx / (float) steps;

yIncrement = dy / (float) steps;

setPixel(ROUND(x), ROUND(y));

for(int k = 0; k < steps; k++){

x += xIncrement;

y += yIncrement;

setPixel(x, y);

}

}

void drawBoundary(pt winMin, pt winMax){
    int x, y;
    x = winMin.x;
    for(y = winMin.y; y < winMax.y; y++){
        setPixel(x,y, blueColor);
    }
    y = winMin.y;
    for(x = winMin.x; x < winMax.x; x++){
        setPixel(x,y, blueColor);
    }
    x = winMax.x;
    for(y = winMin.y; y < winMax.y; y++){
        setPixel(x,y, blueColor);
    }
    y = winMax.y;
    for(x = winMin.x; x < winMax.x; x++){
        setPixel(x,y, blueColor);
    }

}

unsigned char encode(pt Point, pt winMin, pt winMax){
    unsigned char code = 0x00;
    if(Point.x < winMin.x)
        code = code | LEFT_EDGE;
    if(Point.x > winMax.x)
        code = code | RIGHT_EDGE;
    if(Point.y < winMin.y)
        code = code | BOTTOM_EDGE;
    if(Point.y > winMax.y)
        code = code | TOP_EDGE;
    return (code);
}

void swapPts(pt *p1, pt *p2){
    pt temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void swapCodes (unsigned char *c1, unsigned char *c2){
    unsigned char temp;
    temp = *c1;
    *c1 = *c2;
    *c2 = temp;
}

void clipLine (pt winMin, pt winMax, pt p1, pt p2){
    unsigned char code1, code2;
    int done = FALSE, draw = FALSE;
    float m;

    while(!done){
        code1 = encode (p1, winMin, winMax);
        code2 = encode (p2, winMin, winMax);
        if(ACCEPT(code1, code2)){
            done = TRUE;
            draw = TRUE;
        }
        else
            if(REJECT (code1, code2))
                done = TRUE;
            else{
                if (INSIDE(code1)){
                    swapPts(&p1, &p2);
                    swapCodes (&code1, &code2);
                }

                if(p2.x != p1.x)
                    m = (p2.y - p1.y) / (p2.x - p1.x);
                if(code1 & LEFT_EDGE){
                    p1.y += (winMin.x - p1.x) * m;
                    p1.x = winMin.x;
                }else
                    if(code1 & RIGHT_EDGE){
                        p1.y += (winMax.x - p1.x) * m;
                        p1.x = winMax.x;
                    }else
                        if(code1 & BOTTOM_EDGE){
                            if(p2.x != p1.x)
                                p1.x += (winMin.y - p1.y) / m;
                            p1.y = winMin.y;
                        }else
                            if(code1 & TOP_EDGE){
                                if(p2.x != p1.x)
                                    p1.x += (winMax.y - p1.y)/m;
                                p1.y = winMax.y;
                            }

            }
    }
    if(draw){
        drawLineDDA(ROUND(p1.x), ROUND(p1.y), ROUND(p2.x), ROUND(p2.y));
    }
}

/* Window Procedure WndProc */
LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){

    switch(message){
        case WM_PAINT:
            SetWindowHandle(hwnd);
            drawBoundary(winMin, winMax);

            clipLine(winMin, winMax, {78,134},{289,30} );
clipLine(winMin, winMax, {289,30},{376,72} );
clipLine(winMin, winMax, {376,72},{367,85} );
clipLine(winMin, winMax, {367,85},{291,45} );
clipLine(winMin, winMax, {291,45},{107,136} );
clipLine(winMin, winMax, {107,136},{79,135} );

clipLine(winMin, winMax, {320,135},{415,32} );
clipLine(winMin, winMax, {415,32},{507,135} );
clipLine(winMin, winMax, {507,135},{484,135} );
clipLine(winMin, winMax, {484,135},{414,57} );
clipLine(winMin, winMax, {414,57},{347,134} );
clipLine(winMin, winMax, {347,134},{323,135} );

clipLine(winMin, winMax, {331,137},{330,201} );
clipLine(winMin, winMax, {330,201},{499,201} );
clipLine(winMin, winMax, {499,201},{499,136} );

clipLine(winMin, winMax, {131,125},{131,200} );
clipLine(winMin, winMax, {131,200},{301,202} );
clipLine(winMin, winMax, {130,199},{91,246} );

clipLine(winMin, winMax, {85,248},{260,247} );
clipLine(winMin, winMax, {260,247},{314,191} );
clipLine(winMin, winMax, {314,191},{369,248} );
clipLine(winMin, winMax, {369,248},{542,248} );
clipLine(winMin, winMax, {542,248},{542,257} );
clipLine(winMin, winMax, {542,257},{360,256} );
clipLine(winMin, winMax, {360,256},{314,211} );
clipLine(winMin, winMax, {314,211},{269,256} );
clipLine(winMin, winMax, {269,256},{87,256} );
clipLine(winMin, winMax, {87,256},{87,249} );
clipLine(winMin, winMax, {496,201},{535,246} );

clipLine(winMin, winMax, {100,258},{100,354} );
clipLine(winMin, winMax, {100,354},{527,354} );
clipLine(winMin, winMax, {527,354},{528,258} );

clipLine(winMin, winMax, {291,319},{292,257} );
clipLine(winMin, winMax, {292,257},{336,258} );
clipLine(winMin, winMax, {336,258},{337,320} );

clipLine(winMin, winMax, {268,259},{269,342} );
clipLine(winMin, winMax, {269,342},{256,342} );
clipLine(winMin, winMax, {256,342},{257,258} );

clipLine(winMin, winMax, {359,259},{359,341} );
clipLine(winMin, winMax, {359,341},{371,341} );
clipLine(winMin, winMax, {371,341},{370,259} );
clipLine(winMin, winMax, {359,259},{359,341} );
clipLine(winMin, winMax, {359,341},{371,341} );
clipLine(winMin, winMax, {371,341},{370,259} );

clipLine(winMin, winMax, {246,352},{245,344} );
clipLine(winMin, winMax, {245,344},{280,344} );
clipLine(winMin, winMax, {280,344},{280,351} );
clipLine(winMin, winMax, {346,352},{346,344} );
clipLine(winMin, winMax, {346,344},{381,344} );
clipLine(winMin, winMax, {381,344},{381,352} );
clipLine(winMin, winMax, {282,344},{348,346} );
clipLine(winMin, winMax, {269,332},{358,333} );
clipLine(winMin, winMax, {358,321},{269,321} );



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

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int iCmdShow){
    static TCHAR szAppName[] = TEXT("Line Clipping");
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
    if(!RegisterClass(&wndclass)){
        MessageBox(NULL,"Registering the class failled","Error",MB_OK|MB_ICONERROR);
        exit(0);
    }

    // CreateWindow //
    HWND hwnd=CreateWindow(szAppName,"Cohen Sutherland Algorithm - Programming Techniques",
                WS_OVERLAPPEDWINDOW,
                 CW_USEDEFAULT,
                 CW_USEDEFAULT,
                 CW_USEDEFAULT,
                 CW_USEDEFAULT,
                 NULL,
                 NULL,
                 hInstance,
                 NULL);
    if(!hwnd){
        MessageBox(NULL,"Window Creation Failed!","Error",MB_OK);
        exit(0);
    }
    // ShowWindow and UpdateWindow //
    ShowWindow(hwnd,iCmdShow);
    UpdateWindow(hwnd);

    // Message Loop //
    MSG msg;
    while(GetMessage(&msg,NULL,0,0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    /* return no error to the operating system */
    return 0;
}
