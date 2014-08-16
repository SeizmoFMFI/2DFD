#include "global.h"

void hom_displacement_nonreflecting(int l) {
//____________________________________________________________ LEFT BOUNDARY ___
    u[1][l] = co_ale01 * u[2][l]
            + co_ale02 * u[3][l]
            + co_ale10 * stored_u_1_level0[l]  
			+ co_ale11 * stored_u_2_level0[l]
            + co_ale12 * stored_u_3_level0[l]
            + co_ale20 * stored_u_1_level1     
			+ co_ale21 * stored_u_2_level1
            + co_ale22 * stored_u_3_level1;

    w[0][l] = co_ale01 * w[1][l]
            + co_ale02 * w[2][l]
            + co_ale10 * stored_w_0_level0[l]
			+ co_ale11 * stored_w_1_level0[l]
            + co_ale12 * stored_w_2_level0[l]
            + co_ale20 * stored_w_0_level1
			+ co_ale21 * stored_w_1_level1
            + co_ale22 * stored_w_2_level1;

//___________________________________________________________ RIGHT BOUNDARY ___
    u[mx1][l] = co_ari01 * u[mx2][l]
              + co_ari02 * u[mx3][l]
              + co_ari10 * stored_u_mx1_level0[l]
			  + co_ari11 * stored_u_mx2_level0[l]
              + co_ari12 * stored_u_mx3_level0[l]
              + co_ari20 * stored_u_mx1_level1
		      + co_ari21 * stored_u_mx2_level1
              + co_ari22 * stored_u_mx3_level1;

    w[mx1][l] = co_ari01 * w[mx2][l]
              + co_ari02 * w[mx3][l]
              + co_ari10 * stored_w_mx1_level0[l]
			  + co_ari11 * stored_w_mx2_level0[l]
			  + co_ari12 * stored_w_mx3_level0[l]
              + co_ari20 * stored_w_mx1_level1
			  + co_ari21 * stored_w_mx2_level1
              + co_ari22 * stored_w_mx3_level1;
}

void hom_displacement_nonreflecting_mz3() {
//____________________________________________________________ LEFT BOUNDARY ___
	int l = mz3;
    u[1][l] = co_ale01 * u[2][l]
            + co_ale02 * u[3][l]
            + co_ale10 * stored_u_mz3_level0[1]  
			+ co_ale11 * stored_u_mz3_level0[2]
            + co_ale12 * stored_u_mz3_level0[3]
            + co_ale20 * stored_u_mz3_level1[1]     
			+ co_ale21 * stored_u_mz3_level1[2]
            + co_ale22 * stored_u_mz3_level1[3];
	
	w[0][l] = co_ale01 * w[1][l]
            + co_ale02 * w[2][l]
            + co_ale10 * stored_w_mz3_level0[0]  
			+ co_ale11 * stored_w_mz3_level0[1]
            + co_ale12 * stored_w_mz3_level0[2]
            + co_ale20 * stored_w_mz3_level1[0]     
			+ co_ale21 * stored_w_mz3_level1[1]
            + co_ale22 * stored_w_mz3_level1[2];

//___________________________________________________________ RIGHT BOUNDARY ___ 
	u[mx1][l] = co_ari01 * u[mx2][l]
              + co_ari02 * u[mx3][l]
              + co_ari10 * stored_u_mz3_level0[mx1]
			  + co_ari11 * stored_u_mz3_level0[mx2]
			  + co_ari12 * stored_u_mz3_level0[mx3]
			  + co_ari20 * stored_u_mz3_level1[mx1]
			  + co_ari21 * stored_u_mz3_level1[mx2]
			  + co_ari22 * stored_u_mz3_level1[mx3];
	
	w[mx1][l] = co_ari01 * w[mx2][l]
              + co_ari02 * w[mx3][l]
              + co_ari10 * stored_w_mz3_level0[mx1]
			  + co_ari11 * stored_w_mz3_level0[mx2]
			  + co_ari12 * stored_w_mz3_level0[mx3]
			  + co_ari20 * stored_w_mz3_level1[mx1]
			  + co_ari21 * stored_w_mz3_level1[mx2]
			  + co_ari22 * stored_w_mz3_level1[mx3];
}

