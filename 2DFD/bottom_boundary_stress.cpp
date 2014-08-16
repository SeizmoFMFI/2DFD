#include "global.h"

void bottom_boundary_2_stress_int() {
  ll  = mz-2;
  int lp1 = ll+1;

  for(int i=1;i<mx1;i++) {
	  e1 = u[i+1][ll] - u[i][ll];
	  e2 = w[i][lp1] - w[i][ll];

	  txx_hline[i] = co_lam2mu*e1 + co_lam*e2;
  }
}

void bottom_boundary_2_stress_2nd() {
  hom_stress_zz_2nd(1,mz2);
  hom_stress_zx_2nd(1,mz2);
  hom_stress_zz_2nd(mx2,mz2);
  hom_stress_zx_2nd(mx1,mz2);
}

void bottom_boundary_3_stress_int() {
	ll  = mz-3;

	for(int i=2;i<mx2;i++) {
		compute_e1_e2_int(i,ll);

		txx_hline[i] = co_lam2mu*e1 + co_lam*e2;
	}

	ll++;
	int ll_ind = (ll%4 + 0)%4;
	for(int i=2;i<mx2;i++) {
		compute_e1_e2_2nd(i,ll);
		tzz_mline[i][ll_ind] = co_lam*e1 + co_lam2mu*e2;
	}

	ll++;
	ll_ind = (ll%4 + 3)%4;
	for(int i=2;i<mx1;i++) {
		compute_e12_2nd(i,ll);
		tzx_mline[i][ll_ind] = co_mu*e12;
	}
}
