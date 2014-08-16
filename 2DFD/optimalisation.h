#ifndef OPTIM_H
#define OPTIM_H
#include "global.h"

class Optimalisation {
public:
	const static int  attenuate_boundary_n  =  100; //180;
	int  iter_when_save_state;

	void record_state();

	void check_for_save(const int iter);

	void attenuate_bottom(),attenuate_NR_bounds(const float dlzka);
};

extern Optimalisation optimalisation;
#endif
