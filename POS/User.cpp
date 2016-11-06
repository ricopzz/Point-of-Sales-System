#include "User.hpp"

User::~User(){}

User::User(){}
	
User::User(string fname, string lname, string username, string password, int age)
{
	this->fname=fname;
	this->lname=lname;
	this->age=age;
	this->username=username;
	this->password=password;
}

string User::getUserN()
{
	return username;
}

void User::setBalance(int balance)
{
	this->balance=balance;
}

void User::addBalance(int amount)
{
	this->balance+=amount;
}

int User::getBalance()
{
	return balance;
}
