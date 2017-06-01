// Menu.cpp
// Brian Keppinger

#include "stdafx.h"
#include "Menu.h"
#include "2-3-4_B_Tree.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Default constructor
Menu::Menu(void)
{
	userMenuSelection = Quit;
}

// Default destructor
Menu::~Menu(void)
{
	cout << "Destroying Menu." << endl;
}

// Getter
MenuChoices Menu::Get()
{
	return userMenuSelection;
}

// Setter
void Menu::Set(MenuChoices newValue)
{
	userMenuSelection = newValue;
}

void Menu::Display()
{
	cout << endl;
	cout << left << setw(32) << "1: Quit" << endl;
	cout << left << setw(32) << "2: Insert" << endl;
	cout << left << setw(32) << "3: Remove" << endl;
	cout << left << setw(32) << "4: Find" << endl;
	cout << left << setw(32) << "5: Preorder Traversal" << endl;
	cout << left << setw(32) << "6: Inorder Traversal" << endl;
	cout << left << setw(32) << "7: Postorder Traversal" << endl;
	cout << left << setw(32) << "8: Height" << endl;
	cout << left << setw(32) << "9: NodeCount" << endl << endl;

} // end Display()


void Menu::QueryUser()
{
	int selection;

	cout << "Please enter menu selection." << endl;

	cin >> selection;

	switch (selection)
	{
	case 1: userMenuSelection = Quit;
		break;
	case 2: userMenuSelection = Insert;
		break;
	case 3: userMenuSelection = Remove;
		break;
	case 4: userMenuSelection = Find;
		break;
	case 5: userMenuSelection = Preorder;
		break;
	case 6: userMenuSelection = Inorder;
		break;
	case 7: userMenuSelection = Postorder;
		break;
		/*
		TODO:
	case 8: userMenuSelection = Height;
		break;
	case 9: userMenuSelection = NodeCount;
		break;
		*/
	default: userMenuSelection = Quit;
	}
	cout << endl;
} // end QueryUser()

bool Menu::Continue()
{
	return userMenuSelection != Quit;
} // end Continue()

void Menu::ProcessCommand(Tree234& twoThreeFourTree)
{
	int key;

	if (userMenuSelection != Quit)
	{
		switch (userMenuSelection)
		{
		case Insert:
			cout << "Please enter a value to be inserted into the tree." << endl;
			cin >> key;
			twoThreeFourTree.Insert(key);
			cout << endl;
			break;
			
		case Remove:
			cout << "Please enter a value to be removed from the tree." << endl;
			cin >> key;
			twoThreeFourTree.RemoveFromTree(key);
			cout << endl;
			break;

		case Find:
			cout << "Please enter a value to search for." << endl;
			cin >> key;
			twoThreeFourTree.Find(key);
			cout << endl;
			break;

		case Preorder:
			cout << "Recursive preorder traversal." << endl;
			twoThreeFourTree.DisplayPreOrder();
			break;

		case Inorder:
			cout << "Recursive inorder traversal." << endl;
			twoThreeFourTree.DisplayInOrder();
			break;

		case Postorder:
			cout << "Recursive postorder traversal." << endl;
			twoThreeFourTree.DisplayPostOrder();
			cout << endl;
			break;
			/*
			TODO:
		case Height:
			cout << "Assessing the height of the tree:" << endl;
			cout << "The tree is " << binaryTree.TreeHeight() << " levels tall." << endl;
			cout << endl;
			break;

		case Nodecount:
			cout << "There are " << twoThreeFourTree.NodeCount() << " nodes in the tree." << endl;
			break;
			*/
		}
	}
}