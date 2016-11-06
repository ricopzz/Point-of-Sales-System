#ifndef FUNCPRO_HPP
#define FUNCPRO_HPP

/* STANDARD LIBRARY */
#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <cstdlib>
#include "Product.hpp"
#include "User.hpp"
using namespace std;

/* CONSTANTS FOR TEXT COLORING */
#define TEXT_BLACK           0
#define TEXT_BLUE            1
#define TEXT_GREEN           2
#define TEXT_AQUA            3
#define TEXT_RED             4
#define TEXT_PURPLE          5
#define TEXT_YELLOW          6
#define TEXT_WHITE           7
#define TEXT_GRAY            8
#define TEXT_LIGHTBLUE       9
#define TEXT_LIGHTGREEN     10
#define TEXT_LIGHTAQUA      11
#define TEXT_LIGHTRED       12
#define TEXT_LIGHTPURPLE    13
#define TEXT_LIGHTYELLOW    14
#define TEXT_BRIGHTWHITE    15

/* CONSTANTS FOR SYMBOLS, ABREVATIONS, ETC */
#define BL_VERTICAL        (char)186   // ║
#define BL_HOR1            (char)205   // ═
#define BL_HOR2            (char)196   // ─
#define BL_BOTLEFT         (char)200   // ╚
#define BL_BOTRIGHT        (char)188   // ╝
#define BL_TOPLEFT         (char)201   // ╔
#define BL_TOPRIGHT        (char)187   // ╚
#define BL_CROSSUP         (char)202   // ╩
#define BL_CROSSDOWN       (char)209   // ╤
#define BL_INTERSECT       (char)215   // ╫
#define DR_ASCENDING       (char)175   // >>
#define DR_DESCENDING      (char)174   // <<

/* DEFINE PROGRAM TITLE */
#define PROGRAM_TITLE "POINT OF SALES SYSTEM"

void ADMIN_Add(HANDLE WINHANDLE);
void ADMIN_Topup(HANDLE WINHANDLE);
void RANDOM_ID();
void MENU_Admin(HANDLE WINHANDLE);
void INIT_Welcome(HANDLE WINHANDLE); 
void INIT_Register(HANDLE WINHANDLE);
void INIT_Header(char menuName[]);
void INIT_Login(HANDLE WINHANDLE);
void INIT_MenuBox_Top();
void INIT_MenuBox_Bottom();
void MENU_Menu(HANDLE WINHANDLE);
void MENU_Order(HANDLE WINHANDLE);
void MENU_Cancel(HANDLE WINHANDLE);
void MENU_Checkout(HANDLE WINHANDLE);
void INIT_Menu(HANDLE WINHANDLE);

#endif

