#include<Windows.h>
#include<gl/GL.h>
#include<gl/GLU.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#define IDT_TIMER1 WM_USER+11

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

//callback function
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Handle to be passed th Wndproc
HWND ghwnd = NULL;

//Device context
HDC ghdc = NULL;

//Rendering context
HGLRC ghrc = NULL;

//For fullscreen
DWORD dwStyle;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };

//WM_ACTIVATE
bool gbActiveWindow = false;

//WM_KEYDOWN
bool gbEscapeKeyIsPressed = false;

//WM_KEYDOWN
bool gbFullScreen = false;

bool gbSpaceKeyIsPresed = false;

GLfloat x = -3.0f;
GLfloat y = 3.0f;

GLfloat x1 = 3.0f;
GLfloat y1 = -3.0f;

GLfloat pqr = -8.5f;

GLfloat left_end = -5.0f;
GLfloat right_end = -5.0f;

BOOL start_rendering = 1;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	void initialize(void);
	void uninitialize(void);
	void display(void);
	void update(void);

	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;

	//Name of class to be passed in WNDCLASSEX
	TCHAR szClassName[] = TEXT("Ananth Chandrasekharan's Window");

	//for Message loop
	bool bDone = false;

	//Initializing structure on wndclass
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szClassName;
	wndclass.lpszMenuName = NULL;

	RegisterClassEx(&wndclass);

	hwnd = CreateWindowEx(
		WS_EX_APPWINDOW,
		szClassName,
		TEXT("I"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
		0,
		0,
		WIN_WIDTH,
		WIN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ghwnd = hwnd;

	initialize();

	ShowWindow(hwnd, iCmdShow);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	while (bDone == false)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				bDone = true;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (gbActiveWindow == true)
			{
				if (gbEscapeKeyIsPressed == true)
				{
					bDone = true;
				}

				if (start_rendering == 1)
				{
					update();
					display();
					start_rendering = 0;
					SetTimer(hwnd, IDT_TIMER1, 50, (TIMERPROC)NULL);
				}
			}
		}
	}

	uninitialize();
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	void initialize(void);
	void resize(int width, int height);
	void uninitialize(void);
	void ToggleFullScreen(void);

	switch (iMsg)
	{
	case WM_ACTIVATE:
		if (HIWORD(wParam) == 0)
		{
			gbActiveWindow = true;
		}
		else
		{
			gbActiveWindow = false;
		}
		break;

	case WM_ERASEBKGND:
		return 0;
		break;

	case WM_SIZE:
		resize(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_LBUTTONDOWN:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			gbEscapeKeyIsPressed = true;
			break;

		case VK_SPACE:
			gbSpaceKeyIsPresed = true;
			break;

		case 'F':
		case 'f':
			if (gbFullScreen == false)
			{
				ToggleFullScreen();
				gbFullScreen = true;
			}
			else
			{
				ToggleFullScreen();
				gbFullScreen = false;
			}
			break;
		}
		break;

	case WM_TIMER:
		switch (wParam)
		{
		case IDT_TIMER1:
			start_rendering = 1;
			break;
		}
		break;

	default:
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

void initialize(void)
{
	void resize(int width, int height);

	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex;

	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 8;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;
	pfd.cDepthBits = 32;

	ghdc = GetDC(ghwnd);

	//Checking for nearest matching pfd in table
	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);
	if (iPixelFormatIndex == 0)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	//Setting the nearest matching pfd . This function may fail
	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	ghrc = wglCreateContext(ghdc);
	if (ghrc == NULL)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	//Make the rendering context current context
	if (wglMakeCurrent(ghdc, ghrc) == FALSE)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);

	resize(WIN_WIDTH, WIN_HEIGHT);
}

void resize(int width, int height)
{
	if (height == 0)
	{
		height = 1;
	}
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (width <= height)
	{
		gluPerspective(45.0f, (GLfloat)height / (GLfloat)width, 0.1f, 100.0f);
	}
	else
	{
		gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
	}
}

void uninitialize(void)
{
	if (gbFullScreen == true)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_FRAMECHANGED);

		ShowCursor(TRUE);
	}

	wglMakeCurrent(NULL, NULL);

	wglDeleteContext(ghrc);
	ghrc = NULL;

	ReleaseDC(ghwnd, ghdc);
	ghdc = NULL;

	DestroyWindow(ghwnd);
	ghwnd = NULL;
}

void ToggleFullScreen(void)
{
	MONITORINFO mi;

	if (gbFullScreen == false)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
		if (dwStyle & WS_OVERLAPPEDWINDOW)
		{
			mi = { sizeof(MONITORINFO) };

			if (GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
			{
				SetWindowLong(ghwnd, GWL_STYLE, dwStyle&~WS_OVERLAPPEDWINDOW);
				SetWindowPos(ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED);
			}
			ShowCursor(FALSE);
		}
	}
	else
	{
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_FRAMECHANGED);

		ShowCursor(TRUE);
	}
}

void display()
{
	void display_I(void);
	void display_N(void);
	void display_D(void);
	void display_I1(void);
	void display_A(void);
	void DrawStripes(void);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	display_I();
	display_N();
	display_D();
	display_I1();
	display_A();
	DrawStripes();

	SwapBuffers(ghdc);
}

void update(void)
{
	if (x < -1.9f)
	{
		x = x + 0.01f;
	}

	if (y >= 0.0f && x >= -1.9f)
	{
		y = y - 0.01f;
	}

	if (y<=0.0f && pqr <= 1.0f)
	{
		pqr = pqr + 0.1f;
		//pqr = 1.0f;
	}

	if (y1 <= 0.0f && pqr >= 1.0f)
	{
		y1 = y1 + 0.01f;
	}

	if (x1 >= 1.1f && y1 >= 0.0f)
	{
		x1 = x1 - 0.01f;
	}

	if (x1 <= 1.1f)
	{
		if (left_end < 1.03f)
		{
			left_end = left_end + 0.02f;
		}

		if (right_end < 1.64f)
		{
			right_end = right_end + 0.05f;
		}
	}
}

