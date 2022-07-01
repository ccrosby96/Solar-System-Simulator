#include "Object.hpp"

class Circle : Object{

    public:

        Circle(float x, float y, float z, float radius, int numberOfSides);

        void Init();




};

Circle::Circle(float x, float y, float z, float radius, int numberOfSides){
    int numVertices = numberOfSides + 1;
    
    GLfloat doublePi = 2.0f * M_PI;
    
    GLfloat circleVerticesX[numVertices];
    GLfloat circleVerticesY[numVertices];
    GLfloat circleVerticesZ[numVertices];

    for ( int i = 0; i < numVertices; i++ )
    {
        circleVerticesX[i] = x + ( radius * cos( i * doublePi / numberOfSides ) );
        circleVerticesY[i] = y + ( radius * sin( i * doublePi / numberOfSides ) );
        circleVerticesZ[i] = z;
    }
    
    GLfloat allCircleVertices[numVertices * 3];
    
    for ( int i = 0; i < numVertices; i++ )
    {
        allCircleVertices[i * 3] = circleVerticesX[i];
        allCircleVertices[( i * 3 ) + 1] = circleVerticesY[i];
        allCircleVertices[( i * 3 ) + 2] = circleVerticesZ[i];
    }
    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 3, GL_FLOAT, 0, allCircleVertices );
    glDrawArrays( GL_LINE_STRIP, 0, numVertices );
    glDisableClientState( GL_VERTEX_ARRAY );
}

void drawCircle( GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides )
{
    GLint numberOfVertices = numberOfSides + 1;
    
    GLfloat doublePi = 2.0f * M_PI;
    
    GLfloat circleVerticesX[numberOfVertices];
    GLfloat circleVerticesY[numberOfVertices];
    GLfloat circleVerticesZ[numberOfVertices];

    
    
    //circleVerticesX[0] = x;
    //circleVerticesY[0] = y;
    //circleVerticesZ[0] = z;
    
    for ( int i = 0; i < numberOfVertices; i++ )
    {
        circleVerticesX[i] = x + ( radius * cos( i * doublePi / numberOfSides ) );
        circleVerticesY[i] = y + ( radius * sin( i * doublePi / numberOfSides ) );
        circleVerticesZ[i] = z;
    }
    
    GLfloat allCircleVertices[numberOfVertices * 3];
    
    for ( int i = 0; i < numberOfVertices; i++ )
    {
        allCircleVertices[i * 3] = circleVerticesX[i];
        allCircleVertices[( i * 3 ) + 1] = circleVerticesY[i];
        allCircleVertices[( i * 3 ) + 2] = circleVerticesZ[i];
    }
    
    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 3, GL_FLOAT, 0, allCircleVertices );
    glDrawArrays( GL_LINE_STRIP, 0, numberOfVertices );
    glDisableClientState( GL_VERTEX_ARRAY );
}
