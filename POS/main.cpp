/* STANDARD LIBRARY */
#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>

/* HEADER */
#include "Product.hpp"
#include "FuncPro.hpp"
#include "User.hpp"
using namespace std;

int main()
{
	// GET WINDOWS HANDLE
	const HANDLE CSL_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);
	
	
	INIT_Welcome(CSL_HANDLE);
	
    INIT_Menu(CSL_HANDLE);

	return 0;
}
