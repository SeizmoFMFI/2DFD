#include "global.h"

void bottom_boundary_2_velocity() {
  int l = mz-2;
  int lzx2 = ((l+2)%4 + 1)%4;
  int lzx3 = ((l+2)%4 + 2)%4;

  for (int i=2;i<mx1;i++) {
	  vu[i][l] += co_density*(txx_hline[i]       - txx_hline[i-1]
							+ tzx_mline[i][lzx3] - tzx_mline[i][lzx2]);
  }

  int lzz2 = ((l+1)%4 + 2)%4;
  int lzz3 = ((l+1)%4 + 3)%4;

  for (int i=1;i<mx1;i++) {
	  vw[i][l] += co_density*(tzz_mline[i][lzz3]   - tzz_mline[i][lzz2]
							+ tzx_mline[i+1][lzx2] - tzx_mline[i][lzx2]);
  }
}