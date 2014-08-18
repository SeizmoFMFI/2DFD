#include "global.h" 

void InputOutput::record_snapshot(const int active_source) {
	char s[256];
	sprintf(s,"%s_%d.bin",files.snapshot,active_source);
	cout<<"i: recording state "<<active_source<<" "<<s<<endl;
	FILE *out = fopen(s,"wb");
	int size = sizeof(u[0][0]);
	for(int i=0;i<mx;i++) {
		fwrite ( u[i], size, mz, out);
		fwrite ( w[i], size, mz, out);
		fwrite (vu[i], size, mz, out);
		fwrite (vw[i], size, mz, out);
	}

	//non-reflecting bounds
	size = sizeof(stored_u_1_level0[0]);
	fwrite (stored_u_1_level0, size, mz, out);
	fwrite (stored_u_2_level0, size, mz, out);
	fwrite (stored_u_3_level0, size, mz, out);

	fwrite (stored_u_mx1_level0, size, mz, out);
	fwrite (stored_u_mx2_level0, size, mz, out);
	fwrite (stored_u_mx3_level0, size, mz, out);

	fwrite (stored_w_0_level0, size, mz, out);
	fwrite (stored_w_1_level0, size, mz, out);
	fwrite (stored_w_2_level0, size, mz, out);

	fwrite (stored_w_mx1_level0, size, mz, out);
	fwrite (stored_w_mx2_level0, size, mz, out);
	fwrite (stored_w_mx3_level0, size, mz, out);

	fwrite (stored_u_mz1_level0, size, mx, out);
	fwrite (stored_u_mz2_level0, size, mx, out);
	fwrite (stored_u_mz2_level1, size, mx, out);
	fwrite (stored_u_mz3_level0, size, mx, out);
	fwrite (stored_u_mz3_level1, size, mx, out);

	fwrite (stored_w_mz1_level0, size, mx, out);
	fwrite (stored_w_mz2_level0, size, mx, out);
	fwrite (stored_w_mz2_level1, size, mx, out);
	fwrite (stored_w_mz3_level0, size, mx, out);
	fwrite (stored_w_mz3_level1, size, mx, out);

	fwrite (&stored_u_1_level1, size, 1, out);
	fwrite (&stored_u_2_level1, size, 1, out);
	fwrite (&stored_u_3_level1, size, 1, out);
	fwrite (&stored_u_mx3_level1, size, 1, out);
	fwrite (&stored_u_mx2_level1, size, 1, out);
	fwrite (&stored_u_mx1_level1, size, 1, out);

	fwrite (&stored_w_0_level1, size, 1, out);
	fwrite (&stored_w_1_level1, size, 1, out);
	fwrite (&stored_w_2_level1, size, 1, out);
	fwrite (&stored_w_mx3_level1, size, 1, out);
	fwrite (&stored_w_mx2_level1, size, 1, out);
	fwrite (&stored_w_mx1_level1, size, 1, out);
	fclose(out);
}
