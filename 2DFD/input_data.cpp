#include "global.h"
int max_num_iter,source_num_active_iter,tmp;
int key_typ_src_function,record_every_nth_step;

//sprintf (name,"sirenia_stanice/out_at_%d_riedke.dat",zdroj);
void loadData() {
	FILE* in = fopen(files.input_data,"r");
	if (in == NULL) {
		ERR("No input data file");
	}
	tmp = fscanf(in,"%d %d",&max_num_iter,&record_every_nth_step);
	tmp = fscanf(in,"%f",&dt);
	tmp = fscanf(in,"%d",&optimalisation.iter_when_save_state);

	fclose(in);
}
