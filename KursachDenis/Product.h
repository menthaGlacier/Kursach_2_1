#pragma once

#include "Header.h"

// Перечисление, необходимое для определения
// поля для сортировки/поиска
enum class ProductFieldName {
	Name, Category, Quantity, Price,
	Percentage, Day, Month, Year
};

// Класс продукта справочника склада
class Product {
public:
	// Конструкторы
	Product();
	Product(const std::string& _name, const std::string& _category, size_t _quantity, double _price,
		double _percentage, size_t _day, size_t _month, size_t _year);
	Product(const Product& copy);

	// Получение значаений
	std::string getName() const;
	std::string getCategory() const;
	size_t getQuantity() const;
	double getPrice() const;
	double getPercentage() const;
	size_t getDay() const;
	size_t getMonth() const;
	size_t getYear() const;

	// Установка значений
	void setName(const std::string& _name);
	void setCategory(const std::string& _category);
	void setQuantity(size_t _quantity);
	void setPrice(double _price);
	void setPercentage(double _percentage);
	void setDate(size_t _day, size_t _month, size_t _year);
	void setDay(size_t _day);
	void setMonth(size_t _month);
	void setYear(size_t _year);

	// Средства вывода
	void output() const;
	friend std::ostream& operator<<(std::ostream& _output, const Product& _product);

	// Операторы
	Product& operator=(const Product& _product);
	bool operator==(const Product& _product) const;
	bool operator>(const Product& _product) const;
	bool operator<(const Product& _product) const;

private:
	std::string name, category;
	size_t quantity;
	double price, percentage;
	size_t day, month, year;
};
