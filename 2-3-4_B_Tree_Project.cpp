// 2-3-4_B_Tree_Project.cpp : Defines the entry point for the console application.
// Brian Keppinger

#include "stdafx.h"
#include "2-3-4_B_Tree.h"
#include "Menu.h"
#include <iostream>

using namespace std;

int main()
{
	Tree234 tree234;
	Menu menu;
	/*
	tree234.Insert(16);
	tree234.Insert(3);
	tree234.Insert(8);
	tree234.Insert(1);
	tree234.Insert(22);
	tree234.Insert(18);
	tree234.Insert(19);
	tree234.Insert(24);
	tree234.Insert(25);
	tree234.Insert(26);
	tree234.Insert(2);
	tree234.Insert(5);
	tree234.Insert(6);
*/
	// User menu do while loop
	do
	{
		menu.Display();
		menu.QueryUser();
		menu.ProcessCommand(tree234);
	} while (menu.Continue());

    return 0;
}

