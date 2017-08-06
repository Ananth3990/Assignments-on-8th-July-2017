#include<Windows.h>
#include<math.h>
#include<gl/GL.h>
#include<gl/GLU.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

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

GLfloat anglePyramid = 0.0f;

#define NUMBER_OF_ROWS 4
#define NUMBER_OF_COLOUMNS 4

GLfloat identity[16];
GLfloat translation[16];
GLfloat translation1[16];
GLfloat scaling[16];
static const GLfloat pi = (GLfloat)(22.0f / 7.0f);
GLfloat rotationX[16];
GLfloat rotationY[16];
GLfloat rotationZ[16];

LRESULT CALLBACK AcCallBack(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

void update(void)
{
	anglePyramid = anglePyramid + 0.1f;

	if (anglePyramid >= 360.0f)
	{
		anglePyramid = 0.0f;
	}
}

GLint WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, GLint iCmdShow)
{
	void initialize(void);
	void uninitialize(void);
	void display(void);
	void update(void);
	void resize(GLint, GLint);

	WNDCLASSEX ac;
	HWND hwnd;
	MSG msg;
	TCHAR szClassName[] = TEXT("Rotating Pyramid");
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
	return ((GLint)msg.wParam);
}

void initialize(void)
{
	void resize(GLint width, GLint height);

	PIXELFORMATDESCRIPTOR pfd;
	GLint iPixelFormatIndex;

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
	pfd.cDepthBits = 32;

	ghdc = GetDC(ghwnd);

	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);
	if (iPixelFormatIndex == 0)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == false)
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

	if (wglMakeCurrent(ghdc, ghrc) == FALSE)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
		wglDeleteContext(ghrc);
		ghrc = NULL;
	}

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//----------------------
	identity[0] = 1.0f;
	identity[1] = 0.0f;
	identity[2] = 0.0f;
	identity[3] = 0.0f;

	identity[4] = 0.0f;
	identity[5] = 1.0f;
	identity[6] = 0.0f;
	identity[7] = 0.0f;

	identity[8] = 0.0f;
	identity[9] = 0.0f;
	identity[10] = 1.0f;
	identity[11] = 0.0f;

	identity[12] = 0.0f;
	identity[13] = 0.0f;
	identity[14] = 0.0f;
	identity[15] = 1.0f;
	//----------------------

	//----------------------
	translation[0] = 1.0f;
	translation[1] = 0.0f;
	translation[2] = 0.0f;
	translation[3] = 0.0f;

	translation[4] = 0.0f;
	translation[5] = 1.0f;
	translation[6] = 0.0f;
	translation[7] = 0.0f;

	translation[8] = 0.0f;
	translation[9] = 0.0f;
	translation[10] = 1.0f;
	translation[11] = 0.0f;

	translation[12] = -1.5f; //Tx
	translation[13] = 0.0f; //Ty
	translation[14] = -6.0f; //Tz
	translation[15] = 1.0f;
	//----------------------

	//----------------------
	translation1[0] = 1.0f;
	translation1[1] = 0.0f;
	translation1[2] = 0.0f;
	translation1[3] = 0.0f;

	translation1[4] = 0.0f;
	translation1[5] = 1.0f;
	translation1[6] = 0.0f;
	translation1[7] = 0.0f;

	translation1[8] = 0.0f;
	translation1[9] = 0.0f;
	translation1[10] = 1.0f;
	translation1[11] = 0.0f;

	translation1[12] = 1.5f; //Tx
	translation1[13] = 0.0f; //Ty
	translation1[14] = -6.0f; //Tz
	translation1[15] = 1.0f;
	//----------------------

	//----------------------
	scaling[0] = 0.75f; //Sx
	scaling[1] = 0.0f;
	scaling[2] = 0.0f;
	scaling[3] = 0.0f;

	scaling[4] = 0.0f;
	scaling[5] = 0.75f; //Sy
	scaling[6] = 0.0f;
	scaling[7] = 0.0f;

	scaling[8] = 0.0f;
	scaling[9] = 0.0f;
	scaling[10] = 0.75f; //Sz
	scaling[11] = 0.0f;

	scaling[12] = 0.0f;
	scaling[13] = 0.0f;
	scaling[14] = 0.0f;
	scaling[15] = 1.0f;
	//----------------------

	resize(WIN_WIDTH, WIN_HEIGHT);
}

