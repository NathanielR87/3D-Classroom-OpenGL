/*
 *  3D Objects
 *
 *  Demonstrates how to draw objects in 3D.
 *
 *  Key bindings:
 *  m/M        Cycle through different sets of objects
 *  a          Toggle axes
 *  arrows     Change view angle
 *  0          Reset view angle
 *  ESC        Exit
 */
#include "CSCIx229.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#ifdef USEGLEW
#include <GL/glew.h>
#endif
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
// Tell Xcode IDE to not gripe about OpenGL deprecation
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#else
#include <GL/glut.h>
#endif
//  Default resolution
//  For Retina displays compile with -DRES=2
#ifndef RES
#define RES 1
#endif

int th=0;          //  Azimuth of view angle
int ph=0;          //  Elevation of view angle

int theta = 0;//can be 0 or 180 its just rotation


int axes=1;        //  Display axes
int mode=0;        //  What to display
int per_mode = 0;
int tex_mode = 0;
int ntex=0;   
int fov=100;       //  Field of view (for perspective)
double dim=50;   //  Size of world
double asp=1;     //  Aspect ratio
double Dx = 0;
double Dy = 0;
double Dz = -4;

double Cx = 0;
double Cy = 0;
double Cz = 0;
const char* text[] = {"Atom","Lolipop","Prism","Scene"};
// Light values
int move=1;       //  Move light
int light     =   1;  // Lighting
int one       =   1;  // Unit value
int distance  =   5;  // Light distance
int inc       =  10;  // Ball increment
int smooth    =   1;  // Smooth/Flat shading
int local     =   0;  // Local Viewer Model
int emission  =   0;  // Emission intensity (%)
int ambient   =  10;  // Ambient intensity (%)
int diffuse   =  50;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   5;  // Shininess (power of two)
float shiny   =   5;  // Shininess (value)
int zh        =  90;  // Light azimuth
float ylight  =   0;  // Elevation of light
typedef struct {float x,y,z;} vtx;
typedef struct {int A,B,C;} tri;
unsigned int texture[20]; // Texture names

#define PI 3.1415927





/*
 *  Check for OpenGL errors
 */





/*
 *  Draw a cube
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */

