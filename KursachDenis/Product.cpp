#include "Product.h"

// ����������� �� ���������
Product::Product()
	: name(), category(), quanity(0), price(1.0), percentage(0.0),
	day(1), month(1), year(1970) {}

// ����������� �� ����������
Product::Product(std::string _name, std::string _category, size_t _quanity,
	double _price, double _percentage, size_t _day, size_t _month, size_t _year) {
	this->setName(_name);
	this->setCategory(_category);
	this->setQuanity(_quanity);
	this->setPrice(_price);
	this->setPercentage(_percentage);
	this->setDay(_day);
	this->setMonth(_month);
	this->setYear(_year);
}

// ����������� �����������
Product::Product(const Product& copy) {
	this->setName(copy.name);
	this->setCategory(copy.category);
	this->setQuanity(copy.quanity);
	this->setPrice(copy.price);
	this->setPercentage(copy.percentage);
	this->setDay(copy.day);
	this->setMonth(copy.month);
	this->setYear(copy.year);
}

// �������
std::string Product::getName() const {
	return name;
}

std::string Product::getCategory() const {
	return category;
}

size_t Product::getQuanity() const {
	return quanity;
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

// �������
void Product::setName(std::string _name) {
	name = _name;
}

void Product::setCategory(std::string _category) {
	category = _category;
}

void Product::setQuanity(size_t _quanity) {
	if (_quanity < 0) {
		quanity = 0;
	} else if (_quanity > 9999) {
		quanity = 9999;
	} else {
		quanity = _quanity;
	}
}

void Product::setPrice(double _price) {
	if (_price < 1.0) { // ���� �� ����� ���� ���� 1
		price = 1.0;
	} else if (_price > 99999.0) { // ����� �� ����� ��������� 99999
		price = 99999.0;
	} else {
		price = _price;
	}
}

void Product::setPercentage(double _percentage) {
	if (_percentage < 0.0) { // ������� �� ����� ���� ������ 0
		percentage = 0.0f;
	} else if (_percentage > 10.0) { // ���� ��������� 10 (1000%) 
		percentage = 10.0;
	} else {
		percentage = _percentage;
	}
}

void Product::setDay(size_t _day) {
	if (_day < 1) { // ���� �� ����� ���� ������ 1
		day = 1;
	} else if (_day > 31) { // ���� ��������� 31
		day = 31;
	} else {
		day = _day;
	}
}

void Product::setMonth(size_t _month) {
	if (_month < 1) { // ����� �� ����� ���� ������ 1
		month = 1;
	} else if (_month > 12) { // ���� ��������� 12
		month = 12;
	} else {
		month = _month;
	}
}

void Product::setYear(size_t _year) {
	if (_year < 1970) { // ��� �� ����� ���� ������ 1970
		year = 1970;
	} else if (_year > 2038) { // ���� ��������� 2038
		year = 2038;
	} else {
		year = _year;
	}
}

// ����� ������
void Product::output() const {
	std::cout <<
		"Product name: " << this->name << "\n" <<
		"Category: " << this->category << "\n" <<
		"Quanity: " << this->quanity << "\n" <<
		"Price for 1: " << this->price << "\n" <<
		"Sale percentage: " << this->percentage << "\n" <<
		"Receipt date: " << this->day << ":" << this->month << ":" << this->year <<
	std::endl;
}

// �������� ������ � �����
std::ostream& operator<<(std::ostream _output, const Product& _product) {
	_output <<
		"Product name: " << _product.getName() << "\n" <<
		"Category: " << _product.getCategory() << "\n" <<
		"Quanity: " << _product.getQuanity() << "\n" <<
		"Price for 1: " << _product.getPrice() << "\n" <<
		"Sale percentage: " << _product.getPercentage() << "\n" <<
		"Receipt date: " << _product.getDay() << ":" << _product.getMonth() << ":" << _product.getYear();
	return _output;
}

// �������� ������������
Product& Product::operator=(const Product& _product) {
	// ���� ������� ���������, ����������� �� ���������
	if (this == &_product) {
		return *this;
	}

	// ����� �������� ���������� _product � ������
	this->setName(_product.name);
	this->setCategory(_product.category);
	this->setQuanity(_product.quanity);
	this->setPrice(_product.price);
	this->setPercentage(_product.percentage);
	this->setDay(_product.day);
	this->setMonth(_product.month);
	this->setYear(_product.year);
	return *this;
}

// �������� ��������� "�����"
bool Product::operator==(const Product& _product) const {
	// ���� �����-���� ���� �� ��������� � ������������ - ������� �� �����
	if (this->name != _product.name
		|| this->category != _product.category
		|| this->quanity != _product.quanity
		|| this->percentage != _product.percentage
		|| this->price != _product.price
		|| this->day != _product.day
		|| this->month != _product.month
		|| this->year != _product.year) {
		return false;
	}

	return true;
}

// �������� ��������� "������"
bool Product::operator>(const Product& _product) const {
	// ��������� ��� �� ���� "������������ ������"
	if (this->name > _product.name) {
		return true;
	}

	return false;
}

// �������� ��������� "������"
bool Product::operator<(const Product& _product) const {
	// ��������� ��� �� ���� "������������ ������"
	if (this->name < _product.name) {
		return true;
	}

	return false;
}