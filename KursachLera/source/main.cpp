#include "../include/dependencies.h"
#include "../include/Train.h"
#include "../include/FileList.h"

int main() {
	Train train_1;
	Train train_2;
	train_1.setTrainNumber(3);
	FileList list("test");
	list.insert(train_1);
	list.insert(train_2);

	return 0;
}
