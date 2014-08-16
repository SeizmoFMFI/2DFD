#include "global.h"

float bedrock_density, bedrock_vP, bedrock_vS, bedrock_lam, bedrock_mu;
float model_w, model_h, model_h_hom, dh; //model dimensions [m]
int mx, mhom, mz; 

float l, m;

#define DIM 1000
float density_u[DIM][DIM], density_w[DIM][DIM], lam[DIM][DIM], mu[DIM][DIM], muzx[DIM][DIM];
	/*
		number of model grid points;   
		
		model has 2 parts:
			inhomogeneous   < 0, mhom> x <0,mx>
			  homogeneous   (mhom, mz) x <0,mx>

		inhomogeneous part is saved as staggered grid with values of density, lambda and mu
		homogeneous part has only one value of constant bedrock density, lambda and mu
	*/

float compute_mu(const float vS, const float density) {
	return SQR(vS)*density;
}

float compute_lam(const float vP, const float density,const float mu) {
	float lam = SQR(vP)*density - 2 * mu;
	assert(lam >= 0 && "Heeey, lambda can not be negative! Values of vP and vS are wrong.");
	return lam;
}

void save_medium() {
	FILE *out;
	out = fopen("model.txt","w");
	fprintf(out,"%d %d %d\n",mx,mhom,mz);
	fprintf(out,"%f %f %f\n",bedrock_density,bedrock_lam,bedrock_mu);
	for(int i=0;i<mx;i++) 
	for(int l=0;l<mhom;l++)
		fprintf(out,"%f %f %f %f %f\n",density_u[i][l],density_w[i][l],lam[i][l],mu[i][l],muzx[i][l]);
	fclose(out);
}

void prepare_hom_medium() {
	for(int i=0;i<mx;i++) 
	for(int l=0;l<mz;l++) {
		density_u[i][l] = bedrock_density;
		density_w[i][l] = bedrock_density;

		 mu[i][l] = bedrock_mu;
		lam[i][l] = bedrock_lam;
		muzx[i][l]= bedrock_mu;
	}
}

