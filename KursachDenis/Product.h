#pragma once

#include "Header.h"

// ������������, ����������� ��� �����������
// ���� ��� ����������/������
enum class ProductFieldName {
	Name, Category, Quantity, Price,
	Percentage, Date
};

// ����� �������� ����������� ������
class Product {
public:
	// ������������
	Product();	//����������� �� ���������
	Product(const std::string& _name, const std::string& _category, size_t _quantity, double _price,
		double _percentage, size_t _day, size_t _month, size_t _year); //����������� �� ����������
	Product(const Product& copy);//���������� �����������

	// ��������� ���������
	std::string getName() const;
	std::string getCategory() const;
	size_t getQuantity() const;
	double getPrice() const;
	double getPercentage() const;
	size_t getDay() const;
	size_t getMonth() const;
	size_t getYear() const;

	// ��������� ��������
	void setName(const std::string& _name);
	void setCategory(const std::string& _category);
	void setQuantity(size_t _quantity);
	void setPrice(double _price);
	void setPercentage(double _percentage);
	void setDate(size_t _day, size_t _month, size_t _year);
	void setDay(size_t _day);
	void setMonth(size_t _month);
	void setYear(size_t _year);

	// �������� ������
	void output() const;
	friend std::ostream& operator<<(std::ostream& _output, const Product& _product);

private:
	std::string name, category;	//������������ ������ � ���������
	size_t quantity;	//���������� ������
	double price, percentage;	//���� � ������� �������� ��������
	size_t day, month, year;//����, �����, ��� �����������
};
