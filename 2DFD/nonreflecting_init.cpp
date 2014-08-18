#include "global.h"

float ale01[BIGDIM], ale02[BIGDIM], ale10[BIGDIM], ale11[BIGDIM], ale12[BIGDIM], ale20[BIGDIM], ale21[BIGDIM], ale22[BIGDIM],
		ari01[BIGDIM], ari02[BIGDIM], ari10[BIGDIM], ari11[BIGDIM], ari12[BIGDIM], ari20[BIGDIM], ari21[BIGDIM], ari22[BIGDIM],
		co_ale01, co_ale02, co_ale10, co_ale11, co_ale12, co_ale20, co_ale21, co_ale22,
		co_ari01, co_ari02, co_ari10, co_ari11, co_ari12, co_ari20, co_ari21, co_ari22,
		co_abt01, co_abt02, co_abt10, co_abt11, co_abt12, co_abt20, co_abt21, co_abt22;

void NonReflectingEmermanStephenmaxP::set_nonreflecting_coeff() {
	//_________________________________ Emerman & Stephen, max. P-w. att. ___
	float t1, t2, alfa;

	for (int l = 0; l<l_hom; l++) {
		//left
		alfa = sqrtf((lam[0][l] + 2 * mu[0][l]) *density_w[0][l] * h*h / dt);
		t1 = (dt - h / alfa) / (dt + h / alfa);
		t2 = 2.0f*h / alfa / (dt + h / alfa);
		ale01[l] = t1;
		ale02[l] = 0.0f;
		ale10[l] = t2;
		ale11[l] = t2;
		ale12[l] = 0.0f;
		ale20[l] = t1;
		ale21[l] = -1.0f;
		ale22[l] = 0.0f;

		//right
		alfa = sqrtf((lam[mx1][l] + 2 * mu[mx1][l]) *density_w[mx1][l] * h*h / dt);
		t1 = (dt - h / alfa) / (dt + h / alfa);
		t2 = 2.0f*h / alfa / (dt + h / alfa);
		ari01[l] = t1;
		ari02[l] = 0.0f;
		ari10[l] = t2;
		ari11[l] = t2;
		ari12[l] = 0.0f;
		ari20[l] = t1;
		ari21[l] = -1.0f;
		ari22[l] = 0.0f;
	}

	t1 = (dt - h / co_vP) / (dt + h / co_vP);
	t2 = 2.0f*h / co_vP / (dt + h / co_vP);
	//left_hom
	co_ale01 = t1;
	co_ale02 = 0.0f;
	co_ale10 = t2;
	co_ale11 = t2;
	co_ale12 = 0.0f;
	co_ale20 = t1;
	co_ale21 = -1.0f;
	co_ale22 = 0.0f;
	//right_hom
	co_ari01 = t1;
	co_ari02 = 0.0f;
	co_ari10 = t2;
	co_ari11 = t2;
	co_ari12 = 0.0f;
	co_ari20 = t1;
	co_ari21 = -1.0f;
	co_ari22 = 0.0f;
	//bottom_hom
	co_abt01 = t1;
	co_abt02 = 0.0f;
	co_abt10 = t2;
	co_abt11 = t2;
	co_abt12 = 0.0f;
	co_abt20 = t1;
	co_abt21 = -1.0f;
	co_abt22 = 0.0f;
}
void NonReflectingEmermanStephenmaxP::set_starting_values_for_boundaries() {
	for (int i = 0; i<mx; i++) {
		stored_u_mz1_level0[i] = 0;
		stored_u_mz2_level0[i] = 0;
		stored_u_mz2_level1[i] = 0;
		stored_u_mz3_level0[i] = 0;
		stored_u_mz3_level1[i] = 0;

		stored_w_mz1_level0[i] = 0;
		stored_w_mz2_level0[i] = 0;
		stored_w_mz2_level1[i] = 0;
		stored_w_mz3_level0[i] = 0;
		stored_w_mz3_level1[i] = 0;
	}
	for (int l = 0; l<mz; l++) {
		stored_u_1_level0[l] = 0;
		stored_u_2_level0[l] = 0;
		stored_u_3_level0[l] = 0;
		stored_u_mx3_level0[l] = 0;
		stored_u_mx2_level0[l] = 0;
		stored_u_mx1_level0[l] = 0;

		stored_w_0_level0[l] = 0;
		stored_w_1_level0[l] = 0;
		stored_w_2_level0[l] = 0;
		stored_w_mx3_level0[l] = 0;
		stored_w_mx2_level0[l] = 0;
		stored_w_mx1_level0[l] = 0;
	}
	stored_u_1_level1 = 0;
	stored_u_2_level1 = 0;
	stored_u_3_level1 = 0;
	stored_u_mx3_level1 = 0;
	stored_u_mx2_level1 = 0;
	stored_u_mx1_level1 = 0;

	stored_w_0_level1 = 0;
	stored_w_1_level1 = 0;
	stored_w_2_level1 = 0;
	stored_w_mx3_level1 = 0;
	stored_w_mx2_level1 = 0;
	stored_w_mx1_level1 = 0;

	stored_u_mz1_level1 = 0;
	stored_w_mz1_level1 = 0;
}