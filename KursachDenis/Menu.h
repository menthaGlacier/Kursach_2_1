#pragma once
#include "Header.h"
#include "List.h"

class Menu {
public:
	void launch();
private:
	void actionAdd();
	void actionRemove();
	void actionSort();
	void actionSearch();
	void actionSave();
	void actionLoad();
	void actionInvoice();

	Product inputProduct();

	List warehouse;
	std::string input_line;
};