static void cube2(unsigned int tex,double x,double y,double z,double dx,double dy, double dz, double th, double xx,double zz)
{
    //  Set specular color to white
   float white[] = {1,1,1,1};
   float black[] = {0,0,0,1};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
   //  Save transformation
   glPushMatrix();
   //  Offset
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glRotated(xx,1,0,0);
   glRotated(zz,0,0,1); 
   glScaled(dx,dy,dz);

   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,tex_mode?GL_REPLACE:GL_MODULATE);
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,tex);


   //  Cube
   
   //  Front
   if (ntex) glBindTexture(GL_TEXTURE_2D,tex);
   glBegin(GL_QUADS);
   glColor3f(0,0,0);
   glNormal3f( 0, 0, 1);
   glTexCoord2f(0,0); glVertex3f(-1,-1, 1);
   glTexCoord2f(1,0); glVertex3f(+1,-1, 1);
   glColor3f(1,1,1);
   glTexCoord2f(1,1); glVertex3f(+1,+1, 1);
   glTexCoord2f(0,1); glVertex3f(-1,+1, 1);
   glEnd();
   //  Back
   if (ntex) glBindTexture(GL_TEXTURE_2D,tex);
   glBegin(GL_QUADS);
   glColor3f(0,0,0);
   glNormal3f( 0, 0,-1);
   glTexCoord2f(0,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(1,0); glVertex3f(-1,-1,-1);
   glColor3f(1,1,1);
   glTexCoord2f(1,1); glVertex3f(-1,+1,-1);
   glTexCoord2f(0,1); glVertex3f(+1,+1,-1);
   glEnd();
   //  Right
   if (ntex) glBindTexture(GL_TEXTURE_2D,tex);
   glBegin(GL_QUADS);
   glColor3f(0,0,0);
   glNormal3f(+1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(+1,-1,+1);
   glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
   glColor3f(1,1,1);
   glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
   glTexCoord2f(0,1); glVertex3f(+1,+1,+1);
   glEnd();

   //  Left
   if (ntex) glBindTexture(GL_TEXTURE_2D,tex);
   glBegin(GL_QUADS);
   glColor3f(0,0,0);
   glNormal3f(-1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(1,0); glVertex3f(-1,-1,+1);
   glColor3f(1,1,1);
   glTexCoord2f(1,1); glVertex3f(-1,+1,+1);
   glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
   glEnd();
   //  Top
   if (ntex) glBindTexture(GL_TEXTURE_2D,tex);
   glBegin(GL_QUADS);
   glColor3f(0,0,0);
   glNormal3f( 0,+1, 0);
   glTexCoord2f(0,0); glVertex3f(-1,+1,+1);
   glTexCoord2f(1,0); glVertex3f(+1,+1,+1);
   glColor3f(1,1,1);
   glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
   glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
   glEnd();
   //  Bottom
   if (ntex) glBindTexture(GL_TEXTURE_2D,tex);
   glBegin(GL_QUADS);
   glColor3f(0,0,0);
   glNormal3f( 0,-1, 0);
   glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
   glColor3f(1,1,1);
   glTexCoord2f(1,1); glVertex3f(+1,-1,+1);
   glTexCoord2f(0,1); glVertex3f(-1,-1,+1);
   //  End
   glEnd();
   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}


static void room(double x,double y,double z,double dx,double dy,double dz,double th){
   glPushMatrix();
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);

   //right
   cube2(texture[0],-25,0,0, .001,25,25, 0,0, 0);
   //back
   cube2(texture[0],0,0,25, 25,25,.001, 0,0, 0);
   //left
   cube2(texture[0],25,0,0, .001,25,25, 0,0, 0);
   // WordWall
   cube2(texture[9],24,1,1, .001,10,10, 0,0, 0);
   //front
   cube2(texture[0],0,0,-25, 25,25,.001, 0,0, 0);
   //floor
   cube2(texture[2],0,-25,0, 25,.001,25, 0,0, 0);
   //SchoolRug
   cube2(texture[7],0,-24,0, 8,.001,8, 0,0, 0);
   //celing
   cube2(texture[10],0,25,0, 25,.001,25, 0,0, 0);

   glPopMatrix();
}

void leg(double x,double y,double z, double dx, double dy, double dz, double th)
{
   glPushMatrix();
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScalef(dx,dy,dz);
   glColor3f(1,1,1);
   glutSolidCube(1.0);
   glPopMatrix();
}

void desk(double x,double y,double z, double dx, double dy, double dz, double th)
{
    glPushMatrix();
    glTranslated(x,y,z);
    glRotated(th,0,1,0);
    glScaled(dx,dy,dz);

    cube2(texture[1],0,5,0, 20,1,10 , 0,0, 0);
    
    //leggs

    cube2(texture[6],-15,-7,7, 1,12,1, 0,0,0);
    cube2(texture[6],-15,-20,0, 1,1,8, 0,0,0);
    cube2(texture[6],-15,-7,-7, 1,12,1, 0,0,0);

    cube2(texture[6],15,-7,7, 1,12,1, 0,0,0);
    cube2(texture[6],15,-20,0, 1,1,8, 0,0,0);
    cube2(texture[6],15,-7,-7, 1,12,1, 0,0,0);


    glPopMatrix();
}



//https://gist.github.com/nikAizuddin/5ea402e9073f1ef76ba6
#define PI 3.1415927
void draw_cylinder(unsigned int tex, double radius, double height, double x, double y, double z, double dx, double dy, double dz, double th, double zz)
{
   glPushMatrix();
   //default variables
   double angle = 0.0;
   double angle_stepsize = 0.1;

   glTranslated(x,y,z);
   glRotated(zz,0,0,1);
   glRotated(th,1,0,0);
   
   glScaled(dx,dy,dz);

   //Enable Texture
   glEnable(GL_TEXTURE_2D);

    /** Draw the tube */
    glColor3ub(160,82,45);
    glBindTexture(GL_TEXTURE_2D, tex);
    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
        while( angle < 2*PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glNormal3f(cos(angle),sin(angle),0);
            const float tc = angle / (float)(2 * PI);
            glTexCoord2f(tc , 1.0);
            glVertex3f(x, y , height);
            glTexCoord2f(tc, 0.0);
            glVertex3f(x, y , 0.0);
            angle = angle + angle_stepsize;
        }
        glTexCoord2f(0.0, 1.0);
        glVertex3f(radius, 0.0, height);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(radius, 0.0, 0.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    /** Draw the circle on top of cylinder */
    glColor3ub(0,0,0);
    glBegin(GL_POLYGON);
    angle = 0.0;
        while( angle < 2*PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x, y , height);
            glNormal3f(0, 1, 0);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, height);
    glEnd();
    glPopMatrix();
}


static void ball(double x,double y,double z,double r)
{
   //  Set specular color to white
   float white[] = {1,1,1,1};
   float black[] = {0,0,0,1};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,1);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   
   glColor3f(1,1,1);
   glutSolidSphere(1.0,16,16);
   //  Undo transofrmations
   
   glPopMatrix();
}



