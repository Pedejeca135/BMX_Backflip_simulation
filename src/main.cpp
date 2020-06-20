#include <stdio.h>
#include <stdlib.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <armadillo>
#include "Object.hpp"
#include "Transform.hpp"
#include "Plotter.hpp"
#include "UtilComm.hpp"
#include "BMX.hpp"


/*********************************************************
 * 
 *  global variables 
 * 
 * ***********************************************************/
vector<Object> models;
vector<arma::fmat> models_transf;
vector<Timer> models_time;

Transform Tr = Transform();

const int numVarCapture = 4;

float shift_variables_offset[numVarCapture];
float shift_variables_vpn[numVarCapture];
float shift_variables_vpn_max[numVarCapture];
float shift_variables_delta[numVarCapture];

float arrow_vpn[numVarCapture];

const float scaleSimulation = 0.003;


/*************************************************
 * functions declaration
 * ************************************************/
int screenInit(GLFWwindow** window, char* windowName, int xSize, int ySize, Color3f windowColor);


int keyPress(GLFWwindow** window,float eye[3], float camera[3]);
int keyPressCapture(GLFWwindow** window, int  shiftCounter);


int presentationWindow();
int captureWindow();
int animationWindow();

void print(std::string printing);

//
//arma::fmat bezier(arma:: fmat GH, float t);


/*************************************************
 * Main function
 * ************************************************/
int main( void )
{
    

/********************************************
 * 
 *  initialization of windows models.
 * 
 * ******************************************/

    /**********************************
     * 
     *              For presentation:
     * ***********************************************/
    //BMX object----------------------------- 0
    Object obj_BMX = Object();
    obj_BMX.init("./models/BMXO.obj");
    models.push_back(obj_BMX);    
    models_transf.push_back(Tr.S(0.1,0.1,0.1));
    models_time.push_back(Timer());
    
    //Title text------------------------------ 1
    Object obj_Title = Object();
    obj_Title.init("./models/text_BMXBackflip.obj");
    models.push_back(obj_Title);
    models_transf.push_back(Tr.S(0.1,0.1,0.1));
    models_time.push_back(Timer());

    //continue text---------------------------- 2
    Object obj_Continue = Object();
    obj_Continue.init("./models/text_Continue.obj");
    models.push_back(obj_Continue);
    models_transf.push_back(Tr.S(0.1,0.1,0.1));
    models_time.push_back(Timer());

    /**********************************
     * 
     *              Capture_Text:
     * ***********************************************/
    //mass text-------------------------------- 3
    Object obj_Mass_Text = Object();
    obj_Mass_Text.init("./models/text_Mass.obj");
    models.push_back(obj_Mass_Text);
    models_transf.push_back(Tr.S(0.1,0.1,0.1));
    models_time.push_back(Timer());

    //Jump text-------------------------------- 4
    Object obj_Jump_Text = Object();
    obj_Jump_Text.init("./models/text_Jump.obj");
    models.push_back(obj_Jump_Text);
    models_transf.push_back(Tr.S(0.1,0.1,0.1));
    models_time.push_back(Timer());

    //Initial_Velocity text ---------------------5
    Object obj_Initial_Velocity_Text = Object();
    obj_Initial_Velocity_Text.init("./models/text_Initial_Velocity.obj");
    models.push_back(obj_Initial_Velocity_Text);
    models_transf.push_back(Tr.S(0.1,0.1,0.1));
    models_time.push_back(Timer());


    //Angular_Velocity text ----------------------6
    Object obj_Angular_Velocity_Text = Object();
    obj_Angular_Velocity_Text.init("./models/text_angular_velocity.obj");
    models.push_back(obj_Angular_Velocity_Text);
    models_transf.push_back(Tr.S(0.1,0.1,0.1));
    models_time.push_back(Timer());

   /**********************************
     * 
     *              Capture_BAR:
     * ***********************************************/

    //mass bar----------------------------------- 7
     Object obj_Mass_Bar = Object();
    obj_Mass_Bar.init("./models/BARRA.obj");
    models.push_back(obj_Mass_Bar);
    models_transf.push_back(Tr.S(0.1,0.1,0.1));
    models_time.push_back(Timer());

     //Jump bar
    models_transf.push_back(Tr.S(0.1,0.1,0.1));
    models_time.push_back(Timer());

     //Initial_Velocity bar
    models_transf.push_back(Tr.S(0.1,0.1,0.1));
    models_time.push_back(Timer());

    //Angular_Velocity bar
    models_transf.push_back(Tr.S(0.1,0.1,0.1));
    models_time.push_back(Timer());

    /**********************************
     * 
     *              Capture_INDI:
     * ***********************************************/

    //mass indicator --------------------------------- 8
     Object obj_Mass_INDI = Object();
    obj_Mass_INDI.init("./models/INDI_ARROW.obj");
    models.push_back(obj_Mass_INDI);
    models_transf.push_back(Tr.S(0.1,0.1,0.1));
    models_time.push_back(Timer());

    //Jump indicator
    models_transf.push_back(Tr.S(0.1,0.1,0.1));
    models_time.push_back(Timer());

    //Initial_Velocity indicator
    models_transf.push_back(Tr.S(0.1,0.1,0.1));
    models_time.push_back(Timer());

    //Angular_Velocity indicator
    models_transf.push_back(Tr.S(0.1,0.1,0.1));
    models_time.push_back(Timer());


    /************************************************
     * 
     * Capture extra text
     * 
     * *******************************************/
    //mass indicator --------------------------------- 9
     Object obj_parameters_Text = Object();
    obj_parameters_Text.init("./models/text_simulation_Parameters.obj");
    models.push_back(obj_parameters_Text);
    models_transf.push_back(Tr.S(0.1,0.1,0.1));
    models_time.push_back(Timer());

        

        shift_variables_vpn[0] = 5.0;//jump angle
        shift_variables_vpn[1] = 2.0;//velocity
        shift_variables_vpn[2] = 0.3;//jump
        shift_variables_vpn[3] = 45;//angular velocity

        shift_variables_offset[0] = 0.0;
        shift_variables_offset[1] = 0.0;
        shift_variables_offset[2] = 0.0;
        shift_variables_offset[3] = 0.0;

        shift_variables_vpn_max[0] = 90.0;
        shift_variables_vpn_max[1] = 12.0;
        shift_variables_vpn_max[2] = 1.5;
        shift_variables_vpn_max[3] = 720;

        shift_variables_delta[0] = (shift_variables_vpn_max[0] - shift_variables_vpn[0])/48 ; 
        shift_variables_delta[1] = (shift_variables_vpn_max[1] - shift_variables_vpn[1])/48 ; 
        shift_variables_delta[2] = (shift_variables_vpn_max[2] - shift_variables_vpn[2])/48 ; 
        shift_variables_delta[3] = (shift_variables_vpn_max[3] - shift_variables_vpn[3])/48 ; 

    /************************************************
     * 
     * RAMP
     * 
     * *******************************************/
    //ramp --------------------------------- 10
    Object obj_RAMP = Object();
    obj_RAMP.init("./models/RAMP.obj");
    models.push_back(obj_RAMP);
    models_transf.push_back(Tr.S(0.1,0.1,0.1));
    models_time.push_back(Timer());
    


    int res_AnimationW;

    do{
        if(presentationWindow() != 0)
        {
            return -1;
        }
        else if(captureWindow() != 0)
        {
            return -1;
        }
        else
        {
            do
            {
                res_AnimationW = animationWindow();
            } while (res_AnimationW == 1);
        }
        
    }while (res_AnimationW == 2 );

    glfwTerminate();

    return 0;

}//main (END).

