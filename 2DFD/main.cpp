#include "global.h"
int active_source;
Files files;
Optimalisation optimalisation;

void aux_model_parameters() {
	co_mu = co_vS*co_vS*co_density;
	co_lam = co_vP*co_vP*co_density - 2 * co_mu;
	co_muzx = co_mu;
	co_lam2mu = co_lam + 2 * co_mu;
}

void main_forward() {
	for(int i=0;i<n_src;i++) {
		cout<<"i: active source "<<i<<endl;
		cout<<"i: main loop running"<<endl;
		time_loop(i);
		cout<<"i: source "<<i<<" finished"<<endl;
	}
}

void load() {
	cout << "i: loading" << endl;
	loadModel();
	loadSource();
	loadReceivers();
	auxiliary();
}

int main() {
	CPU_TIME();
	
	load();
	aux_charakteristika();

	CPU_TIME();
	main_forward();

	CPU_TIME();
	cout<<"Finished."<<endl;
	
	return(0);
}