void hom_displacement_nonreflecting_mz2() {
//____________________________________________________________ LEFT BOUNDARY ___
  int l=mz2;
    u[1][l] = co_ale01 * u[2][l]
            + co_ale02 * u[3][l]
            + co_ale10 * stored_u_mz2_level0[1]  
			+ co_ale11 * stored_u_mz2_level0[2]
            + co_ale12 * stored_u_mz2_level0[3]
            + co_ale20 * stored_u_mz2_level1[1]     
			+ co_ale21 * stored_u_mz2_level1[2]
            + co_ale22 * stored_u_mz2_level1[3];
	
	w[0][l] = co_ale01 * w[1][l]
            + co_ale02 * w[2][l]
            + co_ale10 * stored_w_mz2_level0[0]  
			+ co_ale11 * stored_w_mz2_level0[1]
            + co_ale12 * stored_w_mz2_level0[2]
            + co_ale20 * stored_w_mz2_level1[0]     
			+ co_ale21 * stored_w_mz2_level1[1]
            + co_ale22 * stored_w_mz2_level1[2];

//___________________________________________________________ RIGHT BOUNDARY ___ 
	u[mx1][l] = co_ari01 * u[mx2][l]
              + co_ari02 * u[mx3][l]
              + co_ari10 * stored_u_mz2_level0[mx1]
			  + co_ari11 * stored_u_mz2_level0[mx2]
			  + co_ari12 * stored_u_mz2_level0[mx3]
			  + co_ari20 * stored_u_mz2_level1[mx1]
			  + co_ari21 * stored_u_mz2_level1[mx2]
			  + co_ari22 * stored_u_mz2_level1[mx3];
	
	w[mx1][l] = co_ari01 * w[mx2][l]
              + co_ari02 * w[mx3][l]
              + co_ari10 * stored_w_mz2_level0[mx1]
		 	  + co_ari11 * stored_w_mz2_level0[mx2]
			  + co_ari12 * stored_w_mz2_level0[mx3]
			  + co_ari20 * stored_w_mz2_level1[mx1]
			  + co_ari21 * stored_w_mz2_level1[mx2]
			  + co_ari22 * stored_w_mz2_level1[mx3];
}

void hom_displacement_nonreflecting_mz1() {
  for (int i=2;i<mx1;i++) {
	  stored_u_mz1_level1    = stored_u_mz1_level0[i];
	  stored_u_mz1_level0[i] = u[i][mz1];

	  u[i][mz1] = co_abt01 * u[i][mz2]
			    + co_abt02 * u[i][mz3]
			    + co_abt10 * stored_u_mz1_level0[i]
			    + co_abt11 * stored_u_mz2_level0[i]
			    + co_abt12 * stored_u_mz3_level0[i]
			    + co_abt20 * stored_u_mz1_level1
			    + co_abt21 * stored_u_mz2_level1[i]
			    + co_abt22 * stored_u_mz3_level1[i];
  }

  for (int i=1;i<mx1;i++) {
	  stored_w_mz1_level1    = stored_w_mz1_level0[i];
	  stored_w_mz1_level0[i] = w[i][mz1];

	  w[i][mz1] = co_abt01 * w[i][mz2]
			    + co_abt02 * w[i][mz3]
			    + co_abt10 * stored_w_mz1_level0[i]
			    + co_abt11 * stored_w_mz2_level0[i]
			    + co_abt12 * stored_w_mz3_level0[i]
			    + co_abt20 * stored_w_mz1_level1
			    + co_abt21 * stored_w_mz2_level1[i]
			    + co_abt22 * stored_w_mz3_level1[i];
  }
}

void inh_displacement_nonreflecting(int l) {
//____________________________________________________________ LEFT BOUNDARY ___
    u[1][l] = ale01[l] * u[2][l]
            + ale02[l] * u[3][l]
            + ale10[l] * stored_u_1_level0[l]  
			+ ale11[l] * stored_u_2_level0[l]
            + ale12[l] * stored_u_3_level0[l]
            + ale20[l] * stored_u_1_level1     
			+ ale21[l] * stored_u_2_level1
            + ale22[l] * stored_u_3_level1;

    w[0][l] = ale01[l] * w[1][l]
            + ale02[l] * w[2][l]
            + ale10[l] * stored_w_0_level0[l]
			+ ale11[l] * stored_w_1_level0[l]
            + ale12[l] * stored_w_2_level0[l]
            + ale20[l] * stored_w_0_level1
			+ ale21[l] * stored_w_1_level1
            + ale22[l] * stored_w_2_level1;

//___________________________________________________________ RIGHT BOUNDARY ___
    u[mx1][l] = ari01[l] * u[mx2][l]
              + ari02[l] * u[mx3][l]
              + ari10[l] * stored_u_mx1_level0[l]
			  + ari11[l] * stored_u_mx2_level0[l]
              + ari12[l] * stored_u_mx3_level0[l]
              + ari20[l] * stored_u_mx1_level1
			  + ari21[l] * stored_u_mx2_level1
              + ari22[l] * stored_u_mx3_level1;

    w[mx1][l] = ari01[l] * w[mx2][l]
              + ari02[l] * w[mx3][l]
              + ari10[l] * stored_w_mx1_level0[l]
			  + ari11[l] * stored_w_mx2_level0[l]
			  + ari12[l] * stored_w_mx3_level0[l]
              + ari20[l] * stored_w_mx1_level1
			  + ari21[l] * stored_w_mx2_level1
              + ari22[l] * stored_w_mx3_level1;
}