void prepare_one_layer_medium() {
	float den, l, m;
	float vP, vS;

	den = get_input("density of layer [kg/m^3]:", 1000.f, 3000.f);
	vP = get_input("vP in layer [m/s]:", 200.f, 6000.f);
	vS = get_input("vS in layer [m/s]:", 0.f, 4000.f);

	m = compute_mu(vS,den);
	l = compute_lam(vP, den, m);

	for(int i=0;i<mx;i++) {
		for(int l=0;l<mhom;l++) {
			density_u[i][l] = den;
			density_w[i][l] = den;
			lam[i][l]       = l;
			mu[i][l]        = m;
			muzx[i][l]      = m;
		}
	}
}
/*
void prepare_vertical_grad_medium() {
	cout<<"Set value of: v_surface / v_bottom in percents: ";
	float k;
	cin>>k;
	k/=100;

	float tmp;
	for(int i=0;i<mx;i++) 
	for(int l=0;l<mz;l++) {
		tmp = (k*(mz-1-l)+1*l)/(mz-1);
		tmp = (tmp*tmp);
		density_u[i][l] = co_density/tmp;
		density_w[i][l] = co_density/tmp;

		 mu[i][l] = co_mu;
		lam[i][l] = co_lam;
		muzx[i][l]= co_muzx;
	}
	save_medium(mx,mz);
}

void prepare_diamond_heterogenity() {
	cout<<"Set value of rho deviation in percents: ";
	float dr;
	cin>>dr;
	dr/=100;
	cout<<"Set value of lambda deviation in percents: ";
	float dl;
	cin>>dl;
	dl/=100;
	cout<<"Set value of mu deviation in percents: ";
	float dm;
	cin>>dm;
	dm/=100;
	cout<<"Set dimension in percents: ";
	float mm;
	cin>>mm;
	mm/=100;
	cout<<"Set height in percents: ";
	float hh;
	cin>>hh;
	hh/=100;

	float tmp;
	float manhattan;
	for(int i=0;i<mx;i++) 
	for(int l=0;l<mz;l++) {
		tmp = 1;
		manhattan = (float) (abs(i-mx/2)+abs(l-mz*hh));

		if (manhattan<mx*mm) {
			manhattan/= mx;
			tmp = (mm - manhattan)/(mm/4);
			if (tmp>1) tmp = 1;
			density_u[i][l] = co_density*(1*(1-tmp) + tmp*dr);
			density_w[i][l] = co_density*(1*(1-tmp) + tmp*dr);

			 mu[i][l] = co_mu*(1*(1-tmp) + tmp*dm);
			lam[i][l] = co_lam*(1*(1-tmp) + tmp*dl);
			muzx[i][l]= co_muzx*(1*(1-tmp) + tmp*dm);
		}
		else {
			density_u[i][l] = co_density;
			density_w[i][l] = co_density;

			 mu[i][l] = co_mu;
			lam[i][l] = co_lam;
			muzx[i][l]= co_muzx;
		}
	}

	save_medium(mx,mz);
}

void prepare_checkerboard_medium() {
	int nt;
	float abs,k;
	cout<<"How many checkerboard tiles in X direction? ";
	cin>>nt;
	nt = (int)(mx/nt);
	cout<<"Deviations +/- percents? ";
	cin>>abs;

	bool change_rho=false,change_mu=false,change_lam=false;
	char c;
	cout<<"Change rho? Press 'y' ";
	cin>>c;
	if ((c=='y')||(c=='Y')) change_rho = true;
	cout<<"Change lam? Press 'y' ";
	cin>>c;
	if ((c=='y')||(c=='Y')) change_lam = true;
	cout<<"Change mu?  Press 'y' ";
	cin>>c;
	if ((c=='y')||(c=='Y')) change_mu  = true;

	for(int i=0;i<mx;i++) 
	for(int l=0;l<mz;l++) {
		if ((i/nt)%2 + (l/nt)%2 == 1) 
			k= (1 + abs/100);
		else 
			k= (1 - abs/100);

		density_u[i][l] = co_density;
		density_w[i][l] = co_density;
		lam[i][l]       = co_lam;
		mu[i][l]        = co_mu;
		muzx[i][l]      = co_muzx;

		if (change_rho) {
			density_u[i][l] /= k;
			density_w[i][l] /= k;
		}
		if (change_lam) {
			lam[i][l]       *= k;
		}
		if (change_mu)  {
			mu[i][l]        *= k;
			muzx[i][l]      *= k;
		}
	}
	save_medium(mx,mz);
}
*/

void prepare_model() {
	model_w	  = get_input("model dimensions\nmodel width [m]:", 0.f,20000.f);
	model_h_hom = get_input("model inhomogeneous depth [m]:", 0.f,20000.f);
	model_h	  = get_input("model depth [m]:", model_h_hom,20000.f);

	dh = get_input("model depth [m]:", model_h_hom, 20000.f);

	mx = model_w / dh;
	mz = model_h / dh;
	mhom = model_h_hom / dh;

	cout << "grid size is " <<mx<<" x "<<mz<< endl;
	cout << "inhomogeneous part " << mx << " x " << mhom << endl;
	cout << "press anything to continue" << endl;
	cin.get();
	
	bedrock_density = get_input("bedrock density [kg/m^3]:", 1000.f, 3000.f);
	bedrock_vP		= get_input("bedrock P speed [m/s]:", 1000.f, 10000.f);
	bedrock_vS		= get_input("bedrock S speed [m/s]:",  500.f,  7000.f);

	bedrock_mu = compute_mu(bedrock_vS, bedrock_density);
	bedrock_lam = compute_lam(bedrock_vP, bedrock_density, bedrock_mu);

	cout<<"What kind of model do you want?"<<endl
		<<"Homogeneous - 'h'"<<endl
		<<"Homogeneous Layer - 'l'"<<endl
		//<<"Linear vertical gradient - 'g'"<<endl
		//<<"Checkerboard - 'c'"<<endl
		//<<"Diamond heterogenity in the middle - 'd'"<<endl
		<<"Quit editor (don't save any changes!) - press anything else"<<endl;
	char c;
	cin>>c;

	if (c == 'h')
		prepare_hom_medium();
	else if (c == 'l')
		prepare_one_layer_medium();
	else
		return;
	/*
	if (c=='g')
		prepare_vertical_grad_medium();
	if (c=='c')
		prepare_checkerboard_medium();
	if (c=='d')
		prepare_diamond_heterogenity();
	*/

	save_medium();
}