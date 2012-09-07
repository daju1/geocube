///////////////////////////////////////////////////////////////////////////////
// stencilTess.cpp
// ===============
// Tessellation with Stencil buffer fill technique
// It produces exactly same effect as tessellation without using tessellator.
// 
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2006-03-01
// UPDATED: 2006-03-03
///////////////////////////////////////////////////////////////////////////////

#include <GL/glut.h>
#include <iostream>
#include <sstream>
#include <iomanip>

using std::stringstream;
using std::cout;
using std::cerr;
using std::endl;
using std::ends;



// GLUT CALLBACK functions ////////////////////////////////////////////////////
void displayCB();
void reshapeCB(int w, int h);
void timerCB(int millisec);
void idleCB();
void keyboardCB(unsigned char key, int x, int y);
void mouseCB(int button, int stat, int x, int y);
void mouseMotionCB(int x, int y);



// function declarations //////////////////////////////////////////////////////
void initGL();
int  initGLUT(int argc, char **argv);
bool initSharedMem();
void clearSharedMem();
void initLights();
void setCamera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ);
void drawString(const char *str, int x, int y, float color[4], void *font);
void drawString3D(const char *str, float pos[3], float color[4], void *font);
void showInfo();
void draw1();
void draw2();
void draw3();



// constants //////////////////////////////////////////////////////////////////
const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 200;




// global variables ///////////////////////////////////////////////////////////
void *font = GLUT_BITMAP_8_BY_13;
bool mouseLeftDown;
bool mouseRightDown;
float mouseX, mouseY;
float cameraAngleX;
float cameraAngleY;
float cameraDistance;
int drawMode = 0;
int stencilBits;


///////////////////////////////////////////////////////////////////////////////
// draw a simple concave quad
///////////////////////////////////////////////////////////////////////////////
void draw1()
{
    // define concave quad data (vertices only)
    //  0    2
    //  \ \/ /
    //   \3 /
    //    \/
    //    1
    GLdouble quad1[4][3] = { {-1,3,0}, {0,0,0}, {1,3,0}, {0,2,0} };

    // We are going to do 2-pass draw: draw to stencil buffer first,
    // then draw to color buffer.
    glEnable(GL_STENCIL_TEST);          // enable stencil test

    // PASS 1: draw to stencil buffer only
    // The reference value will be written to the stencil buffer plane if test passed
    // The stencil buffer is initially set to all 0s.
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); // disable writing to color buffer
    glStencilFunc(GL_ALWAYS, 0x1, 0x1);
    glStencilOp(GL_KEEP, GL_INVERT, GL_INVERT);

    glBegin(GL_TRIANGLE_FAN);
        glVertex3dv(quad1[0]);
        glVertex3dv(quad1[1]);
        glVertex3dv(quad1[2]);
        glVertex3dv(quad1[3]);
    glEnd();


    // PASS 2: draw color buffer
    // Draw again the exact same polygon to color buffer where the stencil
    // value is only odd number(1). The even(0) area will be descarded.
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);    // enable writing to color buffer
    glStencilFunc(GL_EQUAL, 0x1, 0x1);                  // test if it is odd(1)
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    glColor3f(1,1,1);
    glBegin(GL_TRIANGLE_FAN);
        glVertex3dv(quad1[0]);
        glVertex3dv(quad1[1]);
        glVertex3dv(quad1[2]);
        glVertex3dv(quad1[3]);
    glEnd();

    glDisable(GL_STENCIL_TEST);
}



