#include "Plotter.hpp"
#include "Transform.hpp"
#include "UtilComm.hpp"

class BMX : public Object
{
    public:
    BMX(float initial_Velocity, float impulse, float angular_Velocity, vector< Object> ObjectList);
    void makeStep();
    Timer t = Timer();

    private:
    float initial_Velocity = 0;
    float impulse = 0;
    float angular_Velocity = 0;
};