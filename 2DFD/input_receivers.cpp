#include "global.h"

int n_rec;
Receiver rec[50];

bool InputOutput::load_receivers() {
	int tmp;
	FILE* in = fopen(files.input_receivers,"r");
	if (in == NULL) {
		ERR("No input receivers file");
		return false;
	}

	tmp = fscanf(in,"%d",&n_rec);
	if (n_rec > 50) {
		ERR("Too many receivers");
		return false;
	}

	for(int i=0;i<n_rec;i++) {
		float sx,sz;
		tmp = fscanf(in,"%f %f",&sx,&sz); 
		rec[i].x=(int)(sx*(mx-2*attenuate_boundary_n+0.5)) + attenuate_boundary_n;
		rec[i].z=(int)(sz*(mz - attenuate_boundary_n+0.5));
	}
	fclose(in);

	return true;
}
