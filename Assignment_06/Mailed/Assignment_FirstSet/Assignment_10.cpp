#include<Windows.h>
#include<math.h>
#include<gl/GL.h>

#define WIN_WIDTH 600
#define WIN_HEIGHT 600
#define PI 3.1415926535898

typedef struct
{
	GLfloat x;
	GLfloat y;
}CIRCLE;

CIRCLE  circle;

#pragma comment(lib,"opengl32.lib")
#pragma comment (lib,"glu32.lib")

HWND ghwnd = NULL;
HDC ghdc = NULL;
HGLRC ghrc = NULL;

DWORD dwStyle;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };
bool gbActiveWindow = false;
bool gbEscapeKeyIsPressed = false;
bool gbFullScreen = false;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	void initialize(void);
	void uninitialize(void);
	void display(void);
	LRESULT CALLBACK AcCallBack(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

	WNDCLASSEX ac;
	HWND hwnd;
	MSG msg;
	TCHAR szClassName[] = TEXT("First Assignment");
	bool bDone = false;

	ac.cbSize = sizeof(WNDCLASSEX);
	ac.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	ac.cbClsExtra = 0;
	ac.cbWndExtra = 0;
	ac.hInstance = hInstance;
	ac.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	ac.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	ac.hCursor = LoadCursor(NULL, IDC_ARROW);
	ac.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	ac.lpfnWndProc = AcCallBack;
	ac.lpszClassName = szClassName;
	ac.lpszMenuName = NULL;

	RegisterClassEx(&ac);

	hwnd = CreateWindowEx(
		WS_EX_APPWINDOW,
		szClassName,
		TEXT("Shree Ganesha"),
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

	ShowWindow(hwnd, SW_SHOWNORMAL);
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
				display();
				if (gbEscapeKeyIsPressed == true)
				{
					bDone = true;
				}
			}
		}
	}
	uninitialize();
	return ((int)msg.wParam);
}

void initialize(void)
{
	void resize(UINT width, UINT height);

	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex;

	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cRedBits = 8;
	pfd.cBlueBits = 8;
	pfd.cGreenBits = 8;
	pfd.cAlphaBits = 8;

	ghdc = GetDC(ghwnd);

	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);
	if (iPixelFormatIndex == 0)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	ghrc = wglCreateContext(ghdc);
	if (ghrc == NULL)
	{
		ReleaseDC(ghwnd, ghdc);
		ghrc = NULL;

	}

	if (wglMakeCurrent(ghdc, ghrc) == false)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//resize(WIN_WIDTH, WIN_HEIGHT);
}

void uninitialize(void)
{
	if (gbFullScreen == true)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
		ShowCursor(TRUE);
	}
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(ghrc);
	ghrc = NULL;
	ReleaseDC(ghwnd, ghdc);
	ghdc = NULL;
	DestroyWindow(ghwnd);
}

void resize(UINT width, UINT height)
{
	if (height == 0)
	{
		height = 1;
	}
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

void ToggleFullScreen(void)
{
	BOOL isWindowPlacement = FALSE;
	BOOL isMonitorInfo = FALSE;
	HMONITOR hMonitor = NULL;
	MONITORINFO mi;

	if (gbFullScreen == false)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
		if (dwStyle & WS_OVERLAPPEDWINDOW)
		{
			isWindowPlacement = GetWindowPlacement(ghwnd, &wpPrev);
			hMonitor = MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY);
			mi = { sizeof(MONITORINFO) };
			isMonitorInfo = GetMonitorInfo(hMonitor, &mi);

			if (isWindowPlacement == TRUE && isMonitorInfo == TRUE)
			{
				SetWindowLong(ghwnd, GWL_STYLE, dwStyle&~WS_OVERLAPPEDWINDOW);
				SetWindowPos(ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED);
			}
		}
		ShowCursor(FALSE);
	}
	else
	{
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
		ShowCursor(TRUE);
	}
}

/*
void CreateCircle(GLint k,GLint r,GLint h)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glBegin(GL_LINES);
	glColor3f(1.0f,1.0f,1.0f);
	for (GLint i=0;i<180;i++)
	{
		circle.x =(GLfloat) ((r*cos(i)) - h);
		circle.y = (GLfloat) ((r*sin(i)) + k);
		glVertex3f(circle.x+k,circle.y-k,0.0f);

		circle.x = (GLfloat) ((r*cos(i + 0.1)) - h);
		circle.y = (GLfloat) ((r*sin(i + 0.1)) + k);
		glVertex3f(circle.x+k,circle.y-h, 0.0f);
	}
	glEnd();
}
*/

