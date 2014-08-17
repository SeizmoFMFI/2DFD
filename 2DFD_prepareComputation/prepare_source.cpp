#include "global.h"

void prepare_source() {
	int n_src,src_type,src_time_function;
	float src_char_time;
	
	n_src		= get_input("Number of sources:", 1, 999);
	src_type	= get_input("Number of sources:\n1 - explosion\n2 - double couple", 1, 2);
	src_time_function = get_input("Source time function:\n0-read from file\n1-Kupper\n2-Ricker\n3-Gabor\n4-Berlage", 0, 4);
	src_char_time = get_input("Characteristic time [ms]:", 0.f, 100000.f);

	FILE *out = fopen("sources.txt", "w");
	fprintf(out, "%d\n", n_src);
    fprintf(out,"%d %d\n",src_type,src_time_function);
	fprintf(out,"%f\n",src_char_time);

	if (src_type == 1) {
		float tmpf;
		for (int i = 0; i < n_src; i++) {
			cout << "moment M0 of source "<<i<<": ";
			cin >> tmpf;
			fprintf(out, "%f 0\n", tmpf);
		}
	}
	else if (src_type == 2) {
		float tmpm,tmpd;
		for (int i = 0; i < n_src; i++) {
			cout << "moment M0 and dip [degrees] of source "<<i<<": ";
			cin >> tmpm;
			cin >> tmpd;
			fprintf(out, "%f %f\n", tmpm, tmpd);
		}
	}
	else {
		cout << "ERR: unknown source type";
		return;
	}

	char c;
	cout<<"Random positions of sources? y/n: ";
	cin>>c;
	float sx, sz;
	for (int i=0;i<n_src;i++) {
		if (c=='y') {
			sx=(float)rand()/(float)RAND_MAX*0.8f+0.1f;
			sz=(float)rand()/(float)RAND_MAX*0.8f+0.1f;
		}
		else {
			cout<<"Position [x,depth] of source "<<i<<" in grid (percents): ";
			cin>>sx;
			sx/=100;
			cin>>sz;
			sz/=100;
			if ((sx<0.f)||(sx>1.f)||(sz<0.f)||(sz>1.f)) {
				cout<<"source position is wrong. Should be in %."<<endl;
				i--;
				continue;
			}
		}
		fprintf(out,"%f %f\n",sx,sz);
	}
	fclose(out);
}