#include "global.h"

void Optimalisation::attenuate_bottom() {
	const float dlzka = 40.f;
	for(int l=src[active_source].z;l<mz;l++) {
		const float at = exp(-SQR((float)(src[active_source].z - l)/dlzka));
		for(int i=0;i<mx;i++) {
			u[i][l] *= at;
			w[i][l] *= at;
			vu[i][l]*= at;
			vw[i][l]*= at;
		}
	}
	attenuate_NR_bounds(dlzka);
}
void Optimalisation::attenuate_NR_bounds(const float dlzka) {
	for(int i=0;i<mx;i++) {
		stored_w_mz1_level0[i] = 0;
		stored_w_mz2_level0[i] = 0;
		stored_w_mz2_level1[i] = 0;
		stored_w_mz3_level0[i] = 0;
		stored_w_mz3_level1[i] = 0;

		stored_u_mz1_level0[i] = 0;
		stored_u_mz2_level0[i] = 0;
		stored_u_mz2_level1[i] = 0;
		stored_u_mz3_level0[i] = 0;
		stored_u_mz3_level1[i] = 0;
	}

	for(int l=src[active_source].z;l<mz;l++) {
		const float at = exp(-SQR((float)(src[active_source].z - l)/dlzka));
		stored_u_1_level0[l] *= at;
		stored_u_2_level0[l] *= at;
		stored_u_3_level0[l] *= at;

		stored_u_mx1_level0[l] *= at;
		stored_u_mx2_level0[l] *= at;
		stored_u_mx3_level0[l] *= at;
	}
}
