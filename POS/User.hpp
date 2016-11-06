#ifndef USER_HPP
#define USER_HPP
#include <iostream>
using namespace std;
class User
{
private:
	string username;
	string password;
	string fname,lname;
	int age;
	int balance,amount;
public:
	~User();
	User();
	User(string fname, string lname, string username, string password, int age);
	string getUserN();
	void setBalance(int balance);
	void addBalance(int amount);
	int getBalance();
};

#endif