void RenderCircle(GLfloat rad, GLfloat *arr, GLfloat *color, GLint circle_points)
{
	GLdouble angle = 0.0f;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 1.0f, 0.0f);
	for (int i = 0; i < circle_points; i++)
	{
		angle = (2 * PI * i) / circle_points;
		glVertex3f((GLfloat)((rad*cos(angle)) + arr[0]), (GLfloat)((rad*sin(angle)) + arr[1]), arr[2]);
	}
	glEnd();

	/*
	void RenderCircle(GLfloat rad, GLfloat *arr, GLfloat *color)
	{
	GLfloat angle = 0.0f;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glBegin(GL_POINTS);
	glColor3f(color[0], color[1], color[2]);
	for (angle = 0.0f; angle <= (2.0f*pi); angle = angle + 0.001f)
	{
	glVertex3f((GLfloat)((rad*cos(angle)) + arr[0]), (GLfloat)((rad*sin(angle)) + arr[1]), arr[2]);
	}
	glEnd();
	}
	*/
}


void RenderLine(GLfloat vertices[], GLfloat lineWidth, GLfloat color[])
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLineWidth(lineWidth);
	glBegin(GL_LINES);
	glColor3f(color[0], color[1], color[2]);
	glVertex3f(vertices[0], vertices[1], vertices[2]);
	glVertex3f(vertices[3], vertices[4], vertices[5]);
	glEnd();
}

