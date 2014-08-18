#include "global.h"

void attenuate_horizontal_line(const int l) {
	//similar function in displacement_int.cpp
	float k = ((float)(attenuate_boundary_n - (mz - l))) / attenuate_boundary_n;
	k = 1 - 0.05f*SQR(k);

	for(int i=1;i<mx;i++)
      u[i][l] *= k;

	for(int i=0;i<mx;i++)
      w[i][l] *= k;
}

void displacement_update() {
  for(int l=0;l<l_hom;l++) {
     store_boundary(l);
     displacement_int(l);
     inh_displacement_nonreflecting(l);
  }
  
  for(int l=l_hom;l<mz3;l++) {
     store_boundary(l);
     displacement_int(l);
     hom_displacement_nonreflecting(l);
  }

  store_boundary_mz3();
  displacement_int(mz3);
  hom_displacement_nonreflecting_mz3();

  store_boundary_mz2();
  displacement_int(mz2);
  hom_displacement_nonreflecting_mz2();
  
  hom_displacement_nonreflecting_mz1();

  for (int l = mz - attenuate_boundary_n + 1; l < mz; l++) {
	  attenuate_horizontal_line(l);
  }
}
