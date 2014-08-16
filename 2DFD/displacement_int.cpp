#include "global.h"

void attenuate(const int l) {
	//similar function in displacement_update.cpp
	float k;
	for(int i=2;i<attenuate_boundary_n;i++) {
		k = (float)(attenuate_boundary_n - i) / attenuate_boundary_n;
		k = 1 - 0.05f*SQR(k);
		u[i][l] *= k;
		w[i][l] *= k;
	}

	for(int i=mx-attenuate_boundary_n;i<mx-1;i++) {
		k = (float)(i - (mx - attenuate_boundary_n)) / attenuate_boundary_n;
		k = 1 - 0.05f*SQR(k);
		u[i][l] *= k;
		w[i][l] *= k;
	}
}

void displacement_int(int l) {
  for(int i=2;i<mx-1;i++)
      u[i][l] += dt * vu[i][l];

  for(int i=1;i<mx-1;i++)
      w[i][l] += dt * vw[i][l];

    attenuate(l);
}
