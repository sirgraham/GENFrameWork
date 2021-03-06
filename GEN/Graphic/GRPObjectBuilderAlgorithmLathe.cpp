
/*------------------------------------------------------------------------------------------
//  GRPOBJECTBUILDERALGORITHMLATHE.CPP
//
//  Creates a revolution Surface from mesh spline
//
//  Author            : Diego Martinez Ruiz de Gaona
//  Date Of Creation  : 27/06/2014 15:53:13
//  Last Modification :
//
//  GEN  Copyright (C).  All right reserved.
//----------------------------------------------------------------------------------------*/


/*---- INCLUDES --------------------------------------------------------------------------*/

#include "GRPElement.h"
#include "GRPShape.h"
#include "GRPFace.h"
#include <math.h>
#include "GRPObjectBuilderAlgorithmLathe.h"

#include "XMemory.h"

/*---- GENERAL VARIABLE ------------------------------------------------------------------*/


/*---- CLASS MEMBERS ---------------------------------------------------------------------*/


/*-------------------------------------------------------------------
//  GRPOBJECTBUILDERALGORITHMLATHE::GRPOBJECTBUILDERALGORITHMLATHE
*/
/**
//
//  Class Constructor GRPOBJECTBUILDERALGORITHMLATHE
//
//  @author       Diego Martinez Ruiz de Gaona
//  @version      27/06/2014 15:57:41
//
//  @param        builder :
*/
/*-----------------------------------------------------------------*/
GRPOBJECTBUILDERALGORITHMLATHE::GRPOBJECTBUILDERALGORITHMLATHE(GRPOBJECTBUILDER* builder)
{
  Clean();
  this->builder = builder;

}




