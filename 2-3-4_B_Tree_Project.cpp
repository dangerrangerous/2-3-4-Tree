// 2-3-4_B_Tree_Project.cpp : Defines the entry point for the console application.
//

// 2-3-4 trees are balanced trees. They are slightly less efficient than red-black trees but are easier to implement.
// They serve as an-easy-to-understand introduction to B trees.

// A node with one data item must always have 2 children. A node with two data items must always have 3 children.
// And a node with three data items must always have 4 children. Hence the name.

// Node Splits:
// A new empty node is created as a sibling of the node being split and is placed to its right.
// Data item C is moved into the new node.
// Data item B is moved into the parent of the node being split.
// Data item A remains where it is.
// The rightmost two children are disconnected from the node being split and are connected to the new node.

// Splitting the Root:
// Create a new root.
// A second new node is created as the sibling of the node bing split.
// Data item C is moved into the new sibling.
// Data item B is moved into the new root.
// Data item A remains where it is.
// The two rightmost children of the node being split are disconnected from it and connected to the new right-hand node.

//  Implement a 2-3-4 B Tree class.  Implement an Insert and Delete operators, as well as any others that are necessary.  
// See the LaFore text. Also implement Inorder, Preorder, and Postorder tree traversal  operators recursively.  
// When the traversal operator visits a node, it should output all node key values. 
#include "stdafx.h"
#include "2-3-4_B_Tree.h"
#include <iostream>

int main()
{
	DataItem dataItem;
	dataItem.data = 2;

	dataItem.DisplayItem();
	
	DataItem* dataPtr;
	dataPtr = &dataItem;
	TwoThreeFourNode node1;
	node1.InsertItem(dataPtr);
	node1.InsertItem(dataPtr);

	node1.DisplayNode();

    return 0;
}

