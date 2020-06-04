#include <stdio.h>
#include <stdlib.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <armadillo>
#include "Object.hpp"
#include "Transform.hpp"
#include "Plotter.hpp"



/*************************************************
 * functions declaration
 * ************************************************/
int screenInit(GLFWwindow** window, char* windowName, int xSize, int ySize, Color3f windowColor);
int keyPress(GLFWwindow** window,float eye[3], float camera[3]);
void keyPressCapture();


/*************************************************
 * Main function
 * ************************************************/
int main( void )
{

    if( !glfwInit() )
    {
        fprintf( stderr, "GLFW initialization fail\n" );
        getchar();
        return -1;
    }
    

    float timeDelay = 40.0f;


    //vector<Object> bmx = readObjFile("BMX.obj");
    //Object ramp = readFirstObjFile("RAMPA.obj");

    
    
    GLFWwindow* mainWindow;
    GLFWwindow* captureWindow;

    if(screenInit(&mainWindow,"BMX BackFlip",1000,750,Color3f(0.2,0.18,0.2)) == -1)
    {
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
//Projections
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    int width, height;
	glfwGetFramebufferSize(mainWindow,&width, &height);
	float ar = (float)width/(float)height;

//Perspective projection
    glFrustum(-ar, ar, -ar, ar, 2.0, 4.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    Transform Tr = Transform();
    float t_angle = 0.0f;

    //arma::frowvec eye = {0.0, 0.0, 10.0};
    //arma::frowvec camera = {0.0, 0.0, 0.0};
    float eye [3] = {0.0,0.0,3.0};
	float camera [3] = {0.0,0.0,0.0};
	float F[3] = {0.0,3.0,0.0};

    int res = -1;   
//the first window cicle for capturing values.
do{

        glfwMakeContextCurrent(captureWindow);
        glfwSetInputMode(captureWindow, GLFW_STICKY_KEYS, GL_TRUE);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear( GL_COLOR_BUFFER_BIT );

         




    do {
        res = keyPress(&mainWindow,eye,camera);
        glClear( GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT );
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(eye[0], eye[1], eye[2], 
                camera[0], camera[1], camera[2], 
                0.0, 1.0, 0.0);




        //draw(ramp,Color3f(0.0,0.0,1.0));
        //draw(bmx[0],Color3f(1.0,0.0,0.0));

        glfwSwapBuffers(mainWindow);
        glfwPollEvents();

    } while( glfwGetKey(mainWindow, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(mainWindow) == 0 && res != 1);

}while(res == 1);



    glfwTerminate();

    return 0;

}//main (END).



//screen initialization.
//glfw has to be already initializated.
int screenInit(GLFWwindow** window, char* windowName, int xSize, int ySize, Color3f windowColor)
{
    *window = glfwCreateWindow(xSize,ySize, windowName, NULL, NULL);
    if( *window == NULL ) {
        fprintf( stderr, "opening GLFW window fail.\n" );
        getchar();
        glfwTerminate();
        return -1;
    }
	
    glfwMakeContextCurrent(*window);
    glfwSetInputMode(*window, GLFW_STICKY_KEYS, GL_TRUE);

    
   glClearColor(windowColor.r,windowColor.g,windowColor.b,0.0f);
	return 0;
}

//key press actions.
int keyPress(GLFWwindow** window,float eye[3], float camera[3])
{
		if(glfwGetKey(*window,  GLFW_KEY_UP) == GLFW_PRESS)//move the camera up.
		{
			eye[1] += 0.05;
			camera[1] += 0.05;
		}
		else if(glfwGetKey(*window,  GLFW_KEY_DOWN) == GLFW_PRESS)//move the camera down.
		{
			eye[1] -= 0.05;
			camera[1] -= 0.05;
		}
		else if(glfwGetKey(*window,  GLFW_KEY_RIGHT) == GLFW_PRESS)//move the camera to the right.
		{
			eye[0] += 0.05;
			camera[0] += 0.05;
		}
		else if(glfwGetKey(*window,  GLFW_KEY_LEFT) == GLFW_PRESS)//move the camera to left.
		{
			eye[0] -= 0.05;
			camera[0] -= 0.05;
		}
		else if(glfwGetKey(*window,GLFW_KEY_KP_SUBTRACT  ) == GLFW_PRESS)//ward off.
		{
			eye[2] += 0.05;
			camera[2] += 0.05;
		}
		else if(glfwGetKey(*window, GLFW_KEY_KP_ADD ) == GLFW_PRESS)//get closer.
		{
			eye[2] -= 0.05;
			camera[2] -= 0.05;
		}
		else if(glfwGetKey(*window, GLFW_KEY_R ) == GLFW_PRESS)//rewind the whole move.
        {
            return 0;
        }			
        else if(glfwGetKey(*window, GLFW_KEY_C ) == GLFW_PRESS)//new values.
        {
            return 1;
        }
		return -1;
}

//key press actions on capturing values.
int keyPressCapture(GLFWwindow** window,float shift_Var[], int  shiftCounter)
{
		if(glfwGetKey(*window,  GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(*window,  GLFW_KEY_RIGHT) == GLFW_PRESS)//increase the value.
		{
            if(shiftCounter == 0)
            {
                shift_Var[shiftCounter] += 0.5;
                if(shift_Var[shiftCounter] > 90)
                {
                    shift_Var[shiftCounter] = 90;
                }
            }
            else if(shiftCounter == 1)
            {
                shift_Var[shiftCounter] += 0.25;
                if(shift_Var[shiftCounter] > 10)
                {
                    shift_Var[shiftCounter] = 10;
                }
            }
            else if(shiftCounter == 2)
            {
                shift_Var[shiftCounter] += 0.05;
                if(shift_Var[shiftCounter] > 1.5)
                {
                    shift_Var[shiftCounter] = 1.5;
                }
            }
            else if(shiftCounter == 3)
            {
                shift_Var[shiftCounter] += 0.05;
                if(shift_Var[shiftCounter] > 3)
                {
                    shift_Var[shiftCounter] = 3;
                }
            }			
		}
		else if(glfwGetKey(*window,  GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(*window,  GLFW_KEY_LEFT) == GLFW_PRESS)//decreasse the value.
		{
			if(shiftCounter == 0)
            {
                shift_Var[shiftCounter] -= 0.5;
                if(shift_Var[shiftCounter] < 40)
                {
                    shift_Var[shiftCounter] = 40;
                }
            }
            else if(shiftCounter == 1)
            {
                shift_Var[shiftCounter] -= 0.25;
                if(shift_Var[shiftCounter] < 2)
                {
                    shift_Var[shiftCounter] = 2;
                }
            }
            else if(shiftCounter == 2)
            {
                shift_Var[shiftCounter] -= 0.05;
                if(shift_Var[shiftCounter] < 0.5)
                {
                    shift_Var[shiftCounter] = 0.5;
                }
            }
            else if(shiftCounter == 3)
            {
                shift_Var[shiftCounter] -= 0.05;
                if(shift_Var[shiftCounter] < 1)
                {
                    shift_Var[shiftCounter] = 1;
                }
            }
		}
		else if(glfwGetKey(*window,  GLFW_KEY_ENTER) == GLFW_PRESS)//go to the next value.
		{
			return 1;
		}
        return 0;		
}

void captureCicle(GLFWwindow** window, float arrayOfValues[],int n)
{
 
    /*  
    *   - Mass(0): 40 - 90.
    *   - Initial velocity(1): 2.0m/s - 10.0m/s.
    *   - Total jump length(2): 0.5m - 1.5m.
    *   - Angular velocity(3):  π/2s - π/s.
    */

    int shiftCounter = 0 ;

    do
    {
        shiftCounter += keyPressCapture(window, arrayOfValues[],shiftCounter) ;  
        glBegin(GL_TRIANGLES);
            glVertex3f(0.0,-1.0, 0.0);
            glVertex3f(0.5, 0.0, 0.0);
            glVertex3f(-0.5, 0.0, 0.0);
        glEnd();     
    }
    while (shiftCounter < n)
    
}