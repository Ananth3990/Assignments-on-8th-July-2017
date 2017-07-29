#include<Windows.h>
#include<math.h>
#include<gl/GL.h>
#include<gl/GLU.h>
#include<stdio.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define PI 3.1415926535898f

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

typedef struct
{
	GLfloat arr[2][3];
}TwoArray;

typedef struct
{
	GLfloat arr[3][3];
}ThreeArray;

typedef struct
{
	GLfloat side_ab;
	GLfloat side_bc;
	GLfloat side_ac;  //This is base
}Triangle_sides;


GLfloat angleTri = 0.0f;
GLfloat angleCircle = 0.0f;

void update(void)
{
	angleTri = angleTri + 0.05f;
	if (angleTri>=360.0f)
	{
		angleTri = 0.0f;
	}

	angleCircle = angleCircle + 0.05f;
	if (angleCircle>=360.0f)
	{
		angleCircle = 0.0f;
	}
}

void Calculate_length(GLfloat arr[][3], GLfloat *result)
{
	GLfloat  x1, y1, z1;
	GLfloat  x2, y2, z2;

	x1 = arr[0][0];
	y1 = arr[0][1];
	z1 = arr[0][2];

	x2 = arr[1][0];
	y2 = arr[1][1];
	z2 = arr[1][2];

	GLfloat temp1 = (x2 - x1);
	GLfloat temp2 = (y2 - y1);

	*result = (temp1*temp1) + (temp2*temp2);
	*result = (GLfloat)sqrtf(result[0]);
}

void Calculate_Height(Triangle_sides *ts, GLfloat *height)
{
	GLfloat temp1 = (*ts).side_ab;
	GLfloat temp2 = (*ts).side_ac;
	GLfloat temp3 = (*ts).side_bc;

	*height = (temp3*temp3) - ((0.5f*temp2)*(0.5f*temp2));
	*height = sqrtf(*height);
}

void Calculate_Area(Triangle_sides *ts, float *area)
{
	GLfloat s;
	s = (ts->side_ab) + (ts->side_ac) + (ts->side_bc);
	s = s / 2;
	*area = sqrtf((s * (s - ts->side_ab) * (s - ts->side_ac) * (s - (ts->side_bc))));
}


void Calculate_Permeter(Triangle_sides *ta, GLfloat *perimeter)
{
	*perimeter = ((*ta).side_ab) + ((*ta).side_ac) + ((*ta).side_bc);
}

void Calculate_CenterOfIncircle(GLfloat vert[][3], Triangle_sides *ta, GLfloat *perimeter, GLfloat center[3])
{
	float temp;
	temp = (GLfloat)(vert[0][0] * (*ta).side_bc) + (vert[1][0] * (*ta).side_ac) + (vert[2][0] * (*ta).side_ab);
	temp = temp / (*perimeter);
	center[0] = temp;

	temp = (GLfloat)(vert[0][1] * (*ta).side_bc) + (vert[1][1] * (*ta).side_ac) + (vert[2][1] * (*ta).side_ab);
	temp = temp / (*perimeter);
	center[1] = temp;

	temp = (GLfloat)(vert[0][2] * (*ta).side_bc) + (vert[1][2] * (*ta).side_ac) + (vert[2][2] * (*ta).side_ab);
	temp = temp / (*perimeter);
	center[2] = temp;
}

void Calculate_RadiusOfIncircle(GLfloat *area, GLfloat *perimeter, GLfloat *rad)
{
	GLfloat temp = (2 * (*area));
	temp = temp / (*perimeter);
	*rad = temp;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	void initialize(void);
	void uninitialize(void);
	void display(void);
	void update(void);
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
				update();
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
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
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
	resize(WIN_WIDTH, WIN_HEIGHT);
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
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
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

void RenderUnfilledTriangle(GLfloat vert[][3],GLfloat *color)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f,0.0f,-6.0f);
	glRotatef(angleTri,0.0f,1.0f,0.0f);
	glBegin(GL_LINE_LOOP);
	glColor3f(color[0], color[1], color[2]);
	glVertex3f(vert[0][0], vert[0][1], vert[0][2]);
	glVertex3f(vert[1][0], vert[1][1], vert[1][2]);
	glVertex3f(vert[2][0], vert[2][1], vert[2][2]);
	glEnd();
}

void RenderLine(GLfloat vertices[], GLfloat lineWidth, GLfloat color[])
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -6.0f);
	glLineWidth(lineWidth);
	glBegin(GL_LINES);
	glColor3f(color[0], color[1], color[2]);
	glVertex3f(vertices[0], vertices[1], vertices[2]);
	glVertex3f(vertices[3], vertices[4], vertices[5]);
	glEnd();
}

