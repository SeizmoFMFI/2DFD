#include "global.h"

char name[50];
bool adjoint_computation,adjoint_iteration,adjoint_kernel,prepare_synthetics;

void aux_model_parameters() {
	co_mu = co_vS*co_vS*co_density;
	co_lam = co_vP*co_vP*co_density - 2 * co_mu;
	co_muzx = co_mu;
	co_lam2mu = co_lam + 2 * co_mu;
}

void main_vstup() {
	char c=' ';

	while(c!='f') {
		cout<<"Press:"<<endl;
		cout<<"'f' to start Forward computations"<<endl;
		cout<<endl;
		cout<<"'m' to prepare Model"<<endl;
		cout<<"'g' to prepare Grid"<<endl;
		cout<<"'s' to set Sources"<<endl;
		cout<<"'r' to set Receivers"<<endl;
		cout<<"'d' to set computation Data"<<endl;

		cin>>c;

		if (c=='d') prepare_data();
		if (c=='g') prepare_grid();
		if (c=='m') prepare_model();
		if (c=='s') prepare_source();
		if (c=='r') prepare_receivers();

		if (c=='f') {
			prepare_synthetics = true;
		}
	}
}
