#include "global.h"

void free_surface_TXX_2nd(int i, int l) {
	nastav_lambda(i, l);
	compute_e1_e2_2nd(i, l);
	vyrataj_xx(i);
}

void free_surface_TZZ_2nd(int i, int l) {
	nastav_lambda(i, l);
	compute_e1_e2_2nd(i, l);
	vyrataj_zz(i, l);
}

void free_surface_TZX_2nd(int i, int l) {
	compute_e12_2nd(i, l);
	vyrataj_zx(i, l, l - 1);
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX   surface       XXXXXXXXXXXXXXXXXXXXXXX
void free_surface_0_stress_int() {
	for (int i = 2; i<mx2; i++) {
		nastav_lambda(i, 0);

		e1 = a_FD*(u[i + 2][0] - u[i - 1][0]) + b_FD*(u[i + 1][0] - u[i][0]);
		e2 = -22.0f*w[i][0]
			+ 17.0f*w[i][1]
			+ 9.0f*w[i][2]
			- 5.0f*w[i][3]
			+ w[i][4];
		e2 /= 24.0f;

		vyrataj_xx(i);
		vyrataj_zz(i, 0);
	}

	for (int i = 2; i<mx2; i++) {
		nastav_lambda(i, 1);
		compute_e1_e2_int(i, 1);
		vyrataj_zz(i, 1);
	}

	for (int i = 2; i<mx2; i++) {
		nastav_lambda(i, 2);
		compute_e1_e2_int(i, 2);
		vyrataj_zz(i, 2);
	}

	for (int i = 2; i<mx2; i++) {
		nastav_lambda(i, 3);
		compute_e1_e2_int(i, 3);
		vyrataj_zz(i, 3);
	}

	float w_tmp;
	for (int i = 2; i<mx1; i++) {
		w_tmp = -a_FD*(w[i + 1][0] - w[i - 2][0])
			- b_FD*(w[i][0] - w[i - 1][0]);
		e12 = a_FD*(w[i + 1][1] - w[i - 2][1])
			+ b_FD*(w[i][1] - w[i - 1][1])
			- w_tmp / 22
			- 577 * u[i][0] / 528
			+ 603 * u[i][1] / 528
			- 27 * u[i][2] / 528
			+ 1 * u[i][3] / 528;

		vyrataj_zx(i, 1, 0);
	}

	for (int i = 2; i<mx1; i++) {
		compute_e12_int(i, 2);
		vyrataj_zx(i, 2, 1);
	}

	for (int i = 2; i<mx1; i++) {
		compute_e12_int(i, 3);
		vyrataj_zx(i, 3, 2);
	}

	for (int i = 2; i<mx1; i++) {
		compute_e12_int(i, 4);
		vyrataj_zx(i, 4, 3);
	}
}

void free_surface_0_stress_2nd() {
	free_surface_TXX_2nd(1, 0);
	free_surface_TZZ_2nd(1, 0);

	free_surface_TXX_2nd(mx2, 0);
	free_surface_TZZ_2nd(mx2, 0);

	free_surface_TZZ_2nd(1, 1);
	free_surface_TZZ_2nd(1, 2);
	free_surface_TZZ_2nd(1, 3);

	free_surface_TZZ_2nd(mx2, 1);
	free_surface_TZZ_2nd(mx2, 2);
	free_surface_TZZ_2nd(mx2, 3);

	free_surface_TZX_2nd(1, 1);
	free_surface_TZX_2nd(1, 2);
	free_surface_TZX_2nd(1, 3);
	free_surface_TZX_2nd(1, 4);

	free_surface_TZX_2nd(mx1, 1);
	free_surface_TZX_2nd(mx1, 2);
	free_surface_TZX_2nd(mx1, 3);
	free_surface_TZX_2nd(mx1, 4);
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX   surface - 1   XXXXXXXXXXXXXXXXXXXXXXX
void free_surface_1_stress_int() {
	for (int i = 2; i<mx2; i++) {
		nastav_lambda(i, 1);
		compute_e1_e2_int(i, 1);
		vyrataj_xx(i);
	}
}

void free_surface_1_stress_2nd() {
	free_surface_TXX_2nd(1, 1);
	free_surface_TXX_2nd(mx2, 1);
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX   surface - 2   XXXXXXXXXXXXXXXXXXXXXXX
void free_surface_2_stress_int() {
	for (int i = 2; i<mx2; i++) {
		nastav_lambda(i, 2);
		compute_e1_e2_int(i, 2);
		vyrataj_xx(i);
	}
}

void free_surface_2_stress_2nd() {
	free_surface_TXX_2nd(1, 2);
	free_surface_TXX_2nd(mx2, 2);
}
