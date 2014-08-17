#include "global.h"
int max_num_iter,tmp;

bool InputOutput::load_data() {
	FILE* in = fopen(files.input_data,"r");
	if (in == NULL) {
		ERR("No input data file");
		return false;
	}

	float time;
	tmp = fscanf(in, "%d", &mx);
	tmp = fscanf(in, "%f", &time);
	tmp = fscanf(in, "%f", &dt);
	max_num_iter = (int)(time / dt);

	tmp = fscanf(in, "%f", &time);
	iter_when_record_snapshot = (int)(time / dt);
	tmp = fscanf(in, "%d", &record_sparse_every_n_binary);
	tmp = fscanf(in, "%d", &record_sparse_every_n_txt);
	tmp = fscanf(in, "%d", &sparse_spacing);

	fclose(in);
	return true;
}


