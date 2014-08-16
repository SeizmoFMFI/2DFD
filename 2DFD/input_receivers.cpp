#include "global.h"

void loadReceivers() {
	load_grid();

	FILE* in = fopen(files.input_receivers,"r");
	if (in == NULL) {
		ERR("No input receivers file");
	}

	tmp = fscanf(in,"%d",&n_rec);
	if (n_rec>50) 
		ERR("Too many receivers");

	for(int i=0;i<n_rec;i++) {
		float sx,sz;
		tmp = fscanf(in,"%f %f",&sx,&sz); 
		rec[i].x=(int)(sx*(mx-2*optimalisation.attenuate_boundary_n+0.5)) + optimalisation.attenuate_boundary_n;
		rec[i].z=(int)(sz*(mz - optimalisation.attenuate_boundary_n+0.5));
	}
	fclose(in);
}
