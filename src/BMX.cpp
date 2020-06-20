#include"BMX.hpp"


BMX::BMX(Object model, float scale, float jumpAngle, float jump, Color3f color,  Vertex aceleration, Vertex velocity, Vertex position, Vertex angular_Aceleration, Vertex angular_Velocity, Vertex rotation_Angle, Vertex rampIni, Vertex rampEnd)
{           
    std::vector<Vertex> model_vertices = model.get_faces_verts();

    this->scale = scale;
    this->jumpAngle = jumpAngle;
    this->jump = jump;
    this->color = color;

    this->aceleration = aceleration;//m/s*s
    this->velocity = velocity;// in m/s

    this->position = position;//escaled

    this->angular_Aceleration = angular_Aceleration;// 
    this->angular_Velocity = angular_Velocity;//m/s
    this->rotation_Angle = rotation_Angle;//360.

    this->rampIni = rampIni;
    this->rampEnd = rampEnd;
}

void BMX::makeStep()
{
    double delta = t.Delta();
    double time = delta - positionLastTime ;
    positionLastTime = delta;

    if(befRampDone == false)
    {
        if(position.x > rampIni.x)
        {
            befRampDone = true;            
            t.Restart();
            positionLastTime = t.Delta();
        }
        else
        {            
            calculatePosition();
        }        
    }
    else if(rampDone == false)
    {           
        dt_factor = VelocityScaled().x / scaled(rampEnd.x);
        dt_Bezier = dt_factor * time;
        t_Bezier += dt_Bezier;
        arma::fmat newPosition = bezier_(GH1, t_Bezier);
        position.x = newPosition[0];
        position.y = newPosition[1];
        position.z = newPosition[2];

        transformation = Tr.T(position.x, position.y + alturaModel, position.z)* Tr.S(scale, scale, scale)* Tr.R(1.0, 0.0, 0.0,rotation_Angle.x ) * Tr.R(0.0,1.0, 0.0, rotation_Angle.y) * Tr.R(0.0, 0.0 ,1.0, rotation_Angle.z) ;

        if(position.x > scaled(23))
        {
            rotation_Angle.z = 15.0;
        }
        if(position.x > scaled(95))
        {
            rotation_Angle.z = 17.68;
        }
        if(position.x > scaled(195) )
        {
            rotation_Angle.z = 20.00;
        }
        if(position.x > rampEnd.x || t_Bezier > 1)
        {
            t_Bezier = 0.0;
            rampDone = true;
            t.Restart();
            positionLastTime = t.Delta();
        }        
    }
    else if (jumpDone == false)
    {
        float v0 = pow((aceleration.y*2)*jumpScaled()*(1.0/pow(sin(jumpAngle),2)) ,0.5);
        position.y = scaled(rampEnd.y) + (v0 * sin(jumpAngle) * time) - ( aceleration.y * time * time);
        position.x += scaledPhysic(velocity.x) * time;

        if(position.y > (scaled(rampEnd.y) + jumpScaled()) /2)
        {
            rotation_Angle.z += angular_Velocity.z * time;
        }
        if(position.y > scaled(rampEnd.y) + jumpScaled())
        {
            jumpDone = true;
            t.Restart();
            positionLastTime = t.Delta();
        }
        transformation = Tr.T(position.x, position.y + alturaModel, position.z)* Tr.S(scale, scale, scale)* Tr.R(1.0, 0.0, 0.0,rotation_Angle.x ) * Tr.R(0.0,1.0, 0.0, rotation_Angle.y) * Tr.R(0.0, 0.0 ,1.0, rotation_Angle.z) ;
    }
    else // just being around.
    {

   }
    

}

void BMX::draw()
{
    std::vector< Vertex > draw_vertices;
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_TRIANGLES);
    for ( unsigned int i=0; i<this->model_vertices.size(); i++ ) 
        {
            arma::fcolvec v = this->model_vertices[i].getHomg();
            arma::fcolvec vp =  this->transformation * v;
            Vertex rv = Vertex();
            rv.set_value(arma::trans(vp));
            //draw_vertices.push_back(rv);
            arma::frowvec vert = rv.get_value();
            glVertex3f(vert[0], vert[1], vert[2]);
        }
        glEnd();
}

arma::fmat BMX::Transformation()
{
    calculatePosition();
    calculateRotation();
    return  Tr.T(position.x, position.y + alturaModel, position.z)* Tr.S(scale, scale, scale)* Tr.R(1.0, 0.0, 0.0,rotation_Angle.x ) * Tr.R(0.0,1.0, 0.0, rotation_Angle.y) * Tr.R(0.0, 0.0 ,1.0, rotation_Angle.z) ;
    
}
     
void BMX::calculatePosition()
{
    double delta = t.Delta();
    double time = delta - positionLastTime ;
    positionLastTime = delta;

    velocity.x = velocity.x + (aceleration.x * time);
    position.x = position.x + (velocity.x * time);

    velocity.y = velocity.y + (aceleration.y * time);
    position.y = position.y + (velocity.y * time);

    velocity.z = velocity.z + (aceleration.z * time);
    position.z = position.z + (velocity.z * time);
}

void BMX::calculateRotation()
{
    double delta = t.Delta();
    double time = delta - rotationLastTime ;
    rotationLastTime = delta;

    angular_Velocity.x = angular_Velocity.x + (angular_Aceleration.x * time);
    rotation_Angle.x = rotation_Angle.x + (angular_Velocity.x * time);

    angular_Velocity.y = angular_Velocity.y + (angular_Aceleration.y * time);
    rotation_Angle.y = rotation_Angle.y + (angular_Velocity.y * time);

    angular_Velocity.z = angular_Velocity.z + (angular_Aceleration.z * time);
    rotation_Angle.z = rotation_Angle.z + (angular_Velocity.z * time);
}

Vertex BMX::VelocityScaled()
{
    Vertex res = Vertex(velocity.x * scale, velocity.y * scale, velocity.z * scale);
    return res;
} 

float BMX::jumpScaled()
{
    return jump * scaled(rateScale);
}

float BMX::scaledPhysic(float toScale)
{
    return toScale * scaled(rateScale);

}

float BMX::scaled(float toScale)
{
    return toScale * scale;
}