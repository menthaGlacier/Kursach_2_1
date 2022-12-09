#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Train.h"
#include "List.h"

int main() {
	Train train(420, "Heartbeat Heartbreak", 11, 0, 0, 47, 11, 14,
		vector<uint>{13, 22, 30});
	Train train2(17, "Life will change", 13, 3, 11, 18, 14, 22, 
		vector<uint>{15, 16, 17, 21});

	train.print();
	train2.print();

	Train read;
	fstream fl;
	fl.open("TEST.bin", ios::out | ios::binary);
	fl << train;
	fl.close();

	fl.open("TEST.bin", ios::in | ios::binary);
	fl >> read;
	fl.close();
	read.print();
}
