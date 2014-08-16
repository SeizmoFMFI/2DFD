#include "global.h"

void attenuate(const int l,const float k) {
	//similar function in displacement_int.cpp
	for(int i=1;i<mx;i++)
      u[i][l] *= 1 - 0.05f*k*k;

	for(int i=0;i<mx;i++)
      w[i][l] *= 1 - 0.05f*k*k;
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

	 //500
	 /*
	 if (l-l_hom>0.7f*(mz3-l_hom)) { 
		 float k = (l-l_hom) - 0.7f*(mz3-l_hom);
		 k /= 0.3f*(mz3-l_hom);
		 attenuate(l,k);
	 }
	 */
	 if (mz-l<optimalisation.attenuate_boundary_n) { 
		 float k = (float)(optimalisation.attenuate_boundary_n - (mz-l));
		 k /= optimalisation.attenuate_boundary_n;
		 attenuate(l,k);
	 }
  }

  store_boundary_mz3();
  displacement_int(mz3);
  hom_displacement_nonreflecting_mz3();

  store_boundary_mz2();
  displacement_int(mz2);
  hom_displacement_nonreflecting_mz2();
  
  hom_displacement_nonreflecting_mz1();
}