//screen initialization.
//glfw has to be already initializated.
int screenInit(GLFWwindow** window, char* windowName, int xSize, int ySize, Color3f windowColor)
{
    //glfw initalization:
    if( !glfwInit() )
    {
        fprintf( stderr, "GLFW initialization fail\n" );
        getchar();
        return -1;
    }

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
            return 0;
		}
		else if(glfwGetKey(*window,  GLFW_KEY_DOWN) == GLFW_PRESS)//move the camera down.
		{
			eye[1] -= 0.05;
			camera[1] -= 0.05;
            return 0;
		}
		else if(glfwGetKey(*window,  GLFW_KEY_RIGHT) == GLFW_PRESS)//move the camera to the right.
		{
			eye[0] += 0.05;
			camera[0] += 0.05;
            return 0;
		}
		else if(glfwGetKey(*window,  GLFW_KEY_LEFT) == GLFW_PRESS)//move the camera to left.
		{
			eye[0] -= 0.05;
			camera[0] -= 0.05;
            return 0;
		}
		else if(glfwGetKey(*window,GLFW_KEY_KP_SUBTRACT  ) == GLFW_PRESS)//ward off.
		{
			eye[2] += 0.05;
			camera[2] += 0.05;
            return 0;
		}
		else if(glfwGetKey(*window, GLFW_KEY_KP_ADD ) == GLFW_PRESS)//get closer.
		{
			eye[2] -= 0.05;
			camera[2] -= 0.05;
            return 0;
		}
		else if(glfwGetKey(*window, GLFW_KEY_R ) == GLFW_PRESS)//rewind the whole move.
        {
            return 1;
        }			
        else if(glfwGetKey(*window, GLFW_KEY_C ) == GLFW_PRESS)//new values.
        {
            return 2;
        }
		return -1;
}