///////////////////////////////////////////////////////////////////////////////
// draw a polygon with a hole
///////////////////////////////////////////////////////////////////////////////
void draw2()
{
    // define concave quad with a hole
    //  0--------3
    //  | 4----7 |
    //  | |    | |
    //  | 5----6 |
    //  1--------2
    GLdouble quad2[8][3] = { {-2,3,0}, {-2,0,0}, {2,0,0}, { 2,3,0},
                             {-1,2,0}, {-1,1,0}, {1,1,0}, { 1,2,0} };

    glEnable(GL_STENCIL_TEST);          // enable stencil test

    // PASS 1: draw to stencil buffer only
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); // disable writing to color buffer
    glStencilFunc(GL_ALWAYS, 0x1, 0x1);
    glStencilOp(GL_KEEP, GL_INVERT, GL_INVERT);

    // outer contour
    glBegin(GL_TRIANGLE_FAN);
        glVertex3dv(quad2[0]);
        glVertex3dv(quad2[1]);
        glVertex3dv(quad2[2]);
        glVertex3dv(quad2[3]);
    glEnd();
    //inner contour
    glBegin(GL_TRIANGLE_FAN);
        glVertex3dv(quad2[4]);
        glVertex3dv(quad2[5]);
        glVertex3dv(quad2[6]);
        glVertex3dv(quad2[7]);
    glEnd();

    // PASS 2: draw color buffer
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);    // enable writing to color buffer
    glStencilFunc(GL_EQUAL, 0x1, 0x1);                  // test if it is odd(1)
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    glColor3f(1,1,1);

    // outer contour
    glBegin(GL_TRIANGLE_FAN);
        glVertex3dv(quad2[0]);
        glVertex3dv(quad2[1]);
        glVertex3dv(quad2[2]);
        glVertex3dv(quad2[3]);
    glEnd();
    //inner contour
    glBegin(GL_TRIANGLE_FAN);
        glVertex3dv(quad2[4]);
        glVertex3dv(quad2[5]);
        glVertex3dv(quad2[6]);
        glVertex3dv(quad2[7]);
    glEnd();
}



///////////////////////////////////////////////////////////////////////////////
// draw a self-intersecting polygon (star)
///////////////////////////////////////////////////////////////////////////////
void draw3()
{
    // define self-intersecting star shape (with color)
    //      0
    //     / \
    //3---+---+---2
    //  \ |   | /
    //   \|   |/
    //    +   +
    //    |\ /|
    //    | + |
    //    |/ \|
    //    1   4
    GLdouble star[5][6] = { { 0.0, 3.0, 0,  1, 0, 0},       // 0: x,y,z,r,g,b
                            {-1.0, 0.0, 0,  0, 1, 0},       // 1:
                            { 1.6, 1.9, 0,  1, 0, 1},       // 2:
                            {-1.6, 1.9, 0,  1, 1, 0},       // 3:
                            { 1.0, 0.0, 0,  0, 0, 1} };     // 4:

    glEnable(GL_STENCIL_TEST);          // enable stencil test

    // PASS 1: draw to stencil buffer only
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); // disable writing to color buffer
    glStencilFunc(GL_ALWAYS, 0x1, 0x1);
    glStencilOp(GL_KEEP, GL_INVERT, GL_INVERT);

    glBegin(GL_TRIANGLE_FAN);
        glColor3dv(star[0]+3);
        glVertex3dv(star[0]);
        glColor3dv(star[1]+3);
        glVertex3dv(star[1]);
        glColor3dv(star[2]+3);
        glVertex3dv(star[2]);
        glColor3dv(star[3]+3);
        glVertex3dv(star[3]);
        glColor3dv(star[4]+3);
        glVertex3dv(star[4]);
    glEnd();

    // PASS 2: draw color buffer
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);    // enable writing to color buffer
    glStencilFunc(GL_EQUAL, 0x1, 0x1);                  // test if it is odd(1)
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    glColor3f(1,1,1);
    glDisable(GL_DEPTH_TEST);

    glBegin(GL_TRIANGLE_FAN);
        glColor3dv(star[0]+3);
        glVertex3dv(star[0]);
        glColor3dv(star[1]+3);
        glVertex3dv(star[1]);
        glColor3dv(star[2]+3);
        glVertex3dv(star[2]);
        glColor3dv(star[3]+3);
        glVertex3dv(star[3]);
        glColor3dv(star[4]+3);
        glVertex3dv(star[4]);
    glEnd();

    glEnable(GL_DEPTH_TEST);

}



///////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
    initSharedMem();

    // init GLUT and GL
    initGLUT(argc, argv);
    initGL();

    // make sure stencil buffer is existed
    glGetIntegerv(GL_STENCIL_BITS, &stencilBits);
    if(stencilBits < 1)
        cout << "ERROR: No stencil buffer!" << endl;

    // the last GLUT call (LOOP)
    // window will be shown and display callback is triggered by events
    // NOTE: this call never return main().
    glutMainLoop(); /* Start GLUT event-processing loop */

    return 0;
}



