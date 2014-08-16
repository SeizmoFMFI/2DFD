#include "global.h"

int n_src,n_rec,key_typ_src;
Source src[50];
Receiver rec[50];


void loadSource() {
	FILE* in = fopen(files.input_source,"r");
	if (in == NULL) {
		cout<<files.input_source<<endl;
		ERR("No input source file");
	}
	
	tmp = fscanf(in,"%d",&n_src);
	if (n_src>50) 
		ERR("Err: privela zdrojov");
	tmp = fscanf(in,"%d %d",&key_typ_src,&key_typ_src_function);
	tmp = fscanf(in,"%d",&source_num_active_iter);

	int ts = 0;
	//______________________________________________ SOURCE FUNCTION FROM FILE ___
	if (key_typ_src==0) {
		ERR("treba nakodit nacitanie zdrojovovej funkcie v input_source::loadSource");
	}

	for(int i=0;i<n_src;i++) {
		tmp = fscanf(in,"%f %f",&src[i].m0,&src[i].dip);
	}

	load_grid();
	for(int i=0;i<n_src;i++) {
		float sx,sz;
		tmp = fscanf(in,"%f %f",&sx,&sz);

		src[i].x = (int)(sx*(mx-2*optimalisation.attenuate_boundary_n+0.5) + optimalisation.attenuate_boundary_n);
		src[i].z = (int)(sz*(mz - optimalisation.attenuate_boundary_n+0.5));
	}
	//______________________________________________ EXPLOSIVE SOURCE ___
	if (key_typ_src==1)
	for(int i=0;i<n_src;i++) {
		src[i].mxx= src[i].m0 / (h*h*h) /2;
		src[i].mzz= src[i].m0 / (h*h*h) /2;
		
		ts = src[i].sprav_time_function();
	}

	//______________________________________________ DOUBLE-COUPLE SOURCE ___
	if (key_typ_src==2)
	for(int i=0;i<n_src;i++) {
		src[i].dip*=PI/180;
		
		src[i].mxx= - src[i].m0 * sin(2*src[i].dip)/(h*h*h);
		src[i].mzx= - src[i].m0 * cos(2*src[i].dip)/(4*h*h*h);
		src[i].mzz=   src[i].m0 * sin(2*src[i].dip)/(h*h*h);
		ts = src[i].sprav_time_function();
	}

    if (source_num_active_iter>19990)
		ERR("pridlha zdrojova funkcia, zmenit velkost pola");
    
	fclose(in);

	max_num_iter += (int)(2*ts);
	//cout<<"i: number of iterations after adding source duration "<<max_num_iter<<endl;
}