/*-------------------------------------------------------------------
//  GRPOBJECTBUILDERALGORITHMLATHE::Execute
*/
/**
//
//
//
//  @author       Diego Martinez Ruiz de Gaona
//  @version      27/06/2014 16:07:21
//
//  @return       GRPELEMENT* :
//
//  @param        shape :
*/
/*-----------------------------------------------------------------*/
GRPELEMENT* GRPOBJECTBUILDERALGORITHMLATHE::Execute(GRPSHAPE* shape)
{
  if(!builder) return NULL;

  GRPSHAPE*           _shape = builder->MergeInnerSplines(shape);
  XVECTOR<GRPFACE*>   faces;


  meridianangle=(maxangle-InitialAngle)/nmeridians;

  GLFLOAT             anglepersegment = (GLFLOAT)meridianangle;
  GLFLOAT             angle           = InitialAngle;
  GLFLOAT             radianangle     = 0.0f;

  int n=0;

  for(int nsegments=0;nsegments<nmeridians;nsegments++,angle+=anglepersegment)
  {


    XVECTOR<GRPPOINT*> MeridianO;
    XVECTOR<GRPPOINT*> MeridianF;

    for(XDWORD e=0;e<_shape->contours.Get(0)->points.GetSize();e++)
    {
      GRPPOINT * o=new GRPPOINT();
      GRPPOINT a = _shape->contours.Get(0)->points.Get(e)->value;

      radianangle= (angle * PI / 180);

          o->x  = (float)cos(radianangle) * a.x;
          o->y  = a.y;
          o->z  = (float)sin(radianangle) * a.x;

          o->index=n;

          MeridianO.Add(o);

      GRPPOINT * f=new GRPPOINT();
      radianangle= ((angle+meridianangle) * PI / 180);

          f->x  = (float)cos(radianangle) * a.x;
          f->y  = a.y;
          f->z  = (float)sin(radianangle) * a.x;

          f->index=n+_shape->contours.Get(0)->points.GetSize();

          MeridianF.Add(f);
          n++;
    }

    for(XDWORD e=0;e<_shape->contours.Get(0)->points.GetSize()-1;e++)
    {
          GRPFACE* face = new GRPFACE();
          if(face)
          {
            GRPPOINT *point=NULL;

            GRPPOINT *ao=MeridianO.Get(e);
            GRPPOINT *bo=MeridianO.Get(e+1);
            GRPPOINT *bf=MeridianF.Get(e+1);

              float u=nsegments/nmeridians;
              float v=float(e/_shape->contours.Get(0)->points.GetSize());

              point = new GRPPOINT(ao->x,ao->y,ao->z,n);
              if(point) face->Add(point);
              face->a=ao->index;

              point = new GRPPOINT(bo->x,bo->y,bo->z,n);
              if(point) face->Add(point);
              face->b=bo->index;

              point =new GRPPOINT(bf->x,bf->y,bf->z,n);
              if(point) face->Add(point);
              face->c=bf->index;

              face->CalculateNormal();
              faces.Add(face);
          }
          face = new GRPFACE();
          if(face)
          {
            GRPPOINT *point=NULL;

            GRPPOINT *ao=MeridianO.Get(e);
            GRPPOINT *bf=MeridianF.Get(e+1);
            GRPPOINT *af=MeridianF.Get(e);

              point = new GRPPOINT(ao->x,ao->y,ao->z,ao->index);
              if(point) face->Add(point);
              face->a=ao->index;

              point = new GRPPOINT(bf->x,bf->y,bf->z,bf->index);
              if(point) face->Add(point);
              face->b=bf->index;

              point = new GRPPOINT(af->x,af->y,af->z,n);
              if(point) face->Add(point);
              face->c=af->index;

              face->CalculateNormal();
              faces.Add(face);
          }
    }

    MeridianF.DeleteContents();
    MeridianF.DeleteAll();
    MeridianO.DeleteContents();
    MeridianO.DeleteAll();

  }


  /*
  for(int nsegments=0;nsegments<nmeridians;nsegments++)
    {
      angle+=anglepersegment;
      int lao,lbo,laf,lbf;

      for(XDWORD e=1;e<_shape->contours.Get(0)->points.GetSize();e++)
        {
          GRPPOINT a = _shape->contours.Get(0)->points.Get(e-1)->value;
          GRPPOINT b = _shape->contours.Get(0)->points.Get(e)->value;

          radianangle= (angle * PI / 180);

          GRPPOINT ao;
          ao.x  = cos(radianangle) * a.x;
          ao.y  = a.y;
          ao.z  = sin(radianangle) * a.x;

          GRPPOINT bo;
          bo.x  = cos(radianangle) * b.x;
          bo.y  = b.y;
          bo.z  = sin(radianangle) * b.x;

          radianangle= ((angle+meridianangle) * PI / 180);

          GRPPOINT af;
          af.x=cos(radianangle)*a.x;
          af.y=a.y;
          af.z=sin(radianangle)*a.x;

          GRPPOINT bf;
          bf.x=cos(radianangle)*b.x;
          bf.y=b.y;
          bf.z=sin(radianangle)*b.x;

          GRPFACE*  face;
          GRPPOINT* point;
          GRPVECTOR va(a);
          GRPVECTOR vb(b);



          face = new GRPFACE();
          if(face)
            {
              float u=nsegments/nmeridians;
              float v=float(e/_shape->contours.Get(0)->points.GetSize());

              point = new GRPPOINT(ao.x,ao.y,ao.z,n);
              if(point) face->Add(point);
              face->a=n++;
              lao=face->a;

              point = new GRPPOINT(bo.x,bo.y,bo.z,n);
              if(point) face->Add(point);
              face->b=n++;
              lbo=face->b;

              point =new GRPPOINT(bf.x,bf.y,bf.z,n);
              if(point) face->Add(point);
              face->c=n++;

              lbf=face->c;

              face->CalculateNormal();
              faces.Add(face);
            }

          face = new GRPFACE();
          if(face)
            {
              point = new GRPPOINT(ao.x,ao.y,ao.z,ao.index);
              if(point) face->Add(point);
              face->a=ao.index;

              point = new GRPPOINT(bf.x,bf.y,bf.z,bf.index);
              if(point) face->Add(point);
              face->b=bf.index;

              point = new GRPPOINT(af.x,af.y,af.z,n);
              if(point) face->Add(point);
              face->c=n++;

              face->CalculateNormal();
              faces.Add(face);
            }
        }
    }
    */

  GRPELEMENT* element = new GRPELEMENT();
  if(element)
    {
      element->GetMesh()->LoadModel(&faces);
      element->SetProgram(programID);
    }

  faces.DeleteContents();
  faces.DeleteAll();
  delete(_shape);
  _shape=NULL;
  return element;
}


