// windowAPI_Gal'sPanic.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "windowAPI_Gal'sPanic.h"
#include "list.h"
#include "header.h"
#include "Circle.h"
#include "Rectangle.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
RECT rectView;

// >> : Window
POINT WindowSize = { 1920, 1080 };
HDC hdc;
// <<

// >> : DoubleBuffering
void DoubleBuffering(HDC hdc);
// <<

// >> : Bitmap
HBITMAP hImage, hOldBitmap, hsilhouette;
int image_width;
int image_height;
// <<

// >> : Point
void DrawMap(HDC hdc);
List* lefttop = new List;
List* leftbottom = new List;
List* rightbottom = new List;
List* righttop = new List;
int Listnum;
POINT* p = new POINT[MAX];
// <<

// >> : Map
void UpdateMap();
// << :

// >> : Player
List* playerPos;
void DrawPlayer(HDC, List*);
void GetKey();
void GetnewKey();
bool SameLine(int, int);
// <<

// >> : move
List* moving = nullptr;
// <<

// >> : Brush
HBRUSH redbrush = CreateSolidBrush(RGB(255, 0, 0));
HBRUSH greenbrush = CreateSolidBrush(RGB(0, 255, 0));
HBRUSH bluebrush = CreateSolidBrush(RGB(0, 0, 255));
HBRUSH blackbrush = CreateSolidBrush(RGB(0, 0, 0));
HBRUSH whitebrush = CreateSolidBrush(RGB(255, 255, 255));
// <<

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
					 _In_opt_ HINSTANCE hPrevInstance,
					 _In_ LPWSTR    lpCmdLine,
					 _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WINDOWAPIGALSPANIC, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 애플리케이션 초기화를 수행합니다:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWAPIGALSPANIC));

	MSG msg;

	// 기본 메시지 루프입니다:
	while (GetMessage(& msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style          = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc    = WndProc;
	wcex.cbClsExtra     = 0;
	wcex.cbWndExtra     = 0;
	wcex.hInstance      = hInstance;
	wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWAPIGALSPANIC));
	wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWAPIGALSPANIC);
	wcex.lpszClassName  = szWindowClass;
	wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   hImage = (HBITMAP)LoadImage(NULL, TEXT("Thanos.bmp"), IMAGE_BITMAP, 0, 0,
	   LR_LOADFROMFILE | LR_CREATEDIBSECTION);
   if (hImage != NULL)
   {
	   BITMAP bitmap;
	   if (GetObject(hImage, sizeof(BITMAP), &bitmap))
	   {
		   image_width = bitmap.bmWidth;
		   image_height = bitmap.bmHeight;
	   }
	   //DeleteObject(bitmap);
   }

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	  CW_USEDEFAULT, 0, WINDOW_WIDTH, WINDOW_HEIGHT, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
	  return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		GetClientRect(hWnd, &rectView);
		SetTimer(hWnd, 1, 1, NULL);

		// 시작 테두리
		{
			lefttop->p = { 0,0 };
			List* prevList = lefttop;
			for (int i = PIXEL; i < image_height; i += PIXEL)
			{
				List* newList = new List;
				newList->p = { 0,i };
				prevList->next = newList;
				newList->pre = prevList;

				prevList = prevList->next;
			}

			leftbottom->p = { 0,image_height };
			prevList->next = leftbottom;
			leftbottom->pre = prevList;
			prevList = prevList->next;

			for (int i = PIXEL; i < image_width; i += PIXEL)
			{
				List* newList = new List;
				newList->p = { i,image_height };
				prevList->next = newList;
				newList->pre = prevList;

				prevList = prevList->next;
			}

			rightbottom->p = { image_width,image_height };
			prevList->next = rightbottom;
			rightbottom->pre = prevList;
			prevList = prevList->next;

			for (int i = image_height - PIXEL; i > 0; i -= PIXEL)
			{
				List* newList = new List;
				newList->p = { image_width,i };
				prevList->next = newList;
				newList->pre = prevList;

				prevList = prevList->next;
			}

			righttop->p = { image_width,0 };
			prevList->next = righttop;
			righttop->pre = prevList;
			prevList = prevList->next;

			for (int i = image_width - PIXEL; i > 0; i -= PIXEL)
			{
				List* newList = new List;
				newList->p = { i,0 };
				prevList->next = newList;
				newList->pre = prevList;

				prevList = prevList->next;
			}

			prevList->next = lefttop;
			lefttop->pre = prevList;
		}

		// 플레이어 초기화
		playerPos = lefttop;

		Listnum = ((image_width / PIXEL) + (image_height / PIXEL)) * 2;

		break;
	}
	case WM_TIMER:
		InvalidateRgn(hWnd, NULL, FALSE);
		break;
	case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			// 메뉴 선택을 구문 분석합니다:
			switch (wmId)
			{
			case IDM_ABOUT:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				break;
			case IDM_EXIT:
				DestroyWindow(hWnd);
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		break;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			hdc = BeginPaint(hWnd, &ps);

			DoubleBuffering(hdc);

			EndPaint(hWnd, &ps);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	bool pushSpace;
	
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		pushSpace = true;
	}
	else
	{
		pushSpace = false;
	}

	if (pushSpace)
	{
		GetnewKey();
	}
	else
	{
		if (moving == nullptr)
		{
			GetKey();
		}
		else
		{

		}
	}

	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void DoubleBuffering(HDC hdc)
{
	HDC memdc;
	static HBITMAP  hBit, oldBit;

	memdc = CreateCompatibleDC(hdc);
	hBit = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);

	oldBit = (HBITMAP)SelectObject(memdc, hBit);
	HBRUSH hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
	RECT rect = { 0, 0, rectView.right, rectView.bottom };
	FillRect(memdc, &rect, hBrush);

	SelectObject(memdc, hImage);

	DrawMap(memdc);

	DrawPlayer(memdc, playerPos);

	BitBlt(hdc, (rectView.right - image_width) / 2, (rectView.bottom - image_height) / 2, rectView.right, rectView.bottom, memdc, 0, 0, SRCCOPY);

	SelectObject(memdc, oldBit);
	DeleteDC(memdc);
}

