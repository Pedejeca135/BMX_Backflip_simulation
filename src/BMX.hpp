#include "Plotter.hpp"
#include "Transform.hpp"
#include "UtilComm.hpp"

class BMX 
{
    public:
    BMX(float masa, float initial_Velocity, float impulse, float angular_Velocity, vector< Object> ObjectList, Color3f color);
    void makeStep();
    Timer t = Timer();
    Object obj_BMX_Model;

    void draw_BMX();

    void draw_BMX(vector<Vertex> draw_vertices);


    

    private:
    float masa = 0;
    float initial_Velocity = 0;
    float impulse = 0;
    float angular_Velocity = 0;
    Color3f Color;


};

