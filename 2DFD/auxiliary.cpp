#include "global.h"
#include <ctime>

float u[BIGDIM][BIGDIM],w[BIGDIM][BIGDIM],vu[BIGDIM][BIGDIM],vw[BIGDIM][BIGDIM],
      txx_hline[BIGDIM],tzz_mline[BIGDIM][4],tzx_mline[BIGDIM][4];

float a_FD= -1.0f/24.0f, b_FD = 9.0f/8.0f;

float ale01[BIGDIM],ale02[BIGDIM],ale10[BIGDIM],ale11[BIGDIM],ale12[BIGDIM],ale20[BIGDIM],ale21[BIGDIM],ale22[BIGDIM],
	  ari01[BIGDIM],ari02[BIGDIM],ari10[BIGDIM],ari11[BIGDIM],ari12[BIGDIM],ari20[BIGDIM],ari21[BIGDIM],ari22[BIGDIM],
	  co_ale01,co_ale02,co_ale10,co_ale11,co_ale12,co_ale20,co_ale21,co_ale22,
	  co_ari01,co_ari02,co_ari10,co_ari11,co_ari12,co_ari20,co_ari21,co_ari22,
	  co_abt01,co_abt02,co_abt10,co_abt11,co_abt12,co_abt20,co_abt21,co_abt22;


void CPU_TIME() {
time_t rawtime;
time ( &rawtime );
cout<< ctime (&rawtime)<<endl;
}

void aux_charakteristika() {
	cout<<"Rozmery:   "<<h*mx<<"m, siet: "<<mx<<"x"<<mz<<endl;
	cout<<"Cas:       "<<dt*max_num_iter<<"ms, iteracii: "<<max_num_iter<<endl; 
}

void ERR(string s) {
	FILE *out = fopen("ERR.log","a");
	fprintf(out,"%s\n",s.c_str());
	fclose(out);
	cout<<"ERR: "<<s<<endl;
}

void set_starting_values() {
	FORALL {
		w[i][l]=0;
		u[i][l]=0;
		vw[i][l]=0;
		vu[i][l]=0;
	}

	 co_lam2mu /= h;
	 co_mu     /= h;
	 co_lam    /= h;
	 co_muzx   /= h;
	 
	 co_density = dt/(h*co_density);

	for(int l=0;l<l_hom+4;l++)
	for(int i=0;i<mx;i++) {
	//FORINH {
		 density_u[i][l] = dt/(h*density_u[i][l]);
		 density_w[i][l] = dt/(h*density_w[i][l]);
		 mu[i][l]  /= h;
		 lam[i][l] /= h;
		 muzx[i][l]/= h;
	}

	for(int i=0;i<mx;i++) {
		txx_hline[i]=0;
		for (int j=0;j<4;j++) {
			tzx_mline[i][j]=0;
			tzz_mline[i][j]=0;
		}
	}

	
	for(int i=0;i<mx;i++) {
		stored_u_mz1_level0[i] = 0;
		stored_u_mz2_level0[i] = 0;
		stored_u_mz2_level1[i] = 0;
		stored_u_mz3_level0[i] = 0;
		stored_u_mz3_level1[i] = 0;

		stored_w_mz1_level0[i] = 0;
		stored_w_mz2_level0[i] = 0;
		stored_w_mz2_level1[i] = 0;
		stored_w_mz3_level0[i] = 0;
		stored_w_mz3_level1[i] = 0;
	}
	for(int l=0;l<mz;l++) {
		stored_u_1_level0[l]  = 0;
		stored_u_2_level0[l]  = 0;
		stored_u_3_level0[l]  = 0;
		stored_u_mx3_level0[l]= 0;
		stored_u_mx2_level0[l]= 0;
		stored_u_mx1_level0[l]= 0;

		stored_w_0_level0[l]  = 0;
		stored_w_1_level0[l]  = 0;
		stored_w_2_level0[l]  = 0;
		stored_w_mx3_level0[l]= 0;
		stored_w_mx2_level0[l]= 0;
		stored_w_mx1_level0[l]= 0;
	}
	stored_u_1_level1 = 0;
	stored_u_2_level1 = 0;
	stored_u_3_level1 = 0;
	stored_u_mx3_level1=0;
	stored_u_mx2_level1=0;
	stored_u_mx1_level1=0;

	stored_w_0_level1 = 0;
	stored_w_1_level1 = 0;
	stored_w_2_level1 = 0;
	stored_w_mx3_level1=0;
	stored_w_mx2_level1=0;
	stored_w_mx1_level1=0;

	stored_u_mz1_level1= 0;
	stored_w_mz1_level1= 0;
}