void chair(double x,double y,double z, double dx, double dy, double dz, double th, double zz)
{
   glPushMatrix();
   //  Offset
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glRotated(zz,0,0,1);
   glScaled(dx,dy,dz);

   //seat
   cube2(texture[11],0,-8,0, 8,1.5,10, 0,0,0);
   ///back support
   cube2(texture[11],0,4,10, 8,12,1.5, 0,0,0);


   cube2(texture[6], 4, -15, -4, 1, 6, 1, 0, 0, 0); // front right leg
   cube2(texture[6], -4, -15, -4, 1, 6, 1, 0, 0, 0); // front left leg
   cube2(texture[6], 4, -15, 4, 1, 6, 1, 0, 0, 0);   // back right leg
   cube2(texture[6], -4, -15, 4, 1, 6, 1, 0, 0, 0);  // back left leg


   glPopMatrix();

}


void notebook(double x, double y, double z, double dx, double dy, double dz, double th)
{
    glPushMatrix();
    //  Offset
    glTranslated(x, y, z);
    glRotated(th, 0, 1, 0);
    glScaled(dx, dy, dz);

    // notebook cover
    cube2(texture[12], 0, 0, 0, 5, 0.2, 7, 0, 0, 0);

    // notebook pages
    cube2(texture[16], 0, 0, 0, 5, 0.2, 7, 0, 0, 0);

    glPopMatrix();
}

void pencil(double x, double y, double z, double dx, double dy, double dz, double th)
{
    glPushMatrix();
    //  Offset
    glTranslated(x, y, z);
    glRotated(th, 0, 1, 0);
    glScaled(dx, dy, dz);

    // pencil body
    cube2(texture[13], 0, 0, 0, 0.2, 0.2, 5, 0, 0, 0);

    // eraser
    cube2(texture[14], 0, 0.2, 0, 0.3, 0.1, 0.3, 0, 0, 0);

    glPopMatrix();
}

static void Vertex(double th,double ph)
{
  double x = Sin(th)*Cos(ph);
  double y = Cos(th)*Cos(ph);
  double z =         Sin(ph);

  glNormal3d(x,y,z);
  glTexCoord2d(th/360.0,ph/180.0+0.5);
  glVertex3d(x,y,z);
}

static void oval(unsigned int tex, double x,double y,double z, double dx, double dy, double dz, double th, double xx, double zz)
{
   //  Set specular color to white
   float white[] = {1,1,1,1};
   float black[] = {0,0,0,1};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,1);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glRotated(xx,1,0,0); 
   glRotated(zz,0,0,1); 
   glScaled(dx,dy,dz);

   glColor3f(1,1,1);
   
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D,tex);
   
   for (int ph=-90;ph<90;ph+=5)
   {
      glBegin(GL_QUAD_STRIP);
      for (int th=0;th<=360;th+=5)
      {
         Vertex(th,ph);
         Vertex(th,ph+5);
      }
      glEnd();
   }
   //  Undo transofrmations

   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}







