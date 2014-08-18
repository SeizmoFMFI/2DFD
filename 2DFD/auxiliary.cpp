#include "global.h"
#include <ctime>

float u[BIGDIM][BIGDIM],w[BIGDIM][BIGDIM],vu[BIGDIM][BIGDIM],vw[BIGDIM][BIGDIM],
      txx_hline[BIGDIM],tzz_mline[BIGDIM][4],tzx_mline[BIGDIM][4];

float a_FD= -1.0f/24.0f, b_FD = 9.0f/8.0f;

void CPU_TIME() {
time_t rawtime;
time ( &rawtime );
cout<< ctime (&rawtime)<<endl;
}

void aux_charakteristika() {
	cout << "Dimensions:   " << h*mx << "m x " << h*mz << "m" << endl;
	cout << "Grid: " << mx << "x" << mz <<", inhomogeneus part"<<l_hom<< endl;
	cout << "Time:       " << dt*max_num_iter << "ms, iterations: " << max_num_iter << endl;
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

	co_mu     /= h;
	co_lam    /= h;
	co_lam2mu = co_lam + 2 * co_mu;
	 
	co_density = dt/(h*co_density);

	nonreflecting.co_vP = sqrtf(co_lam2mu*co_density); //not sure about this..

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

	nonreflecting.set_starting_values_for_boundaries();
}

void auxiliary() {
     mx1   =mx-1;
     mx2   =mx-2;
	 mx3   =mx-3;
     mz1   =mz-1;
     mz2   =mz-2;
	 mz3   =mz-3;
     
	set_starting_values();
	nonreflecting.set_nonreflecting_coeff();
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