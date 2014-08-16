#include "global.h"
#include <vector>

int l_hom,mx,mx1,mx2,mx3,mz,mz1,mz2,mz3,dm;
float h,dt;

float lam[BIGDIM][BIGDIM],mu[BIGDIM][BIGDIM],muzx[BIGDIM][BIGDIM],density_u[BIGDIM][BIGDIM],density_w[BIGDIM][BIGDIM];
float co_density,co_lam,co_mu,co_lam2mu,co_muzx,co_vS,co_vP;

//void interpolate_sparse_grid(vector<vector<float>> &a) {
void interpolate_bigdim_grid(float a[][BIGDIM],const int dmx,const int dmz,const int tox,const int toz) {
	if ((dmx == 1) && (dmz ==1))
		return;
	int ii,ll,i1,l1,i2,l2;
	//vyuzivam bilineranu interpolaciu, preto tie i2,l2,..
	for(int l=toz;l>=0;l--) {
		ll=l/dmz;
		l2=l-ll*dmz;
		l1=dmz-l2;
	for(int i=tox;i>=0;i--) {
		ii=i/dmx;
		i2=i-ii*dmx;
		i1=dmx-i2;
		
		a[i][l]=(a[ii+1][ll+1]*l2*i2 + a[ii][ll+1]*l2*i1 + a[ii+1][ll]*i2*l1 + a[ii][ll]*l1*i1)/dmx/dmz;
	}}
}
void interpolate(float **a,const int dmx,const int dmz,const int tox,const int toz) {
	if ((dmx == 1) && (dmz ==1))
		return;
	int ii,ll,i1,l1,i2,l2;
	//vyuzivam bilineranu interpolaciu, preto tie i2,l2,..
	for(int l=toz;l>=0;l--) {
		ll=l/dmz;
		l2=l-ll*dmz;
		l1=dmz-l2;
	for(int i=tox;i>=0;i--) {
		ii=i/dmx;
		i2=i-ii*dmx;
		i1=dmx-i2;
		
		a[i][l]=(a[ii+1][ll+1]*l2*i2 + a[ii][ll+1]*l2*i1 + a[ii+1][ll]*i2*l1 + a[ii][ll]*l1*i1)/dmx/dmz;
	}}
}
void downsample_bigdim_grid(float a[][BIGDIM],const int dmx,const int dmz,const int tox,const int toz) {
	if ((dmx == 1) && (dmz ==1))
		return;

	for(int l=0;l<toz;l++) 
	for(int i=0;i<tox;i++) {
		a[i][l] = a[i*dmx][l*dmz];
	}
}
void interpolate_muzx_from_mu() {
	for(int i=1;i<mx;i++)
	for(int l=1;l<l_hom;l++) {
		muzx[i][l] = (mu[i][l]+mu[i-1][l]+mu[i-1][l-1]+mu[i][l-1])/4.0f;
	}
	for(int i=1;i<mx;i++)
		muzx[i][0] = (mu[i][0]+mu[i-1][0])/2.0f;
	for(int l=1;l<l_hom;l++)
		muzx[0][l] = (mu[0][l]+mu[0][l-1])/2.0f;
	muzx[0][0] = mu[0][0];
}

void add_boundary_layer_to_parameter(float a[][BIGDIM]) {
	const int s = optimalisation.attenuate_boundary_n;
	//move to the right
	for(int i=mx-1;i>=0;i--)
	for(int l=l_hom-1;l>=0;l--)
		a[i+s][l] = a[i][l];

	//add left
	for(int i=0;i<s;i++)
	for(int l=0;l<l_hom;l++)
		a[i][l] = a[s][l];

	//add right
	for(int i=mx+s;i<mx+2*s;i++)
	for(int l=0;l<l_hom;l++)
		a[i][l] = a[mx+s-1][l];

	//bottom is hom - not needed
	/*
	for(int i=s;i<mx+s;i++)
	for(int l=l_hom;l<l_hom+s;l++)
		a[i][l] = a[i][l_hom-1];

	for(int i=0;i<s;i++)
	for(int l=0;l<l_hom+s;l++)
		a[i][l] = a[s][l];

	for(int i=mx+s;i<mx+2*s;i++)
	for(int l=0;l<l_hom+s;l++)
		a[i][l] = a[mx+s-1][l];
	*/
}

void add_boundary_layer() {
	if (optimalisation.attenuate_boundary_n<1)
		return;

	add_boundary_layer_to_parameter(density_u);
	add_boundary_layer_to_parameter(density_w);
	add_boundary_layer_to_parameter(lam);
	add_boundary_layer_to_parameter(mu);

	if (optimalisation.attenuate_boundary_n>0) {
		mx += 2*optimalisation.attenuate_boundary_n;
		mz +=   optimalisation.attenuate_boundary_n;
	}

	INFO1 cout<<"i: boundaries added, new model size "<<mx<<" x "<<mz<<" ("<<l_hom<<")"<<endl; 
}

