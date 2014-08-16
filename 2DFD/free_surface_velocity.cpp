#include "global.h"

void free_surface_0_velocity_int() {
  for(int i=3;i<mx2;i++) {
      vu[i][0] += density_u[i][0]*(a_FD*(txx_hline[i+1]-txx_hline[i-2])
                                 + b_FD*(txx_hline[i]  -txx_hline[i-1])
                                 +17.0f* tzx_mline[i][0]/24.0f
                                 + 9.0f* tzx_mline[i][1]/24.0f
                                 - 5.0f* tzx_mline[i][2]/24.0f
                                 +       tzx_mline[i][3]/24.0f);
  }
      
  for(int i=2;i<mx2;i++) {
    vw[i][0] += density_w[i][0]*(35.0f* tzz_mline[i][0]/ 8.0f
                             -   35.0f* tzz_mline[i][1]/24.0f
                             +   21.0f* tzz_mline[i][2]/40.0f
                             -    5.0f* tzz_mline[i][3]/56.0f);
  }
}

void free_surface_0_VU_2nd(int i,int l) {
     vu[i][l] += density_u[i][l]*(txx_hline[i]-txx_hline[i-1]+tzx_mline[i][0]);
}

void free_surface_0_VW_2nd(int i,int l) {
     vw[i][l] += density_w[i][l]*(3.0f*tzz_mline[i][0] - tzz_mline[i][1]/3.0f);
}

void free_surface_0_velocity_2nd() {
  free_surface_0_VW_2nd(1,0);
  free_surface_0_VU_2nd(2,0);

  free_surface_0_VU_2nd(mx2,0);
  free_surface_0_VW_2nd(mx2,0);
}

void free_surface_1_velocity_int() {
  int i,l=1;

  for(i=3;i<mx2;i++) {
    vu[i][l] += density_u[i][l]*(a_FD*(txx_hline[i+1] - txx_hline[i-2] + tzx_mline[i][2])
                               + b_FD*(txx_hline[i]   - txx_hline[i-1] + tzx_mline[i][1] - tzx_mline[i][0]));
  }

  for(i=2;i<mx2;i++) {
		vw[i][l] += density_w[i][l]*(a_FD*(tzx_mline[i+2][0] - tzx_mline[i-1][0])
								   + b_FD*(tzx_mline[i+1][0] - tzx_mline[i]  [0]) 
								   -31.0f/ 24.0f * tzz_mline[i][0]
								   +29.0f/ 24.0f * tzz_mline[i][1]
								   - 3.0f/ 40.0f * tzz_mline[i][2]
								   + 1.0f/168.0f * tzz_mline[i][3] );
  }
}

void free_surface_1_VU_2nd(int i,int l) {
	vu[i][l] += density_u[i][l] * (txx_hline[i] - txx_hline[i-1] + tzx_mline[i][1] - tzx_mline[i][0]);
}

void free_surface_1_VW_2nd(int i,int l) {
    vw[i][l] += density_w[i][l] * (tzz_mline[i][1] - tzz_mline[i][0] + tzx_mline[i+1][0] - tzx_mline[i][0]);
}

void free_surface_1_velocity_2nd() {
  free_surface_1_VW_2nd(1,1);
  free_surface_1_VU_2nd(2,1);

  free_surface_1_VU_2nd(mx2,1);
  free_surface_1_VW_2nd(mx2,1);
}

void free_surface_2_velocity_int() {
	int l=2;

	for(int i=3;i<mx2;i++) {
		vu[i][l] += density_u[i][l]*(a_FD*(txx_hline[i+1] - txx_hline[i-2] + tzx_mline[i][3] - tzx_mline[i][0])
                                   + b_FD*(txx_hline[i]   - txx_hline[i-1] + tzx_mline[i][2] - tzx_mline[i][1]));
	}

	for(int i=2;i<mx2;i++) {
		vw[i][l] += density_w[i][l]*(a_FD*(tzx_mline[i+2][1] - tzx_mline[i-1][1]
										 + tzz_mline[i][3]   - tzz_mline[i][0])
								   + b_FD*(tzx_mline[i+1][1] - tzx_mline[i][1]
										 + tzz_mline[i][2]   - tzz_mline[i][1]));
	}
}

void free_surface_2_VU_2nd(int i,int l) {
	vu[i][l] += density_u[i][l] * (txx_hline[i] - txx_hline[i-1] + tzx_mline[i][2] - tzx_mline[i][1]);
}

void free_surface_2_VW_2nd(int i,int l) {
    vw[i][l] += density_w[i][l] * (tzz_mline[i][2] - tzz_mline[i][1] + tzx_mline[i+1][1] - tzx_mline[i][1]);
}

void free_surface_2_velocity_2nd() {
	free_surface_1_VW_2nd(1,2);
	free_surface_1_VU_2nd(2,2);

	free_surface_1_VU_2nd(mx2,2);
	free_surface_1_VW_2nd(mx2,2);
}
