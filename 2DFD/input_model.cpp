#include "global.h"
#include <vector>

int l_hom,mx,mx1,mx2,mx3,mz,mz1,mz2,mz3,dm;
float h,dt;

float lam[BIGDIM][BIGDIM],mu[BIGDIM][BIGDIM],muzx[BIGDIM][BIGDIM],density_u[BIGDIM][BIGDIM],density_w[BIGDIM][BIGDIM];
float co_density,co_lam,co_mu,co_lam2mu,co_muzx,co_vS,co_vP;

void interpolate_bigdim_grid(float a[][BIGDIM],const int dm,const int tox,const int toz) {
	if (dm == 1)
		return;
	int ii,ll,i1,l1,i2,l2;
	//vyuzivam bilineranu interpolaciu, preto tie i2,l2,..
	for(int l=toz-1;l>=0;l--) {
		ll=l/dm;
		l2=l-ll*dm;
		l1=dm-l2;
	for(int i=tox-1;i>=0;i--) {
		ii=i/dm;
		i2=i-ii*dm;
		i1=dm-i2;
		
		a[i][l]=(a[ii+1][ll+1]*l2*i2 + a[ii][ll+1]*l2*i1 + a[ii+1][ll]*i2*l1 + a[ii][ll]*l1*i1)/SQR(dm);
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
void downsample_bigdim_grid(float a[][BIGDIM],const int dm,const int tox,const int toz) {
	if (dm == 1)
		return;

	for(int l=0;l<toz;l++) 
	for(int i=0;i<tox;i++) {
		a[i][l] = a[i*dm][l*dm];
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
	const int s = attenuate_boundary_n;
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

	//bottom is hom - does not need to add layers
}

void add_boundary_layer() {
	if (attenuate_boundary_n<1)
		return;

	add_boundary_layer_to_parameter(density_u);
	add_boundary_layer_to_parameter(density_w);
	add_boundary_layer_to_parameter(lam);
	add_boundary_layer_to_parameter(mu);

	mx += 2*attenuate_boundary_n;
	mz +=   attenuate_boundary_n;

	INFO cout<<"i: boundaries added, new model size "<<mx<<" x "<<mz<<" ("<<l_hom<<")"<<endl; 
}

void interpolate_model(const int dm) {
	cout << "i: interpolating model, sampling " << dm << endl;
	interpolate_bigdim_grid(density_u, dm, mx, l_hom);
	interpolate_bigdim_grid(density_w, dm, mx, l_hom);
	interpolate_bigdim_grid(lam, dm, mx, l_hom);
	interpolate_bigdim_grid(mu, dm, mx, l_hom);
}

void downsample_model(const int dm) {
	cout << "i: downsampling model, sampling " << dm << endl;
	downsample_bigdim_grid(density_u, dm, mx, l_hom);
	downsample_bigdim_grid(density_w, dm, mx, l_hom);
	downsample_bigdim_grid(lam, dm, mx, l_hom);
	downsample_bigdim_grid(mu, dm, mx, l_hom);
}

bool InputOutput::prepare_model_for_computation(const int mmx,const int mml) {
	cout << "i: preparing model " << mx << " " << l_hom << " (" << mz << ") from " << mmx << " " << mml << endl;

	if (mx < mmx) {
		int dm = (mmx - 1) / (mx - 1);
		downsample_model(dm);
	}
	else if (mx > mmx) {
		int dm = (mx - 1) / (mmx - 1);
		interpolate_model(dm);
	}

	add_boundary_layer();

	//neviem, preco to tu musi byt.. je to divne..
	//asi niekde v disp/velocity update saham mimo pola..
	//chcelo by to opravit...
	for (int l = l_hom; l<l_hom + 4; l++)
	for (int i = 0; i <= mx; i++) {
		density_u[i][l] = co_density;
		density_w[i][l] = co_density;

		mu[i][l] = co_mu;
		lam[i][l] = co_lam;
		muzx[i][l] = co_muzx;
	}

	interpolate_muzx_from_mu();
	return true;
}

bool compute_grid_size(const int mmx, const int mmz_hom, const int mmz) {
	//input params are model grid, these need to be rescaled to computation grid, which may be different
	if (mx == mmx) {
		//model grid and computation grid are the same
		mz = mmz;
		l_hom = mmz_hom;
		return true;
	}

	//grids should be odd, not even, to allow direct interpolation
	int dm;
	if (mmx > mx) {
		//input model will be sampled
		if ((mmx - 1) % (mx - 1) != 0) {
			cout << "model width " << mmx - 1 << " can not be diectly sampled to " << mx - 1 << endl;
			return false;
		}
		dm = (int)((mmx - 1) / (mx - 1));

		if ((mmz - 1) % dm != 0) {
			cout << "model height " << mmz - 1 << " can not be diectly sampled by " << dm << endl;
			return false;
		}
		mz = (int)((mmz - 1) / dm) + 1;

		if ((mmz_hom - 1) % dm != 0) {
			cout << "inhomogeneous part " << mmz_hom - 1 << " can not be diectly sampled by " << dm << endl;
			return false;
		}
		l_hom = (int)((mmz_hom - 1) / dm) + 1;
	}
	else {
		//input model will be interpolated
		if ((mx - 1) % (mmx - 1) != 0) {
			cout << "model width " << mmx - 1 << " can not be diectly interpolated to " << mx - 1 << endl;
			return false;
		}
		dm = (int)((mx - 1) / (mmx - 1));
		mz = ((mmz - 1) * dm) + 1;
		l_hom = ((mmz_hom - 1) * dm) + 1;
	}

	return true;
}

bool InputOutput::load_model() {
	int mmx,mmz,mmz_hom;
	FILE* in = fopen(files.input_model,"r");
	if (in == NULL) {
		ERR("No input model file");
		return false;
	}
	fscanf(in,"%d %d %d\n",&mmx,&mmz_hom,&mmz);
	fscanf(in,"%f %f %f\n",&co_density,&co_lam,&co_mu);
	co_lam2mu = co_lam + 2 * co_mu;

	bool grid_is_ok = compute_grid_size(mmx,mmz,mmz_hom);
	if (!grid_is_ok) {
		ERR("Problem with grid/model dimensions");
		return false;
	}

	INFO cout << "i: loading model " << mmx << " x " << mmz_hom << " (" << mmz << ")" << endl;
	for(int i=0;i<mmx;i++) 
	for(int l=0;l<mmz_hom;l++)
		fscanf(in,"%f %f %f %f %f\n",&density_u[i][l],&density_w[i][l],&lam[i][l],&mu[i][l],&muzx[i][l]);

	fclose(in);
	return prepare_model_for_computation(mmx,mmz_hom);
}