///////////////////////////////////////////////////////////////////////////////
// initialize GLUT for windowing
///////////////////////////////////////////////////////////////////////////////
int initGLUT(int argc, char **argv)
{
    // GLUT stuff for windowing
    // initialization openGL window.
    // it is called before any other GLUT routine
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);   // display mode

    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT); // window size

    glutInitWindowPosition(100, 100);           // window location

    // finally, create a window with openGL context
    // Window will not displayed until glutMainLoop() is called
    // it returns a unique ID
    int handle = glutCreateWindow(argv[0]);     // param is the title of window

    // register GLUT callback functions
    glutDisplayFunc(displayCB);
    glutTimerFunc(33, timerCB, 33);             // redraw only every given millisec
    //glutIdleFunc(idleCB);                       // redraw only every given millisec
    glutReshapeFunc(reshapeCB);
    glutKeyboardFunc(keyboardCB);
    glutMouseFunc(mouseCB);
    glutMotionFunc(mouseMotionCB);

    return handle;
}



///////////////////////////////////////////////////////////////////////////////
// initialize OpenGL
// disable unused features
///////////////////////////////////////////////////////////////////////////////
void initGL()
{
    glShadeModel(GL_SMOOTH);                    // shading mathod: GL_SMOOTH or GL_FLAT
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);      // 4-byte pixel alignment

    // enable /disable features
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    //glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    //glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    //glEnable(GL_CULL_FACE);

     // track material ambient and diffuse from surface color, call it before glEnable(GL_COLOR_MATERIAL)
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glClearColor(0, 0, 0, 0);                   // background color
    glClearStencil(0);                          // clear stencil buffer
    glClearDepth(1.0f);                         // 0 is near, 1 is far
    glDepthFunc(GL_LEQUAL);

    // enable stencil buffer test
    glClearStencil(0x0);

    //initLights();
    setCamera(0, 0, 5, 0, 0, 0);
}



///////////////////////////////////////////////////////////////////////////////
// write 2d text using GLUT
// The projection matrix must be set to orthogonal before call this function.
///////////////////////////////////////////////////////////////////////////////
void drawString(const char *str, int x, int y, float color[4], void *font)
{
    glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
    glDisable(GL_LIGHTING);     // need to disable lighting for proper text color

    glColor4fv(color);          // set text color
    glRasterPos2i(x, y);        // place text position

    // loop all characters in the string
    while(*str)
    {
        glutBitmapCharacter(font, *str);
        ++str;
    }

    glEnable(GL_LIGHTING);
    glPopAttrib();
}



///////////////////////////////////////////////////////////////////////////////
// draw a string in 3D space
///////////////////////////////////////////////////////////////////////////////
void drawString3D(const char *str, float pos[3], float color[4], void *font)
{
    glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
    glDisable(GL_LIGHTING);     // need to disable lighting for proper text color

    glColor4fv(color);          // set text color
    glRasterPos3fv(pos);        // place text position

    // loop all characters in the string
    while(*str)
    {
        glutBitmapCharacter(font, *str);
        ++str;
    }

    glEnable(GL_LIGHTING);
    glPopAttrib();
}



///////////////////////////////////////////////////////////////////////////////
// initialize global variables
///////////////////////////////////////////////////////////////////////////////
bool initSharedMem()
{
    mouseLeftDown = mouseRightDown = false;
    return true;
}



///////////////////////////////////////////////////////////////////////////////
// clean up shared memory
///////////////////////////////////////////////////////////////////////////////
void clearSharedMem()
{
}



///////////////////////////////////////////////////////////////////////////////
// initialize lights
///////////////////////////////////////////////////////////////////////////////
void initLights()
{
    // set up light colors (ambient, diffuse, specular)
    GLfloat lightKa[] = {.2f, .2f, .2f, 1.0f};  // ambient light
    GLfloat lightKd[] = {.7f, .7f, .7f, 1.0f};  // diffuse light
    GLfloat lightKs[] = {1, 1, 1, 1};           // specular light
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightKa);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightKd);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightKs);

    // position the light
    float lightPos[4] = {0, 0, 20, 1}; // positional light
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    glEnable(GL_LIGHT0);                        // MUST enable each light source after configuration
}



