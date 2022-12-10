#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Train.h"
#include "List.h"

int main() {
	Train train1(420, "Heartbeat Heartbreak", 11, 0, 0, 47, 11, 14,
		vector<uint>{13, 22, 30});
	Train train2(17, "Life will change", 13, 3, 11, 18, 14, 22, 
		vector<uint>{15, 16, 17, 21});
	Train train3;
	Train train4(4, "Mon Tue Fri Sat", 4, 4, 4, 4, 4, 4, {4, 5, 4});
	Train train5(1919, "191919", 1, 2, 3, 4, 5, 6, {7, 8, 9, 10});

	fstream file("TEST.bin", ios::out | ios::binary);
	file << train1 << train2 << train3 << train4;
	file.close();

	List list;
	list.load("TEST.bin");
	list.print();
	list.remove(2);
	list.save("TEST.bin");
	list.load("TEST.bin");
	list.print();
}
