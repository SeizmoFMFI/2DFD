#include "global.h"
#include <string>

void InputOutput::record_sparse_binary(const int active_source, const int iter) {
	char s[256] ="";
	sprintf(s,"%s_src_%_iter_%d.bin",files.sparse_field_binary,active_source,iter);

	FILE *out = fopen(s,"wb");
	int size = sizeof(u[0][0]);

	if (dm==1) {
		for(int i=0;i<mx;i++) {
			fwrite(u[i + attenuate_boundary_n], size, l_hom, out);
			fwrite(w[i + attenuate_boundary_n], size, l_hom, out);
			fwrite(vu[i + attenuate_boundary_n], size, l_hom, out);
			fwrite(vw[i + attenuate_boundary_n], size, l_hom, out);
		}
		fclose(out);
	}
	else {
		SPARSE; 
		float *tmpu  = new float[upl];
		float *tmpw  = new float[upl];
		float *tmpvu = new float[upl];
		float *tmpvw = new float[upl];
		int ii;
		for(int i=0;i<upi;i++) {
			ii = i*dm + attenuate_boundary_n;
			for(int l=0;l<upl;l++) {
				tmpu[l] = u[ii][l*dm];
				tmpw[l] = w[ii][l*dm];
				tmpvu[l] = vu[ii][l*dm];
				tmpvw[l] = vw[ii][l*dm];
			}
			fwrite (tmpu, size, upl, out);
			fwrite (tmpw, size, upl, out);
			fwrite (tmpvu,size, upl, out);
			fwrite (tmpvw,size, upl, out);
		}
		fclose(out);
		delete [] tmpu;
		delete [] tmpw;
		delete [] tmpvu;
		delete [] tmpvw;
	}
}

void InputOutput::record_sparse_txt(const int active_source, const int iter) {
	char fn[256] ="";
	
	sprintf(fn, "%s_src_%d_%d.txt", io.files.sparse_field_txt, active_source, iter);

	FILE *out = fopen(fn,"w");

	SPARSE;
	fprintf(out, "%d %d\n", upi, upl);
	for (int i = 0; i < upi; i++) {
		int ii = i*dm + attenuate_boundary_n;
		for (int l = 0; l < upl; l++) {
			fprintf(out, "%f %f %f %f\n", u[ii][l*dm], w[ii][l*dm], vu[ii][l*dm], vw[ii][l*dm]);
		}
	}
	fclose(out);
}

FILE *out_rec;
void InputOutput::record_at_receivers(const int iter,const int active_source) {
	if (iter == 0) {
		char s[256] ="";
		sprintf(s,"%s_%d.txt",files.records_from_src,active_source);
		
		out_rec = fopen(s,"w");
		fprintf(out_rec,"%d\n",n_rec);
	}

	for(int i=0;i<n_rec;i++) {
		int tx = rec[i].x;
		int tz = rec[i].z;
		fprintf(out_rec,"%f %f %f %f",u[tx][tz],w[tx][tz],vu[tx][tz],vw[tx][tz]);
	}
	fprintf(out_rec,"\n");

	if (iter == max_num_iter-1) {
		fclose(out_rec);
	}
}

