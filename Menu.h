// Menu.h
// Brian Keppinger

#pragma once

#include "2-3-4_B_Tree.h"

using namespace std;

enum MenuChoices {
	Quit, Insert, Remove, Find, Preorder, Inorder, Postorder, Height, NodeCount
};

class Menu
{
public:
	// Default constructor
	Menu(void);
	// Default destructor
	~Menu(void);

	// Accessor
	MenuChoices Menu::Get();

	// Mutator
	void Menu::Set(MenuChoices);
	void Menu::Display();
	void Menu::QueryUser();
	bool Menu::Continue();
	void Menu::ProcessCommand(Tree234&);

private:

	MenuChoices userMenuSelection;

};