void DrawMap(HDC hdc)
{
	List* current = lefttop;
	
	for (int i = 0; i < Listnum; i++)
	{
		p[i] = current->p;
		current = current->next;
	}
	(HBRUSH)SelectObject(hdc, redbrush);
	Polygon(hdc, p, Listnum);
}

void DrawPlayer(HDC hdc, List* player)
{
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;

	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	oldPen = (HPEN)SelectObject(hdc, hPen);

	hBrush = CreateSolidBrush(RGB(255, 0, 0));
	oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	Ellipse(hdc, player->p.x - PLAYER_RADIUS, player->p.y - PLAYER_RADIUS, player->p.x + PLAYER_RADIUS, player->p.y + PLAYER_RADIUS);

	SelectObject(hdc, oldPen);
	DeleteObject(hPen);
	SelectObject(hdc, oldBrush);
	DeleteObject(hBrush);
}

void GetKey()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		if (playerPos->p.x > playerPos->pre->p.x && SameLine(playerPos->p.y, playerPos->pre->p.y))
		{
			playerPos = playerPos->pre;
			return;
		}
		else if (playerPos->p.x > playerPos->next->p.x && SameLine(playerPos->p.y, playerPos->next->p.y))
		{
			playerPos = playerPos->next;
			return;
		}
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		if (playerPos->p.x < playerPos->pre->p.x && SameLine(playerPos->p.y, playerPos->pre->p.y))
		{
			playerPos = playerPos->pre;
			return;
		}
		else if (playerPos->p.x < playerPos->next->p.x && SameLine(playerPos->p.y, playerPos->next->p.y))
		{
			playerPos = playerPos->next;
			return;
		}
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		if (SameLine(playerPos->p.x, playerPos->pre->p.x) && playerPos->p.y > playerPos->pre->p.y)
		{
			playerPos = playerPos->pre;
			return;
		}
		else if (SameLine(playerPos->p.x, playerPos->next->p.x) && playerPos->p.y > playerPos->next->p.y)
		{
			playerPos = playerPos->next;
			return;
		}
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		if (SameLine(playerPos->p.x, playerPos->pre->p.x) && playerPos->p.y < playerPos->pre->p.y)
		{
			playerPos = playerPos->pre;
			return;
		}
		else if (SameLine(playerPos->p.x, playerPos->next->p.x) && playerPos->p.y < playerPos->next->p.y)
		{
			playerPos = playerPos->next;
			return;
		}
	}
}

void GetnewKey()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		COLORREF a = GetPixel(hdc, playerPos->p.x, playerPos->p.y);
		if (playerPos->p.x > playerPos->pre->p.x && SameLine(playerPos->p.y, playerPos->pre->p.y))
		{
			playerPos = playerPos->pre;
			return;
		}
		else if (playerPos->p.x > playerPos->next->p.x && SameLine(playerPos->p.y, playerPos->next->p.y))
		{
			playerPos = playerPos->next;
			return;
		}
		else if(GetPixel(hdc, playerPos->p.x - PIXEL, playerPos->p.y) == (0,0,0))
		{
			return;
		}
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		if (playerPos->p.x < playerPos->pre->p.x && SameLine(playerPos->p.y, playerPos->pre->p.y))
		{
			playerPos = playerPos->pre;
			return;
		}
		else if (playerPos->p.x < playerPos->next->p.x && SameLine(playerPos->p.y, playerPos->next->p.y))
		{
			playerPos = playerPos->next;
			return;
		}
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		if (SameLine(playerPos->p.x, playerPos->pre->p.x) && playerPos->p.y > playerPos->pre->p.y)
		{
			playerPos = playerPos->pre;
			return;
		}
		else if (SameLine(playerPos->p.x, playerPos->next->p.x) && playerPos->p.y > playerPos->next->p.y)
		{
			playerPos = playerPos->next;
			return;
		}
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		if (SameLine(playerPos->p.x, playerPos->pre->p.x) && playerPos->p.y < playerPos->pre->p.y)
		{
			playerPos = playerPos->pre;
			return;
		}
		else if (SameLine(playerPos->p.x, playerPos->next->p.x) && playerPos->p.y < playerPos->next->p.y)
		{
			playerPos = playerPos->next;
			return;
		}
	}
}

bool SameLine(int x1, int x2)
{
	return (x1 == x2) ? true : false;
}