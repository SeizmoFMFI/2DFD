#include "global.h"

bool InputOutput::load() {
	bool loadok = true;
	cout << "i: loading" << endl;
	loadok &= load_model();
	loadok &= load_sources();
	loadok &= load_receivers();
	auxiliary();

	return loadok;
}