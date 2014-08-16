#include "global.h"

void attenuate(const int l) {
	//similar function in displacement_update.cpp
	float k;
	for(int i=2;i<optimalisation.attenuate_boundary_n;i++) {
		k = (float)(optimalisation.attenuate_boundary_n - i) / optimalisation.attenuate_boundary_n;
		u[i][l] *= 1 - 0.05f*k*k;
		w[i][l] *= 1 - 0.05f*k*k;
	}

	for(int i=mx-optimalisation.attenuate_boundary_n;i<mx-1;i++) {
		k = (float)(i - (mx - optimalisation.attenuate_boundary_n)) / optimalisation.attenuate_boundary_n;
		u[i][l] *= 1 - 0.05f*k*k;
		w[i][l] *= 1 - 0.05f*k*k;
	}
}

void displacement_int(int l) {
  for(int i=2;i<mx-1;i++)
      u[i][l] += dt * vu[i][l];

  for(int i=1;i<mx-1;i++)
      w[i][l] += dt * vw[i][l];

    attenuate(l);
}
