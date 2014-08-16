#include "global.h"

void hom_velocity_int(int l) {
	int lzx1,lzx2,lzx3,lzx4;
	lzx1 = ((l+2)%4 + 0)% 4;
	lzx2 = ((l+2)%4 + 1)% 4;
	lzx3 = ((l+2)%4 + 2)% 4;
	lzx4 = ((l+2)%4 + 3)% 4;

	for (int i=3;i<mx-2;i++) {
		vu[i][l] += co_density*(a_FD*(txx_hline[i+1]    - txx_hline[i-2]
									+ tzx_mline[i][lzx4]- tzx_mline[i][lzx1])
							  + b_FD*(txx_hline[i]		- txx_hline[i-1]
									+ tzx_mline[i][lzx3]- tzx_mline[i][lzx2]));
	}

	int lzz1,lzz2,lzz3,lzz4;
	lzz1 = ((l+1)%4 + 1)% 4;
	lzz2 = ((l+1)%4 + 2)% 4;
	lzz3 = ((l+1)%4 + 3)% 4;
	lzz4 = ((l+1)%4 + 4)% 4;

	for (int i=2;i<mx-2;i++) {
		vw[i][l] += co_density*(a_FD*(tzz_mline[i][lzz4]  - tzz_mline[i][lzz1]
									+ tzx_mline[i+2][lzx2]- tzx_mline[i-1][lzx2])
							  + b_FD*(tzz_mline[i][lzz3]  - tzz_mline[i][lzz2]
									+ tzx_mline[i+1][lzx2]- tzx_mline[i][lzx2]));
	}
}

void hom_velocity_u_2nd(int i,int l) {
	int lzx2,lzx3;
    lzx2 = ((l+2)%4 + 1)%4;
    lzx3 = ((l+2)%4 + 2)%4;

	vu[i][l] += co_density*(txx_hline[i]-txx_hline[i-1]+tzx_mline[i][lzx3]-tzx_mline[i][lzx2]);
}

void hom_velocity_w_2nd(int i,int l) {
	int lzz2,lzz3,lzx2;
	lzz2 = ((l+1)%4 + 2)%4;
    lzz3 = ((l+1)%4 + 3)%4;
    lzx2 = ((l+2)%4 + 1)%4;

	vw[i][l] += co_density*(tzz_mline[i][lzz3]-tzz_mline[i][lzz2]+tzx_mline[i+1][lzx2]-tzx_mline[i][lzx2]);
}

void hom_velocity_2nd(int l) {
  hom_velocity_w_2nd(1,l);
  hom_velocity_u_2nd(2,l);

  hom_velocity_w_2nd(mx2,l);
  hom_velocity_u_2nd(mx2,l);
}

void inh_velocity_int(int l) {
	int lzx1,lzx2,lzx3,lzx4;
	lzx1 = ((l+2)%4 + 0)% 4;
	lzx2 = ((l+2)%4 + 1)% 4;
	lzx3 = ((l+2)%4 + 2)% 4;
	lzx4 = ((l+2)%4 + 3)% 4;
	for (int i=3;i<mx-2;i++) {
		vu[i][l] += density_u[i][l]*(a_FD*(txx_hline[i+1]	 -txx_hline[i-2]
										  +tzx_mline[i][lzx4]-tzx_mline[i][lzx1])
								   + b_FD*(txx_hline[i]		 -txx_hline[i-1]
										  +tzx_mline[i][lzx3]-tzx_mline[i][lzx2]));
	}

	int lzz1,lzz2,lzz3,lzz4;
	lzz1 = ((l+1)%4 + 1)% 4;
	lzz2 = ((l+1)%4 + 2)% 4;
	lzz3 = ((l+1)%4 + 3)% 4;
	lzz4 = ((l+1)%4 + 4)% 4;

	for (int i=2;i<mx-2;i++) {
		vw[i][l] += density_w[i][l]*(a_FD*(tzz_mline[i][lzz4]  - tzz_mline[i][lzz1]
										 + tzx_mline[i+2][lzx2]- tzx_mline[i-1][lzx2])
							       + b_FD*(tzz_mline[i][lzz3]  - tzz_mline[i][lzz2]
									     + tzx_mline[i+1][lzx2]- tzx_mline[i][lzx2]));
	}
}

void inh_velocity_u_2nd(int i,int l) {
	int lzx2,lzx3;
    lzx2 = ((l+2)%4 + 1)%4;
    lzx3 = ((l+2)%4 + 2)%4;

	vu[i][l] += density_u[i][l]*(txx_hline[i]-txx_hline[i-1]+tzx_mline[i][lzx3]-tzx_mline[i][lzx2]);
}

void inh_velocity_w_2nd(int i,int l) {
    int lzz2,lzz3,lzx2;
	lzz2 = ((l+1)%4 + 2)%4;
    lzz3 = ((l+1)%4 + 3)%4;
    lzx2 = ((l+2)%4 + 1)%4;

	vw[i][l] += density_w[i][l]*(tzz_mline[i][lzz3]-tzz_mline[i][lzz2]+tzx_mline[i+1][lzx2]-tzx_mline[i][lzx2]);
}

void inh_velocity_2nd(int l) {
  inh_velocity_w_2nd(1,l);
  inh_velocity_u_2nd(2,l);
  
  inh_velocity_w_2nd(mx2,l); //skontrolovat index mx2
  inh_velocity_u_2nd(mx2,l);
}
