#include "Product.h"

// Конструктор по умолчанию
Product::Product()
	: name(), category(), quantity(0), price(1.0), percentage(0.0),
	day(1), month(1), year(1970) {}

// Конструктор по параметрам
Product::Product(const std::string& _name, const std::string& _category, size_t _quantity,
	double _price, double _percentage, size_t _day, size_t _month, size_t _year) {
	this->setName(_name);
	this->setCategory(_category);
	this->setQuantity(_quantity);
	this->setPrice(_price);
	this->setPercentage(_percentage);
	this->setDate(_day, _month, _year);
}

// Конструктор копирования
Product::Product(const Product& copy) {
	this->setName(copy.name);
	this->setCategory(copy.category);
	this->setQuantity(copy.quantity);
	this->setPrice(copy.price);
	this->setPercentage(copy.percentage);
	this->setDate(copy.day, copy.month, copy.year);
}

// Геттеры
std::string Product::getName() const {
	return name;
}

std::string Product::getCategory() const {
	return category;
}

size_t Product::getQuantity() const {
	return quantity;
}

double Product::getPrice() const {
	return price;
}

double Product::getPercentage() const {
	return percentage;
}

size_t Product::getDay() const {
	return day;
}

size_t Product::getMonth() const {
	return month;
}

size_t Product::getYear() const {
	return year;
}

// Сеттеры
void Product::setName(const std::string& _name) {
	name = _name;
}

void Product::setCategory(const std::string& _category) {
	category = _category;
}

void Product::setQuantity(size_t _quantity) {
	quantity = _quantity;
}

void Product::setPrice(double _price) {
	if (_price < 1.0) { // Цена не может быть ниже 1
		price = 1.0;
	} else {
		price = _price;
	}
}

void Product::setPercentage(double _percentage) {
	if (_percentage < 0.0) { // Процент не может быть меньше 0
		percentage = 0.0f;
	} else if (_percentage > 1000.0) { // Либо превышать 1000%
		percentage = 1000.0;
	} else {
		percentage = _percentage;
	}
}

void Product::setDate(size_t _day, size_t _month, size_t _year) {
	if (_year < 1970) {
		_year = 1970;
	} else if (_year > 2038) {
		_year = 2038;
	}

	if (_month == 0) {
		_month = 1;
	} else if (_month > 12) {
		_month = 12;
	}

	size_t day_limit = 31;
	if (_month == 2) {
		if (_year % 4 == 0) {
			day_limit = 29;
		} else {
			day_limit = 28;
		}
	} else 
		if ((_month < 8 && _month % 2 == 0)
			|| (_month > 7 && _month % 2 == 1)) {
			day_limit = 30;
	}

	if (_day == 0) {
		_day = 0;
	} else if (_day > day_limit) {
		_day = day_limit;
	}

	day = _day;
	month = _month;
	year = _year;
}

void Product::setDay(size_t _day) {
	if (_day < 1) { // День не может быть меньше 1
		day = 1;
	} else if (_day > 31) { // Либо превышать 31
		day = 31;
	} else {
		day = _day;
	}
}

void Product::setMonth(size_t _month) {
	if (_month < 1) { // Месяц не может быть меньше 1
		month = 1;
	} else if (_month > 12) { // Либо превышать 12
		month = 12;
	} else {
		month = _month;
	}
}

void Product::setYear(size_t _year) {
	if (_year < 1970) { // Год не может быть меньше 1970
		year = 1970;
	} else if (_year > 2038) { // Либо превышать 2038
		year = 2038;
	} else {
		year = _year;
	}
}

// Метод вывода
void Product::output() const {
	std::cout <<
		"Product name: " << this->name <<
		"\nCategory: " << this->category <<
		"\nQuantity: " << this->quantity <<
		"\nPrice for 1: " << this->price <<
		"\nMarkup percentage: " << this->percentage <<
		"\nReceipt date: " << this->day << "." << this->month << "." << this->year
	<<	std::flush;
}

// Оператор вывода в поток
std::ostream& operator<<(std::ostream& _output, const Product& _product) {
	_output <<
		"Product name: " << _product.name <<
		"\nCategory: " << _product.category <<
		"\nQuantity: " << _product.quantity <<
		"\nPrice for 1: " << _product.price <<
		"\nMarkup percentage: " << _product.percentage <<
		"\nReceipt date: " << _product.day << "." << _product.month << "." << _product.year;
	return _output;
}

// Оператор присваивания
Product& Product::operator=(const Product& _product) {
	// Если объекты совпадают, копирование не требуется
	if (this == &_product) {
		return *this;
	}

	// Иначе копируем содержимое _product в объект
	this->setName(_product.name);
	this->setCategory(_product.category);
	this->setQuantity(_product.quantity);
	this->setPrice(_product.price);
	this->setPercentage(_product.percentage);
	this->setDate(_product.day, _product.month, _product.year);
	return *this;
}

// Оператор сравнения "равно"
bool Product::operator==(const Product& _product) const {
	// Если какое-либо поле не совпадает с сравниваемым - объекты не равны
	if (this->name != _product.name
	|| this->category != _product.category
	|| this->quantity != _product.quantity
	|| this->percentage != _product.percentage
	|| this->price != _product.price
	|| this->day != _product.day
	|| this->month != _product.month
	|| this->year != _product.year) {
		return false;
	}

	return true;
}

// Оператор сравнения "больше"
bool Product::operator>(const Product& _product) const {
	// Сравнение идёт по полю "Наименование товара"
	if (this->name > _product.name) {
		return true;
	}

	return false;
}

// Оператор сравнения "меньше"
bool Product::operator<(const Product& _product) const {
	// Сравнение идёт по полю "Наименование товара"
	if (this->name < _product.name) {
		return true;
	}

	return false;
}