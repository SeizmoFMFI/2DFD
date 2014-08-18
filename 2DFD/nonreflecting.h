#ifndef NONREFLECTING_H
#define NONREFLECTING_H
#include "global.h"

class NonReflectingEmermanStephenmaxP {
public:
	void set_nonreflecting_coeff(), set_starting_values_for_boundaries();
	float co_vP;
};

extern NonReflectingEmermanStephenmaxP nonreflecting;

const static int  attenuate_boundary_n = 100; //180;

extern float stored_u_1_level0[BIGDIM],stored_u_2_level0[BIGDIM],stored_u_3_level0[BIGDIM],
	  stored_u_mx3_level0[BIGDIM],stored_u_mx2_level0[BIGDIM],stored_u_mx1_level0[BIGDIM],
	  stored_u_1_level1,stored_u_2_level1,stored_u_3_level1,
	  stored_u_mx3_level1,stored_u_mx2_level1,stored_u_mx1_level1,

	  stored_u_mz2_level0[BIGDIM],stored_u_mz2_level1[BIGDIM],
	  stored_u_mz3_level0[BIGDIM],stored_u_mz3_level1[BIGDIM];
	  
extern float stored_w_0_level0[BIGDIM],stored_w_1_level0[BIGDIM],stored_w_2_level0[BIGDIM],
	  stored_w_mx3_level0[BIGDIM],stored_w_mx2_level0[BIGDIM],stored_w_mx1_level0[BIGDIM],
	  stored_w_0_level1,stored_w_1_level1,stored_w_2_level1,
	  stored_w_mx3_level1,stored_w_mx2_level1,stored_w_mx1_level1,

	  stored_w_mz2_level0[BIGDIM],stored_w_mz2_level1[BIGDIM],
	  stored_w_mz3_level0[BIGDIM],stored_w_mz3_level1[BIGDIM];

extern float stored_u_mz1_level1,stored_u_mz1_level0[BIGDIM],
	  stored_w_mz1_level1,stored_w_mz1_level0[BIGDIM];
extern float 
	stored_u_mz_level0[BIGDIM],stored_u_mz_level1,stored_w_mz_level0[BIGDIM],stored_w_mz_level1;

extern float ale01[BIGDIM],ale02[BIGDIM],ale10[BIGDIM],ale11[BIGDIM],ale12[BIGDIM],ale20[BIGDIM],ale21[BIGDIM],ale22[BIGDIM],
	  ari01[BIGDIM],ari02[BIGDIM],ari10[BIGDIM],ari11[BIGDIM],ari12[BIGDIM],ari20[BIGDIM],ari21[BIGDIM],ari22[BIGDIM],
	  co_ale01,co_ale02,co_ale10,co_ale11,co_ale12,co_ale20,co_ale21,co_ale22,
	  co_ari01,co_ari02,co_ari10,co_ari11,co_ari12,co_ari20,co_ari21,co_ari22,
	  co_abt01,co_abt02,co_abt10,co_abt11,co_abt12,co_abt20,co_abt21,co_abt22;

#endif
