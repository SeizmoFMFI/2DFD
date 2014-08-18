#include "global.h"

void record(const int iter, const int active_source) {
	io.record_at_receivers(iter,active_source);

	if (iter == io.iter_when_record_snapshot)
		io.record_snapshot(active_source);
	if (iter%io.record_sparse_every_n_txt == 0)
		io.record_sparse_txt(iter,active_source);
	if (iter%io.record_sparse_every_n_binary == 0)
		io.record_sparse_binary(iter,active_source);
}

void time_loop(const int active_source) {
	for (int i=0;i<max_num_iter;i++) {
		velocity_update(i,active_source);
		displacement_update();

		record(i,active_source);
	}
}
