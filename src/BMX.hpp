#include "Plotter.hpp"
#include "Transform.hpp"
#include "UtilComm.hpp"
#include <GLFW/glfw3.h>

#include "UtilComm.hpp"

class BMX 
{

//##################### PUBLIC ####################################3
    public:
    BMX(float masa, float initial_Velocity, float impulse, float angular_Velocity, Object model , Color3f color, arma::fmat transformation, Vertex pos,Vertex rampIni, Vertex rampEnd);
    void makeStep();
    Timer t = Timer();
    Object obj_BMX_Model;    
    arma::fmat transformation;
    std::vector<Vertex> model_vertices;
    
//############################ PRIVATE ###############################################
    private:
    float masa = 0;
    float initial_Velocity = 0;
    float impulse = 0;
    float angular_Velocity = 0;
    Color3f Color;
    Vertex position = Vertex(0.0,0.0,0.0);

    Vertex rampIni_X;
    Vertex rampFinal_X;

    void step();
    void draw();
};

