#include "global.h"

float stored_u_1_level0[BIGDIM],stored_u_2_level0[BIGDIM],stored_u_3_level0[BIGDIM],
	  stored_u_mx3_level0[BIGDIM],stored_u_mx2_level0[BIGDIM],stored_u_mx1_level0[BIGDIM],
	  stored_u_1_level1,stored_u_2_level1,stored_u_3_level1,
	  stored_u_mx3_level1,stored_u_mx2_level1,stored_u_mx1_level1,

	  stored_u_mz2_level0[BIGDIM],stored_u_mz2_level1[BIGDIM],
	  stored_u_mz3_level0[BIGDIM],stored_u_mz3_level1[BIGDIM];
	  

float stored_w_0_level0[BIGDIM],stored_w_1_level0[BIGDIM],stored_w_2_level0[BIGDIM],
	  stored_w_mx3_level0[BIGDIM],stored_w_mx2_level0[BIGDIM],stored_w_mx1_level0[BIGDIM],
	  stored_w_0_level1,stored_w_1_level1,stored_w_2_level1,
	  stored_w_mx3_level1,stored_w_mx2_level1,stored_w_mx1_level1,

	  stored_w_mz2_level0[BIGDIM],stored_w_mz2_level1[BIGDIM],
	  stored_w_mz3_level0[BIGDIM],stored_w_mz3_level1[BIGDIM];

float stored_u_mz1_level1,stored_u_mz1_level0[BIGDIM],
	  stored_w_mz1_level1,stored_w_mz1_level0[BIGDIM];

void store_boundary(int l) {
  stored_u_1_level1    =  stored_u_1_level0[l];
  stored_u_2_level1    =  stored_u_2_level0[l];
  stored_u_3_level1    =  stored_u_3_level0[l];
  stored_u_mx3_level1  =  stored_u_mx3_level0[l];
  stored_u_mx2_level1  =  stored_u_mx2_level0[l];
  stored_u_mx1_level1  =  stored_u_mx1_level0[l];

  stored_w_0_level1    =  stored_w_0_level0[l];
  stored_w_1_level1    =  stored_w_1_level0[l];
  stored_w_2_level1    =  stored_w_2_level0[l];
  stored_w_mx3_level1  =  stored_w_mx3_level0[l];
  stored_w_mx2_level1  =  stored_w_mx2_level0[l];
  stored_w_mx1_level1  =  stored_w_mx1_level0[l];

  stored_u_1_level0[l]	=  u[1][l];
  stored_u_2_level0[l]	=  u[2][l];
  stored_u_3_level0[l]	=  u[3][l];
  stored_u_mx3_level0[l]=  u[mx3][l];
  stored_u_mx2_level0[l]=  u[mx2][l];
  stored_u_mx1_level0[l]=  u[mx1][l];

  stored_w_0_level0[l]  =  w[0][l];
  stored_w_1_level0[l]  =  w[1][l];
  stored_w_2_level0[l]  =  w[2][l];
  stored_w_mx3_level0[l]=  w[mx3][l];
  stored_w_mx2_level0[l]=  w[mx2][l];
  stored_w_mx1_level0[l]=  w[mx1][l];
}

void store_boundary_mz2() {
  for(int i=1;i<mx;i++) {
	stored_u_mz2_level1[i] = stored_u_mz2_level0[i];
    stored_u_mz2_level0[i] = u[i][mz2];
  }

  for(int i=0;i<mx;i++) {
	stored_w_mz2_level1[i] = stored_w_mz2_level0[i];
    stored_w_mz2_level0[i] = w[i][mz2];
  }
}

void store_boundary_mz3() {
  for(int i=1;i<mx;i++) {
    stored_u_mz3_level1[i] = stored_u_mz3_level0[i];
    stored_u_mz3_level0[i] = u[i][mz3];
  }

  for(int i=0;i<mx;i++) {
	stored_w_mz3_level1[i] = stored_w_mz3_level0[i];
    stored_w_mz3_level0[i] = w[i][mz3];
  }
}
