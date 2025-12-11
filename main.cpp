#include "spacetime.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

spacetime::spacetime()
{
    gridesize = 10.0f;
    gridresulation = 50;
    camerax = 60.0f;   
    cameray = 0.0f;    
    cameradistant = 25.0f;
    m_leftd = m_rightd = false;
}

void spacetime::initilization()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    
    masses.clear();
    masses.push_back(masspoint(0.0f, 0.0f, 0.0f, 05.0f));

  
    lightray.clear();

    light ray;
    ray.startx = -12.0f;
    ray.starty = 1.0f;   
    ray.startz = 0.0f;
    ray.directionx = 1.0f;
    ray.directiony = 0.0f;
    ray.directionz = 0.0f;
    lightray.push_back(ray);

    tracelight();
}

GLfloat spacetime::calculategravity(GLfloat x, GLfloat y, GLfloat z)
{
    GLfloat potential = 0.0f;

    for (auto& mass : masses)
    {
        GLfloat dx = x - mass.x;
        GLfloat dy = y - mass.y;
        GLfloat dz = z - mass.z;

        GLfloat distance = sqrtf(dx * dx + dy * dy + dz * dz) + 1e-4f; 
        potential += -G * mass.mass / distance;
    }
    return potential;
}

void spacetime::claculategravityaccelaretion(GLfloat x, GLfloat y, GLfloat z,
    GLfloat& ax, GLfloat& ay, GLfloat& az)
{
    ax = ay = az = 0.0f;
    GLfloat epsilon = 0.05f;

    for (auto& mass : masses)
    {
        GLfloat dx = x - mass.x;
        GLfloat dy = y - mass.y;
        GLfloat dz = z - mass.z;

        GLfloat distance_sp = dx * dx + dy * dy + dz * dz + epsilon * epsilon;
        GLfloat distance = sqrtf(distance_sp);

        GLfloat force = G * mass.mass / (distance_sp * distance);

        GLfloat boost = 2.5f;
        ax -= dx * force * boost;
        ay -= dy * force * boost;
        az -= dz * force * boost;
    }
}

void spacetime::tracelight()
{
    const int     steps = 600;
    const GLfloat step_size = 0.05f;

    for (auto& ray : lightray)
    {
        ray.vertices.clear();

        GLfloat x = ray.startx;
        GLfloat y = ray.starty;
        GLfloat z = ray.startz;

        GLfloat dx = ray.directionx;
        GLfloat dy = ray.directiony;
        GLfloat dz = ray.directionz;

        GLfloat len = sqrtf(dx * dx + dy * dy + dz * dz);
        dx /= len; dy /= len; dz /= len;

        for (int i = 0; i < steps; ++i)
        {
            ray.vertices.push_back(x);
            ray.vertices.push_back(y);
            ray.vertices.push_back(z);

            GLfloat ax, ay, az;
            claculategravityaccelaretion(x, y, z, ax, ay, az);

            dx += ax * step_size;
            dy += ay * step_size;
            dz += az * step_size;

            len = sqrtf(dx * dx + dy * dy + dz * dz);
            dx /= len; dy /= len; dz /= len;

            x += dx * step_size;
            y += dy * step_size;
            z += dz * step_size;

            if (fabsf(x) > gridesize || fabsf(y) > gridesize || fabsf(z) > gridesize)
                break;
        }
    }
}

void spacetime::drawspacetimegride()
{
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);  
    glLineWidth(1.0f);

    const float potentialScale = -0.5f; 

    glBegin(GL_LINES);
    for (int i = -gridresulation / 2; i <= gridresulation / 2; ++i)
    {
        GLfloat x = (GLfloat)i / (gridresulation / 2) * gridesize;

        for (int j = -gridresulation / 2; j <= gridresulation / 2; ++j)
        {
            GLfloat y1 = (GLfloat)(j - 0.5f) / (gridresulation / 2) * gridesize;
            GLfloat y2 = (GLfloat)(j + 0.5f) / (gridresulation / 2) * gridesize;

            GLfloat plot1 = calculategravity(x, y1, 0.0f) * potentialScale;
            GLfloat plot2 = calculategravity(x, y2, 0.0f) * potentialScale;

            glVertex3f(x, y1, plot1);
            glVertex3f(x, y2, plot2);
        }

        for (int j = -gridresulation / 2; j <= gridresulation / 2; ++j)
        {
            GLfloat x1 = (GLfloat)(j - 0.5f) / (gridresulation / 2) * gridesize;
            GLfloat x2 = (GLfloat)(j + 0.5f) / (gridresulation / 2) * gridesize;
            GLfloat y = (GLfloat)i / (gridresulation / 2) * gridesize;

            GLfloat plot1 = calculategravity(x1, y, 0.0f) * potentialScale;
            GLfloat plot2 = calculategravity(x2, y, 0.0f) * potentialScale;

            glVertex3f(x1, y, plot1);
            glVertex3f(x2, y, plot2);
        }
    }
    glEnd();

    glEnable(GL_LIGHTING);
}

