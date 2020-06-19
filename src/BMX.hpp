#include "Plotter.hpp"
#include "Transform.hpp"
#include "UtilComm.hpp"
#include <GLFW/glfw3.h>

#include "UtilComm.hpp"

class BMX 
{

//##################### PUBLIC ####################################3
    public:
    BMX::BMX(Object model, float scale, float mass, float jump, Color3f color, arma::fmat transformation, Vertex aceleration, Vertex velocity, Vertex position, Vertex angular_Aceleration, Vertex angular_Velocity, Vertex rotation_Angle, Vertex rampIni, Vertex rampEnd);
    void makeStep();
    void draw();
    arma::fmat Transformation();
    void calculatePosition();
    double positionLastTime = 0.0;
    void calculateRotation();
    double rotationLastTime = 0.0;

    Timer t = Timer();
    Transform Tr = Transform();


    Object obj_BMX_Model;
    std::vector<Vertex> model_vertices;
    bool rampDone = false;
    float t = 0.0;
    float dt = 0.01;
    bool jumpDone = false;
    bool backFlipDone = false; 
//############################ PRIVATE ###############################################
    private:
    float scale = 0.003;
    float mass = 0;
    float jump = 0;
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

    
};