///////////////////////////////////////////////////////////////////////////////
// set camera position and lookat direction
///////////////////////////////////////////////////////////////////////////////
void setCamera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(posX, posY, posZ, targetX, targetY, targetZ, 0, 1, 0); // eye(x,y,z), focal(x,y,z), up(x,y,z)
}



///////////////////////////////////////////////////////////////////////////////
// display info messages
///////////////////////////////////////////////////////////////////////////////
void showInfo()
{
    // backup current model-view matrix
    glPushMatrix();                     // save current modelview matrix
    glLoadIdentity();                   // reset modelview matrix

    // set to 2D orthogonal projection
    glMatrixMode(GL_PROJECTION);     // switch to projection matrix
    glPushMatrix();                  // save current projection matrix
    glLoadIdentity();                // reset projection matrix
    gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);  // set to orthogonal projection

    float color[4] = {1, 1, 1, 1};

    stringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss << "Stencil Buffer Bits: " << stencilBits << ends;
    drawString(ss.str().c_str(), 1, 486, color, font);
    ss.str("");

    // unset floating format
    ss << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);

    // restore projection matrix
    glPopMatrix();                   // restore to previous projection matrix

    // restore modelview matrix
    glMatrixMode(GL_MODELVIEW);      // switch to modelview matrix
    glPopMatrix();                   // restore to previous modelview matrix
}



//=============================================================================
// CALLBACKS
//=============================================================================

void displayCB()
{
    // clear buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // save the initial ModelView matrix before modifying ModelView matrix
    glPushMatrix();

    // tramsform camera
    glTranslatef(0, 0, cameraDistance);
    glRotatef(cameraAngleX, 1, 0, 0);   // pitch
    glRotatef(cameraAngleY, 0, 1, 0);   // heading


    // draw meshes
    glTranslatef(-4, -1.5f,0);
    draw1();

    glTranslatef(4,0,0);
    draw2();

    glTranslatef(4,0,0);
    draw3();



    // draw info messages
    showInfo();

    glPopMatrix();

    glutSwapBuffers();
}


void reshapeCB(int w, int h)
{
    // set viewport to be the entire window
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    // set perspective viewing frustum
    float aspectRatio = (float)w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glFrustum(-aspectRatio, aspectRatio, -1, 1, 1, 100);
    gluPerspective(60.0f, (float)(w)/h, 1.0f, 1000.0f); // FOV, AspectRatio, NearClip, FarClip

    // switch to modelview matrix in order to set scene
    glMatrixMode(GL_MODELVIEW);
}


void timerCB(int millisec)
{
    glutTimerFunc(millisec, timerCB, millisec);
    glutPostRedisplay();
}


void idleCB()
{
    glutPostRedisplay();
}


void keyboardCB(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 27: // ESCAPE
        clearSharedMem();
        exit(0);
        break;

    case ' ':
        break;

    case 'd': // switch rendering modes (fill -> wire -> point)
    case 'D':
        drawMode = ++drawMode % 3;
        if(drawMode == 0)        // fill mode
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glEnable(GL_DEPTH_TEST);
            //glEnable(GL_CULL_FACE);
        }
        else if(drawMode == 1)  // wireframe mode
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDisable(GL_DEPTH_TEST);
            //glDisable(GL_CULL_FACE);
        }
        else                    // point mode
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            glDisable(GL_DEPTH_TEST);
            //glDisable(GL_CULL_FACE);
        }
        break;

    default:
        ;
    }

    glutPostRedisplay();
}


void mouseCB(int button, int state, int x, int y)
{
    mouseX = x;
    mouseY = y;

    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseLeftDown = true;
        }
        else if(state == GLUT_UP)
            mouseLeftDown = false;
    }

    else if(button == GLUT_RIGHT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseRightDown = true;
        }
        else if(state == GLUT_UP)
            mouseRightDown = false;
    }
}


void mouseMotionCB(int x, int y)
{
    if(mouseLeftDown)
    {
        cameraAngleY += (x - mouseX);
        cameraAngleX += (y - mouseY);
        mouseX = x;
        mouseY = y;
    }
    if(mouseRightDown)
    {
        cameraDistance += (y - mouseY) * 0.2f;
        mouseY = y;
    }

    //glutPostRedisplay();
}