void CalculateRadiusAndCenterOfIncircle(GLfloat *center, GLfloat *rad_of_incircle)
{
	//-----------------------------------
	//Calculate_length(ta.arr,&side_ab);
	//Calculate_length(ta.arr, &side_ac);
	//Calculate_length(ta.arr, &side_bc);
	TwoArray ta;
	float side_ab;
	float side_ac;
	float side_bc;

	//Calculate_Height(&ts,&height);
	Triangle_sides ts;
	float height;

	//Calculate_Area(&ap,&area);
	float area;

	//Calculate_Permeter(&ts,&perimeter);	
	float perimeter;

	//Calculate_CenterOfIncircle(float vert[3], Triangle_sides *ta, *perimeter, float center[2]);
	ThreeArray thra;
	//float center[3];

	//void Calculate_RadiusOfIncircle(float *area,float *perimeter,float *rad);
	//float rad_of_incircle;

	//Calculate_length(ta.arr,&side_ab);
	ta = { { { -1.0f,-1.0f,0.0f },{ 0.0f,1.0f,0.0f } } };
	Calculate_length(ta.arr, &side_ab);

	//Calculate_length(ta.arr, &side_ac);
	ta = { { { -1.0f,-1.0f,0.0f },{ 1.0f,-1.0f,0.0f } } };
	Calculate_length(ta.arr, &side_ac);

	//Calculate_length(ta.arr, &side_bc);
	ta = { { { 0.0f,1.0f,0.0f },{ 1.0f,-1.0f,0.0f } } };
	Calculate_length(ta.arr, &side_bc);

	//Calculate_Height(&ts,&height);
	ts.side_ab = side_ab;
	ts.side_ac = side_ac;
	ts.side_bc = side_bc;
	Calculate_Height(&ts, &height);

	//Calculate_Area(&ap,&area);
	ts.side_ab = side_ab;
	ts.side_ac = side_ac;
	ts.side_bc = side_bc;
	Calculate_Area(&ts, &area);

	//Calculate_Permeter(&ts,&perimeter);
	Calculate_Permeter(&ts, &perimeter);

	//Calculate_CenterOfIncircle(float vert[3], Triangle_sides *ta, *perimeter, float center[2]);
	ts.side_ab = side_ab;
	ts.side_ac = side_ac;
	ts.side_bc = side_bc;
	thra = { { { -1.0f,-1.0f,0.0f },{ 0.0f,1.0f,0.0f },{ 1.0f,-1.0f,0.0f } } };
	Calculate_CenterOfIncircle(thra.arr, &ts, &perimeter, center);

	//Calculate_RadiusOfIncircle(float *area, float *perimeter, float *rad);
	Calculate_RadiusOfIncircle(&area, &perimeter, rad_of_incircle);

	//---------------------------------------
}

void RenderCircle(GLfloat rad, GLfloat *arr, GLfloat *color, GLint circle_points)
{
	GLdouble angle = 0.0f;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -6.0f);
	glRotatef(angleCircle,0.0f,1.0f,0.0f);
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 1.0f, 0.0f);
	for (int i = 0; i < circle_points; i++)
	{
		angle = (2 * PI * i) / circle_points;
		glVertex3f((GLfloat)((rad*cos(angle)) + arr[0]), (GLfloat)((rad*sin(angle)) + arr[1]), arr[2]);
	}
	glEnd();
}

void display(void)
{
	void RenderUnfilledTriangle(GLfloat vert[][3], GLfloat *color);
	void RenderLine(GLfloat vertices[], GLfloat lineWidth, GLfloat color[]);
	void RenderCircle(GLfloat rad, GLfloat *arr, GLfloat *color, GLint circle_points);
	void CalculateRadiusAndCenterOfIncircle(GLfloat *center, GLfloat *rad_of_incircle);
	GLfloat center[3];
	GLfloat rad_of_incircle;

	typedef struct
	{
		GLfloat triangle_vert[3][3];
	}TRIANGLES;

	typedef struct
	{
		GLfloat color[3];
	}COLOR;

	typedef struct
	{
		GLfloat varr[6];
	}line;

	typedef struct
	{
		GLfloat carr[3];
	}circle;

	TRIANGLES triangles;
	COLOR color;
	line vert;
	circle cc;

	glClear(GL_COLOR_BUFFER_BIT);

	triangles = { { {-1.0f, -1.0f, 0.0f} ,{1.0f, -1.0f, 0.0f} ,{0.0f, 1.0f, 0.0f} } };
	color = { 1.0f, 1.0f, 1.0f };
	RenderUnfilledTriangle(triangles.triangle_vert,color.color);

	/*
	vert = { -1.0f,0.0f,0.0f, 1.0f, 0.0f, 0.0f };
	color = { 0.0f,1.0f,0.0f };
	RenderLine(vert.varr, 1.0f, color.color);

	vert = { 0.0f,1.0f,0.0f, 0.0f, -1.0f, 0.0f };
	color = { 0.0f,1.0f,1.0f };
	RenderLine(vert.varr, 1.0f, color.color);

	vert = { 0.5f,1.0f,0.0f, 0.5f, -1.0f, 0.0f };
	color = { 0.0f,1.0f,1.0f };
	RenderLine(vert.varr, 1.0f, color.color);

	vert = { -0.5f,1.0f,0.0f, -0.5f, -1.0f, 0.0f };
	color = { 0.0f,1.0f,1.0f };
	RenderLine(vert.varr, 1.0f, color.color);
	*/

	//Vertices are (-1,-1),(0,1) and (1,-1)

	//---------------------------------------

	CalculateRadiusAndCenterOfIncircle(center,&rad_of_incircle);

	cc = { center[0],center[1],center[2]};
	color = { 1.0f,1.0f,0.0f };
	RenderCircle(rad_of_incircle, cc.carr, color.color, 10000);

	vert = { 0.0f,1.0f,0.0f, 0.0f, -1.0f, 0.0f };
	color = { 0.0f,1.0f,0.0f };
	RenderLine(vert.varr, 1.0f, color.color);

	//glFlush();
	SwapBuffers(ghdc);
}

LRESULT CALLBACK AcCallBack(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	void uninitialize(void);
	void resize(UINT width, UINT height);
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
		return  0;

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