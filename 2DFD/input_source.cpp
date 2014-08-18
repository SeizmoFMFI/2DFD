#include "global.h"

int n_src,src_type,src_time_function;
float src_char_time;
Source src[50];

bool InputOutput::load_sources() {
	int tmp;
	FILE* in = fopen(files.input_source,"r");
	if (in == NULL) {
		cout<<files.input_source<<endl;
		ERR("No input source file");
		return false;
	}
	/*

	for (int i = 0; i < n_src; i++) {
	cout << "moment M0 and dip [degrees] of source " << i << ": ";
	fprintf(out, "%f %f\n", tmpm, tmpd);

	for (int i = 0; i<n_src; i++) {
	fprintf(out, "%f %f\n", sx, sz);
	}
	fclose(out);
	*/
	tmp = fscanf(in,"%d",&n_src);
	if (n_src > 50) {
		ERR("Err: privela zdrojov");
		return false;
	}
	tmp = fscanf(in,"%d %d",&src_type,&src_time_function);
	tmp = fscanf(in,"%d",&src_char_time);

	for(int i=0;i<n_src;i++) {
		tmp = fscanf(in,"%f %f",&src[i].m0,&src[i].dip);
	}

	for(int i=0;i<n_src;i++) {
		float sx,sz;
		tmp = fscanf(in,"%f %f",&sx,&sz);

		src[i].x = (int)(sx*(mx-2*attenuate_boundary_n+0.5) + attenuate_boundary_n);
		src[i].z = (int)(sz*(mz - attenuate_boundary_n+0.5));
	}
	fclose(in);

	//______________________________________________ EXPLOSIVE SOURCE ___
	if (src_type == 1) {
		for (int i = 0; i < n_src; i++) {
			src[i].mxx = src[i].m0 / (h*h*h) / 2;
			src[i].mzz = src[i].m0 / (h*h*h) / 2;
		}
	}

	//______________________________________________ DOUBLE-COUPLE SOURCE ___
	else if (src_type == 2){
		for (int i = 0; i < n_src; i++) {
			src[i].dip *= PI / 180;

			src[i].mxx = -src[i].m0 * sin(2 * src[i].dip) / (h*h*h);
			src[i].mzx = -src[i].m0 * cos(2 * src[i].dip) / (4 * h*h*h);
			src[i].mzz = src[i].m0 * sin(2 * src[i].dip) / (h*h*h);
		}
	}
	else {
		ERR("unknown src type");
		return false;
	}

	bool ok = true;
	for (int i = 0; i < n_src; i++)
		ok &= src[i].make_time_function();

	return ok;
}