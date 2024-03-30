#include <GL/glew.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/constants.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Camera.h"
#include "Text.h"
#include "Mesh.h"

#include <iostream>
using namespace std;
using namespace glm;

int g_winWidth = 1024;
int g_winHeight = 512;
int selectedLight = 1;
Camera g_cam;
Text g_text;

unsigned char g_keyStates[256];

char v_shader_file1[] =
//"..\\..\\shaders\\basic.vert";
//"..\\..\\shaders\\displacement.vert"; // vertex displacement shader with perlin noise
//"..\\..\\shaders\\perVert_lambert.vert"; // basic lambert lighting  
"..\\..\\shaders\\perFrag_phong.vert"; // basic lambert lighting with per-fragment implementation
//"..\\..\\shaders\\toon_shading.vert"; // basic toon shading with per-fragment implementation

char f_shader_file1[] =
//"..\\..\\shaders\\basic.frag";
// "..\\..\\shaders\\displacement.frag"; // vertex displacement shader with perlin noise
// "..\\..\\shaders\\perVert_lambert.frag"; // basic lambert shading 
"..\\..\\shaders\\perFrag_phong.frag"; // basic lambert shading with per-fragment implementation
//"..\\..\\shaders\\toon_shading.frag"; // basic toon shading with per-fragment implementation

char v_shader_file2[] =
//"..\\..\\shaders\\basic.vert";
//"..\\..\\shaders\\displacement.vert"; // vertex displacement shader with perlin noise
"..\\..\\shaders\\perVert_phong.vert"; // basic lambert lighting  
//"..\\..\\shaders\\perFrag_lambert.vert"; // basic lambert lighting with per-fragment implementation
//"..\\..\\shaders\\toon_shading.vert"; // basic toon shading with per-fragment implementation

char f_shader_file2[] =
//"..\\..\\shaders\\basic.frag";
// "..\\..\\shaders\\displacement.frag"; // vertex displacement shader with perlin noise
"..\\..\\shaders\\perVert_phong.frag"; // basic lambert shading 
//"..\\..\\shaders\\perFrag_lambert.frag"; // basic lambert shading with per-fragment implementation
//"..\\..\\shaders\\toon_shading.frag"; // basic toon shading with per-fragment implementation

const char meshFile1[128] =
//"..\\..\\Mesh\\sphere.obj";
//"..\\..\\Mesh\\bunny2K.obj";
"..\\..\\Mesh\\teapot.obj";
//"..\\..\\Mesh\\Mesh\\teddy.obj";

const char meshFile2[128] =
//"..\\..\\Mesh\\sphere.obj";
//"..\\..\\Mesh\\bunny2K.obj";
"..\\..\\Mesh\\teapot.obj";
//"..\\..\\Mesh\\Mesh\\teddy.obj";

Mesh g_mesh;

GLfloat position_light1[] = { 3.0f, 3.0f, 3.0f, 1.0f };
GLfloat position_light2[] = { 1.0f, 0.0f, -2.0f, 1.0f };

float g_time = 0.0f;

void initialization()
{
	g_cam.set(3.0f, 4.0f, 14.0f, 0.0f, 1.0f, -0.5f, g_winWidth, g_winHeight);
	g_text.setColor(0.0f, 0.0f, 0.0f);

	g_mesh.create(meshFile1, v_shader_file2, f_shader_file2);
	g_mesh.create(meshFile2, v_shader_file1, f_shader_file1);
	// add any stuff you want to initialize ...
}

