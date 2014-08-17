#include "global.h"

void time_loop(const int active_source) {
	for (int i=0;i<max_num_iter;i++) {
		velocity_update(active_source);
		displacement_update();

		optimalisation.check_for_save(i+1);
				
		record_at_receivers(i+1);
		if (i%record_every_nth_step==0) {
			record_java(i+1);
			record_sparse(i+1);
		}
	}
}
