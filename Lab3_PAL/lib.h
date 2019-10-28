#ifndef LIB_H
#define LIB_H

#include "mt64.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdint>

using namespace std;

void generate_data(uint64_t size, string file_name) {
	ofstream data_of(file_name);
	string data = "";
	uint64_t max_length = data.max_size() / 100;

	for (uint64_t i = 0; i < size; ++i) {
		string line = to_string(genrand64_int64()) + "\n";
		if (data.length() + line.length() < max_length)
			data += line;
		else {
			data_of << data;
			data = line;
		}
	}

	data_of << data;
	data_of.close();
}

void get_data(uint64_t ** data, uint64_t size, string file_name) {
	ifstream data_if(file_name);
	uint64_t i = 0, j;
	string line;

	while (data_if >> line && i < size) {
		istringstream iss(line);
		iss >> j;

		data[i] = new uint64_t[2] { i + 1, j };
		++i;
	};

	data_if.close();
}

void set_data(uint64_t ** data, uint64_t size, string file_name) {
	ofstream data_of(file_name);
	string data_s = "";
	uint64_t max_length = data_s.max_size() / 100;

	for (uint64_t i = 0; i < size; ++i)
		if (i == 0 || data[i][1] != data[i - 1][1]) {
			string line = to_string(data[i][0]) + "\t" + to_string(data[i][1]) + "\n";
			if (data_s.length() + line.length() < max_length)
				data_s += line;
			else {
				data_of << data_s;
				data_s = line;
			}
		}

	data_of << data_s;
	data_of.close();
}

uint64_t get_max(uint64_t ** arr, uint64_t n) {
	uint64_t max = 0;
	for (uint64_t i = 0; i < n; ++i)
		if (max < arr[i][1])
			max = arr[i][1];

	return max;
}

void count_sort(uint64_t ** arr, uint64_t ** output, uint64_t n, double exp) {
	uint64_t i, count[10] = { 0 };

	for (i = 0; i < n; ++i)
		++count[uint64_t(arr[i][1] * exp) % 10];

	for (i = 1; i < 10; ++i)
		count[i] += count[i - 1];

	i = n;
	while (i != 0) {
		--i;
		uint64_t index = uint64_t(arr[i][1] * exp) % 10;
		output[count[index] - 1][0] = arr[i][0];
		output[count[index] - 1][1] = arr[i][1];
		--count[index];
	}

	for (i = 0; i < n; ++i) {
		arr[i][0] = output[i][0];
		arr[i][1] = output[i][1];
	}
}

void redix_sort(uint64_t ** arr, uint64_t n) {
	uint64_t m = get_max(arr, n);
	uint64_t ** output = new uint64_t*[n];
	for (uint64_t i = 0; i < n; ++i)
		output[i] = new uint64_t[2];

	for (double exp = 1; uint64_t(m * exp) > 0; exp *= 0.1)
		count_sort(arr, output, n, exp);

	for (uint64_t i = 0; i < n; i++)
		delete[] output[i];
	delete[] output;
}

void merge(uint64_t ** arr, uint64_t l, uint64_t m, uint64_t r) {
	uint64_t i, j, k;
	uint64_t n1 = m - l + 1;
	uint64_t n2 = r - m;

	uint64_t ** L = new uint64_t*[n1];
	uint64_t ** R = new uint64_t*[n2];

	for (i = 0; i < n1; ++i) {
		L[i] = new uint64_t[2];
		L[i][0] = arr[l + i][0];
		L[i][1] = arr[l + i][1];
	}
	for (j = 0; j < n2; ++j) {
		R[j] = new uint64_t[2];
		R[j][0] = arr[m + 1 + j][0];
		R[j][1] = arr[m + 1 + j][1];
	}

	i = 0, j = 0, k = l;
	while (i < n1 && j < n2) {
		if (L[i][1] <= R[j][1]) {
			arr[k][0] = L[i][0];
			arr[k][1] = L[i][1];
			++i;
		}
		else {
			arr[k][0] = R[j][0];
			arr[k][1] = R[j][1];
			++j;
		}
		++k;
	}

	while (i < n1) {
		arr[k][0] = L[i][0];
		arr[k][1] = L[i][1];
		++i;
		++k;
	}

	while (j < n2) {
		arr[k][0] = R[j][0];
		arr[k][1] = R[j][1];
		++j;
		++k;
	}

	for (uint64_t i = 0; i < n1; i++)
		delete[] L[i];
	delete[] L;

	for (uint64_t i = 0; i < n2; i++)
		delete[] R[i];
	delete[] R;
}

void merge_sort(uint64_t ** arr, uint64_t l, uint64_t r) {
	if (l < r) {
		uint64_t m = l + (r - l) / 2;

		merge_sort(arr, l, m);
		merge_sort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}

#endif //LIB_H
