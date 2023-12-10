#include "../include/dependencies.h"
#include "../include/Train.h"
#include "../include/FileList.h"

int main() {
	Train train_1(1, "Mon", 11, 2, 5, 5, 1, 3, {2, 7, 8});
	Train train_2(2, "Mon Fri", 14, 1, 3, 3, 2, 7, {3, 4, 6});
	Train train_3(3, "qwerty", 1, 2, 3, 4, 5, 6, {7});
	Train train_4(4, "fourth", 4, 4, 4, 4, 4, 3, {44, 44});
	Train train_5(5, "fifth", 5, 5, 5, 5, 5, 5, {55});
	FileList list("test");
	list.insert(train_1);
	list.insert(train_2);
	list.insert(train_3, 0);
	list.insert(train_4);
	list.insert(train_5, 1);
	list.insert(train_1);

	list.print();
	list.find(3);
//	list.remove();
//	list.print();
	return 0;
}
