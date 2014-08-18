#ifndef MODEL_H
#define MODEL_H
#include "global.h"

extern void interpolate_muzx_from_mu();
extern void interpolate_bigdim_grid(float a[][BIGDIM],const int dmx,const int dmz,const int tox,const int toz);
extern void interpolate(float **a,const int dmx,const int dmz,const int tox,const int toz);
extern int l_hom,mz,mz1,mz2,mz3,mx,mx1,mx2,mx3,dm;

extern float lam[BIGDIM][BIGDIM],mu[BIGDIM][BIGDIM],muzx[BIGDIM][BIGDIM];
extern float density_u[BIGDIM][BIGDIM],density_w[BIGDIM][BIGDIM];

extern float co_density, co_lam, co_mu, co_lam2mu;
#endif