//key press actions on capturing values.
int keyPressCapture(GLFWwindow** window, int  shiftCounter)
{
		if(glfwGetKey(*window,  GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(*window,  GLFW_KEY_RIGHT) == GLFW_PRESS)//increase the value.
		{
            if(shiftCounter >= 0 &&  shiftCounter < numVarCapture )
            {
                shift_variables_offset[shiftCounter] += shift_variables_delta[shiftCounter];
                if(shift_variables_offset[shiftCounter] +  shift_variables_vpn[shiftCounter] > shift_variables_vpn_max[shiftCounter])
                {
                    shift_variables_offset[shiftCounter] = shift_variables_vpn_max[shiftCounter] - shift_variables_vpn[shiftCounter] ;
                }
            }			
		}
		else if(glfwGetKey(*window,  GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(*window,  GLFW_KEY_LEFT) == GLFW_PRESS)//decreasse the value.
		{
			if(shiftCounter >= 0 &&  shiftCounter < numVarCapture )
            {
                shift_variables_offset[shiftCounter] -=shift_variables_delta[shiftCounter];
            }
                   
            if(shift_variables_offset[shiftCounter] < 0)
                {
                    shift_variables_offset[shiftCounter] = 0;
                }
		}
		else if(glfwGetKey(*window,  GLFW_KEY_ENTER) == GLFW_PRESS)//go to the next value.
		{
			return 1;
		}
        return 0;		
}


/********************************************************************************************************
 * 
 * 
 *                                                  
 *                                              WINDOWS FUNCTIONS
 * 
 * ****************************************************************************************************/


//this function is just for present the project.
int presentationWindow()
{
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
        models_transf[1] = Trans.T(0.0,0.65,0.0)*Trans.S(0.0030,0.0030,0.0030) * Trans.R(0.0,1.0,0.0,5.0);//
        
        std::vector<Vertex>  continue_vertices = models[2].get_faces_verts();
        models_time[2].Restart();
        models_transf[2] = Trans.T(0.0,-0.70,0.0)*Trans.S(0.00205,0.00205,0.00205) * Trans.R(0.0,1.0,0.0,5.0);//

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
        for ( unsigned int i=0; i<continue_vertices.size(); i++ ) 
        {
            arma::fcolvec v = continue_vertices[i].getHomg();
            arma::fcolvec vp = models_transf[2] * v;
            Vertex rv = Vertex();
            rv.set_value(arma::trans(vp));
            continue_draw_vertices.push_back(rv);
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
         draw(title_draw_vertices,Color3f(0.5,0.7,0.3)); 
         draw(continue_draw_vertices,Color3f(0.5,0.7,0.3)); 

    glEnd();
    glfwSwapBuffers(window);
    glfwPollEvents();
models_time[0].Restart();
}while( glfwGetKey(window,GLFW_KEY_SPACE) != GLFW_PRESS &&  glfwGetKey(window,GLFW_KEY_ENTER) != GLFW_PRESS   && glfwWindowShouldClose(window) == 0);

glfwTerminate();
return 0;
}




/***********************************************
 * 
 * 
 *                  CAPTURE WINDOW.
 * 
 * 
 * *****************************************************/
//this is for capture the values for the simulation.
int captureWindow()
{
     GLFWwindow* window;
    //window = glfwCreateWindow(1024,860, "BMX BackFlip",NULL,NULL);
    if(screenInit(&window,"BMX Capture Values",1024,860,Color3f(0.2,0.18,0.2)) != 0)
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


    

/*********************************************************************+
 * 
 * TEXTS
 * 
 * **************************************************************************/

        std::vector<Vertex>  mass_text_vertices = models[3].get_faces_verts();
        models_time[3].Restart();
        models_transf[3] = Trans.T(-0.55,0.88,0.0)*Trans.S(0.00080,0.00080,0.00080)* Trans.R(0.0,0.0,1.0,20);//

        std::vector<Vertex>  jump_text_vertices = models[4].get_faces_verts();
        models_time[4].Restart();
        models_transf[4] = Trans.T(-0.25,0.38,0.0)* Trans.S(0.00070,0.00070,0.00070)* Trans.R(0.0,0.0,1.0,20);//

        std::vector<Vertex>  initial_Vel_text_vertices = models[5].get_faces_verts();
        models_time[5].Restart();
        models_transf[5] = Trans.T(0.05,-0.13,0.0) *Trans.S(0.00080,0.00080,0.00080)* Trans.R(0.0,0.0,1.0,20);//

        std::vector<Vertex>  angular_Vel_text_vertices = models[6].get_faces_verts();
        models_time[6].Restart();
        models_transf[6] = Trans.T(0.40,-0.60,0.0)*Trans.S(0.00085,0.00085,0.00085)* Trans.R(0.0,0.0,1.0,20);//

        std::vector<Vertex>  parameters_text_vertices = models[9].get_faces_verts();
        models_time[15].Restart();
        models_transf[15] = Trans.T(0.45,0.80,0.0)*Trans.S(0.0012,0.0012,0.0012);//

         std::vector< Vertex > mass_text_draw_vertices;
        for ( unsigned int i=0; i<mass_text_vertices.size(); i++ ) 
        {
            arma::fcolvec v = mass_text_vertices[i].getHomg();
            arma::fcolvec vp = models_transf[3] * v;
            Vertex rv = Vertex();
            rv.set_value(arma::trans(vp));
            mass_text_draw_vertices.push_back(rv);
        }


        std::vector< Vertex > jump_text_draw_vertices;
        for ( unsigned int i=0; i<jump_text_vertices.size(); i++ ) 
        {
            arma::fcolvec v = jump_text_vertices[i].getHomg();
            arma::fcolvec vp = models_transf[4] * v;
            Vertex rv = Vertex();
            rv.set_value(arma::trans(vp));
            jump_text_draw_vertices.push_back(rv);

        }

        std::vector< Vertex > initial_Vel_text_draw_vertices;
        for ( unsigned int i=0; i<initial_Vel_text_vertices.size(); i++ ) 
        {
            arma::fcolvec v = initial_Vel_text_vertices[i].getHomg();
            arma::fcolvec vp = models_transf[5] * v;
            Vertex rv = Vertex();
            rv.set_value(arma::trans(vp));
            initial_Vel_text_draw_vertices.push_back(rv);
        }

        std::vector< Vertex > angular_Vel_text_draw_vertices;
        for ( unsigned int i=0; i<angular_Vel_text_vertices.size(); i++ ) 
        {
            arma::fcolvec v = angular_Vel_text_vertices[i].getHomg();
            arma::fcolvec vp = models_transf[6] * v;
            Vertex rv = Vertex();
            rv.set_value(arma::trans(vp));
            angular_Vel_text_draw_vertices.push_back(rv);
        }

        std::vector< Vertex > parameters_text_draw_vertices;
        for ( unsigned int i=0; i<parameters_text_vertices.size(); i++ ) 
        {
            arma::fcolvec v = parameters_text_vertices[i].getHomg();
            arma::fcolvec vp = models_transf[15] * v;
            Vertex rv = Vertex();
            rv.set_value(arma::trans(vp));
            parameters_text_draw_vertices.push_back(rv);
        }

/*********************************************************************+
 * 
 * 
 * BAR
 * 
 * 
 * **************************************************************************/

        std::vector<Vertex>  BAR_vertices = models[7].get_faces_verts();
        models_time[7].Restart();
        models_transf[7] = Trans.T(-0.50,0.68,0.0)*Trans.S(0.1500,0.1500,0.1500) ;//

        models_time[8].Restart();
        models_transf[8] = Trans.T(-0.20,0.18,0.0)*Trans.S(0.1500,0.1500,0.1500);//

        models_time[9].Restart();
        models_transf[9] = Trans.T(0.10,-0.32,0.0)*Trans.S(0.1500,0.1500,0.1500);//

        models_time[10].Restart();
        models_transf[10] = Trans.T(0.40,-0.82,0.0)*Trans.S(0.1500,0.1500,0.1500) ;//

        std::vector<Vertex>  mass_BAR_Draw_vertices ;
        std::vector<Vertex>  jump_BAR_Draw_vertices;
        std::vector<Vertex>  initial_Vel_BAR_Draw_vertices ;
        std::vector<Vertex>  angular_Vel_BAR_Draw_vertices ;

        for ( unsigned int i=0; i<BAR_vertices.size(); i++ ) 
        {
            arma::fcolvec v = BAR_vertices[i].getHomg();
            arma::fcolvec vp = models_transf[7] * v;
            Vertex rv0 = Vertex();
            rv0.set_value(arma::trans(vp));
            mass_BAR_Draw_vertices.push_back(rv0);
         
            vp = models_transf[8] * v;
            Vertex rv1 = Vertex();
            rv1.set_value(arma::trans(vp));
            jump_BAR_Draw_vertices.push_back(rv1);             

            vp = models_transf[9] * v;
            Vertex rv2 = Vertex();
            rv2.set_value(arma::trans(vp));
            initial_Vel_BAR_Draw_vertices.push_back(rv2);
            
            vp = models_transf[10] * v;
            Vertex rv3 = Vertex();
            rv3.set_value(arma::trans(vp));
            angular_Vel_BAR_Draw_vertices.push_back(rv3);
        }

/*********************************************************************+
 * 
 * 
 * ARROW
 * 
 * 
 * **************************************************************************/
        float arrow_x[numVarCapture];
        float arrow_vpn_x[numVarCapture];

        arrow_vpn_x[0] = -0.93;
        arrow_vpn_x[1] = -0.63;
        arrow_vpn_x[2] = -0.33;
        arrow_vpn_x[3] = -0.03;


        std::vector<Vertex>  Arrow_vertices = models[8].get_faces_verts();
        models_time[11].Restart();
        arrow_x[0] = arrow_vpn_x[0];
        models_transf[11] = Trans.T(arrow_x[0],0.65,0.0)*Trans.S(0.050,0.050,0.050);

        models_time[12].Restart();
        arrow_x[1] = arrow_vpn_x[1];
        models_transf[12] = Trans.T(arrow_x[1],0.15,0.0)*Trans.S(0.050,0.050,0.050);

        models_time[13].Restart();
        arrow_x[2] = arrow_vpn_x[2];
        models_transf[13] = Trans.T(arrow_x[2],-0.35,0.0)*Trans.S(0.050,0.050,0.050);

        models_time[14].Restart();
        arrow_x[3] = arrow_vpn_x[3] ;
        models_transf[14] = Trans.T(arrow_x[3] ,-0.85,0.0)*Trans.S(0.050,0.050,0.050);


        std::vector<Vertex>  mass_Arrow_Draw_vertices ;
        std::vector<Vertex>  jump_Arrow_Draw_vertices;
        std::vector<Vertex>  initial_Vel_Arrow_Draw_vertices ;
        std::vector<Vertex>  angular_Vel_Arrow_Draw_vertices ;

        for ( unsigned int i=0; i<Arrow_vertices.size(); i++ ) 
        {
            arma::fcolvec v = Arrow_vertices[i].getHomg();
            arma::fcolvec vp = models_transf[11] * v;
            Vertex rv0 = Vertex();
            rv0.set_value(arma::trans(vp));
            mass_Arrow_Draw_vertices.push_back(rv0);

            vp = models_transf[12] * v;
            Vertex rv1 = Vertex();
            rv1.set_value(arma::trans(vp));
            jump_Arrow_Draw_vertices.push_back(rv1);

            vp = models_transf[13] * v;
            Vertex rv2 = Vertex();
            rv2.set_value(arma::trans(vp));
            initial_Vel_Arrow_Draw_vertices.push_back(rv2);

            vp = models_transf[14] * v;
            Vertex rv3 = Vertex();
            rv3.set_value(arma::trans(vp));
            angular_Vel_Arrow_Draw_vertices.push_back(rv3);
        }

        int counter = 0;    
do
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
   int antCont = counter;
         counter += keyPressCapture(&window, counter);
  
        //jump angle
         if(counter == 0)
         {
             draw(mass_text_draw_vertices,Color3f(0.93,0.45,0.1));

             arrow_x[counter] = arrow_vpn_x[counter] + ((shift_variables_offset[counter] / shift_variables_delta[counter])*(0.855))/( (shift_variables_vpn_max[counter] - shift_variables_vpn[counter]) / shift_variables_delta[counter]);
            
             int last = t_angle;
             t_angle = (t_angle < 360.0f) ? t_angle + 22.5 : (last-360);
             models_transf[11] = Trans.T(arrow_x[0],0.65,0.0)*Trans.S(0.050,0.050,0.050)* Trans.R(0.0,1.0,0.0,t_angle);              
         }
         else
         {
             draw(mass_text_draw_vertices,Color3f(0.5,0.7,0.3));

             models_transf[11] = Trans.T(arrow_x[0],0.65,0.0)*Trans.S(0.050,0.050,0.050);
         }
         
         //jump
         if(counter == 1)
         {
             draw(jump_text_draw_vertices,Color3f(0.93,0.45,0.1)); 

             arrow_x[counter] = arrow_vpn_x[counter] + ((shift_variables_offset[counter] / shift_variables_delta[counter])*(0.855))/( (shift_variables_vpn_max[counter] - shift_variables_vpn[counter]) / shift_variables_delta[counter]);

             int last = t_angle;
             t_angle = (t_angle < 360.0f) ? t_angle + 22.5 : (last-360);             
             models_transf[12] = Trans.T(arrow_x[1],0.15,0.0)*Trans.S(0.050,0.050,0.050)* Trans.R(0.0,1.0,0.0,t_angle); 
             
         }
         else
         {
             draw(jump_text_draw_vertices,Color3f(0.5,0.7,0.3)); 

             models_transf[12] = Trans.T(arrow_x[1],0.15,0.0)*Trans.S(0.050,0.050,0.050);
         }
         
         //initial velocity
         if(counter == 2)
         {
             draw(initial_Vel_text_draw_vertices,Color3f(0.93,0.45,0.1));

             arrow_x[counter] = arrow_vpn_x[counter] + ((shift_variables_offset[counter] / shift_variables_delta[counter])*(0.855))/( (shift_variables_vpn_max[counter] - shift_variables_vpn[counter]) / shift_variables_delta[counter]);

             int last = t_angle;
             t_angle = (t_angle < 360.0f) ? t_angle + 22.5 : (last-360);
             models_transf[13] = Trans.T(arrow_x[2],-0.35,0.0)*Trans.S(0.050,0.050,0.050)* Trans.R(0.0,1.0,0.0,t_angle); 
             
         }
         else
         {
             draw(initial_Vel_text_draw_vertices,Color3f(0.5,0.7,0.3));    

             models_transf[13] = Trans.T(arrow_x[2],-0.35,0.0)*Trans.S(0.050,0.050,0.050);      
         }
         
         //angular velocity
         if (counter == 3)
         {
             draw(angular_Vel_text_draw_vertices,Color3f(0.93,0.45,0.1));

             arrow_x[counter] = arrow_vpn_x[counter] + ((shift_variables_offset[counter] / shift_variables_delta[counter])*(0.855))/( (shift_variables_vpn_max[counter] - shift_variables_vpn[counter]) / shift_variables_delta[counter]);

            int last = t_angle;
             t_angle = (t_angle < 360.0f) ? t_angle + 15.5 : (last-360);
             models_transf[14] = Trans.T(arrow_x[3] ,-0.85,0.0)*Trans.S(0.050,0.050,0.050)* Trans.R(0.0,1.0,0.0,t_angle);             
         }
         else
         {
             draw(angular_Vel_text_draw_vertices,Color3f(0.5,0.7,0.3));

             models_transf[14] = Trans.T(arrow_x[3] ,-0.85,0.0)*Trans.S(0.050,0.050,0.050);
         }

        for ( unsigned int i=0; i<Arrow_vertices.size(); i++ ) 
        {
            arma::fcolvec v = Arrow_vertices[i].getHomg();
            arma::fcolvec vp = models_transf[11] * v;
            Vertex rv0 = Vertex();
            rv0.set_value(arma::trans(vp));
            mass_Arrow_Draw_vertices.push_back(rv0);

            vp = models_transf[12] * v;
            Vertex rv1 = Vertex();
            rv1.set_value(arma::trans(vp));
            jump_Arrow_Draw_vertices.push_back(rv1);

            vp = models_transf[13] * v;
            Vertex rv2 = Vertex();
            rv2.set_value(arma::trans(vp));
            initial_Vel_Arrow_Draw_vertices.push_back(rv2);

            vp = models_transf[14] * v;
            Vertex rv3 = Vertex();
            rv3.set_value(arma::trans(vp));
            angular_Vel_Arrow_Draw_vertices.push_back(rv3);
        }

        draw(mass_Arrow_Draw_vertices,Color3f(0.5,0.7,0.3));
        mass_Arrow_Draw_vertices.clear();

        draw(jump_Arrow_Draw_vertices,Color3f(0.5,0.7,0.3));
        jump_Arrow_Draw_vertices.clear();

        draw(initial_Vel_Arrow_Draw_vertices,Color3f(0.5,0.7,0.3)); 
        initial_Vel_Arrow_Draw_vertices.clear();

        draw(angular_Vel_Arrow_Draw_vertices,Color3f(0.5,0.7,0.3));
        angular_Vel_Arrow_Draw_vertices.clear();


        draw(mass_BAR_Draw_vertices ,Color3f(0.5,0.7,0.3),Color3f(0.5,0.3,0.7), 0, arrow_x[0]);
        draw(jump_BAR_Draw_vertices ,Color3f(0.5,0.7,0.3),Color3f(0.5,0.3,0.7), 0, arrow_x[1]); 
        draw(initial_Vel_BAR_Draw_vertices ,Color3f(0.5,0.7,0.3),Color3f(0.5,0.3,0.7), 0, arrow_x[2]);
        draw(angular_Vel_BAR_Draw_vertices ,Color3f(0.5,0.7,0.3) , Color3f(0.5,0.3,0.7), 0, arrow_x[3]);

        draw(parameters_text_draw_vertices,Color3f(0.3, 0.66, 1.0));

    glEnd();
    glfwSwapBuffers(window);
    glfwPollEvents();
models_time[0].Restart();


while(glfwGetKey(window,GLFW_KEY_ENTER) == GLFW_PRESS && antCont < counter)
{
    if(glfwGetKey(window,GLFW_KEY_ENTER) != GLFW_PRESS)
    {
        break;
    }
    glfwPollEvents();
}


}while( counter < 4   && glfwWindowShouldClose(window) == 0);

glfwTerminate();
return 0;
}


bool keyPressed = false;
void key_callback_Animation(GLFWwindow * window, int key, int scancode, int action, int mods)
{
    if(key > 261 && key <268 && (action == GLFW_PRESS || action == GLFW_REPEAT))
    keyPressed = true;
    else
    {
        keyPressed =  false;
    }    
}



/****************************************************
 * 
 * ANIMATION
 * ***********************************************/

//this is a function for the whole simulation.
int animationWindow()
{
    //camera and eye declared:
    float eye[3] = {0.0,0.0,3.0};
    float camera[3] = {0.0, 0.0, 0.0};
    float F3[3] = {0.0,3.0,0.0};
    int res = -1;

    GLFWwindow* window;
    //window = glfwCreateWindow(1024,860, "BMX BackFlip",NULL,NULL);
    if(screenInit(&window,"BMX BackFlip ñ_ñ",1024,860,Color3f(0.1,0.08,0.1)) != 0)
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

    //perspectic projection
    glFrustum(-ar,ar,-ar,ar,1,4.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    Transform Trans = Transform();

        std::vector<Vertex>  ramp_vertices = models[10].get_faces_verts();
        models_time[15].Restart();
        models_transf[15] = Trans.S(0.0030,0.0030,0.0030) ;//
        
         std::vector< Vertex > ramp_draw_vertices;
        for ( unsigned int i=0; i<ramp_vertices.size(); i++ ) 
        {
            arma::fcolvec v = ramp_vertices[i].getHomg();
            arma::fcolvec vp = models_transf[1] * v;
            Vertex rv = Vertex();
            rv.set_value(arma::trans(vp));
            ramp_draw_vertices.push_back(rv);
        }

        Object distancias;
        distancias = Object();
        arma::fmat transformation_distancias =  Tr.S(0.025,0.025,0.025);
        arma::fmat transformation_distancias_F =  Tr.T(1.58,0.0,0.0) * Tr.S(0.025,0.025,0.025);
        arma::fmat ar_trans = Tr.T(1.58,0.69,0.0) * Tr.S(0.025,0.025,0.025);

        //s_ani ************************************************************** s_ani
        arma::fmat s_ani = Tr.T(0.0,0.0,0.0) * Tr.S(0.030,0.030,0.030);
        
        float t = 0.0;
        float dt = 0.005;
        arma:: fmat GHH = {{0.0, 0.0, 0.0}, //P1
                      {0.513,0.15,0.0}, //P2
                      {1.15, 0.35, 0.0}, //P3
                      {1.581, 0.69, 0.0} //P4
                      };


        distancias.init("./models/sphere.obj");

        std::vector<Vertex>  de_sphere_vertices = distancias.get_faces_verts();
        
        std::vector< Vertex > de_sphere_draw_vertices;
        std::vector<Vertex> df_sphere_draw_vertices;
        std::vector<Vertex> ar_draw_vertices;
        for ( unsigned int i=0; i<de_sphere_vertices.size(); i++ ) 
        {
            arma::fcolvec v = de_sphere_vertices[i].getHomg();
            arma::fcolvec vp =  transformation_distancias* v;
            Vertex rv = Vertex();
            rv.set_value(arma::trans(vp));
            de_sphere_draw_vertices.push_back(rv);

            vp = transformation_distancias_F * v;
            rv =  Vertex();
            rv.set_value(arma::trans(vp)); 
            df_sphere_draw_vertices.push_back(rv);

            vp = ar_trans * v;
            rv =  Vertex();
            rv.set_value(arma::trans(vp)); 
            ar_draw_vertices.push_back(rv);
        }

        Object bm;
        bm = Object();
        bm.init("./models/BMX.obj");
        arma::fmat trans_BM = Tr.T(-3.0,0.07,0.0) * Tr.S(0.0030,0.0030,0.0030);//* Trans.R(0.0f,0.0f,1.0f,20.0);        
        std::vector<Vertex>  bm_vertices = bm.get_faces_verts();
        
        std::vector< Vertex > bm_draw_vertices;
        for ( unsigned int i=0; i<bm_vertices.size(); i++ ) 
        {
            arma::fcolvec v = bm_vertices[i].getHomg();
            arma::fcolvec vp =  trans_BM* v;
            Vertex rv = Vertex();
            rv.set_value(arma::trans(vp));
            bm_draw_vertices.push_back(rv);
        }

        arma::fmat trans_BM_1 = Tr.T(-0.07,0.07,0.0) * Tr.S(0.0030,0.0030,0.0030);//* Trans.R(0.0f,0.0f,1.0f,20.0);
        
        std::vector< Vertex > bm_1_draw_vertices;
        for ( unsigned int i=0; i<bm_vertices.size(); i++ ) 
        {
            arma::fcolvec v = bm_vertices[i].getHomg();
            arma::fcolvec vp =  trans_BM_1* v;
            Vertex rv = Vertex();
            rv.set_value(arma::trans(vp));
            bm_1_draw_vertices.push_back(rv);
        }

        arma::fmat trans_BM_2 = Tr.T(0.0,0.07,0.0) * Tr.S(0.0030,0.0030,0.0030) * Trans.R(0.0f,0.0f,1.0f,14.0);
        
        std::vector< Vertex > bm_2_draw_vertices;
        for ( unsigned int i=0; i<bm_vertices.size(); i++ ) 
        {
            arma::fcolvec v = bm_vertices[i].getHomg();
            arma::fcolvec vp =  trans_BM_2 * v;
            Vertex rv = Vertex();
            rv.set_value(arma::trans(vp));
            bm_2_draw_vertices.push_back(rv);
        }

        float jumpAngle = shift_variables_vpn[0] + shift_variables_offset[0];
        float velocity = shift_variables_vpn[1] + shift_variables_offset[1];
        float jump = shift_variables_vpn[2] + shift_variables_offset[2];
        float angularVelocity = shift_variables_vpn[3] + shift_variables_offset[3];

        BMX bicicle = BMX(bm, scaleSimulation , jumpAngle, jump, Color3f(0.6, 0.15, 0.8) ,
        Vertex(0.0,0.0,0.0), Vertex(velocity, 0.0, 0.0), Vertex(-3.0, 0.0, 0.0),  Vertex(0.0, 0.0, 0.0),  
        Vertex(0.0, 0.0, angularVelocity) ,  Vertex(0.0, 0.0, 0.0),  Vertex(0.0, 0.0 ,0.0) ,  Vertex(527.0, 230.0 ,0.0));
    
do
{
   glfwSetKeyCallback(window,key_callback_Animation);
   if(keyPressed == true)
   res = keyPress(&window,eye,camera);

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(eye[0],eye[1], eye[2],camera[0],camera[1],camera[2],0.0,1.0,0.0);
    
        arma::fmat s_ani_res_fmat = bezier_(GHH,t);
        t += dt;
        cout<< s_ani_res_fmat << endl;
        s_ani = Tr.T(s_ani_res_fmat[0], s_ani_res_fmat[1] + (40 * 0.003), s_ani_res_fmat[2])* Tr.S(0.0030, 0.0030, 0.0030);
        std::vector<Vertex> s_ani_draw_vertices;
        for ( unsigned int i=0; i<bm_vertices.size(); i++ ) 
        {
            arma::fcolvec v = bm_vertices[i].getHomg();
            arma::fcolvec vp =  s_ani * v;
            Vertex rv = Vertex();
            rv.set_value(arma::trans(vp));
            s_ani_draw_vertices.push_back(rv);
        }

        draw(s_ani_draw_vertices, Color3f(0.0, 0.20, 0.67));

    draw(ramp_draw_vertices,Color3f(0.65, 0.32, 0.055));
    draw(de_sphere_draw_vertices,Color3f(0.40,0.98,0.30));
    

    //draw(bm_draw_vertices,Color3f(0.40,0.98,0.30));

    //draw(bm_1_draw_vertices,Color3f(0.40,0.98,0.30));

   // draw(bm_2_draw_vertices, Color3f(0.40,0.98,0.30));
   draw(df_sphere_draw_vertices,Color3f(0.40,0.98,0.30));
   //draw(ar_draw_vertces,Color3f(0.40,0.98,0.30));


    glEnd();
    glfwSwapBuffers(window);
    glfwPollEvents();
models_time[0].Restart();
}while( glfwGetKey(window,GLFW_KEY_SPACE) != GLFW_PRESS &&  glfwGetKey(window,GLFW_KEY_ENTER) != GLFW_PRESS   && glfwWindowShouldClose(window) == 0);

glfwTerminate();
return res;
}




/******************************************************
 *  other
 * *****************************************************/
//for "debuging".
void print(std::string printing)
{
    cout<<endl<< printing << endl;
}