void DrawGrid(void)
{
	void RenderLine(GLfloat vertices[], GLfloat lineWidth, GLfloat color[]);

	typedef struct
	{
		GLfloat varr[6];
	}vertices;

	typedef struct color
	{
		GLfloat carr[3];
	}color;

	vertices vert;
	color col;

	//Start of vertical lines

	vert = { 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f };
	col = { 0.0f, 1.0f, 0.0f };
	RenderLine(vert.varr, 3.0f, col.carr);

	vert = { 0.05f, -1.0f, 0.0f,0.05f, 1.0f, 0.0f };
	col = { 0.0f, 0.0f, 1.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 0.10f, -1.0f, 0.0f,0.10f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 0.15f, -1.0f, 0.0f,0.15f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 0.20f, -1.0f, 0.0f,0.20f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 0.25f, -1.0f, 0.0f,0.25f, 1.0f, 0.0f };
	col = { 0.0f, 0.0f, 1.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 0.30f, -1.0f, 0.0f,0.30f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 0.35f, -1.0f, 0.0f,0.35f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 0.40f, -1.0f, 0.0f,0.40f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 0.45f, -1.0f, 0.0f,0.45f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 0.50f, -1.0f, 0.0f,0.50f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 0.55f, -1.0f, 0.0f,0.55f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 0.60f, -1.0f, 0.0f,0.60f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 0.65f, -1.0f, 0.0f,0.65f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 0.70f, -1.0f, 0.0f,0.70f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 0.75f, -1.0f, 0.0f,0.75f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 0.80f, -1.0f, 0.0f,0.80f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 0.85f, -1.0f, 0.0f,0.85f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 0.90f, -1.0f, 0.0f,0.90f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 0.95f, -1.0f, 0.0f,0.95f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, -1.0f, 0.0f,1.0f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	//--------------------------------------------

	vert = { -0.05f, -1.0f, 0.0f,-0.05f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { -0.10f, -1.0f, 0.0f,-0.10f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { -0.15f, -1.0f, 0.0f,-0.15f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { -0.20f, -1.0f, 0.0f,-0.20f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { -0.25f, -1.0f, 0.0f,-0.25f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { -0.30f, -1.0f, 0.0f,-0.30f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { -0.35f, -1.0f, 0.0f,-0.35f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { -0.40f, -1.0f, 0.0f,-0.40f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { -0.45f, -1.0f, 0.0f,-0.45f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { -0.50f, -1.0f, 0.0f,-0.50f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { -0.55f, -1.0f, 0.0f,-0.55f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { -0.60f, -1.0f, 0.0f,-0.60f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { -0.65f, -1.0f, 0.0f,-0.65f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { -0.70f, -1.0f, 0.0f,-0.70f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { -0.75f, -1.0f, 0.0f,-0.75f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { -0.80f, -1.0f, 0.0f,-0.80f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { -0.85f, -1.0f, 0.0f,-0.85f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { -0.90f, -1.0f, 0.0f,-0.90f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { -0.95f, -1.0f, 0.0f,-0.95f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { -1.0f, -1.0f, 0.0f,-1.0f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	//End of vertical lines

	//Start of horizontal lines
	vert = { 1.0f, 0.0f, 0.0f,-1.0f, 0.0f, 0.0f };
	col = { 1.0f, 0.0f, 0.0f };
	RenderLine(vert.varr, 3.0f, col.carr);

	vert = { 1.0f, 0.05f, 0.0f,-1.0f, 0.05f, 0.0f };
	col = { 0.0f, 0.0f, 1.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, 0.1f, 0.0f,-1.0f, 0.1f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, 0.15f, 0.0f,-1.0f, 0.15f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, 0.20f, 0.0f,-1.0f, 0.20f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, 0.25f, 0.0f,-1.0f, 0.25f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, 0.30f, 0.0f,-1.0f, 0.30f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, 0.35f, 0.0f,-1.0f, 0.35f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, 0.40f, 0.0f,-1.0f, 0.40f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, 0.45f, 0.0f,-1.0f, 0.45f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, 0.50f, 0.0f,-1.0f, 0.50f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, 0.55f, 0.0f,-1.0f, 0.55f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, 0.60f, 0.0f,-1.0f, 0.60f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, 0.65f, 0.0f,-1.0f, 0.65f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, 0.70f, 0.0f,-1.0f, 0.70f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, 0.75f, 0.0f,-1.0f, 0.75f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, 0.80f, 0.0f,-1.0f, 0.80f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, 0.85f, 0.0f,-1.0f, 0.85f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, 0.90f, 0.0f,-1.0f, 0.90f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, 0.95f, 0.0f,-1.0f, 0.95f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, 1.0f, 0.0f,-1.0f, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	//Lines drawn below (0,0)

	vert = { 1.0f, -0.05f, 0.0f,-1.0f, -0.05f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, -0.10f, 0.0f,-1.0f, -0.10f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, -0.15f, 0.0f,-1.0f, -0.15f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, -0.20f, 0.0f,-1.0f, -0.20f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, -0.25f, 0.0f,-1.0f, -0.25f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, -0.30f, 0.0f,-1.0f, -0.30f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, -0.35f, 0.0f,-1.0f, -0.35f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, -0.40f, 0.0f,-1.0f, -0.40f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, -0.45f, 0.0f,-1.0f, -0.45f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, -0.50f, 0.0f,-1.0f, -0.50f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, -0.55f, 0.0f,-1.0f, -0.55f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, -0.60f, 0.0f,-1.0f, -0.60f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, -0.65f, 0.0f,-1.0f, -0.65f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, -0.70f, 0.0f,-1.0f, -0.70f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, -0.75f, 0.0f,-1.0f, -0.75f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, -0.80f, 0.0f,-1.0f, -0.80f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, -0.85f, 0.0f,-1.0f, -0.85f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, -0.90f, 0.0f,-1.0f, -0.90f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, -0.95f, 0.0f,-1.0f, -0.95f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	vert = { 1.0f, -1.0f, 0.0f,-1.0f, -1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	//End of horizontal lines
}

void display(void)
{
	void RenderCircle(GLfloat rad, GLfloat *arr, GLfloat *color, GLint circle_points);
	void DrawGrid(void);

	typedef struct
	{
		GLfloat carr[3];
	}circle;

	typedef struct
	{
		GLfloat carr[3];
	}color;

	circle cc;
	color cl;

	cc = { 0.0f,0.0f,0.0f };
	cl = { 1.0f,1.0f,0.0f };

	glClear(GL_COLOR_BUFFER_BIT);
	DrawGrid();
	//CreateCircle(0,0,1);
	RenderCircle(1.0f, cc.carr, cl.carr, 10000);

	//glFlush();
	SwapBuffers(ghdc);
}

LRESULT CALLBACK AcCallBack(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	void uninitialize(void);
	//void display(void);
	void resize(UINT width, UINT height);
	void ToggleFullScreen(void);

	switch (iMsg)
	{
	case WM_ACTIVATE:
		if (HIWORD(wParam)==0)
		{
			gbActiveWindow = true;
		}
		else
		{
			gbActiveWindow = false;
		}
		break;

	/*
	case WM_PAINT:
		display();
	*/

	/*
	case WM_ERASEBKGND:
		return  0;
	*/

	case WM_LBUTTONDOWN:
		break;

	case WM_SIZE:
		resize(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_CLOSE:
		uninitialize();
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			if (gbEscapeKeyIsPressed == false)
			{
				gbEscapeKeyIsPressed = true;
			}
			break;

		case 0x46:
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

		default:
			break;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}