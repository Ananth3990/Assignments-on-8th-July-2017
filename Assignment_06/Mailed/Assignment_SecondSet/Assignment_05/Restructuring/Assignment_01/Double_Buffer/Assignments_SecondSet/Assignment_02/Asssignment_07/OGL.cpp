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
	void RenderLine(GLfloat vertices[], GLfloat lineWidth, GLfloat color[]);
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

void RenderRectangle(GLfloat vertices[][3], GLfloat *color)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glBegin(GL_LINE_LOOP);
	//The quad is defined starting in the top left corner, then top right, bottom right and bottom left last.
	glColor3f(color[0], color[1], color[2]);
	glVertex3f(vertices[0][0], vertices[0][1], vertices[0][2]);
	glVertex3f(vertices[1][0], vertices[1][1], vertices[1][2]);
	glVertex3f(vertices[2][0], vertices[2][1], vertices[2][2]);
	glVertex3f(vertices[3][0], vertices[3][1], vertices[3][2]);
	glEnd();
}

void display(void)
{
	void DrawGraph(GLfloat gap);
	void RenderRectangle(GLfloat vertices[][3], GLfloat *color);

	typedef struct Rectangle
	{
		GLfloat vertex[4][3];
	}rect;

	typedef struct Color
	{
		GLfloat color[3];
	}color;

	rect rc;
	color cc;

	glClear(GL_COLOR_BUFFER_BIT);
	DrawGraph(0.05f);

	rc = { { { -1.0f,1.0f,0.0f },{ -1.0f, -1.0f, 0.0f },{ 1.0f, -1.0f, 0.0f },{ 1.0f, 1.0f, 0.0f } } };
	cc = { 1.0f, 1.0f, 0.0f };
	RenderRectangle(rc.vertex, cc.color);

	rc = { { { -0.5f,0.5f,0.0f },{ -0.5f, -0.5f, 0.0f },{ 0.5f, -0.5f, 0.0f },{ 0.5f, 0.5f, 0.0f } } };
	cc = { 1.0f, 1.0f, 0.0f };
	RenderRectangle(rc.vertex, cc.color);

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

