#include <stdio.h>
#include <stdlib.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <armadillo>
#include "Object.hpp"
#include "Transform.hpp"
#include "Plotter.hpp"
#include "UtilComm.hpp"


/*********************************************************
 * 
 *  global variables 
 * 
 * ***********************************************************/
vector<Object> models;
vector<arma::fmat> models_transf;
vector<Timer> models_time;

Transform Tr = Transform();


/*************************************************
 * functions declaration
 * ************************************************/
int screenInit(GLFWwindow** window, char* windowName, int xSize, int ySize, Color3f windowColor);
int keyPress(GLFWwindow** window,float eye[3], float camera[3]);
void keyPressCapture();
int presentationWindow();

void print(std::string printing);


/*************************************************
 * Main function
 * ************************************************/
int main( void )
{
    //glfw initalization:
    if( !glfwInit() )
    {
        fprintf( stderr, "GLFW initialization fail\n" );
        getchar();
        return -1;
    }

/********************************************
 * 
 *  initialization of windows models.
 * 
 * ******************************************/
    //BMX object
    Object obj_BMX = Object();
    obj_BMX.init("./models/BMXO.obj");
    models.push_back(obj_BMX);    
    models_transf.push_back(Tr.S(0.1,0.1,0.1));
    models_time.push_back(Timer());
    
    //Title text
    Object obj_Title = Object();
    obj_Title.init("./models/armadillo.obj");
    models.push_back(obj_Title);
    models_transf.push_back(Tr.S(0.1,0.1,0.1));
    models_time.push_back(Timer());

    //continue text
    Object obj_Continue = Object();
    obj_Continue.init("./models/armadillo.obj");
    models.push_back(obj_Continue);
    models_transf.push_back(Tr.S(0.1,0.1,0.1));
    models_time.push_back(Timer());

    print("antes de presentation");
    
   presentationWindow();

    print("despues de presentation");
   
  

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
/*
void captureCicle(GLFWwindow** window, float arrayOfValues[],int n)
{
 
    /*  
    *   - Mass(0): 40 - 90.
    *   - Initial velocity(1): 2.0m/s - 10.0m/s.
    *   - Total jump length(2): 0.5m - 1.5m.
    *   - Angular velocity(3):  π/2s - π/s.
    *

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
*/

//this function is just for present the project.
int presentationWindow()
{
    arma::frowvec eye = {0.0 , 10.0 , 10.0};
    arma::frowvec camera = {0.0, 0.0, 10.0};
    GLFWwindow* window;
    //window = glfwCreateWindow(1024,860, "BMX BackFlip",NULL,NULL);
    if(screenInit(&window,"BMX BackFlip",1024,860,Color3f(0.2,0.18,0.2)) != 0)
    {
        return -1;

    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //Projections
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    int width, height;
    glfwGetFramebufferSize(window,&width, & height);
    float ar = width/height;

    //parallel projection
    glViewport(0,0,width, height);
    glOrtho(-ar,ar,-1.0,1.0,-20.0,20.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    Transform Trans = Transform();

  
        float t_angle = 0;
        float a_angle = 0;
        std::vector<Vertex>  bmx_vertices = models[0].get_faces_verts();
        models_time[0].Restart();

        std::vector<Vertex>  title_vertices = models[1].get_faces_verts();
        models_time[1].Restart();
        models_transf[1] = Trans.S(0.005,0.005,0.005) * Trans.T(0.0,0.0,0.0);
        
        std::vector<Vertex>  continue_vertices = models[2].get_faces_verts();
        models_time[2].Restart();
        models_transf[2] = Trans.S(0.005,0.005,0.005) * Trans.T(0.3,0.3,-0.3);

         std::vector< Vertex > title_draw_vertices;
        for ( unsigned int i=0; i<title_vertices.size(); i++ ) 
        {
            arma::fcolvec v = title_vertices[i].getHomg();
            arma::fcolvec vp = models_transf[1] * v;
            Vertex rv = Vertex();
            rv.set_value(arma::trans(vp));
            title_draw_vertices.push_back(rv);
        }

         std::vector< Vertex > continue_draw_vertices;
        for ( unsigned int i=0; i<title_vertices.size(); i++ ) 
        {
            arma::fcolvec v = title_vertices[i].getHomg();
            arma::fcolvec vp = models_transf[2] * v;
            Vertex rv = Vertex();
            rv.set_value(arma::trans(vp));
            title_draw_vertices.push_back(rv);
        }

        float angular_Velocity =  (360.0) / 4.0;
    
do
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
   
    int last = t_angle;
    t_angle = (t_angle < 360.0f) ? t_angle + 22.5 : (last-360);   

    models_transf[0] = Trans.S(0.005f, 0.005f, 0.005f)* Trans.R(0.0f, 1.0f, 0.0f, t_angle) * Trans.R(0.0f,0.0f,1.0f,11.25)* Trans.R(1.0f,0.0f,0.0,-9.25);

        std::vector< Vertex > bmx_draw_vertices;
        for ( unsigned int i=0; i<bmx_vertices.size(); i++ ) 
        {
            arma::fcolvec v = bmx_vertices[i].getHomg();
            arma::fcolvec vp = models_transf[0] * v;
            Vertex rv = Vertex();
            rv.set_value(arma::trans(vp));
            bmx_draw_vertices.push_back(rv);
        }
         draw(bmx_draw_vertices,Color3f(0.5,0.7,0.3));
         //draw(title_draw_vertices,Color3f(0.5,0.7,0.3)); 
         //draw(continue_draw_vertices,Color3f(0.5,0.7,0.3)); 

    glEnd();
    glfwSwapBuffers(window);
    glfwPollEvents();
models_time[0].Restart();
}while( glfwGetKey(window,GLFW_KEY_SPACE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

glfwTerminate();
return 0;
}

//this is for capture the values for the simulation.
int captureWindow()
{

}

//this is a function for the whole simulation.
int animationWindow()
{

}

void print(std::string printing)
{
    cout<<endl<< printing << endl;
}