void spacetime::drawmassobjects()
{
    GLfloat lightpos[] = { 5.0f, 5.0f, 10.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

    for (auto& mass : masses)
    {
        GLfloat intensity = log10f(mass.mass + 1.0f) / 4.0f;
        intensity = fmaxf(0.3f, fminf(1.0f, intensity));

        GLfloat color[] = { intensity, intensity * 0.5f, 0.0f, 1.0f };
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

        GLfloat radius = mass.Rs;
        radius = fmaxf(0.5f, fminf(2.0f, radius));

        glPushMatrix();
        glTranslatef(mass.x, mass.y, mass.z);
        glutSolidSphere(radius, 32, 32);
        glPopMatrix();
    }
}

void spacetime::drawlightrays()
{
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 0.0f); 
    glLineWidth(3.0f);

    for (auto& ray : lightray)
    {
        glBegin(GL_LINE_STRIP);
        for (size_t i = 0; i < ray.vertices.size(); i += 3)
        {
            glVertex3f(ray.vertices[i],
                ray.vertices[i + 1],
                ray.vertices[i + 2]);
        }
        glEnd();
    }
    glEnable(GL_LIGHTING);
}

void spacetime::display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -cameradistant);
    glRotatef(camerax, 1.0f, 0.0f, 0.0f);
    glRotatef(cameray, 0.0f, 1.0f, 0.0f);

    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(3.0f, 0.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 3.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 3.0f);
    glEnd();
    glEnable(GL_LIGHTING);

    drawspacetimegride();
    drawmassobjects();
    drawlightrays();

    glutSwapBuffers();
}

void spacetime::reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void spacetime::keyboad(unsigned char key, int x, int y)
{
    if (key == 'r' || key == 'R')
    {
        tracelight();
    }
    else if (key == 'a' || key == 'A')
    {
        cameray -= 5.0f;
    }
    else if (key == 'd' || key == 'D')
    {
        cameray += 5.0f;
    }
    else if (key == 'w' || key == 'W')
    {
        camerax -= 5.0f;
    }
    else if (key == 's' || key == 'S')   
    {
        cameradistant += 1.0f;
    }
    else if (key == 'e' || key == 'E')   
    {
        cameradistant = fmaxf(5.0f, cameradistant - 1.0f);
    }
    else if (key == 'q' || key == 'Q')   
    {
        cameradistant += 1.0f;
    }
    else if (key == 27)                  
    {
        exit(0);
    }

    glutPostRedisplay();
}

void spacetime::mouse(int botton, int state, int x, int y)
{
    mx = x; my = y;

    if (botton == GLUT_LEFT_BUTTON)
    {
        m_leftd = (state == GLUT_DOWN);
    }
    else if (botton == GLUT_RIGHT_BUTTON)
    {
        m_rightd = (state == GLUT_DOWN);
    }
}

void spacetime::motion(int x, int y)
{
    if (m_leftd)
    {
        cameray += (x - mx) * 0.5f;
        camerax += (y - my) * 0.5f;
    }
    if (m_rightd)
    {
        cameradistant += (y - my) * 0.1f;
    }
    mx = x;
    my = y;

    glutPostRedisplay();
}

spacetime ob;

void displaywrapper() { ob.display(); }
void reshapewarred(int w, int h) { ob.reshape(w, h); }
void keyboardwara(unsigned char key, int x, int y) { ob.keyboad(key, x, y); }
void mousewarsd(int botton, int state, int x, int y) { ob.mouse(botton, state, x, y); }
void motionwarsds(int x, int y) { ob.motion(x, y); }

int main(int argv, char** argc)
{
    glutInit(&argv, argc);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(900, 800);
    glutCreateWindow("DUE TO GRAVITATIONAL FORCE SPACE CURVE");

    ob.initilization();

    glutDisplayFunc(displaywrapper);
    glutReshapeFunc(reshapewarred);
    glutKeyboardFunc(keyboardwara);
    glutMouseFunc(mousewarsd);
    glutMotionFunc(motionwarsds);

    std::cout << "Controls:\n";
    std::cout << "Mouse: Rotate view (LMB)\n";
    std::cout << "Right mouse: Zoom\n";
    std::cout << "WASD: Camera rotation\n";
    std::cout << "Q / S : Zoom out\n";
    std::cout << "E     : Zoom in\n";
    std::cout << "R     : Retrace light rays\n";
    std::cout << "ESC   : Exit\n";

    glutMainLoop();
    return 0;
}
