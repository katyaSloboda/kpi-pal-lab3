// Lab3_PAL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "lib.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	// modes: 0-"full", 1-"half", 2-"short", 3-"super_short"
	int mode = 4;
	uint64_t max_size = 44000000;
	uint64_t size = 48 * (mode == 0 ? max_size
					    : mode == 1 ? max_size / 2
					    : mode == 2 ? max_size / 16
					    : mode == 3 ? max_size / 256
					    : mode == 4 ? 1
					    : 0);

	generate_data(size, "data" + to_string(mode) + ".in");

	uint64_t ** data1 = new uint64_t*[size];
	get_data(data1, size, "data" + to_string(mode) + ".in");

	uint64_t ** data2 = new uint64_t*[size];
	for (uint64_t i = 0; i < size; ++i)
		data2[i] = new uint64_t[2]{data1[i][0], data1[i][1]};

	redix_sort(data1, size);
	set_data(data1, size, "data" + to_string(mode) + "_redix" + ".out");
	merge_sort(data2, 0, size - 1);
	set_data(data2, size, "data" + to_string(mode) + "_merge" + ".out");

	for (uint64_t i = 0; i < size; ++i) {
		delete[] data1[i];
		delete[] data2[i];
	}
	delete[] data1;
	delete[] data2;
}