/*
Index[000] a 000 b 001 c 004 => a) -0.866025 0.100000 -0.500000 b) -0.779423 0.100000 -0.450000 c) -0.735826 0.100000 -0.518227
Index[001] a 000 b 004 c 003 => a) -0.866025 0.100000 -0.500000 b) -0.735826 0.100000 -0.518227 c) -0.817585 0.100000 -0.575808
Index[002] a 001 b 002 c 005 => a) -0.779423 0.100000 -0.450000 b) -0.779423 0.000000 -0.450000 c) -0.735826 0.000000 -0.518227
Index[003] a 001 b 005 c 004 => a) -0.779423 0.100000 -0.450000 b) -0.735826 0.000000 -0.518227 c) -0.735826 0.100000 -0.518227
Index[004] a 003 b 004 c 007 => a) -0.817585 0.100000 -0.575808 b) -0.735826 0.100000 -0.518227 c) -0.686274 0.100000 -0.582260
Index[005] a 003 b 007 c 006 => a) -0.817585 0.100000 -0.575808 b) -0.686274 0.100000 -0.582260 c) -0.762527 0.100000 -0.646956
Index[006] a 004 b 005 c 008 => a) -0.735826 0.100000 -0.518227 b) -0.735826 0.000000 -0.518227 c) -0.686274 0.000000 -0.582260
Index[007] a 004 b 008 c 007 => a) -0.735826 0.100000 -0.518227 b) -0.686274 0.000000 -0.582260 c) -0.686274 0.100000 -0.582260
Index[008] a 006 b 007 c 010 => a) -0.762527 0.100000 -0.646956 b) -0.686274 0.100000 -0.582260 c) -0.631168 0.100000 -0.641581
Index[009] a 006 b 010 c 009 => a) -0.762527 0.100000 -0.646956 b) -0.631168 0.100000 -0.641581 c) -0.701298 0.100000 -0.712868
Index[010] a 007 b 008 c 011 => a) -0.686274 0.100000 -0.582260 b) -0.686274 0.000000 -0.582260 c) -0.631168 0.000000 -0.641581
Index[011] a 007 b 011 c 010 => a) -0.686274 0.100000 -0.582260 b) -0.631168 0.000000 -0.641581 c) -0.631168 0.100000 -0.641581
Index[012] a 009 b 010 c 013 => a) -0.701298 0.100000 -0.712868 b) -0.631168 0.100000 -0.641581 c) -0.570954 0.100000 -0.695709
Index[013] a 009 b 013 c 012 => a) -0.701298 0.100000 -0.712868 b) -0.570954 0.100000 -0.695709 c) -0.634393 0.100000 -0.773010
Index[014] a 010 b 011 c 014 => a) -0.631168 0.100000 -0.641581 b) -0.631168 0.000000 -0.641581 c) -0.570954 0.000000 -0.695709
Index[015] a 010 b 014 c 013 => a) -0.631168 0.100000 -0.641581 b) -0.570954 0.000000 -0.695709 c) -0.570954 0.100000 -0.695709
Index[016] a 012 b 013 c 016 => a) -0.634393 0.100000 -0.773010 b) -0.570954 0.100000 -0.695709 c) -0.506119 0.100000 -0.744207
Index[017] a 012 b 016 c 015 => a) -0.634393 0.100000 -0.773010 b) -0.506119 0.100000 -0.744207 c) -0.562354 0.100000 -0.826897
Index[018] a 013 b 014 c 017 => a) -0.570954 0.100000 -0.695709 b) -0.570954 0.000000 -0.695709 c) -0.506119 0.000000 -0.744207
Index[019] a 013 b 017 c 016 => a) -0.570954 0.100000 -0.695709 b) -0.506119 0.000000 -0.744207 c) -0.506119 0.100000 -0.744207
Index[020] a 015 b 016 c 019 => a) -0.562354 0.100000 -0.826897 b) -0.506119 0.100000 -0.744207 c) -0.437187 0.100000 -0.786681
Index[021] a 015 b 019 c 018 => a) -0.562354 0.100000 -0.826897 b) -0.437187 0.100000 -0.786681 c) -0.485763 0.100000 -0.874090
Index[022] a 016 b 017 c 020 => a) -0.506119 0.100000 -0.744207 b) -0.506119 0.000000 -0.744207 c) -0.437187 0.000000 -0.786681
Index[023] a 016 b 020 c 019 => a) -0.506119 0.100000 -0.744207 b) -0.437187 0.000000 -0.786681 c) -0.437187 0.100000 -0.786681
Index[024] a 018 b 019 c 022 => a) -0.485763 0.100000 -0.874090 b) -0.437187 0.100000 -0.786681 c) -0.364717 0.100000 -0.822789
Index[025] a 018 b 022 c 021 => a) -0.485763 0.100000 -0.874090 b) -0.364717 0.100000 -0.822789 c) -0.405241 0.100000 -0.914210
Index[026] a 019 b 020 c 023 => a) -0.437187 0.100000 -0.786681 b) -0.437187 0.000000 -0.786681 c) -0.364717 0.000000 -0.822789
Index[027] a 019 b 023 c 022 => a) -0.437187 0.100000 -0.786681 b) -0.364717 0.000000 -0.822789 c) -0.364717 0.100000 -0.822789
Index[028] a 021 b 022 c 025 => a) -0.405241 0.100000 -0.914210 b) -0.364717 0.100000 -0.822789 c) -0.289295 0.100000 -0.852237
Index[029] a 021 b 025 c 024 => a) -0.405241 0.100000 -0.914210 b) -0.289295 0.100000 -0.852237 c) -0.321439 0.100000 -0.946930
Index[030] a 022 b 023 c 026 => a) -0.364717 0.100000 -0.822789 b) -0.364717 0.000000 -0.822789 c) -0.289295 0.000000 -0.852237
Index[031] a 022 b 026 c 025 => a) -0.364717 0.100000 -0.822789 b) -0.289295 0.000000 -0.852237 c) -0.289295 0.100000 -0.852237
Index[037] a 027 b 031 c 030 => a) -0.235036 0.100000 -0.971987 b) -0.132057 0.100000 -0.890259 c) -0.146730 0.100000 -0.989177
Index[044] a 033 b 034 c 037 => a) -0.057237 0.100000 -0.998361 b) -0.051514 0.100000 -0.898525 c) 0.029447 0.100000 -0.899518
Index[052] a 039 b 040 c 043 => a) 0.122411 0.100000 -0.992480 b) 0.110170 0.100000 -0.893232 c) 0.190000 0.100000 -0.879716
Index[060] a 045 b 046 c 049 => a) 0.298104 0.100000 -0.954533 b) 0.268293 0.100000 -0.859080 c) 0.344415 0.100000 -0.831492
Index[067] a 049 b 053 c 052 => a) 0.344415 0.100000 -0.831492 b) 0.417749 0.000000 -0.797174 c) 0.417749 0.100000 -0.797174
Index[075] a 055 b 059 c 058 => a) 0.487702 0.100000 -0.756404 b) 0.553708 0.000000 -0.709512 c) 0.553708 0.100000 -0.709512
Index[083] a 061 b 065 c 064 => a) 0.615233 0.100000 -0.656878 b) 0.671778 0.000000 -0.598927 c) 0.671778 0.100000 -0.598927
Index[090] a 067 b 068 c 071 => a) 0.722887 0.100000 -0.536129 b) 0.722887 0.000000 -0.536129 c) 0.768145 0.000000 -0.468992
Index[098] a 073 b 074 c 077 => a) 0.807185 0.100000 -0.398060 b) 0.807185 0.000000 -0.398060 c) 0.839693 0.000000 -0.323906
Index[105] a 078 b 082 c 081 => a) 0.961562 0.100000 -0.274589 b) 0.884114 0.100000 -0.168354 c) 0.982349 0.100000 -0.187060
Index[113] a 084 b 088 c 087 => a) 0.995185 0.100000 -0.098017 b) 0.899970 0.100000 -0.007363 c) 0.999967 0.100000 -0.008181
Index[121] a 090 b 094 c 093 => a) 0.996655 0.100000 0.081721 b) 0.886750 0.100000 0.153866 c) 0.985278 0.100000 0.170962
Index[129] a 096 b 100 c 099 => a) 0.965926 0.100000 0.258819 b) 0.844881 0.100000 0.310124 c) 0.938756 0.100000 0.344582
Index[136] a 102 b 103 c 106 => a) 0.903989 0.100000 0.427555 b) 0.813590 0.100000 0.384800 c) 0.775715 0.100000 0.456362
Index[144] a 108 b 109 c 112 => a) 0.812847 0.100000 0.582478 b) 0.731562 0.100000 0.524230 c) 0.681488 0.100000 0.587856
Index[152] a 114 b 115 c 118 => a) 0.695443 0.100000 0.718582 b) 0.625898 0.100000 0.646723 c) 0.565243 0.100000 0.700357
Index[160] a 120 b 121 c 124 => a) 0.555570 0.100000 0.831470 b) 0.500013 0.100000 0.748323 c) 0.430736 0.100000 0.790232
Index[167] a 124 b 128 c 127 => a) 0.430736 0.100000 0.790232 b) 0.357974 0.000000 0.825745 c) 0.357974 0.100000 0.825745
Index[175] a 130 b 134 c 133 => a) 0.282314 0.100000 0.854575 b) 0.204369 0.000000 0.876489 c) 0.204369 0.100000 0.876489
Index[183] a 136 b 140 c 139 => a) 0.124769 0.100000 0.891309 b) 0.044161 0.000000 0.898916 c) 0.044161 0.100000 0.898916
Index[191] a 142 b 146 c 145 => a) -0.036806 0.100000 0.899247 b) -0.117474 0.000000 0.892300 c) -0.117474 0.100000 0.892300
Index[198] a 148 b 149 c 152 => a) -0.197191 0.100000 0.878132 b) -0.197191 0.000000 0.878132 c) -0.275313 0.000000 0.856856
Index[206] a 154 b 155 c 158 => a) -0.351206 0.100000 0.828646 b) -0.351206 0.000000 0.828646 c) -0.424257 0.000000 0.793729
Index[207] a 154 b 158 c 157 => a) -0.351206 0.100000 0.828646 b) -0.424257 0.000000 0.793729 c) -0.424257 0.100000 0.793729
Index[213] a 159 b 163 c 162 => a) -0.548750 0.100000 0.835987 b) -0.559494 0.100000 0.704958 c) -0.621660 0.100000 0.783287
Index[221] a 165 b 169 c 168 => a) -0.689541 0.100000 0.724247 b) -0.676656 0.100000 0.593411 c) -0.751840 0.100000 0.659346
Index[229] a 171 b 175 c 174 => a) -0.808054 0.100000 0.589108 b) -0.771956 0.100000 0.462692 c) -0.857729 0.100000 0.514102
Index[237] a 177 b 181 c 180 => a) -0.900461 0.100000 0.434936 b) -0.842315 0.100000 0.317025 c) -0.935906 0.100000 0.352250
Index[244] a 183 b 184 c 187 => a) -0.963776 0.100000 0.266713 b) -0.867398 0.100000 0.240042 c) -0.885461 0.100000 0.161115
Index[252] a 189 b 190 c 193 => a) -0.995953 0.100000 0.089872 b) -0.896358 0.100000 0.080885 c) -0.900000 0.100000 -0.000000
Index[000] a 000 b 001 c 004 => a) -0.173205 0.000000 -0.100000 b) -0.173205 0.100000 -0.100000 c) -0.163517 0.100000 -0.115162
Index[001] a 000 b 004 c 003 => a) -0.173205 0.000000 -0.100000 b) -0.163517 0.100000 -0.115162 c) -0.163517 0.000000 -0.115162
Index[002] a 001 b 002 c 005 => a) -0.173205 0.100000 -0.100000 b) -0.000000 0.100000 -0.000000 c) -0.000000 0.100000 -0.000000
Index[003] a 001 b 005 c 004 => a) -0.173205 0.100000 -0.100000 b) -0.000000 0.100000 -0.000000 c) -0.163517 0.100000 -0.115162
Index[004] a 003 b 004 c 007 => a) -0.163517 0.000000 -0.115162 b) -0.163517 0.100000 -0.115162 c) -0.152505 0.100000 -0.129391
Index[005] a 003 b 007 c 006 => a) -0.163517 0.000000 -0.115162 b) -0.152505 0.100000 -0.129391 c) -0.152505 0.000000 -0.129391
Index[006] a 004 b 005 c 008 => a) -0.163517 0.100000 -0.115162 b) -0.000000 0.100000 -0.000000 c) -0.000000 0.100000 -0.000000
Index[007] a 004 b 008 c 007 => a) -0.163517 0.100000 -0.115162 b) -0.000000 0.100000 -0.000000 c) -0.152505 0.100000 -0.129391
Index[008] a 006 b 007 c 010 => a) -0.152505 0.000000 -0.129391 b) -0.152505 0.100000 -0.129391 c) -0.140260 0.100000 -0.142574
Index[009] a 006 b 010 c 009 => a) -0.152505 0.000000 -0.129391 b) -0.140260 0.100000 -0.142574 c) -0.140260 0.000000 -0.142574
Index[010] a 007 b 008 c 011 => a) -0.152505 0.100000 -0.129391 b) -0.000000 0.100000 -0.000000 c) -0.000000 0.100000 -0.000000
Index[011] a 007 b 011 c 010 => a) -0.152505 0.100000 -0.129391 b) -0.000000 0.100000 -0.000000 c) -0.140260 0.100000 -0.142574
Index[012] a 009 b 010 c 013 => a) -0.140260 0.000000 -0.142574 b) -0.140260 0.100000 -0.142574 c) -0.126879 0.100000 -0.154602
Index[013] a 009 b 013 c 012 => a) -0.140260 0.000000 -0.142574 b) -0.126879 0.100000 -0.154602 c) -0.126879 0.000000 -0.154602
Index[014] a 010 b 011 c 014 => a) -0.140260 0.100000 -0.142574 b) -0.000000 0.100000 -0.000000 c) -0.000000 0.100000 -0.000000
Index[015] a 010 b 014 c 013 => a) -0.140260 0.100000 -0.142574 b) -0.000000 0.100000 -0.000000 c) -0.126879 0.100000 -0.154602
Index[016] a 012 b 013 c 016 => a) -0.126879 0.000000 -0.154602 b) -0.126879 0.100000 -0.154602 c) -0.112471 0.100000 -0.165379
Index[017] a 012 b 016 c 015 => a) -0.126879 0.000000 -0.154602 b) -0.112471 0.100000 -0.165379 c) -0.112471 0.000000 -0.165379
Index[018] a 013 b 014 c 017 => a) -0.126879 0.100000 -0.154602 b) -0.000000 0.100000 -0.000000 c) -0.000000 0.100000 -0.000000
Index[019] a 013 b 017 c 016 => a) -0.126879 0.100000 -0.154602 b) -0.000000 0.100000 -0.000000 c) -0.112471 0.100000 -0.165379
Index[020] a 015 b 016 c 019 => a) -0.112471 0.000000 -0.165379 b) -0.112471 0.100000 -0.165379 c) -0.097153 0.100000 -0.174818
Index[021] a 015 b 019 c 018 => a) -0.112471 0.000000 -0.165379 b) -0.097153 0.100000 -0.174818 c) -0.097153 0.000000 -0.174818
Index[022] a 016 b 017 c 020 => a) -0.112471 0.100000 -0.165379 b) -0.000000 0.100000 -0.000000 c) -0.000000 0.100000 -0.000000
Index[023] a 016 b 020 c 019 => a) -0.112471 0.100000 -0.165379 b) -0.000000 0.100000 -0.000000 c) -0.097153 0.100000 -0.174818
Index[024] a 018 b 019 c 022 => a) -0.097153 0.000000 -0.174818 b) -0.097153 0.100000 -0.174818 c) -0.081048 0.100000 -0.182842
Index[025] a 018 b 022 c 021 => a) -0.097153 0.000000 -0.174818 b) -0.081048 0.100000 -0.182842 c) -0.081048 0.000000 -0.182842
Index[026] a 019 b 020 c 023 => a) -0.097153 0.100000 -0.174818 b) -0.000000 0.100000 -0.000000 c) -0.000000 0.100000 -0.000000
Index[027] a 019 b 023 c 022 => a) -0.097153 0.100000 -0.174818 b) -0.000000 0.100000 -0.000000 c) -0.081048 0.100000 -0.182842
Index[028] a 021 b 022 c 025 => a) -0.081048 0.000000 -0.182842 b) -0.081048 0.100000 -0.182842 c) -0.064288 0.100000 -0.189386
Index[029] a 021 b 025 c 024 => a) -0.081048 0.000000 -0.182842 b) -0.064288 0.100000 -0.189386 c) -0.064288 0.000000 -0.189386
Index[030] a 022 b 023 c 026 => a) -0.081048 0.100000 -0.182842 b) -0.000000 0.100000 -0.000000 c) -0.000000 0.100000 -0.000000
Index[031] a 022 b 026 c 025 => a) -0.081048 0.100000 -0.182842 b) -0.000000 0.100000 -0.000000 c) -0.064288 0.100000 -0.189386
Index[034] a 025 b 026 c 029 => a) -0.064288 0.100000 -0.189386 b) -0.000000 0.100000 -0.000000 c) -0.000000 0.100000 -0.000000
Index[037] a 027 b 031 c 030 => a) -0.047007 0.000000 -0.194397 b) -0.029346 0.100000 -0.197835 c) -0.029346 0.000000 -0.197835
Index[041] a 030 b 034 c 033 => a) -0.029346 0.000000 -0.197835 b) -0.011447 0.100000 -0.199672 c) -0.011447 0.000000 -0.199672
Index[044] a 033 b 034 c 037 => a) -0.011447 0.000000 -0.199672 b) -0.011447 0.100000 -0.199672 c) 0.006544 0.100000 -0.199893
Index[048] a 036 b 037 c 040 => a) 0.006544 0.000000 -0.199893 b) 0.006544 0.100000 -0.199893 c) 0.024482 0.100000 -0.198496
Index[052] a 039 b 040 c 043 => a) 0.024482 0.000000 -0.198496 b) 0.024482 0.100000 -0.198496 c) 0.042222 0.100000 -0.195492
Index[055] a 040 b 044 c 043 => a) 0.024482 0.100000 -0.198496 b) 0.000000 0.100000 -0.000000 c) 0.042222 0.100000 -0.195492
Index[059] a 043 b 047 c 046 => a) 0.042222 0.100000 -0.195492 b) 0.000000 0.100000 -0.000000 c) 0.059621 0.100000 -0.190907
Index[063] a 046 b 050 c 049 => a) 0.059621 0.100000 -0.190907 b) 0.000000 0.100000 -0.000000 c) 0.076537 0.100000 -0.184776
Index[067] a 049 b 053 c 052 => a) 0.076537 0.100000 -0.184776 b) 0.000000 0.100000 -0.000000 c) 0.092833 0.100000 -0.177150
Index[070] a 052 b 053 c 056 => a) 0.092833 0.100000 -0.177150 b) 0.000000 0.100000 -0.000000 c) 0.000000 0.100000 -0.000000
Index[074] a 055 b 056 c 059 => a) 0.108378 0.100000 -0.168090 b) 0.000000 0.100000 -0.000000 c) 0.000000 0.100000 -0.000000
Index[078] a 058 b 059 c 062 => a) 0.123046 0.100000 -0.157669 b) 0.000000 0.100000 -0.000000 c) 0.000000 0.100000 -0.000000
Index[082] a 061 b 062 c 065 => a) 0.136718 0.100000 -0.145973 b) 0.000000 0.100000 -0.000000 c) 0.000000 0.100000 -0.000000
Index[085] a 063 b 067 c 066 => a) 0.149284 0.000000 -0.133095 b) 0.160642 0.100000 -0.119140 c) 0.160642 0.000000 -0.119140
Index[089] a 066 b 070 c 069 => a) 0.160642 0.000000 -0.119140 b) 0.170699 0.100000 -0.104221 c) 0.170699 0.000000 -0.104221
Index[093] a 069 b 073 c 072 => a) 0.170699 0.000000 -0.104221 b) 0.179375 0.100000 -0.088458 c) 0.179375 0.000000 -0.088458
Index[096] a 072 b 073 c 076 => a) 0.179375 0.000000 -0.088458 b) 0.179375 0.100000 -0.088458 c) 0.186599 0.100000 -0.071979
Index[100] a 075 b 076 c 079 => a) 0.186599 0.000000 -0.071979 b) 0.186599 0.100000 -0.071979 c) 0.192312 0.100000 -0.054918
Index[104] a 078 b 079 c 082 => a) 0.192312 0.000000 -0.054918 b) 0.192312 0.100000 -0.054918 c) 0.196470 0.100000 -0.037412
Index[107] a 079 b 083 c 082 => a) 0.192312 0.100000 -0.054918 b) 0.000000 0.100000 -0.000000 c) 0.196470 0.100000 -0.037412
Index[111] a 082 b 086 c 085 => a) 0.196470 0.100000 -0.037412 b) 0.000000 0.100000 -0.000000 c) 0.199037 0.100000 -0.019603
Index[115] a 085 b 089 c 088 => a) 0.199037 0.100000 -0.019603 b) 0.000000 0.100000 -0.000000 c) 0.199993 0.100000 -0.001636
Index[118] a 088 b 089 c 092 => a) 0.199993 0.100000 -0.001636 b) 0.000000 0.100000 -0.000000 c) 0.000000 0.100000 0.000000
Index[122] a 091 b 092 c 095 => a) 0.199331 0.100000 0.016344 b) 0.000000 0.100000 0.000000 c) 0.000000 0.100000 0.000000
Index[126] a 094 b 095 c 098 => a) 0.197056 0.100000 0.034192 b) 0.000000 0.100000 0.000000 c) 0.000000 0.100000 0.000000
Index[130] a 097 b 098 c 101 => a) 0.193185 0.100000 0.051764 b) 0.000000 0.100000 0.000000 c) 0.000000 0.100000 0.000000
Index[133] a 099 b 103 c 102 => a) 0.187751 0.000000 0.068916 b) 0.180798 0.100000 0.085511 c) 0.180798 0.000000 0.085511
Index[137] a 102 b 106 c 105 => a) 0.180798 0.000000 0.085511 b) 0.172381 0.100000 0.101414 c) 0.172381 0.000000 0.101414
Index[138] a 103 b 104 c 107 => a) 0.180798 0.100000 0.085511 b) 0.000000 0.100000 0.000000 c) 0.000000 0.100000 0.000000
Index[141] a 105 b 109 c 108 => a) 0.172381 0.000000 0.101414 b) 0.162569 0.100000 0.116496 c) 0.162569 0.000000 0.116496
Index[144] a 108 b 109 c 112 => a) 0.162569 0.000000 0.116496 b) 0.162569 0.100000 0.116496 c) 0.151442 0.100000 0.130635
Index[148] a 111 b 112 c 115 => a) 0.151442 0.000000 0.130635 b) 0.151442 0.100000 0.130635 c) 0.139089 0.100000 0.143716
Index[152] a 114 b 115 c 118 => a) 0.139089 0.000000 0.143716 b) 0.139089 0.100000 0.143716 c) 0.125610 0.100000 0.155635
Index[156] a 117 b 118 c 121 => a) 0.125610 0.000000 0.155635 b) 0.125610 0.100000 0.155635 c) 0.111114 0.100000 0.166294
Index[159] a 118 b 122 c 121 => a) 0.125610 0.100000 0.155635 b) 0.000000 0.100000 0.000000 c) 0.111114 0.100000 0.166294
Index[163] a 121 b 125 c 124 => a) 0.111114 0.100000 0.166294 b) 0.000000 0.100000 0.000000 c) 0.095719 0.100000 0.175607
Index[167] a 124 b 128 c 127 => a) 0.095719 0.100000 0.175607 b) 0.000000 0.100000 0.000000 c) 0.079550 0.100000 0.183499
Index[170] a 127 b 128 c 131 => a) 0.079550 0.100000 0.183499 b) 0.000000 0.100000 0.000000 c) 0.000000 0.100000 0.000000
Index[174] a 130 b 131 c 134 => a) 0.062736 0.100000 0.189906 b) 0.000000 0.100000 0.000000 c) 0.000000 0.100000 0.000000
Index[178] a 133 b 134 c 137 => a) 0.045415 0.100000 0.194775 b) 0.000000 0.100000 0.000000 c) 0.000000 0.100000 0.000000
Index[182] a 136 b 137 c 140 => a) 0.027727 0.100000 0.198069 b) 0.000000 0.100000 0.000000 c) 0.000000 0.100000 0.000000
Index[185] a 138 b 142 c 141 => a) 0.009814 0.000000 0.199759 b) -0.008179 0.100000 0.199833 c) -0.008179 0.000000 0.199833
Index[189] a 141 b 145 c 144 => a) -0.008179 0.000000 0.199833 b) -0.026105 0.100000 0.198289 c) -0.026105 0.000000 0.198289
Index[193] a 144 b 148 c 147 => a) -0.026105 0.000000 0.198289 b) -0.043820 0.100000 0.195140 c) -0.043820 0.000000 0.195140
Index[196] a 147 b 148 c 151 => a) -0.043820 0.000000 0.195140 b) -0.043820 0.100000 0.195140 c) -0.061181 0.100000 0.190413
Index[200] a 150 b 151 c 154 => a) -0.061181 0.000000 0.190413 b) -0.061181 0.100000 0.190413 c) -0.078046 0.100000 0.184144
Index[204] a 153 b 154 c 157 => a) -0.078046 0.000000 0.184144 b) -0.078046 0.100000 0.184144 c) -0.094279 0.100000 0.176384
Index[207] a 154 b 158 c 157 => a) -0.078046 0.100000 0.184144 b) -0.000000 0.100000 0.000000 c) -0.094279 0.100000 0.176384
Index[211] a 157 b 161 c 160 => a) -0.094279 0.100000 0.176384 b) -0.000000 0.100000 0.000000 c) -0.109750 0.100000 0.167197
Index[215] a 160 b 164 c 163 => a) -0.109750 0.100000 0.167197 b) -0.000000 0.100000 0.000000 c) -0.124332 0.100000 0.156657
Index[218] a 163 b 164 c 167 => a) -0.124332 0.100000 0.156657 b) -0.000000 0.100000 0.000000 c) -0.000000 0.100000 0.000000
Index[222] a 166 b 167 c 170 => a) -0.137908 0.100000 0.144849 b) -0.000000 0.100000 0.000000 c) -0.000000 0.100000 0.000000
Index[226] a 169 b 170 c 173 => a) -0.150368 0.100000 0.131869 b) -0.000000 0.100000 0.000000 c) -0.000000 0.100000 0.000000
Index[229] a 171 b 175 c 174 => a) -0.161611 0.000000 0.117822 b) -0.171546 0.100000 0.102820 c) -0.171546 0.000000 0.102820
Index[233] a 174 b 178 c 177 => a) -0.171546 0.000000 0.102820 b) -0.180092 0.100000 0.086987 c) -0.180092 0.000000 0.086987
Index[237] a 177 b 181 c 180 => a) -0.180092 0.000000 0.086987 b) -0.187181 0.100000 0.070450 c) -0.187181 0.000000 0.070450
Index[240] a 180 b 181 c 184 => a) -0.187181 0.000000 0.070450 b) -0.187181 0.100000 0.070450 c) -0.192755 0.100000 0.053343
Index[244] a 183 b 184 c 187 => a) -0.192755 0.000000 0.053343 b) -0.192755 0.100000 0.053343 c) -0.196769 0.100000 0.035803
Index[248] a 186 b 187 c 190 => a) -0.196769 0.000000 0.035803 b) -0.196769 0.100000 0.035803 c) -0.199191 0.100000 0.017974
Index[251] a 187 b 191 c 190 => a) -0.196769 0.100000 0.035803 b) -0.000000 0.100000 0.000000 c) -0.199191 0.100000 0.017974
Index[255] a 190 b 194 c 193 => a) -0.199191 0.100000 0.017974 b) -0.000000 0.100000 -0.000000 c) -0.200000 0.100000 -0.000000
*/