/****** GL callbacks ******/
void initialGL()
{
	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void idle()
{
	// add any stuff to update at runtime ....

	/*g_cam.keyOperation(g_keyStates, g_winWidth, g_winHeight);*/

	glutPostRedisplay();
}

void display()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	//glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// add any stuff you'd like to draw	

	glUseProgram(0);
	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);

	glColor3f(1.0f, 0.0f, 0.0f);

	mat4 mat1 = translate(mat4(1.0f), vec3(position_light1[0], position_light1[1], position_light1[2]));
	mat4 modelmat1 = scale(mat1, vec3(1.8f, 1.8f, 1.8f));
	vec3 pos1 = vec3(position_light1[0], position_light1[1], position_light1[2]);
	mat4 temp1 = g_cam.viewMat * modelmat1;

	glLoadMatrixf(value_ptr(temp1));
	if (selectedLight == 1)
	{
		glutSolidSphere(0.1, 50, 50);
	}
	else if (selectedLight == 2)
	{
		glutWireSphere(0.1, 10, 10);
	}

	glMatrixMode(GL_MODELVIEW);

	glColor3f(1.0f, 0.0f, 0.0f);

	mat4 mat2 = translate(mat4(1.0f), vec3(position_light2[0], position_light2[1], position_light2[2]));
	mat4 modelmat2 = scale(mat2, vec3(2.0f, 2.0f, 2.0f));
	vec3 pos2 = vec3(position_light2[0], position_light2[1], position_light2[2]);
	mat4 temp2 = g_cam.viewMat * modelmat2;

	glLoadMatrixf(value_ptr(temp2));
	if (selectedLight == 1)
	{
		glutWireSphere(0.1, 10, 10);
	}
	else if (selectedLight == 2)
	{
		glutSolidSphere(0.1, 50, 50);
	}


	g_cam.drawGrid();
	g_cam.drawCoordinateOnScreen(g_winWidth, g_winHeight);
	g_cam.drawCoordinate();

	g_time = (float)glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	vec3 EyePos = vec3(g_cam.eye.x, g_cam.eye.y, g_cam.eye.z);
	g_mesh.draw1(g_cam.viewMat, g_cam.projMat, pos1, pos2, g_time, EyePos);
	g_mesh.draw2(g_cam.viewMat, g_cam.projMat, pos1, pos2, g_time, EyePos);

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	g_winWidth = w;
	g_winHeight = h;
	if (h == 0) {
		h = 1;
	}
	g_cam.setProjectionMatrix(g_winWidth, g_winHeight);
	g_cam.setViewMatrix();
	glViewport(0, 0, w, h);
}

void mouse(int button, int state, int x, int y)
{
	g_cam.mouseClick(button, state, x, y, g_winWidth, g_winHeight);
}

void motion(int x, int y)
{
	g_cam.mouseMotion(x, y, g_winWidth, g_winHeight);
}

void keyup(unsigned char key, int x, int y)
{
	g_keyStates[key] = false;
}

void keyboard(unsigned char key, int x, int y)
{
	g_keyStates[key] = true;
	switch (key) {
	case 27:
		exit(0);
		break;
	case '1': //selected light 1
		selectedLight = 1;
		printf("%i", selectedLight);
		break;
	case '2': //selected light 2
		selectedLight = 2;
		printf("%i", selectedLight);
		break;
	case 'w': //light move
		if (selectedLight == 1)
		{
			position_light1[2] -= 0.1;
		}
		else if (selectedLight == 2)
		{
			position_light2[2] -= 0.1;
		}
		break;
	case 's':
		if (selectedLight == 1)
		{
			position_light1[2] += 0.1;
		}
		else if (selectedLight == 2)
		{
			position_light2[2] += 0.1;
		}
		break;
	case 'd':
		if (selectedLight == 1)
		{
			position_light1[0] += 0.1;
		}
		else
		{
			position_light2[0] += 0.1;
		}
		break;
	case 'a':
		if (selectedLight == 1)
		{
			position_light1[0] -= 0.1;
		}
		else
		{
			position_light2[0] -= 0.1;
		}
		break;
	case 'u': //light move
		if (selectedLight == 1)
		{
			position_light1[1] += 0.1;
		}
		else
		{
			position_light2[1] += 0.1;
		}
		break;
	case 'j': //light move
		if (selectedLight == 1)
		{
			position_light1[1] -= 0.1;
		}
		else
		{
			position_light2[1] -= 0.1;
		}
		break;
	case ' ':
		g_cam.PrintProperty();
		break;
	case '+':
		g_mesh.normal_offset += 0.01;
		break;
	case'-':
		g_mesh.normal_offset -= 0.01;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(g_winWidth, g_winHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("VertFrag Shader Example");

	glewInit();
	initialGL();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardUpFunc(keyup);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);

	initialization();
	glutMainLoop();
	return EXIT_SUCCESS;
}