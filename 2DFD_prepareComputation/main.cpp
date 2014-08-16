#include "global.h"

void main() {
	char c = ' ';

	while (c != 'q') {
		clear_screen();
		cout << "Press:" << endl;
		cout << "'d' to prepare computation Data" << endl;
		cout << "'m' to prepare Model" << endl;
		cout << "'s' to prepare Sources" << endl;
		cout << "'r' to prepare Receivers" << endl;
		
		cout << "'q' to Quit" << endl;

		cin >> c;

		if (c == 'd') prepare_data();
		if (c == 'm') prepare_model();
		if (c == 's') prepare_source();
		if (c == 'r') prepare_receivers();
	}
}
