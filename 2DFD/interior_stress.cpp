#include "global.h"

void hom_stress_int(int l) {
	for(int i=2;i<mx2;i++) {
		compute_e1_e2_int(i,l);
		txx_hline[i] = co_lam2mu*e1 + co_lam*e2;
	}

	ll = l+1;
	ll_ind = (ll%4 + 0)%4;

	for(int i=2;i<mx2;i++) {
		compute_e1_e2_int(i,ll);
		tzz_mline[i][ll_ind] = co_lam*e1 + co_lam2mu*e2;
	}

	ll = l+2;
	ll_ind = (ll%4 + 3)%4;
	
	for(int i=2;i<mx1;i++) {
		compute_e12_int(i,ll);
		tzx_mline[i][ll_ind] = co_mu*e12;
	}
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX hom 2nd

void hom_stress_xx_2nd(int i,int l) {
	compute_e1_e2_2nd(i,l);
	txx_hline[i] = co_lam2mu*e1 + co_lam*e2;
}

void hom_stress_zx_2nd(int i,int l) {
	ll_ind = ((l+2)%4 + 1)%4;
	e12 = u[i][l] - u[i][l-1] + w[i][l] - w[i-1][l];
	tzx_mline[i][ll_ind] = co_mu*e12;
}

void hom_stress_zz_2nd(int i,int l) {
	ll_ind = ((l+1)%4 + 3)%4;
	compute_e1_e2_2nd(i,l);
	tzz_mline[i][ll_ind] = co_lam*e1 + co_lam2mu*e2;
}

void hom_stress_2nd(int l) {
  hom_stress_xx_2nd(1,l);
  hom_stress_zx_2nd(1,l);
  hom_stress_zz_2nd(1,l);
  
  hom_stress_zz_2nd(mx2,l);
  hom_stress_xx_2nd(mx2,l);
  hom_stress_zx_2nd(mx1,l);
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX inh int

void inh_stress_int(int l) {
	for(int i=2;i<mx2;i++) {
		nastav_lambda(i,l);
		compute_e1_e2_int(i,l);
		vyrataj_xx(i);
	}

	ll = l+1;
	ll_ind = (ll + 0)%4;

	for(int i=2;i<mx2;i++) {
		nastav_lambda(i,ll);
		compute_e1_e2_int(i,ll);
		vyrataj_zz(i,ll_ind);
	}

	ll = l+2;
	ll_ind = (ll + 3)%4;

	for(int i=2;i<mx1;i++) {
		compute_e12_int(i,ll);
		vyrataj_zx(i,ll,ll_ind);
	}
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX inh 2nd

void inh_stress_xx_2nd(int i,int l) {
	nastav_lambda(i,l);
	compute_e1_e2_2nd(i,l);
	vyrataj_xx(i);
}

void inh_stress_zz_2nd(int i,int l) {
	ll_ind = ((l+1)%4 + 3)%4;
	
	nastav_lambda(i,l);
	compute_e1_e2_2nd(i,l);
	vyrataj_zz(i,ll_ind);
}

void inh_stress_zx_2nd(int i, int l) {
	ll_ind = ((l+2)%4 +1)%4;
	e12 = u[i][l] - u[i][l-1] + w[i][l] - w[i-1][l];
	vyrataj_zx(i,l,ll_ind);
}

void inh_stress_2nd(int l) {
  inh_stress_xx_2nd(1,l);
  inh_stress_zx_2nd(1,l);
  inh_stress_zz_2nd(1,l);
 
  inh_stress_zz_2nd(mx2,l);
  inh_stress_xx_2nd(mx2,l);
  inh_stress_zx_2nd(mx1,l);
}