void display_I(void) //Corrected
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(x, 0.0f, -3.0f);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.75f, 0.0f);
	glVertex2f(0.010f, 1.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.010f, -1.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(-0.010f, -1.0f);

	glColor3f(1.0f, 0.75f, 0.0f);
	glVertex2f(-0.010f, 1.0f);
	glEnd();
}

void display_N(void) //Corrected
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(-1.1f, y, -3.0f);

	//Right portion of N
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.75f, 0.0f);
	glVertex2f(0.3f, 1.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.3f, -1.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.280f, -1.0f);

	glColor3f(1.0f, 0.75f, 0.0f);
	glVertex2f(0.280f, 1.0f);
	glEnd();

	//Left portion of N
	glBegin(GL_QUADS);

	glColor3f(1.0f, 0.75f, 0.0f);
	glVertex2f(-0.3f, 1.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(-0.3f, -1.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(-0.280f, -1.0f);

	glColor3f(1.0f, 0.75f, 0.0f);
	glVertex2f(-0.280f, 1.0f);
	glEnd();

	//Middle Portion of N
	glBegin(GL_QUADS);

	glColor3f(1.0f, 0.75f, 0.0f);
	glVertex2f(-0.280f, 1.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.3f, -1.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.280f, -1.0f);

	glColor3f(1.0f, 0.75f, 0.0f);
	glVertex2f(-0.3f, 1.0f);
	glEnd();
}

void display_D(void) //Corrected
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(-0.3f, 0.0f, -3.0f);

	//Left portion of D
	glBegin(GL_QUADS);

	glColor4f(1.0f, 0.75f, 0.0f,pqr);
	glVertex2f(-0.2f, 1.0f);

	glColor4f(0.0f, 1.0f, 0.0f,pqr);
	glVertex2f(-0.2f, -1.0f);

	glColor4f(0.0f, 1.0f, 0.0f,pqr);
	glVertex2f(-0.180f, -1.0f);

	glColor4f(1.0f, 0.75f, 0.0f,pqr);
	glVertex2f(-0.180f, 1.0f);
	glEnd();

	//Right portion of D
	glBegin(GL_QUADS);

	glColor4f(1.0f, 0.75f, 0.0f,pqr);
	glVertex2f(0.3f, 1.0f);

	glColor4f(0.0f, 1.0f, 0.0f,pqr);
	glVertex2f(0.3f, -1.0f);

	glColor4f(0.0f, 1.0f, 0.0f,pqr);
	glVertex2f(0.280f, -1.0f);

	glColor4f(1.0f, 0.75f, 0.0f,pqr);
	glVertex2f(0.280f, 1.0f);
	glEnd();

	//Upper portion of D
	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.75f, 0.0f,pqr);
	glVertex2f(0.3f, 1.0f);
	glVertex2f(0.3f, 0.98f);
	glVertex2f(-0.3f, 0.98f);
	glVertex2f(-0.3f, 1.0f);
	glEnd();

	//Lower portion of D
	glBegin(GL_QUADS);
	glColor4f(0.0f, 1.0f, 0.0f,pqr);
	glVertex2f(0.3f, -0.98f);
	glVertex2f(0.3f, -1.0f);
	glVertex2f(-0.3f, -1.0f);
	glVertex2f(-0.3f, -0.98f);
	glEnd();
}

void display_I1(void) //Corrected
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.5f, y1, -3.0f);

	//Middle portion of I
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.75f, 0.0f);
	glVertex2f(0.010f, 1.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.010f, -1.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(-0.010f, -1.0f);

	glColor3f(1.0f, 0.75f, 0.0f);
	glVertex2f(-0.010f, 1.0f);
	glEnd();
}

void display_A(void) //Corrected
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//glTranslatef(1.1f, 0.0f, -3.0f);
	glTranslatef(x1, 0.0f, -3.0f);

	//Left portion of A
	glBegin(GL_QUADS);

	glColor3f(1.0f, 0.75f, 0.0f);
	glVertex2f(0.210f, 1.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(-0.280f, -1.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(-0.3f, -1.0f);

	glColor3f(1.0f, 0.75f, 0.0f);
	glVertex2f(0.190f, 1.0f);
	glEnd();

	//Right portion of A
	glBegin(GL_QUADS);

	glColor3f(1.0f, 0.75f, 0.0f);
	glVertex2f(0.210f, 1.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.9f, -1.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.88f, -1.0f);

	glColor3f(1.0f, 0.75f, 0.0f);
	glVertex2f(0.190f, 1.0f);
	glEnd();
}

void DrawStripes(void)
{
	//Drawing saffron color
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glTranslatef(1.34f, 0.0f, -3.0f);
	glTranslatef(0.0f, 0.0f, -3.0f);
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.75f, 0.0f);
	glVertex2f(right_end, 0.0f);
	glVertex2f(left_end, 0.0f);
	glEnd();

	//Drawing White color
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glTranslatef(1.34f, 0.0f, -3.0f);
	glTranslatef(0.0f, -0.01f, -3.0f);
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(right_end, 0.0f);
	glVertex2f(left_end, 0.0f);
	glEnd();

	//Drawing Green color
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glTranslatef(1.34f, 0.0f, -3.0f);
	glTranslatef(0.0f, -0.02f, -3.0f);
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(right_end, 0.0f);
	glVertex2f(left_end, 0.0f);
	glEnd();
}