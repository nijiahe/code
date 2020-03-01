#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <memory>
#include <numeric>
#include <iterator>
#include <cstdlib>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <utility>
#include <cstring>

class Quote
{
public:
	Quote() = default;
	Quote(const std::string &book, double sales_price):bookNo(book),price(sales_price){}
	std::string isbn() const { return bookNo; }
	virtual double net_price(std::size_t n) const { return n * price; }
	virtual ~Quote() = default;
private:
	std::string bookNo;
protected:
	double price = 0.0;
};

double print_total(std::ostream &os, const Quote &item, std::size_t n)
{
	double price = item.net_price(n);
	os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << price << std::endl;
	return price;
}

class Bulk_quote :public Quote {
public:
	Bulk_quote() = default;
	Bulk_quote(const std::string& isbn, double price, std::size_t sz, double disc):Quote(isbn,price),min_qty(sz),discount(disc){}
	double net_price(std::size_t) const override;
private:
	std::size_t min_qty = 0;
	double discount = 0.0;
};

double Bulk_quote::net_price(std::size_t count) const
{
	if (count < min_qty)
		return price * count;
	else
		return price * count * (1 - discount);
}

class Limit_quote :public Quote {
public:
	Limit_quote() = default;
	Limit_quote(const std::string& isbn, double price, std::size_t sz, double disc) :Quote(isbn, price), max_qty(sz), discount(disc) {}
	double net_price(std::size_t) const override;
private:
	std::size_t max_qty = 0;
	double discount = 0.0;
};

double Limit_quote::net_price(std::size_t sz) const
{
	if (sz > max_qty)
		return (sz - max_qty)*price + max_qty * price*(1 - discount);
	else
		return price * sz * (1 - discount);
}

int main15_2_1()
{
	Quote q1 = Quote("Cpp", 99);
	Bulk_quote q2 = Bulk_quote("Hacking", 20, 2, 0.5);
	Limit_quote q3 = Limit_quote("Exploitation", 30, 4, 0.5);
	print_total(std::cout, q1, 2);
	print_total(std::cout, q2, 1);
	print_total(std::cout, q2, 3);
	print_total(std::cout, q3, 3);
	print_total(std::cout, q3, 5);

	system("pause");
	return 0;
}