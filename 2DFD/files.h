#ifndef FILES_H
#define FILES_H
#include "global.h"
#include <fstream>
#include <iostream>

class Files {
public:
	static const char *input_data,*input_model,*input_grid,*input_receivers,*input_source,
		*snapshot,
		*sparse_direct_field,*sparse_grid_data,*records_at_src,*records_from_src,
		*sparse_java_direct;
};

extern Files files;
#endif