void ChalkWall(double x,double y,double z, double dx, double dy, double dz, double th, double zz){
   glPushMatrix();
   //  Offset
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glRotated(zz,0,0,1); 
   glScaled(dx,dy,dz);

   cube2(texture[8],-10,-10,0, 40,20,.001, 0,0, 0);

   glPopMatrix();
}

//https://community.khronos.org/t/half-sphere/49408/2
void drawHalfSphere(int R, int g, int b, int scaley, int scalex, GLfloat r, double x,double y,double z, double dx, double dy, double dz, double th, double zz) {

   glPushMatrix();
   //  Offset
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glRotated(zz,0,0,1); 
    
   glScaled(dx,dy,dz);


   int i, j;
   GLfloat v[scalex*scaley][3];

   glColor3f(R,g,b); 

   for (i=0; i<scalex; ++i) {
     for (j=0; j<scaley; ++j) {
       v[i*scaley+j][0]=r*cos(j*2*M_PI/scaley)*cos(i*M_PI/(2*scalex));
       v[i*scaley+j][1]=r*sin(i*M_PI/(2*scalex));
       v[i*scaley+j][2]=r*sin(j*2*M_PI/scaley)*cos(i*M_PI/(2*scalex));
     }
   }

   glBegin(GL_QUADS);
     for (i=0; i<scalex-1; ++i) {
       for (j=0; j<scaley; ++j) {
         glVertex3fv(v[i*scaley+j]);
         glVertex3fv(v[i*scaley+(j+1)%scaley]);
         glVertex3fv(v[(i+1)*scaley+(j+1)%scaley]);
         glVertex3fv(v[(i+1)*scaley+j]);
       }
     }
   glEnd();
   glPopMatrix();
 }

void lamp(double x,double y,double z, double dx, double dy, double dz, double th, double zz){
   glPushMatrix();
   //  Offset
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glRotated(zz,0,0,1); 
   glScaled(dx,dy,dz);

   oval(texture[4], 0,-10,0, 10,1,10, 90,0,0);
   draw_cylinder(texture[6], 1,30, 0,-9,0, 1,1,1, -90,0);
   drawHalfSphere(1,1,1, 24, 24, 2, 0,14,0, 8,4,8, 0,0);

   glPopMatrix();
}



void window(double x,double y,double z, double dx, double dy, double dz, double th, double zz){
   glPushMatrix();
   //  Offset
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glRotated(zz,0,0,1); 
   glScaled(dx,dy,dz);

   cube2(texture[3], 0,0,0 ,0.001,30,20, 0,0,0);

   glPopMatrix();
}



void door(double x,double y,double z, double dx, double dy, double dz, double th, double xx, double zz){

   glPushMatrix();
   //  Offset
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glRotated(xx,1,0,0);
   glRotated(zz,0,0,1); 
   glScaled(dx,dy,dz);

   cube2(texture[5], 0,0,0 ,25,45,.5, 0,0,0);
   

   glPopMatrix();

}

void fan(double x,double y,double z, double dx, double dy, double dz, double th, double xx, double zz){

   glPushMatrix();
   //  Offset
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glRotated(xx,1,0,0);
   glRotated(zz,0,0,1); 
   glScaled(dx,dy,dz);

   oval(texture[4], 0,0,-16, 4,1,15 ,0,0,0);

   oval(texture[4], 0,0,16, 4,1,15 ,0,0,0);

   oval(texture[4], -16,0,0, 15,1,4 ,0,0,0);

   oval(texture[4], 16,0,0, 15,1,4 ,0,0,0);

   glPopMatrix();
}