void load_grid() {
	FILE* ing = fopen(files.input_grid,"r");
	if (ing == NULL) {
		ERR("No input grid file");
		return;
	}
	fscanf(ing,"%f\n",&h);
	fscanf(ing,"%d %d %d\n",&mx,&mz,&l_hom);
	if (max(mx,mz) >= BIGDIM) {
		ERR("Grid too BIG");
	}
	fscanf(ing,"%d\n",&dm);
	fclose(ing);

	if (mz - l_hom <3) {
		ERR("wrong grid model - l_hom (3rd param) should be at least 3 points smaller than mz (2nd)");
	}

	if (optimalisation.attenuate_boundary_n>0) {
		mx += 2*optimalisation.attenuate_boundary_n;
		mz +=   optimalisation.attenuate_boundary_n;
	}
}

void load_model() {
	load_grid();

	if (optimalisation.attenuate_boundary_n>0) {
		mx -= 2*optimalisation.attenuate_boundary_n;
		mz -=   optimalisation.attenuate_boundary_n;
	}

	int mmx,mmz;
	FILE* in = fopen(files.input_model,"r");
	if (in == NULL) {
		ERR("No input model file");
		return;
	}
	fscanf(in,"%d %d\n",&mmx,&mmz);
	fscanf(in,"%f %f %f %f %f %f %f\n",&co_density,&co_vP,&co_vS,&co_lam,&co_lam2mu,&co_mu,&co_muzx);
		//nacitavat a interpolovat z velkosti modelu ()
	for(int i=0;i<mmx;i++) 
	for(int l=0;l<mmz;l++)
		fscanf(in,"%f %f %f %f %f\n",&density_u[i][l],&density_w[i][l],&lam[i][l],&mu[i][l],&muzx[i][l]);

	INFO1 cout<<"i: loading model "<<mmx<<" "<<mmz<<" vs "<<(mx-1)/dm+1<<" "<<(l_hom-1)/dm+1<<endl;

	if ((mmx>(mx-1)/dm+1) && (mmz>(l_hom-1)/dm+1)) {
		int dmx = (mmx-1)/((mx-1)/dm);
		int dmz = (mmz-1)/((l_hom-1)/dm);
		cout<<"i: downsampling model, size ratio "<<dmx<<" "<<dmz<<endl;
		downsample_bigdim_grid(density_u,dmx,dmz,(mx-1)/dm+1,(l_hom-1)/dm+1);
		downsample_bigdim_grid(density_w,dmx,dmz,(mx-1)/dm+1,(l_hom-1)/dm+1);
		downsample_bigdim_grid(lam,dmx,dmz,(mx-1)/dm+1,(l_hom-1)/dm+1);
		downsample_bigdim_grid(mu,dmx,dmz,(mx-1)/dm+1,(l_hom-1)/dm+1);
	}
	else if ((mmx!=(mx-1)/dm+1)||(mmz!=(l_hom-1)/dm+1)) {
		//cout<<"WARNING: model "<<mmx<<"x"<<mmz<<" doesn't equal sparse grid "<<(mx-1)/dm+1<<"x"<<(l_hom-1)/dm+1<<". We need to interpolate."<<endl;
		int dmx = ((mx-1)/dm)/(mmx-1);
		int dmz = ((l_hom-1)/dm)/(mmz-1);

		if ((dmz<1)||(dmx<1)) {
			char* s="";
			sprintf(s,"wrong spacing X %d Z %d",dmx,dmz);
			ERR(s);
			return;
		}
		if (((mx-1)/dm)%(mmx-1)!=0) cout<<"WARNING: number of grid points in x-axis can't be matched to sparse model grid"<<endl;
		if (((l_hom-1)/dm)%(mmz-1)!=0) cout<<"WARNING: number of grid points in z-axis can't be matched to sparse model grid"<<endl;

		interpolate_bigdim_grid(density_u,dmx,dmz,(mx-1)/dm,(l_hom-1)/dm);
		interpolate_bigdim_grid(density_w,dmx,dmz,(mx-1)/dm,(l_hom-1)/dm);
		interpolate_bigdim_grid(lam,dmx,dmz,(mx-1)/dm,(l_hom-1)/dm);
		interpolate_bigdim_grid(mu,dmx,dmz,(mx-1)/dm,(l_hom-1)/dm);
		//interpolate_sparse_grid(muzx,dmx,dmz,(mx-1)/dm,(l_hom-1)/dm);
	}
}

void loadModel() {
	load_model();

	interpolate_bigdim_grid(density_u,dm,dm,mx-1,l_hom-1);
	interpolate_bigdim_grid(density_w,dm,dm,mx-1,l_hom-1);
	interpolate_bigdim_grid(lam,dm,dm,mx-1,l_hom-1);
	interpolate_bigdim_grid(mu,dm,dm,mx-1,l_hom-1);
	//interpolate_sparse_grid(muzx,dm,dm,mx-1,l_hom-1);

	add_boundary_layer();

	//neviem, preco to tu musi byt.. je to divne..
	for(int l=l_hom;l<l_hom+4;l++)
	for(int i=0;i<=mx;i++) {
		density_u[i][l] = co_density;
		density_w[i][l] = co_density;

		 mu[i][l] = co_mu;
		lam[i][l] = co_lam;
		muzx[i][l]= co_muzx;
	}

	interpolate_muzx_from_mu();
}

