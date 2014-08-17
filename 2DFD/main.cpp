#include "global.h"
InputOutput io;

void main_forward() {
	for(int i=0;i<n_src;i++) {
		cout<<"i: active source "<<i<<endl;
		cout<<"i: main loop running"<<endl;
		time_loop(i);
		cout<<"i: source "<<i<<" finished"<<endl;
	}
}

int main() {
	CPU_TIME();
	
	bool loadok = io.load();
	if (!loadok) {
		ERR("loading went wrong");
		return;
	}
	aux_charakteristika();

	CPU_TIME();
	main_forward();

	CPU_TIME();
	cout<<"Finished."<<endl;
	
	return(0);
}
