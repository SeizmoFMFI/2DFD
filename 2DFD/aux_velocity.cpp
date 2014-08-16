#include "global.h"

void compute_e1_e2_int(int i,int l) {
	e1 = a_FD*(u[i+2][l]-u[i-1][l])
	   + b_FD*(u[i+1][l]-u[i][l]);

    e2 = a_FD*(w[i][l+2]-w[i][l-1])
	   + b_FD*(w[i][l+1]-w[i][l]);
}

void compute_e1_e2_2nd(int i,int l) {
	e1 = u[i+1][l]-u[i][l];
    e2 = w[i][l+1]-w[i][l];
}

void compute_e12_int(int i,int l) {
	e12= a_FD*(u[i][l+1] - u[i][l-2]
			 + w[i+1][l] - w[i-2][l] )
	   + b_FD*(u[i]  [l] - u[i][l-1]
			 + w[i]  [l] - w[i-1][l] );
}

void compute_e12_2nd(int i,int l) {
	e12= u[i][l] - u[i][l-1]
       + w[i][l] - w[i-1][l];
}

void nastav_lambda(int i,int l) {
      lam_il     = lam[i][l];
      lam2mu_il  = lam_il + 2* mu[i][l];
}

void vyrataj_xx(int i) {
     txx_hline[i] = lam2mu_il * e1 + lam_il *e2;
}

void vyrataj_zz(int i,int lzz) {
     tzz_mline[i][lzz] = lam_il * e1 + lam2mu_il * e2;
}

void vyrataj_zx(int i,int l,int lzx) {
    tzx_mline[i][lzx] = muzx[i][l] * e12;
}