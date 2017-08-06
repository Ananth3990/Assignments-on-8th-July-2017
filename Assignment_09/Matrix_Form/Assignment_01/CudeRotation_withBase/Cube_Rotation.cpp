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

static const GLfloat pi = 3.14285714286f;

GLfloat *translationMatrix = NULL;
GLfloat *identityMatrix = NULL;

LRESULT CALLBACK AcCallBack(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

void AllocateMatrix(float **arr, int row, int col)
{
	*arr = (float*)malloc(row*col * sizeof(float));
}

void LoadIdentityMatrix(float **arr, int row, int col)
{
	AllocateMatrix(&(*arr), NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);
	for (int i = 0; i<(row*col); i++)
	{
		if (i % 5 == 0)
		{
			*((*arr) + i) = 1.0f;
		}
		else
		{
			*((*arr) + i) = 0.0f;
		}
	}
}

void TransposeMatrix(float **arr, int row, int col)
{
	int i, j, z;
	float *dup = NULL;
	int index1, index2;
	AllocateMatrix(&dup, row, col);
	for (i = 0; i<row; i++)
	{
		for (j = 0; j<col; j++)
		{
			//index in original matrix
			index1 = i*col + j;

			//index in transposed matrix
			index2 = j*row + i;

			*(dup + index2) = *((*arr) + index1);
		}
	}

	for (z = 0; z < row*col; z++)
	{
		*((*arr) + z) = *(dup + z);
	}
}

/* //Done by Atharva
void TranslationMatrix(float x, float y, float z, float **mat)
{
void AllocateMatrix(float **arr, int row, int col);
void LoadIdentityMatrix(float **arr, int row, int col);
void TransposeMatrix(float **arr, int row, int col);

AllocateMatrix(&(*mat), NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);
LoadIdentityMatrix(&(*mat), NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);
*((*mat) + 12) = x;
*((*mat) + 13) = y;
*((*mat) + 14) = z;
//TransposeMatrix(&(*mat), NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);
}
*/

void TranslationMatrix(float x, float y, float z, float **mat)
{
	void AllocateMatrix(float **arr, int row, int col);
	void LoadIdentityMatrix(float **arr, int row, int col);
	void TransposeMatrix(float **arr, int row, int col);

	AllocateMatrix(&(*mat), NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);
	LoadIdentityMatrix(&(*mat), NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);
	*((*mat) + 12) = x;
	*((*mat) + 13) = y;
	*((*mat) + 14) = z;
	//TransposeMatrix(&(*mat), NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS); //Transpose is done by glLoadMatrix()
}

void ScalingMatrix(float x, float y, float z, float **mat)
{
	void AllocateMatrix(float **arr, int row, int col);
	void LoadIdentityMatrix(float **arr, int row, int col);
	void TransposeMatrix(float **arr, int row, int col);

	AllocateMatrix(&(*mat), NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);
	LoadIdentityMatrix(&(*mat), NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);

	for (int i = 0; i<16; i++)
	{
		if (i % 5 == 0)
		{
			if (i == 15)
			{
				*((*mat) + i) = 1.0f;
			}
			else
			{
				if (i == 0)
				{
					*((*mat) + i) = x;
				}

				if (i == 5)
				{
					*((*mat) + i) = y;
				}

				if (i == 10)
				{
					*((*mat) + i) = z;
				}
			}
		}
		else
		{
			*((*mat) + i) = 0.0f;
		}
	}
}

void MultiplyMatrixbyFactor(float **mat, float factor, int row, int col)
{
	for (int i = 0; i<(row*col); i++)
	{
		*((*mat) + i) = *((*mat) + i) * factor;
	}
}

void RotationMatrix_x(float angle_in_degree, float factor, float **mat)
{
	void AllocateMatrix(float **arr, int row, int col);
	void LoadIdentityMatrix(float **arr, int row, int col);
	void TransposeMatrix(float **arr, int row, int col);
	void MultiplyMatrixbyFactor(float **mat, float factor, int row, int col);

	float angle_in_radian = 0.0f;
	angle_in_radian = angle_in_degree*(pi / 180.0f);

	AllocateMatrix(&(*mat), NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);
	LoadIdentityMatrix(&(*mat), NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);

	for (int i = 0; i<NUMBER_OF_COLOUMNS*NUMBER_OF_ROWS; i++)
	{
		if (i == 5 || i == 10)
		{
			*((*mat) + i) = cosf(angle_in_radian);
		}

		if (i == 6)
		{
			*((*mat) + i) = sinf(angle_in_radian);
		}

		if (i == 9)
		{
			*((*mat) + i) = -sinf(angle_in_radian);
		}
	}
	MultiplyMatrixbyFactor(&(*mat), factor, NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);
}

void RotationMatrix_y(float angle_in_degree, float factor, float **mat)
{
	void AllocateMatrix(float **arr, int row, int col);
	void LoadIdentityMatrix(float **arr, int row, int col);
	void TransposeMatrix(float **arr, int row, int col);
	void MultiplyMatrixbyFactor(float **mat, float factor, int row, int col);

	float angle_in_radian = 0.0f;
	angle_in_radian = angle_in_degree*(pi / 180.0f);

	AllocateMatrix(&(*mat), NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);
	LoadIdentityMatrix(&(*mat), NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);

	for (int i = 0; i<NUMBER_OF_COLOUMNS*NUMBER_OF_ROWS; i++)
	{
		if (i == 0 || i == 10)
		{
			*((*mat) + i) = cosf(angle_in_radian);
		}

		if (i == 8)
		{
			*((*mat) + i) = sinf(angle_in_radian);
		}

		if (i == 2)
		{
			*((*mat) + i) = -sinf(angle_in_radian);
		}
	}
	MultiplyMatrixbyFactor(&(*mat), factor, NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);
}

void RotationMatrix_z(float angle_in_degree, float factor, float **mat)
{
	void AllocateMatrix(float **arr, int row, int col);
	void LoadIdentityMatrix(float **arr, int row, int col);
	void TransposeMatrix(float **arr, int row, int col);
	void MultiplyMatrixbyFactor(float **mat, float factor, int row, int col);

	float angle_in_radian = 0.0f;
	angle_in_radian = angle_in_degree*(pi / 180.0f);

	AllocateMatrix(&(*mat), NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);
	LoadIdentityMatrix(&(*mat), NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);

	for (int i = 0; i<NUMBER_OF_COLOUMNS*NUMBER_OF_ROWS; i++)
	{
		if (i == 0 || i == 5)
		{
			*((*mat) + i) = cosf(angle_in_radian);
		}

		if (i == 1)
		{
			*((*mat) + i) = sinf(angle_in_radian);
		}

		if (i == 4)
		{
			*((*mat) + i) = -sinf(angle_in_radian);
		}
	}
	MultiplyMatrixbyFactor(&(*mat), factor, NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);
}

GLfloat* GetTranslationMatrix()
{
	return (translationMatrix);
}

void SetTranslationMatrix(GLfloat **mat)
{
	translationMatrix = *mat;
}

GLfloat* GetIdentityMatrix()
{
	return (identityMatrix);
}

void SetIdentityMatrix(GLfloat **mat)
{
	identityMatrix = *mat;
}

void update(void)
{
	anglePyramid = anglePyramid + 0.1f;

	if (anglePyramid >= 360.0f)
	{
		anglePyramid = 0.0f;
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	void initialize(void);
	void uninitialize(void);
	void display(void);
	void update(void);
	void resize(int, int);

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
	return ((int)msg.wParam);
}

void initialize(void)
{
	void resize(GLint width, GLint height);
	void SetTranslationMatrix(GLfloat **mat);
	void SetIdentityMatrix(GLfloat **mat);

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

	//glLoadIdentity();
	GLfloat *identitymatrix = NULL;
	AllocateMatrix(&identitymatrix, NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);
	LoadIdentityMatrix(&identitymatrix, NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);
	SetIdentityMatrix(&identitymatrix);

	//glTranslatef(0.0f, 0.0f, -6.0f);
	GLfloat *translationMatrix = NULL;
	AllocateMatrix(&translationMatrix, NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);
	TranslationMatrix(0.0f, 0.0f, -6.0f, &translationMatrix);
	SetTranslationMatrix(&translationMatrix);

	
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
	void RotationMatrix_z(GLfloat angle_in_degree, GLfloat factor,GLfloat **mat);
	void RotationMatrix_z(GLfloat angle_in_degree,GLfloat factor, GLfloat **mat);
	void RotationMatrix_z(GLfloat angle_in_degree, GLfloat factor,GLfloat **mat);
	void ScalingMatrix(GLfloat x, GLfloat y, GLfloat z, GLfloat **mat);
	void TranslationMatrix(GLfloat x, GLfloat y, GLfloat z, GLfloat **mat);
	GLfloat* GetTranslationMatrix();
	GLfloat* GetIdentityMatrix();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(GetIdentityMatrix());
	glMultMatrixf(GetTranslationMatrix());

	
	//glRotatef(anglePyramid, 1.0f, 1.0f, 1.0f);
	GLfloat *rotationmatrix_x = NULL;
	AllocateMatrix(&rotationmatrix_x, NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);
	RotationMatrix_x(anglePyramid,1.0f, &rotationmatrix_x);

	GLfloat *rotationmatrix_y = NULL;
	AllocateMatrix(&rotationmatrix_y, NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);
	RotationMatrix_y(anglePyramid,1.0f, &rotationmatrix_y);

	GLfloat *rotationmatrix_z = NULL;
	AllocateMatrix(&rotationmatrix_z, NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);
	RotationMatrix_z(anglePyramid,1.0f, &rotationmatrix_z);

	glMultMatrixf(rotationmatrix_x);
	glMultMatrixf(rotationmatrix_y);
	glMultMatrixf(rotationmatrix_z);

	/*
	//glRotatef(anglePyramid, 0.0f, 1.0f, 0.0f);
	GLfloat *rotationmatrix_y = NULL;
	AllocateMatrix(&rotationmatrix_y, NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);
	RotationMatrix_y(anglePyramid, &rotationmatrix_y);
	glMultMatrixf(rotationmatrix_y);
	*/
	
	/*
	//glRotatef(anglePyramid, 1.0f, 0.0f, 0.0f);
	GLfloat *rotationmatrix_x = NULL;
	AllocateMatrix(&rotationmatrix_x, NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);
	RotationMatrix_x(anglePyramid, &rotationmatrix_x);
	glMultMatrixf(rotationmatrix_x);
	*/

	//glRotatef(anglePyramid, 0.5f, 0.5f, 0.5f);

	/*
	GLfloat *rotationmatrix_z = NULL;
	AllocateMatrix(&rotationmatrix_z, NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);
	RotationMatrix_z(anglePyramid, &rotationmatrix_z);
	glMultMatrixf(rotationmatrix_z);
	*/

	/*
	//glRotatef(anglePyramid, 0.0f, 1.0f, 0.0f);
	GLfloat *rotationmatrix_y = NULL;
	AllocateMatrix(&rotationmatrix_y, NUMBER_OF_ROWS, NUMBER_OF_COLOUMNS);
	RotationMatrix_y(anglePyramid, &rotationmatrix_y);
	glMultMatrixf(rotationmatrix_y);
	*/

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