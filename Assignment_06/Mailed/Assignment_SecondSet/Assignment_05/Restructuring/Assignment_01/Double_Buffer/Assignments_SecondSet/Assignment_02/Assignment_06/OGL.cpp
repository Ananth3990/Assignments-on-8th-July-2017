#include <GL/freeglut.h>
#include<math.h>

//global variable declaration
bool bFullscreen=false; //variable to toggle for fullscreen


static const GLfloat pi = 3.1415f;

int main(int argc,char** argv)
{
	//function prototypes
	void display(void);
	void resize(int,int);
	void keyboard(unsigned char,int,int);
	void mouse(int,int,int,int);
	void initialize(void);
	void uninitialize(void);

	//code
	glutInit(&argc,argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(800,600); //to declare initial window size
	glutInitWindowPosition(100,100); //to declare initial window position
	glutCreateWindow("OpenGL First Window : Hello World !!!"); //open the window with "OpenGL First Window : Hello World" in the title bar

	initialize();

	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutCloseFunc(uninitialize);

	glutMainLoop();

//	return(0); 
}

void RenderCircle(GLfloat rad, GLfloat *arr)
{
	GLfloat angle = 0.0f;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 0.0f);
	for (angle = 0.0f; angle <= (2.0f*pi); angle = angle + 0.001f)
	{
		glVertex3f((GLfloat)((rad*cos(angle)) + arr[0]), (GLfloat)((rad*sin(angle)) + arr[1]), 0.0f);
	}
	glEnd();
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

void DrawGraph(GLfloat gap)
{
	void RenderLine(GLfloat *first_set, GLfloat lineWidth, GLfloat *color);
	GLfloat val = 0.0f;

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
	vert = { val, -1.0f, 0.0f, val, 1.0f, 0.0f };
	col = { 0.0f, 1.0f, 0.0f };
	RenderLine(vert.varr, 3.0f, col.carr);

	val = val + gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	col = { 0.0f, 0.0f, 1.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	col = { 0.0f, 0.0f, 1.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	//--------------------------------------------
	val = -gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val-gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val - gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val - gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val - gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val - gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val - gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val - gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val - gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val - gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val - gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val - gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val - gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val - gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val - gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val - gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val - gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val - gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val - gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val - gap;
	vert = { val, -1.0f, 0.0f,val, 1.0f, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	//End of vertical lines
	
	//Start of horizontal lines
	val = 0.0f;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	col = { 1.0f, 0.0f, 0.0f };
	RenderLine(vert.varr, 3.0f, col.carr);

	val = val + gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	col = { 0.0f, 0.0f, 1.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val + gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	//Lines drawn below (0,0)
	val = -gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val - gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val - gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val - gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val - gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val - gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val - gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val - gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val - gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val - gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val - gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val - gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val - gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val - gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val - gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val - gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val - gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val - gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val - gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	val = val - gap;
	vert = { 1.0f, val, 0.0f,-1.0f, val, 0.0f };
	RenderLine(vert.varr, 1.0f, col.carr);

	//End of horizontl lines
}

void RenderUnfilledTriangle(GLfloat vert[][3], GLfloat *color)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glBegin(GL_LINE_LOOP);
	glColor3f(color[0], color[1], color[2]);
	glVertex3f(vert[0][0], vert[0][1], vert[0][2]);
	glVertex3f(vert[1][0], vert[1][1], vert[1][2]);
	glVertex3f(vert[2][0], vert[2][1], vert[2][2]);
	glEnd();
}


void display(void)
{
	void DrawGraph(GLfloat gap);
	void RenderUnfilledTriangle(GLfloat vert[][3], GLfloat *color);

	typedef struct
	{
		GLfloat triangle_vert[3][3];
	}TRIANGLES;

	typedef struct
	{
		GLfloat color[3];
	}COLOR;

	TRIANGLES triangles;
	COLOR color;

	glClear(GL_COLOR_BUFFER_BIT);
	DrawGraph(0.05f);

	triangles = { { { -1.0f, -1.0f, 0.0f } ,{ 1.0f, -1.0f, 0.0f } ,{ 0.0f, 1.0f, 0.0f } } };
	color = { 1.0f,1.0f,0.0f};
	RenderUnfilledTriangle(triangles.triangle_vert, color.color);
	
	//glFlush();
	glutSwapBuffers();
}


void initialize(void)
{
	//code
	//to select clearing (background) clear
	glClearColor(0.0f,0.0f,0.0f,0.0f); //blue 
}

void keyboard(unsigned char key,int x,int y)
{
	//code
	switch(key)
	{
	case 27: // Escape
		glutLeaveMainLoop();
		break;
	case 'F':
	case 'f':
		if(bFullscreen==false)
		{
			glutFullScreen();
			bFullscreen=true;
		}
		else
		{
			glutLeaveFullScreen();
			bFullscreen=false;
		}
		break;
	default:
		break;
	}
}

void mouse(int button,int state,int x,int y)
{
	//code
	switch(button)
	{
	case GLUT_LEFT_BUTTON:
		break;
	default:
		break;
	}
}

void resize(int width,int height)
{
	// code
	if (height == 0)
	{
		height = 1;
	}
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

void uninitialize(void)
{
	// code
}

