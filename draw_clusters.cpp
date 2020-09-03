#include "draw_clusters.h"
#include "pointvector.h"
#include <GL/freeglut.h>
#include <math.h>
#include <vector>
#include <iostream>

Draw_Clusters::Draw_Clusters(){}
Draw_Clusters::~Draw_Clusters(){}

std::vector<Point> temp; //znam da je globalna varijabla, ali za openGL se preporuča

void draw_circle(float x, float y, float radius,int color) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(x, y, 0.0f);

    static const int circle_points = 100;
    static const float angle = 2.0f * 3.1416f / circle_points;

    glBegin(GL_POLYGON);

    //boja ovisno o clusteru
    if(color == 0) glColor3f(1.0f, 0.0f, 0.0f);
    if(color == 1) glColor3f(0.0f, 1.0f, 0.0f);
    if(color == 2) glColor3f(0.0f, 0.0f, 1.0f);
    if(color == 3) glColor3f(1.0f, 1.0f, 0.0f);
    if(color == 4) glColor3f(0.0f, 1.0f, 1.0f);
    if(color == 5) glColor3f(1.0f, 0.0f, 1.0f);
    if(color == 6) glColor3f(1.0f, 1.0f, 1.0f);
    if(color == 7) glColor3f(0.5f, 0.5f, 0.5f);

    double angle1=0.0;
    glVertex2d(radius * cos(0.0) , radius * sin(0.0));
    int i;
    //crtanje kruga
    for (i=0; i<circle_points; i++){
        glVertex2d(radius * cos(angle1), radius *sin(angle1));
        angle1 += angle;
    }
    glEnd();

    glPopMatrix();
}

void display() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // black BG color
   glClear(GL_COLOR_BUFFER_BIT);


   for(Point&pt : temp){
   // crtanje točke na lokaciji iz vektora
   draw_circle((pt.x-60)/100,(pt.y-50)/100,0.02, pt.cluster);
   }

   glFlush();  //renderiraj
}

int Draw_Clusters::paint_up(int argc, char** argv, std::vector<Point>* points) {
   glutInit(&argc, argv);     //  init

   glutCreateWindow("KMeans Preview"); // title
   glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
   glutInitWindowSize(320, 320);   // width/height
   glutInitWindowPosition(200, 200); // Position the window's initial top-left corner
   temp = *points;
   glutDisplayFunc(display); // re-paint
   glutMainLoop();           // loop
   return 0;
}
