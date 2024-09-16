//  CSCIx229 library
//  Willem A. (Vlakkies) Schreuder
#include "CSCIx229.h"

//
//  Set projection
//
void Project(int per_mode, double fov, double asp, double dim)
{
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective transformation
   if (per_mode == 0 || per_mode == 1)
      gluPerspective(fov,asp,dim/4,16*dim);
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}

