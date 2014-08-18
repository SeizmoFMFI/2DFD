#ifndef IO_H
#define IO_H

class Files {
public:
	static const char *input_data, *input_model, *input_receivers, *input_source,
		*snapshot, *sparse_field_binary, *sparse_field_txt,
		*records_from_src;
};

class InputOutput {
public:
	Files files;

	bool load(), load_data(), load_model(), load_sources(), load_receivers();
	bool prepare_model_for_computation(const int mmx, const int mml);
	void record_snapshot(const int active_source), record_sparse_binary(const int iter), record_sparse_txt(const int iter);
	void check_recording();

	int record_sparse_every_n_binary, record_sparse_every_n_txt, iter_when_record_snapshot;
	int sparse_spacing;
	void record_at_receivers(const int iter, const int active_source);
};

extern InputOutput io;
#endif
