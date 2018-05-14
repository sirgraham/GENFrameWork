/*------------------------------------------------------------------------------------------
//  GRPCUBECOORDS.H
*/
/**
// \class
//
//  Cube Coordinates
//
//  @author  Diego Martinez Ruiz de Gaona
//
//  Date Of Creation  : 27/05/2014 14:07:54
//  Last Modification :
*/
/*  GEN  Copyright (C).  All right reserved.
//----------------------------------------------------------------------------------------*/


/*---- INCLUDES --------------------------------------------------------------------------*/

#include "GRPCubeCoords.h"

#include "XMemory.h"


GLfloat CubeVertex[6*4*3] =
{
   /* FRONT */
   -1.0,    -1.0,  1.0,     //{-1.0,-1.0,1.0}
   1.0,   -1.0,  1.0,     //{1.0,-1.0,1.0}
   -1.0,   1.0,  1.0,    //{-1.0,1.0,1.0}
   1.0,    1.0,  1.0,     //{1.0,1.0,1.0}

   /* BACK */
   -1.0,    -1.0, -1.0,   //-1.0,-1.0,-1.0
   -1.0,     1.0, -1.0,    //{-1.0,1.0,-1.0}
    1.0,  -1.0, -1.0,    //{1.0,-1.0,-1.0}
    1.0,   1.0, -1.0,    //{1.0,1.0,-1.0}

   /* LEFT */
   -1.0, -1.0,  1.0,    //{-1.0,-1.0,1.0}
   -1.0,  1.0,  1.0,  //{-1.0,1.0,1.0}
   -1.0, -1.0, -1.0,    //{-1.0,-1.0,-1.0}
   -1.0,  1.0, -1.0,  //{-1.0,1.0,-1.0}

   /* RIGHT */
   1.0, -1.0, -1.0,   //{1.0,-1.0,-1.0}
   1.0,  1.0, -1.0,   //{1.0,1.0,-1.0}
   1.0, -1.0,  1.0,   //{1.0,-1.0,1.0}
   1.0,  1.0,  1.0,   //{1.0,1.0,1.0}

   /* TOP */
   -1.0,  1.0,  1.0,  //{-1.0,1.0,1.0}
    1.0,  1.0,  1.0,   //{1.0,1.0,1.0}
   -1.0,  1.0, -1.0,  //{-1.0,1.0,-1.0}
    1.0,  1.0, -1.0,   //{1.0,1.0,-1.0}

   /* BOTTOM */
   -1.0,    -1.0,  1.0, //{-1.0,-1.0,1.0}
   -1.0,    -1.0, -1.0, //{-1.0,-1.0,-1.0}
    1.0,  -1.0,  1.0,  //{1.0,-1.0,-1.0}
    1.0,  -1.0, -1.0,  //{1.0,-1.0,-1.0}
};

GLfloat CubeNormals[6*4*3] =
{
     /* FRONT */
   -1.0,    -1.0, 1.0,
   1.0,   -1.0, 1.0,
   -1.0,    1.0,  1.0,
   1.0,   1.0,  1.0,

   /* BACK */
   -1.0,    -1.0,-1.0,
   -1.0,    1.0,-1.0,
   1.0,   -1.0,-1.0,
   1.0,   1.0,-1.0,

   /* LEFT */
   -1.0,-1.0,1.0,
   -1.0,1.0,1.0,
   -1.0,-1.0,-1.0,
   -1.0,1.0,-1.0,

   /* RIGHT */
   1.0,-1.0,-1.0,
   1.0,1.0,-1.0,
   1.0,-1.0,1.0,
   1.0,1.0,1.0,

   /* TOP */
   -1.0,1.0,1.0,
   1.0,1.0,1.0,
   -1.0,1.0,-1.0,
   1.0,1.0,-1.0,

   /* BOTTOM */
   -1.0,-1.0,1.0,
   -1.0,-1.0,-1.0,
   1.0,-1.0,-1.0,
   1.0,-1.0,-1.0
};

GLfloat CubeTextureCoords [6 * 4 * 2] = {
   0.f,  0.f,
   1.f,  0.f,
   0.f,  1.f,
   1.f,  1.f,

   0.f,  0.f,
   1.f,  0.f,
   0.f,  1.f,
   1.f,  1.f,

   0.f,  0.f,
   1.f,  0.f,
   0.f,  1.f,
   1.f,  1.f,

   0.f,  0.f,
   1.f,  0.f,
   0.f,  1.f,
   1.f,  1.f,

   0.f,  0.f,
   1.f,  0.f,
   0.f,  1.f,
   1.f,  1.f,

   0.f,  0.f,
   1.f,  0.f,
   0.f,  1.f,
   1.f,  1.f,
};

GLfloat QuadVertex[5*3]= {
  1.0,  1.0,  0.0,
  1.0,  -1.0, 0.0,
  -1.0, -1.0, 0.0,
  -1.0, 1.0,  0.0,
  1.0,  1.0,  0.0,
  /*
   1.0,  1.0,  0.0,
  -1.0, +1.0,  0.0,
  -1.0, -1.0,  0.0,
   1.0, -1.0,  0.0,
   1.0,  1.0,  0.0,
   */
};
GLfloat QuadNormals[5*3]= {
  0, 0, 1,   //-1.0,-1.0,-1.0
  0, 0, 1,
  0, 0, 1,
  0, 0, 1,
};

GLFLOAT QuadTextureCoords[5*2]={
      0.0,1.0,
      0.0,0.0,
      1.0,0.0,
      1.0,1.0,
      0.0,1.0
   };

GLFLOAT Colors  [4*3*50]={
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0,
    1.0,0.0,0.0,1.0,    1.0,1.0,0.0,1.0,    0.0,1.0,1.0,1.0

};
/*---- DEFINES & ENUMS  ------------------------------------------------------------------*/


/*---- CLASS -----------------------------------------------------------------------------*/

/*---- INLINE FUNCTIONS ------------------------------------------------------------------*/