void uninitialize(void)
{
	if (gbFullScreen == true)
	{
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
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

void resize(GLint width, GLint height)
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
	MONITORINFO mi;

	if (gbFullScreen == false)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
		if (dwStyle&WS_OVERLAPPEDWINDOW)
		{
			mi = { sizeof(MONITORINFO) };
			if (GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
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
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
		ShowCursor(TRUE);
	}
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(identity);
	glMultMatrixf(translation);
	glMultMatrixf(scaling);

	//-------------------------------------
	rotationX[0] = 1.0f;
	rotationX[1] = 0.0f;
	rotationX[2] = 0.0f;
	rotationX[3] = 0.0f;

	rotationX[4] = 0.0f;
	rotationX[5] = cosf(anglePyramid*(pi / 180.0f));
	rotationX[6] = sinf(anglePyramid*(pi / 180.0f));
	rotationX[7] = 0.0f;

	rotationX[8] = 0.0f;
	rotationX[9] = -sinf(anglePyramid*(pi / 180.0f));
	rotationX[10] = cosf(anglePyramid*(pi / 180.0f));
	rotationX[11] = 0.0f;

	rotationX[12] = 0.0f;
	rotationX[13] = 0.0f;
	rotationX[14] = 0.0f;
	rotationX[15] = 1.0f;
	//-------------------------------------

	rotationY[0] = cosf(anglePyramid*(pi / 180.0f));
	rotationY[1] = 0.0f;
	rotationY[2] = -sinf(anglePyramid*(pi / 180.0f));
	rotationY[3] = 0.0f;

	rotationY[4] = 0.0f;
	rotationY[5] = 1.0f;
	rotationY[6] = 0.0f;
	rotationY[7] = 0.0f;

	rotationY[8] = sinf(anglePyramid*(pi / 180.0f));
	rotationY[9] = 0.0f;
	rotationY[10] = cosf(anglePyramid*(pi / 180.0f));
	rotationY[11] = 0.0f;

	rotationY[12] = 0.0f;
	rotationY[13] = 0.0f;
	rotationY[14] = 0.0f;
	rotationY[15] = 1.0f;
	//-------------------------------------
	rotationZ[0] = cosf(anglePyramid*(pi / 180.0f));
	rotationZ[1] = sinf(anglePyramid*(pi / 180.0f));
	rotationZ[2] = 0.0f;
	rotationZ[3] = 0.0f;

	rotationZ[4] = -sinf(anglePyramid*(pi / 180.0f));
	rotationZ[5] = cosf(anglePyramid*(pi / 180.0f));
	rotationZ[6] = 0.0f;
	rotationZ[7] = 0.0f;

	rotationZ[8] = 0.0f;
	rotationZ[9] = 0.0f;
	rotationZ[10] = 1.0f;
	rotationZ[11] = 0.0f;

	rotationZ[12] = 0.0f;
	rotationZ[13] = 0.0f;
	rotationZ[14] = 0.0f;
	rotationZ[15] = 1.0f;
	//-------------------------------------

	glMultMatrixf(rotationX);
	glMultMatrixf(rotationY);
	glMultMatrixf(rotationZ);

	glBegin(GL_QUADS);

	//Bottom face
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);

	//Back face
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	//Right Face
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	//Left Face
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);

	//Front Face
	glColor3f(0.75f, 0.75f, 0.75f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	//Top Face
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glEnd();


	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(identity);
	glMultMatrixf(translation1);

	//-------------------------------------
	rotationX[0] = 1.0f;
	rotationX[1] = 0.0f;
	rotationX[2] = 0.0f;
	rotationX[3] = 0.0f;

	rotationX[4] = 0.0f;
	rotationX[5] = cosf(anglePyramid*(pi / 180.0f));
	rotationX[6] = sinf(anglePyramid*(pi / 180.0f));
	rotationX[7] = 0.0f;

	rotationX[8] = 0.0f;
	rotationX[9] = -sinf(anglePyramid*(pi / 180.0f));
	rotationX[10] = cosf(anglePyramid*(pi / 180.0f));
	rotationX[11] = 0.0f;

	rotationX[12] = 0.0f;
	rotationX[13] = 0.0f;
	rotationX[14] = 0.0f;
	rotationX[15] = 1.0f;
	//-------------------------------------

	glMultMatrixf(rotationX);

	glBegin(GL_TRIANGLES);
	//Front face
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f); //apex

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f); //left corner of front face

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f); //right corner of front face

								   //Right Face
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f); //apex

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f); //left corner of Right face

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f); //right corner of Right face

									//Back face
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f); //apex

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f); //left corner of Back face

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f); //right corner of Back face

									 //Left Face
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f); //apex

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f); //left corner of Back face

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f); //right corner of Back face									
	glEnd();

	glBegin(GL_QUADS);
	//Bottom
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);

	glEnd();

	SwapBuffers(ghdc);
}

LRESULT CALLBACK AcCallBack(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	void uninitialize(void);
	void resize(GLint width, GLint height);
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