#include "Plotter.hpp"
#include "Transform.hpp"
#include "UtilComm.hpp"

class BMX 
{
    public:
    BMX(float initial_Velocity, float impulse, float angular_Velocity, vector< Object> ObjectList);
    void makeStep();
    Timer t = Timer();
    Object obj_BMX_Model;

    void draw();

    void draw(vector<Vertex> draw_vertices);






    

    private:
    float initial_Velocity = 0;
    float impulse = 0;
    float angular_Velocity = 0;
};

