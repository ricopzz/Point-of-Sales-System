#include "Product.hpp"
#include "FuncPro.hpp"

Product::~Product(){}

Product::Product(){}

Product::Product(string productName, string productCode, int price)
{
	this->productName=productName;
	this->productCode=productCode;
	this->price=price;
}
void Product::setPName(string productName)
{
	this->productName=productName;
}

void Product::setPCode(string productCode)
{
	this->productCode=productCode;
}

void Product::setPrice(int price)
{
	this->price=price;
}

void Product::setQty(int quantity)
{
	this->quantity=quantity;
}

string Product::getPName()
{
	return productName;
}

string Product::getPCode()
{
	return productCode;
}

int Product::getPrice()
{
	return price;	
}

int Product::getQty()
{
	return quantity;	
}
