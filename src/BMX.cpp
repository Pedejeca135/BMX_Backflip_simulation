#include"BMX.hpp"


BMX::BMX(Object model, float scale, float mass, float jump, Color3f color, arma::fmat transformation, Vertex aceleration, Vertex velocity, Vertex position, Vertex angular_Aceleration, Vertex angular_Velocity, Vertex rotation_Angle, Vertex rampIni, Vertex rampEnd)
{           
    std::vector<Vertex> model_vertices = model.get_faces_verts();

    this->scale = scale;
    this->mass = mass;
    this->jump = jump;
    this->color = color;
    this->transformation = transformation;

    this->aceleration = aceleration;
    this->velocity = velocity;
    this->position = position;

    this->angular_Aceleration = angular_Aceleration;
    this->angular_Velocity = angular_Velocity;
    this->rotation_Angle = rotation_Angle;

    this->rampIni = rampIni;
    this->rampEnd = rampEnd;
}

void BMX::makeStep()
{
    
    if(rampDone == false)
    {        
        if(bezier(,))
        {
            position.x > rampEnd.x;
        }
    }
    else if (jumpDone == false)
    {
        
    }
    else if(backFlipDone == false)
    {

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
    return  Tr.T(position.x, position.y, position.z) * Tr.S(scale, scale, scale)* Tr.R(rotation_Angle.x,rotation_Angle.y, rotation_Angle.z);
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