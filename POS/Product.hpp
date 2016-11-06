#ifndef PRODUCT_HPP
#define PRODUCT_HPP
#include <iostream>
using namespace std;
class Product
{
private:
	string productName;
	string productCode;
	int price;
	int quantity;
public:
	~Product();
	Product();
	Product(string productName, string productCode, int price);
	void setPName(string productName);
	void setPCode(string productCode);
	void setPrice(int price);
	void setQty(int quantity);
	string getPName();
	string getPCode();
	int getPrice();
	int getQty();
};

#endif
