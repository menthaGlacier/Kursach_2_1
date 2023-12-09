#include "../include/dependencies.h"
#include "../include/Train.h"
#include "../include/FileList.h"

int main() {
	Train train_1(1, "Mon", 11, 2, 5, 5, 1, 3, {2});
	Train train_2(2, "Mon Fri", 14, 1, 3, 3, 2, 7, {3, 4, 6});
	Train train_3;
	train_1.setTrainNumber(3);
	FileList list("test");
	list.insert(train_1);
	list.insert(train_2);
	list.insert(train_3, 0);

//	list.print();
	return 0;
}
