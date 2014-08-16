#ifndef GLOBAL_H
#define GLOBAL_H

#include <assert.h>
#include <iostream>
using namespace std;

#define SQR(x) (x)*(x)

extern void prepare_model(),prepare_data(),prepare_source(),prepare_receivers(),prepare_grid();

void clear_screen() {
	for (int i = 0; i<50; i++)
		cout << endl;
}
template<class T> T get_input(char* querry, T min_value, T max_value) {
	//waiting for input until correct value within min-max range is submited

	clear_screen();

	T input;
	cout << querry << endl;
	cin >> input;

	if ((input<min_value) || (input>max_value)) {
		cout << "ERR: value outside allowed range <" << min_value << "," << max_value << ">" << endl;
		input = get_input(querry, min_value, max_value);
	}

	return input;
}
#endif GLOBAL_H