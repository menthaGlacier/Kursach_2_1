#pragma once

#include <iostream>
#include <string>

using namespace std;

class Train {
public:
	Train();
	Train();
	Train(const Train& copy);
private:
	int number;
	string dayOfWeeks;

};
