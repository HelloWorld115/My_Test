

#include <GLTools.h>
#include <GL\glew.h>
#include <GLFrustum.h>
#include <GLMatrixStack.h>
#include <GLGeometryTransform.h>
#include <iostream>

#include <GLFrame.h>



#define FREEGLUT_STATIC

#include <GL/glut.h>

GLShaderManager shader;
GLTriangleBatch glBatch;
GLFrustum viewFrustum;
GLMatrixStack modelViewMatrix;
GLMatrixStack projectMatrix;
GLGeometryTransform tranformPipeLine;
GLFrame		cameraFrame;
GLFrame     objectFrame;

GLfloat vWhite[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat vGreen[] = { .0f, 1.0f, .0f, 1.0f };

void ChangeSize(int w, int h)
{
	glViewport(0, 0, w, h);
	viewFrustum.SetPerspective(35.0f, float(w) / float(h), 1.0f, 500.0f);
	projectMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
	modelViewMatrix.LoadIdentity();
}

void SetupRC()
{	
	glClearColor(0.7f, .70f, .70f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	shader.InitializeStockShaders();
	cameraFrame.MoveForward(-15);


	gltMakeSphere(glBatch, 3.0, 10, 20);
	

//	gltMakeTorus(glBatch, 3.0f, 0.75f, 15, 15);
//	tranformPipeLine.SetMatrixStacks(modelViewMatrix, projectMatrix);

	
}

void SpecialFunc(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
	{
		cameraFrame.MoveForward(10);
	}
	else if (key == GLUT_KEY_DOWN)
	{
		cameraFrame.MoveForward(-10);
	}
	else if (key == GLUT_KEY_LEFT)
	{
		objectFrame.RotateWorld(m3dDegToRad(-5), 0, 1, 0);
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		objectFrame.RotateWorld(m3dDegToRad(5), 0, 1, 0);
	}

	glutPostRedisplay();

}


void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	modelViewMatrix.PushMatrix();
	M3DMatrix44f mCamera;
	//cameraFrame.MoveForward(-15);
	cameraFrame.GetCameraMatrix(mCamera);
	modelViewMatrix.MultMatrix(mCamera);

	M3DMatrix44f objectMatrix;
	objectFrame.GetMatrix(objectMatrix);
	
	modelViewMatrix.MultMatrix(objectMatrix);
//	shader.UseStockShader(GLT_SHADER_FLAT, tranformPipeLine.GetModelViewProjectionMatrix() , vGreen);
	M3DMatrix44f desM;

	m3dMatrixMultiply44(desM, projectMatrix.GetMatrix(), modelViewMatrix.GetMatrix());

	shader.UseStockShader(GLT_SHADER_FLAT, desM, vGreen);
	
//	shader.UseStockShader(GLT_SHADER_FLAT, desM, vWhite);
	glBatch.Draw();
	modelViewMatrix.PopMatrix();
	glutSwapBuffers();

}

int main(int argc, char* argv[])
{
	gltSetWorkingDirectory(argv[0]);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutCreateWindow("fuck");

	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutSpecialFunc(SpecialFunc);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		return 1;
	}


	SetupRC();
	glutMainLoop();
	return 0;
}