#include"BMX.hpp"

    BMX::BMX(float masa, float initial_Velocity, float impulse, float angular_Velocity, Object model , Color3f color, arma::fmat transformation,Vertex pos, Vertex rampIni, Vertex rampEnd)
    {
        this->initial_Velocity = initial_Velocity;
        this-> impulse = impulse;        
        this->angular_Velocity = angular_Velocity;
        this->transformation = transformation;
        this->rampIni = rampIni;
        this->rampEnd = rampEnd;
        this->model_vertices = model.get_faces_verts();
        this->position = pos;

    }

    void step()
    {

    }
    void draw()
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

    void step_RAMP()
    {

    }

    void step_JUMP()
    {

    }

    void step_BACK_FLIP()
    {

    }

    void step_MANUAL()
    {

    }
     
     

   
