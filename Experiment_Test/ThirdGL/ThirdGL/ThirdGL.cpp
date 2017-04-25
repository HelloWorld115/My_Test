// ThirdGL.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"



#include <GLTools.h>
#include <GLShaderManager.h>
#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL\glut.h>
#endif

GLBatch  triangleBatch, squareBatch;
GLTriangleBatch sphereBatch;
GLShaderManager shaderManager;

GLfloat blockSize = 0.1f;

GLfloat vVerts[] = { -blockSize, -blockSize, .0f,
blockSize, -blockSize, 0.f,
blockSize, blockSize, .0f,
-blockSize, blockSize, .0f };



void ChangeSize(int w, int h)
{
	glViewport(0, 0, w, h);
}

void SetupRC()
{

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	shaderManager.InitializeStockShaders();
	//GLfloat vVerts[] = { -0.5f, 0.0f, 0.0f,
	//	0.5f, 0.0f, 0.0f,
	//	0.0f, 0.5f, 0.0f };
	//triangleBatch.Begin(GL_TRIANGLES, 3);
	//triangleBatch.CopyVertexData3f(vVerts);
	//triangleBatch.End();

	/*GLfloat vVertsN[] = { -0.5f, 0.2f, 0.2f, 
		0.5f, 0.2f, .2f,
		.5f, -0.5f, .2f, 
		-0.5f, -0.5f, .2f
		};*/
	squareBatch.Begin(GL_TRIANGLE_FAN, 4);
	squareBatch.CopyVertexData3f(vVerts);
	squareBatch.End();	

//	gltMakeSphere(sphereBatch, 0.4, 20, 10);
}


void BounceFunction()
{
	static GLfloat xDir = 1.0f;
	static GLfloat yDir = 1.0f;
	GLfloat stepSize = 0.005f;

	GLfloat blockX = vVerts[0];
	GLfloat blockY = vVerts[7];

	blockY += stepSize * yDir;
	blockX += stepSize * xDir;


	if (blockX < -1.0f)
	{
		blockX = -1.0f;
		xDir *= -1.0f;
	}
		

	if (blockX >(1.0f - blockSize * 2))
	{
		blockX = 1.0f - blockSize * 2;
		xDir *= -1.0f;
	}

	if (blockY < -1.0f + blockSize * 2)
	{
		blockY = -1.0f + blockSize * 2;
		yDir *= -1.0f;
	}

	if (blockY > 1.0f)
	{
		blockY = 1.0f;
		yDir *= -1.0f;
	}

	vVerts[0] = blockX;
	vVerts[1] = blockY - blockSize * 2;
	vVerts[3] = blockX + blockSize * 2;
	vVerts[4] = blockY - blockSize * 2;

	vVerts[6] = blockX + blockSize * 2;
	vVerts[7] = blockY;

	vVerts[9] = blockX;
	vVerts[10] = blockY;


	squareBatch.CopyVertexData3f(vVerts);

	glutPostRedisplay();
}

void SpecialKeys(int key, int x, int y)
{
	GLfloat stepSize = 0.025f;

	GLfloat blockX = vVerts[0];
	GLfloat blockY = vVerts[7];

	if (key == GLUT_KEY_UP)
	{
		blockY += stepSize;
	}

	if (key == GLUT_KEY_DOWN)
	{
		blockY -= stepSize;
	}

	if (key == GLUT_KEY_LEFT)
	{
		blockX -= stepSize;
	}

	if (key == GLUT_KEY_RIGHT)
	{
		blockX += stepSize;
	}

	if (blockX < -1.0f)
		blockX = -1.0f;

	if (blockX > (1.0f - blockSize * 2))
	{
		blockX = 1.0f - blockSize * 2;
	}

	if (blockY < -1.0f + blockSize * 2)
	{
		blockY = -1.0f + blockSize * 2;
	}

	if (blockY > 1.0f)
	{
		blockY = 1.0f;
	}
	
	vVerts[0] = blockX;
	vVerts[1] = blockY - blockSize * 2;
	vVerts[3] = blockX + blockSize * 2;
	vVerts[4] = blockY - blockSize * 2;

	vVerts[6] = blockX + blockSize * 2;
	vVerts[7] = blockY;

	vVerts[9] = blockX;
	vVerts[10] = blockY;

	
	squareBatch.CopyVertexData3f(vVerts);

	glutPostRedisplay();
}


void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	GLfloat vRed[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);

	squareBatch.Draw();
	glutSwapBuffers();

	BounceFunction();
	glutPostRedisplay();
}




int _tmain(int argc, char* argv[])
{
	gltSetWorkingDirectory(argv[0]);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glEnable(GL_DEPTH_TEST);
	glutInitWindowSize(800, 600);
	glutCreateWindow("move Block with Arrow Keys");


	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "glew error: %s\n", glewGetErrorString(err));
		return 1;
	}

	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
//	glutSpecialFunc(SpecialKeys);

	SetupRC();
	glutMainLoop();
	return 0;
}