void globe(double x,double y,double z, double dx, double dy, double dz, double th, double zz){

   glPushMatrix();
   //  Offset
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glRotated(zz,0,0,1);
   glScaled(dx,dy,dz);

   oval(texture[15], 0,4.8,0, 2,2,2, -200,100, -10);
    draw_cylinder(texture[6], .3,2, -1,3,0, 1,1,1, 90,-20);
    draw_cylinder(texture[6], .3,2, 1,3,0, 1,1,1, 90,20);
    //draw_cylinder(texture[8], .5,4, 0,3,0, 1,1,1, 90,0);


   glPopMatrix();

}


/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */

void display()
{
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
   //  Undo previous transformations
   glLoadIdentity();
   if (per_mode == 0)
   { 
      double Ex = -2*dim*Sin(th)*Cos(ph);
      double Ey = +2*dim        *Sin(ph);
      double Ez = +2*dim*Cos(th)*Cos(ph);
      gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
   }
   else if(per_mode == 1){
    
      Cx = (-2*dim*Sin(theta));
      Cy = (2*dim   *Sin(ph));
      Cz = (2*dim*Cos(theta));
      gluLookAt(Dx,Dy,Dz , Cx+Dx,Cy+Dy,Cz+Dz , 0,1,0);
   }

   glShadeModel(smooth ? GL_SMOOTH : GL_FLAT);

   //  Light switch
   if (light==0)
   {

       //  Translate intensity to color vectors
      float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
      float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
      float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
      //  Light position
      float Position[]  = {90,25,-90,1};
      //  Draw light position as ball (still no lighting here)
      glColor3f(1,1,1);
      ball(Position[0],Position[1],Position[2] , 5);
      //  OpenGL should normalize normal vectors
      glEnable(GL_NORMALIZE);
      //  Enable lighting
      glEnable(GL_LIGHTING);
      //  Location of viewer for specular calculations
      glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
      //  glColor sets ambient and diffuse color materials
      glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
      glEnable(GL_COLOR_MATERIAL);
      //  Enable light 0
      glEnable(GL_LIGHT0);
      //  Set ambient, diffuse, specular components and position of light 0
      glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
      glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
      glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
      glLightfv(GL_LIGHT0,GL_POSITION,Position);

      
   }
   else if (light == 1)
   {
     //  Translate intensity to color vectors
      float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
      float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
      float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
      //  Light position
      float Position[]  = {0,45,0,1.0};
      //  Draw light position as ball (still no lighting here)
      glColor3f(1,1,1);
      ball(Position[0],Position[1],Position[2] , 5);
      //  OpenGL should normalize normal vectors
      glEnable(GL_NORMALIZE);
      //  Enable lighting
      glEnable(GL_LIGHTING);
      //  Location of viewer for specular calculations
      glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
      //  glColor sets ambient and diffuse color materials
      glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
      glEnable(GL_COLOR_MATERIAL);
      //  Enable light 0
      glEnable(GL_LIGHT0);
      //  Set ambient, diffuse, specular components and position of light 0
      glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
      glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
      glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
      glLightfv(GL_LIGHT0,GL_POSITION,Position);
   }
   else{
      glDisable(GL_LIGHTING);
   }
   ball(0,45,0,4.8);
   
   //  Set view angle
//    glRotatef(ph,1,0,0);
//    glRotatef(th,0,1,0);
   //  Decide what to draw
   switch (mode)
   {
      // scene
      case 0:
         room(0,0,0 , 5,2,5, 0);
         // front row desk
         desk(-100,-30,-70 , 1,1,1, 0);
         chair(-100,-30,-60, 1,1,1, 0, 0);
         notebook(-100, -24, -70, 1, 1, 1, 0);
         pencil(-100, -23.5, -70, 1, 1, 1, 90);
           
        

           
         desk(-50,-30,-70 , 1,1,1, 0);
         chair(-50,-30,-60, 1,1,1, 0, 0);
         notebook(-50, -24, -70, 1, 1, 1, 0);
         pencil(-50, -23.5, -70, 1, 1, 1, 90);
           
         desk(0,-30,-70 , 1,1,1, 0);
         chair(0,-30,-60, 1,1,1, 0, 0);
         notebook(0, -24, -70, 1, 1, 1, 0);
         pencil(0, -23.5, -70, 1, 1, 1, 90);
           
         globe(-7,-29,-75, 5,5,5, 0, 0);
           
         desk(50,-30,-70 , 1,1,1, 0);
         chair(50,-30,-60, 1,1,1, 0, 0);
         notebook(50, -24, -70, 1, 1, 1, 0);
         pencil(50, -23.5, -70, 1, 1, 1, 90);
           
           


           
         // second row row desk
         desk(-100,-30,-10 , 1,1,1, 0);
         chair(-100,-30,0, 1,1,1, 0, 0);
         notebook(-100, -24, -10, 1, 1, 1, 0);
         pencil(-100, -23.5, -10, 1, 1, 1, 90);
           
         desk(-50,-30,-10 , 1,1,1, 0);
         chair(-50,-30,0, 1,1,1, 0, 0);
         notebook(-50, -24, -10, 1, 1, 1, 0);
         pencil(-50, -23.5, -10, 1, 1, 1, 90);
           
         desk(0,-30,-10 , 1,1,1, 0);
         chair(0,-30,0, 1,1,1, 0, 0);
         notebook(0, -24, -10, 1, 1, 1, 0);
         pencil(0, -23.5, -10, 1, 1, 1, 90);
           
         desk(50,-30,-10 , 1,1,1, 0);
         chair(50,-30,0, 1,1,1, 0, 0);
         notebook(50, -24, -10, 1, 1, 1, 0);
         pencil(50, -23.5, -10, 1, 1, 1, 90);
           
           
           
         // second row row desk
         desk(-100,-30,50 , 1,1,1, 0);
         chair(-100,-30,60, 1,1,1, 0, 0);
         notebook(-100, -24, 50, 1, 1, 1, 0);
         pencil(-100, -23.5, 50, 1, 1, 1, 90);

         desk(-50,-30,50 , 1,1,1, 0);
         chair(-50,-30,60, 1,1,1, 0, 0);
         notebook(-50, -24, 50, 1, 1, 1, 0);
         pencil(-50, -23.5, 50, 1, 1, 1, 90);
           
         desk(0,-30,50 , 1,1,1, 0);
         chair(0,-30,60, 1,1,1, 0, 0);
         notebook(0, -24, 50, 1, 1, 1, 0);
         pencil(0, -23.5, 50, 1, 1, 1, 90);
           
         desk(50,-30,50 , 1,1,1, 0);
         chair(50,-30,60, 1,1,1, 0, 0);
         notebook(50, -24, 50, 1, 1, 1, 0);
         pencil(50, -23.5, 50, 1, 1, 1, 90);


        
         ChalkWall(10,20,-123, 1.5,1.5,1.5, 0, 0);
         lamp(90,-20,-100, 1,3,1, 0,0);
         window(-124,0,0, 1,1,1, 0,0);
         window(-124,0,50, 1,1,1, 0,0);
         window(-124,0,100, 1,1,1, 0,0);
         window(-124,0,-50, 1,1,1, 0,0);
         window(-124,0,-100, 1,1,1, 0,0);
         
         //main
         door(93,-5,125, 1,1,1, 0,0,0);
         fan(0,45,0, 1,1,1, zh,0,0);
           
        // ********** NEED TO ADD BASKETBAL AS WELL AS CHAIRS, NOTEBOOKS FOR SOME TABLES AND PENCLES.
        // ********** ALSO NEED TO ADD A WORLD GLOBE. 


         }
   //  White
   glColor3f(1,1,1);
   //  Draw axes
   if (axes)
   {
      const double len=1.5;  //  Length of axes
      glBegin(GL_LINES);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(len,0.0,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,len,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,0.0,len);
      glEnd();
      //  Label axes
      glRasterPos3d(len,0.0,0.0);
      Print("X");
      glRasterPos3d(0.0,len,0.0);
      Print("Y");
      glRasterPos3d(0.0,0.0,len);
      Print("Z");
   }
   //  Five pixels from the lower left corner of the window
   glWindowPos2i(5,5);

   Print("Angle=%d,%d  Dim=%.1f Light=%s Texture=%s",th,ph,dim,light?"Ceiling fan":"Lamp",tex_mode?"Replace":"Modulate");
   if (light == 0 || light == 1)
   {
      glWindowPos2i(5,45);
      Print("Model=%s LocalViewer=%s Distance=%d Elevation=%.1f",smooth?"Smooth":"Flat",local?"Ceiling fan":"Lamp",distance,ylight);
      glWindowPos2i(5,25);
      Print("Ambient=%d  Diffuse=%d Specular=%d Emission=%d Shininess=%.0f",ambient,diffuse,specular,emission,shiny);
   }
   if(per_mode == 0){
       Print("Angle=%d,%d  Dim=%.1f FOV=%d Projection=%s",th,ph,dim,fov,"Perpective");
   }
   else{
       Print("Angle=%d,%d  Dim=%.1f FOV=%d Projection=%s",theta,ph,dim,fov,"First person");
   }
   
   //  Render the scene
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   if(per_mode ==0){
       if (key == GLUT_KEY_RIGHT){
           th += 5;
       }
            
   //  Left arrow key - decrease angle by 5 degrees
       else if (key == GLUT_KEY_LEFT){
           th -= 5;
       }
            
   //  Up arrow key - increase elevation by 5 degrees
       else if (key == GLUT_KEY_UP){
           ph += 5;
       }
      
   //  Down arrow key - decrease elevation by 5 degrees
       else if (key == GLUT_KEY_DOWN){
           ph -= 5;
       }
       //  Smooth color model
   else if (key == GLUT_KEY_F1)
      smooth = 1-smooth;
   //  Local Viewer
   else if (key == GLUT_KEY_F2)
      local = 1-local;
      
   }
   else if(per_mode == 1){
       if (key == GLUT_KEY_RIGHT){
           theta += 5;
       }
            
   //  Left arrow key - decrease angle by 5 degrees
       else if (key == GLUT_KEY_LEFT){
           theta -= 5;
       }
            
   //  Up arrow key - increase elevation by 5 degrees
       else if (key == GLUT_KEY_UP){
           ph += 5;
       }
      
   //  Down arrow key - decrease elevation by 5 degrees
       else if (key == GLUT_KEY_DOWN){
           ph -= 5;
       }

   }
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   theta %= 360;
   //  Update projection
   Project(per_mode,fov,asp,dim);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when there is nothing else to do
 */
void idle()
{
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   zh = fmod(90*t,360);
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset view angle
   else if (ch == '0')
      th = ph = 0;
   //  Toggle axes
   else if (ch == 'v' || ch == 'V')
      axes = 1-axes;
   //  Switch display mode
   else if (ch == 'z' || ch == 'Z')
      per_mode = (1-per_mode)%2;
   else if (ch == 'x' || ch == 'X')
      per_mode = (1+per_mode)%2;
   else if (ch == 'm')
      mode = (mode+1)%1;
   else if (ch == 'M')
      mode = (mode)%1;
   else if (ch == 'l' || ch == 'L')
      light = 1-light;
   else if (ch == 'k' || ch == 'K')
   light = (1+light)%2;
   //  Toggle light movement
   else if (ch == 'c' || ch == 'C')
      move = 1-move;
   //  Move light
   else if (ch == '<')
      zh += 1;
   else if (ch == '>')
      zh -= 1;
   else if (ch == '-' && ch>1)
      fov--;
   else if (ch == '+' && ch<179)
      fov++;
    //  Light elevation
   else if (ch=='[')
      ylight -= 0.1;
   else if (ch==']')
      ylight += 0.1;
   //  Ambient level
   else if (ch=='1' && ambient>0)
      ambient -= 5;
   else if (ch=='2' && ambient<100)
      ambient += 5;
   //  Diffuse level
   else if (ch=='3' && diffuse>0)
      diffuse -= 5;
   else if (ch=='4' && diffuse<100)
      diffuse += 5;
   //  Specular level
   else if (ch=='5' && specular>0)
      specular -= 5;
   else if (ch=='6' && specular<100)
      specular += 5;
   //  Emission level
   else if (ch=='e' && emission>0)
      emission -= 5;
   else if (ch=='E' && emission<100)
      emission += 5;
   //  Shininess level
   else if (ch=='n' && shininess>-1)
      shininess -= 1;
   else if (ch=='N' && shininess<7)
      shininess += 1;
   //  Toggle texture mode
   else if (ch == 'u' || ch == 'U')
      tex_mode = 1-tex_mode;
   else if (ch == 't')
      ntex = 1-ntex;
   if(per_mode == 1){
      double dt = .05;
       if(ch == 'w' || ch == 'W'){
           Dx += Cx*dt;
           Dz += Cz*dt;
       }
       else if(ch == 's' || ch == 'S'){
           Dx -= Cx*dt;
           Dz -= Cz*dt;
       }
       else if(ch == 'a' || ch == 'A'){
           Dx += Cz*dt;
           Dz -= Cx*dt;
       }
       else if(ch == 'd' || ch == 'D'){
           Dx -= Cz*dt;
           Dz += Cx*dt;
       }
   }
    //  Update projection
   Project(per_mode,fov,asp,dim);
   //  Translate shininess power to value (-1 => 0)
   shiny = shininess<0 ? 0 : pow(2.0,shininess);
   //  Reproject
   Project(per_mode,fov,asp,dim);
   glutIdleFunc(move?idle:NULL);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, RES*width,RES*height);
   //  Set projection
   Project(per_mode,fov,asp,dim);
   
}




