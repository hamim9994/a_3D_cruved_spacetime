#ifndef SPACETIME_H
#define SPACETIME_H

#include <GL/freeglut.h>
#include <vector>
#include <cmath>

using namespace std;

const float G = 1.0f;
const float c = 1.0f;
const float c2 = 1.0f;

struct masspoint
{
    float   x, y, z;
    float   mass;
    float   Rs;

    masspoint(float px, float py, float pz, float m)
    {
        x = px;
        y = py;
        z = pz;
        mass = m;

        Rs = 0.5f * sqrtf(mass);
    }
};

struct light {
    std::vector<GLfloat> vertices;
    GLfloat startx, starty, startz;
    GLfloat directionx, directiony, directionz;
};

class spacetime
{
private:
    std::vector<masspoint> masses;
    std::vector<light>     lightray;
    GLfloat gridesize;
    int     gridresulation;

    
    GLfloat camerax, cameray;
    GLfloat cameradistant;
    int     mx, my;
    bool    m_leftd, m_rightd;

public:
    spacetime();
    void initilization();
    void display();
    void reshape(int w, int h);
    void keyboad(unsigned char key, int x, int y);
    void mouse(int botton, int state, int x, int y);
    void motion(int x, int y);

    void tracelight();
    void drawspacetimegride();
    void drawmassobjects();
    void drawlightrays();

    GLfloat calculategravity(GLfloat x, GLfloat y, GLfloat z);
    void claculategravityaccelaretion(GLfloat x, GLfloat y, GLfloat z,
        GLfloat& ax, GLfloat& ay, GLfloat& az);
};

#endif
