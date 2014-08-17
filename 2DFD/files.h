#ifndef FILES_H
#define FILES_H
#include "global.h"
#include <fstream>
#include <iostream>

class Files {
public:
	static const char *input_data,*input_model,*input_receivers,*input_source,
		*snapshot,*sparse_field_binary,*sparse_field_txt,
		*records_from_src;
};

extern Files files;
#endif