void set_nonreflecting_coeff() {
//_________________________________ Emerman & Stephen, max. P-w. att. ___
	float t1,t2,alfa;

	for(int l=0;l<l_hom;l++) {
		//left
		alfa = sqrtf( (lam[0][l] + 2*mu[0][l]) *density_w[0][l]*h*h/dt);
		t1 = (dt - h/alfa )/(dt + h/alfa );
		t2 =  2.0f*h/alfa  /(dt + h/alfa );
		  ale01[l] =  t1;
		  ale02[l] =  0.0f;
		  ale10[l] =  t2;
		  ale11[l] =  t2;
		  ale12[l] =  0.0f;
		  ale20[l] =  t1;
		  ale21[l] = -1.0f;
		  ale22[l] =  0.0f;

		//right
		alfa = sqrtf( (lam[mx1][l] + 2*mu[mx1][l]) *density_w[mx1][l]*h*h/dt);
		t1 = (dt - h/alfa )/(dt + h/alfa );
		t2 =  2.0f*h/alfa  /(dt + h/alfa );
		  ari01[l] =  t1;
		  ari02[l] =  0.0f;
		  ari10[l] =  t2;
		  ari11[l] =  t2;
		  ari12[l] =  0.0f;
		  ari20[l] =  t1;
		  ari21[l] = -1.0f;
		  ari22[l] =  0.0f;
	}

	t1 = (dt - h/co_vP )/(dt + h/co_vP );
	t2 =  2.0f*h/co_vP  /(dt + h/co_vP );
	//left_hom
		  co_ale01 =  t1;
		  co_ale02 =  0.0f;
		  co_ale10 =  t2;
		  co_ale11 =  t2;
		  co_ale12 =  0.0f;
		  co_ale20 =  t1;
		  co_ale21 = -1.0f;
		  co_ale22 =  0.0f;
	//right_hom
		  co_ari01 =  t1;
		  co_ari02 =  0.0f;
		  co_ari10 =  t2;
		  co_ari11 =  t2;
		  co_ari12 =  0.0f;
		  co_ari20 =  t1;
		  co_ari21 = -1.0f;
		  co_ari22 =  0.0f;
	//bottom_hom
		  co_abt01 =  t1;
		  co_abt02 =  0.0f;
		  co_abt10 =  t2;
		  co_abt11 =  t2;
		  co_abt12 =  0.0f;
		  co_abt20 =  t1;
		  co_abt21 = -1.0f;
		  co_abt22 =  0.0f;
}

void auxiliary() {
     mx1   =mx-1;
     mx2   =mx-2;
	 mx3   =mx-3;
     mz1   =mz-1;
     mz2   =mz-2;
	 mz3   =mz-3;
     
	set_starting_values();
	set_nonreflecting_coeff();
}

float **allocate2Dzeros(const int &sizeX,const int &sizeY) {
	float** arr = new float*[sizeX];
	for(int i = 0; i < sizeX; i++) {
		arr[i] = new float[sizeY];
		for (int j=0;j<sizeY;j++) 
			arr[i][j] = 0;
	}
	return arr;
}
void delete2D(float **arr,const int &sizeX) {
	for(int i = 0; i < sizeX; i++) {
		delete[] arr[i];
	}
	delete[] arr;
}