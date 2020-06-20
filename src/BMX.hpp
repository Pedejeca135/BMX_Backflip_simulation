#ifndef BMX_H
#define BMX_H

#include "Plotter.hpp"
#include "Transform.hpp"
#include "UtilComm.hpp"
#include <GLFW/glfw3.h>

#include "UtilComm.hpp"

class BMX 
{

//##################### PUBLIC ####################################3
    public:
    BMX(Object model, float scale, float mass, float jump, Color3f color, Vertex aceleration, Vertex velocity, Vertex position, Vertex angular_Aceleration, Vertex angular_Velocity, Vertex rotation_Angle, Vertex rampIni, Vertex rampEnd);
    void makeStep();
    void draw();
    arma::fmat Transformation();
    void calculatePosition();
    double positionLastTime = 0.0;
    double makeStepLastTime = 0.0;
    void calculateRotation();
    double rotationLastTime = 0.0;

    Timer t = Timer();
    Transform Tr = Transform();


    Object obj_BMX_Model;
    std::vector<Vertex> model_vertices;
    bool rampDone = false;
    bool befRampDone = false;
    float t_Bezier = 0.0;
    float dt_Bezier = 0.01;
    float dt_factor = 0.0;

    bool jumpDone = false;
    bool backFlipDone = false; 

    float rateScale = 40.0/0.55;
//############################ PRIVATE ###############################################
    private:
    float scale = 0.003;
    float alturaModel = 20 * scale;
    float jumpAngle = 0.0;
    float jump = 0.0;
    Color3f color;
    arma::fmat transformation;

/************************
*   vectorial parameters
*************************/
    Vertex aceleration;
    Vertex velocity;
    Vertex position;

    Vertex angular_Aceleration;
    Vertex angular_Velocity;
    Vertex rotation_Angle;

    Vertex rampIni;
    Vertex rampEnd;

    arma:: fmat GH1 = {{0.0, 0.0, 0.0}, //P1
                      {0.513,0.15,0.0}, //P2
                      {1.15, 0.35, 0.0}, //P3
                      {1.581, 0.69, 0.0} //P4
                      };

Vertex VelocityScaled();
float scaled(float toScale);
float jumpScaled();

float scaledPhysic(float toScale);

    
};

#endif