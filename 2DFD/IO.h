#ifndef IO_H
#define IO_H

class InputOutput {
public:
	Files files;

	bool load(), load_data(), load_model(), load_sources(), load_receivers();
	bool prepare_model_for_computation();
	void record_snapshot(), record_sparse_binary(), record_sparse_txt();
	void check_recording();

	int record_sparse_every_n_binary, record_sparse_every_n_txt, iter_when_record_snapshot;
	int sparse_spacing;
};

extern InputOutput io;
#endif
