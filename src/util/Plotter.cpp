#include <Plotter.hpp>


Color3f::Color3f()//for white color.
{
    r = 0.0;
    g = 0.0;
    b = 0.0;
}

Color3f::Color3f(float i) // for black color.
{

}

Color3f::Color3f(float _r, float _g, float _b)
{
    r = _r;
    g = _g;
    b = _b;
}

void plotWireFrame(Object obj){

	for(int f = 0; f < obj.faces.size(); f++) 
    {
		Face face = obj.faces[f];        
		    glColor3f(1.0, 1.0, 1.0);
		    glBegin(GL_LINE_LOOP);
		    for(int v = 0; v < face.verticesIndex.size(); v++) {
			    Vertex vertex = obj.vertices[face.verticesIndex[v]-1];
			    glVertex3f(vertex.x, vertex.y, vertex.z);
		    }
		    glEnd();
        
	}
}

void plotWireFrame(vector<Object> objs){
    
    for(int i= 0 ; i< objs.size(); i++)
    {
        plotWireFrame(objs[i]);
    }
}

void plotWireFrame(vector<Object> objs, float scale){
    
    for(int i= 0 ; i< objs.size(); i++)
    {
        plotWireFrame(objs[i],scale);
    }
}


void plotWireFrame(Object obj, float scale){

	for(int f = 0; f < obj.faces.size(); f++) 
    {
		Face face = obj.faces[f];        
		    glColor3f(1.0, 1.0, 1.0);
		    glBegin(GL_LINE_LOOP);
		    for(int v = 0; v < face.verticesIndex.size(); v++) {
			    Vertex vertex = obj.vertices[face.verticesIndex[v]-1];
			    glVertex3f(vertex.x*scale, vertex.y*scale, vertex.z*scale);
		    }
		    glEnd();
        
	}
}


void draw(Object obj){

	for(int f = 0; f < obj.faces.size(); f++) 
    {
		Face face = obj.faces[f];        
		    glColor3f(1.0, 1.0, 1.0);
		    glBegin(GL_POLYGON);
		    for(int v = 0; v < face.verticesIndex.size(); v++) {
			    Vertex vertex = obj.vertices[face.verticesIndex[v]-1];
			    glVertex3f(vertex.x, vertex.y, vertex.z);
		    }
		    glEnd();
        
	}
}

void draw(vector<Object> objs){
    
    for(int i= 1 ; i < objs.size() -1; i++)
    {
        draw(objs[i]);
    }
}

void draw(vector<Object> objs, float scale){
    
    for(int i= 0 ; i< objs.size(); i++)
    {
        draw(objs[i],scale);
    }
}


void draw(Object obj, float scale){

	for(int f = 0; f < obj.faces.size(); f++) 
    {
		Face face = obj.faces[f];        
		    glColor3f(1.0, 1.0, 1.0);
		    glBegin(GL_POLYGON);
		    for(int v = 0; v < face.verticesIndex.size(); v++) {
			    Vertex vertex = obj.vertices[face.verticesIndex[v]-1];
			    glVertex3f(vertex.x*scale, vertex.y*scale, vertex.z*scale);
		    }
		    glEnd();
        
	}
}

/***************************************************
*
*            for passing the color.
*
****************************************************/

void plotWireFrame(Object obj, Color3f color){

	for(int f = 0; f < obj.faces.size(); f++) 
    {
		Face face = obj.faces[f];        
		    glColor3f(color.r, color.g, color.b);
		    glBegin(GL_LINE_LOOP);
		    for(int v = 0; v < face.verticesIndex.size(); v++) {
			    Vertex vertex = obj.vertices[face.verticesIndex[v]-1];
			    glVertex3f(vertex.x, vertex.y, vertex.z);
		    }
		    glEnd();
        
	}
}

void plotWireFrame(vector<Object> objs, Color3f color){
    
    for(int i= 0 ; i< objs.size(); i++)
    {
        plotWireFrame(objs[i], color);
    }
}

void plotWireFrame(vector<Object> objs, float scale, Color3f color){
    
    for(int i= 0 ; i< objs.size(); i++)
    {
        plotWireFrame(objs[i],scale, color);
    }
}


void plotWireFrame(Object obj, float scale, Color3f color){

	for(int f = 0; f < obj.faces.size(); f++) 
    {
		Face face = obj.faces[f];        
		    glColor3f(color.r, color.g, color.b);
		    glBegin(GL_LINE_LOOP);
		    for(int v = 0; v < face.verticesIndex.size(); v++) {
			    Vertex vertex = obj.vertices[face.verticesIndex[v]-1];
			    glVertex3f(vertex.x*scale, vertex.y*scale, vertex.z*scale);
		    }
		    glEnd();
        
	}
}


void draw(Object obj, Color3f color){

	for(int f = 0; f < obj.faces.size(); f++) 
    {
		Face face = obj.faces[f];        
		    glColor3f(color.r, color.g, color.b);
		    glBegin(GL_POLYGON);
		    for(int v = 0; v < face.verticesIndex.size(); v++) {
			    Vertex vertex = obj.vertices[face.verticesIndex[v]-1];
			    glVertex3f(vertex.x, vertex.y, vertex.z);
		    }
		    glEnd();
        
	}
}

void draw(vector<Object> objs, Color3f color){
    
    for(int i= 0 ; i< objs.size(); i++)
    {
        draw(objs[i], color);
    }
}
void draw(Object obj, float scale, Color3f color){

	for(int f = 0; f < obj.faces.size(); f++) 
    {
		Face face = obj.faces[f];        
		    glColor3f(color.r, color.g, color.b);
		    glBegin(GL_POLYGON);
		    for(int v = 0; v < face.verticesIndex.size(); v++) {
			    Vertex vertex = obj.vertices[face.verticesIndex[v]-1];
			    glVertex3f(vertex.x*scale, vertex.y*scale, vertex.z*scale);
		    }
		    glEnd();        
	}
}


void draw(vector<Object> objs, float scale, Color3f color){
    
    for(int i= 0 ; i< objs.size(); i++)
    {
        draw(objs[i],scale, color);
    }
}




void draw(vector<Vertex> vertices, Color3f color)
{
	glColor3f(color.r, color.g, color.b);
        glBegin(GL_TRIANGLES);
        for ( unsigned int i=0; i<vertices.size(); i++ ) {
            arma::frowvec vert = vertices[i].get_value();
            glVertex3f(vert[0], vert[1], vert[2]);
        }
        glEnd();
}



        


