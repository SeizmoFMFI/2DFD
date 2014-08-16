#include "global.h"

void prepare_receivers() {
	int n_rec = get_input("Number of receivers:",0,100);

	FILE *out = fopen("receivers.txt","w");
	fprintf(out,"%d\n",n_rec);
    //prepares random positions at the surface - you can edit them manualy later
	for (int i=0;i<n_rec;i++) {
		fprintf(out,"%f %f\n",(float)rand()/(float)RAND_MAX*0.8f+0.1f,0.f);
	}
	
	fclose(out);
}