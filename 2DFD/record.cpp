#include "global.h"
#include <string>

void record_sparse_data() {
	FILE *out = fopen(files.sparse_grid_data,"w");
	SPARSE;
	fprintf(out,"%d %d\n",upi,upl);
	fprintf(out,"%f %f\n",h*dm,dt);
	fclose(out);
}
void record_sparse(const int iter) {
	if (iter==0)
		record_sparse_data();

	char s[256] ="";
	sprintf(s,"%s_%d.bin",files.sparse_direct_field,iter);

	FILE *out = fopen(s,"wb");
	int size = sizeof(u[0][0]);
	
	if (dm==1) {
		SPARSE;
		for(int i=0;i<upi;i++) {
			fwrite (u[i*dm], size, upl, out);
			fwrite (w[i*dm], size, upl, out);
			fwrite (vu[i*dm],size, upl, out);
			fwrite (vw[i*dm],size, upl, out);
		}
		fclose(out);
	}
	else {
		SPARSE; 
		float *tmpu  = new float[upl];
		float *tmpw  = new float[upl];
		float *tmpvu = new float[upl];
		float *tmpvw = new float[upl];
		for(int i=0;i<upi;i++) {
			for(int l=0;l<upl;l++) {
				tmpu[l]  = u[i*dm][l*dm];
				tmpw[l]  = w[i*dm][l*dm];
				tmpvu[l] = vu[i*dm][l*dm];
				tmpvw[l] = vw[i*dm][l*dm];
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

void record_java(const int iter) {
	if (iter%20!=1) 
		return;
	char fn[256] ="";
	
	sprintf(fn,"%s_%d_src_%d.txt",files.sparse_java_direct,iter,active_source);

	dm*=2;
	//dm/=4;
	FILE *out = fopen(fn,"w");
	fprintf(out,"%d %d\n",(mx-1)/dm+1,(mz-1)/dm+1);

	for(int i=0;i<(mx-1)/dm+1;i++)
	for(int l=0;l<(mz-1)/dm+1;l++){
		fprintf(out,"%f %f %f %f\n",u[i*dm][l*dm],w[i*dm][l*dm],vu[i*dm][l*dm],vw[i*dm][l*dm]);
	}
	fclose(out);
	//dm*=4;
	dm/=2;
}

FILE *out_rec,*out_src;
bool opened_rec=false,opened_src=false;
void record_at_receivers(const int iter) {
	if (iter == 1) {
		char s[256] ="";
		sprintf(s,"%s_%d.txt",files.records_from_src,active_source);
		
		out_rec = fopen(s,"w");
		fprintf(out_rec,"%d\n",n_rec);

		for(int j=1;j<iter;j++) {
			for(int i=0;i<n_rec;i++)
				fprintf(out_rec,"%f %f ",0.0f,0.0f);
			fprintf(out_rec,"\n");
		}
		opened_rec=true;
	}

	if (opened_rec) {
		for(int i=0;i<n_rec;i++) {
			int tx = rec[i].x;
			int tz = rec[i].z;
			fprintf(out_rec,"%f %f %f %f",u[tx][tz],w[tx][tz],vu[tx][tz],vw[tx][tz]);
		}
		fprintf(out_rec,"\n");

		if (iter == max_num_iter) {
			fclose(out_rec);
			opened_rec = false;
		}
	}
}