/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT and process user parameters
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitWindowSize(300,300);
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   //  Create the window
   glutCreateWindow("Nathaniel Ramirez");
#ifdef USEGLEW
   //  Initialize GLEW
   if (glewInit()!=GLEW_OK) Fatal("Error initializing GLEW\n");
#endif
   //  Tell GLUT to call "idle" when there is nothing else to do
   glutIdleFunc(idle);
   
   //  Tell GLUT to call "reshape" when the window is resized
   glutReshapeFunc(reshape);
   //  Tell GLUT to call "special" when an arrow key is pressed
   glutSpecialFunc(special);
   //  Tell GLUT to call "key" when a key is pressed
   glutKeyboardFunc(key);
   //  Tell GLUT to call "display" when the scene should be drawn
   glutDisplayFunc(display);
   texture[0] = LoadTexBMP("schoolWall.bmp");
   texture[1] = LoadTexBMP("woodDesk.bmp");
   texture[2] = LoadTexBMP("blueCarpet.bmp");
   texture[3] = LoadTexBMP("Window_1.bmp");
   texture[4] = LoadTexBMP("wood.bmp");
   texture[5] = LoadTexBMP("schoolDoor2.bmp");
   texture[6] = LoadTexBMP("metalLeg.bmp");
   texture[7] = LoadTexBMP("schoolCarpet.bmp");
   texture[8] = LoadTexBMP("chalkBoard.bmp");
   texture[9] = LoadTexBMP("wordWall.bmp");
   texture[10] = LoadTexBMP("schoolCeiling.bmp");
   texture[11] = LoadTexBMP("chair.bmp");
   texture[12] = LoadTexBMP("notebook1.bmp");
   texture[13] = LoadTexBMP("pencil.bmp");
   texture[14] = LoadTexBMP("pink.bmp");
   texture[15] = LoadTexBMP("map.bmp");
   texture[16] = LoadTexBMP("solid_white.bmp");


   //  Pass control to GLUT so it can interact with the user
   glutMainLoop();
   return 0;
}
