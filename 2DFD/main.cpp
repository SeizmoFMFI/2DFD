#include "global.h"
int active_source;
Files files;
Optimalisation optimalisation;

void main_forward() {
	cout<<"i: loading"<<endl;
	loadModel();
	loadSource();
	loadReceivers();
    auxiliary();
	for(int i=0;i<n_src;i++) {
		active_source = i;
		cout<<"active source "<<i<<endl;
		cout<<"i: main loop running"<<endl;
		time_loop();
		cout<<"i: source "<<i<<" finished"<<endl;
	}
}

int main() {
	main_vstup();
	CPU_TIME();
	
	loadData();
	load_grid();

	aux_charakteristika();
	main_forward();

	cout<<"Finished."<<endl;
	
	return(0);
}
