#ifndef OPTIM_H
#define OPTIM_H
#include "global.h"

class Optimalisation {
public:
	
	int  iter_when_save_state;

	void record_state();

	void check_for_save(const int iter);
};

extern Optimalisation optimalisation;
#endif
