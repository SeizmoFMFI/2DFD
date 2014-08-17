#include "global.h"

void prepare_data() {
	float tmpf;
	int tmp;

	FILE *out = fopen("data.txt","w");
	tmp = get_input("Number of grid points in X-direction:", 0, 1200);
	fprintf(out, "%d\n", tmp);

	tmpf = get_input("Total time [s]:", 0.f, 24*3600.f);
	fprintf(out, "%f\n", tmpf);

	tmpf = get_input("dt [s]:", 0.f, 1000.f);
	fprintf(out, "%f\n", tmpf);

	tmpf = get_input("Time when save state [s] (or '0' to not):", 0.f, 24 * 3600.f);
	fprintf(out, "%f\n", tmpf);

	tmp = get_input("Sparse snapshot after every n iterations (or '0' to not) to binary:", 0, 1000);
	fprintf(out, "%d\n", tmp);

	tmp = get_input("Sparse snapshot after every n iterations (or '0' to not) to txt:", 0, 1000);
	fprintf(out, "%d\n", tmp);

	tmp = get_input("Sparse snapshot at every N-th grid point (or '0' to not):", 0, 100);
	fprintf(out, "%d\n", tmp);

	fclose(out);
}