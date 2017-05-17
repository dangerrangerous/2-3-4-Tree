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

using namespace std;

int main()
{
	Tree234 tree234;

	DataItem dataItem;
	dataItem.data = 2;

	DataItem dataItem2;
	dataItem2.data = 5;
	
	DataItem dataItem3;
	dataItem3.data = 7;


	dataItem.DisplayItem();
	
	DataItem* dataPtr = &dataItem;

	DataItem* dataPtr2 = &dataItem2;
	
	DataItem* dataPtr3 = &dataItem3;
	
	TwoThreeFourNode node1;
	TwoThreeFourNode node2;
	TwoThreeFourNode node3;

	TwoThreeFourNode* node1Ptr = &node1;
	TwoThreeFourNode* node2Ptr = &node2;
	TwoThreeFourNode* node3Ptr = &node3;

	node1Ptr->InsertItem(dataPtr);
	node1Ptr->InsertItem(dataPtr);


	node2Ptr->InsertItem(dataPtr2);
	node2Ptr->InsertItem(dataPtr3);
	cout << "node2ptr node: " << endl;
	node2Ptr->DisplayNode();

	node3Ptr->InsertItem(dataPtr);
	node3Ptr->InsertItem(dataPtr2);
	node3Ptr->InsertItem(dataPtr3);
	cout << "node3ptr node: " << endl;
	node3Ptr->DisplayNode();
	cout << endl;

	cout << "node1Ptr node: " << endl;
	node1Ptr->DisplayNode();
	cout << endl;

	cout << "node1ptr GetNumItems(): " << endl;
	node1Ptr->GetNumItems();
	cout << endl;

	node1Ptr->ConnectChild(1, node2Ptr);
	node2Ptr->ConnectChild(0, node3Ptr);

	// messy checks
	TwoThreeFourNode* node2child = node2Ptr->GetChild(0);
	TwoThreeFourNode* node2parent = node2Ptr->GetParent();
	TwoThreeFourNode* node1child = node1Ptr->GetChild(1);

	cout << "node2 parent: " << endl;
	node2parent->DisplayNode();
	cout << endl;

	cout << "node2 child[0]: " << endl;
	node2child->DisplayNode();
	cout << endl;

	// disconnect node 3 from node 2
	node2Ptr->DisconnectChild(0);

	// should throw error as node2child no longer points to anything.
	// create error handling
	cout << "node2 child[0] after Disconnect: " << endl;
	// node2child should be node3, calling node3 get child would point to non
	// existant node4. returns null, pass.
	node2child->GetChild(0);
	node1child->GetChild(0);
	cout << "node1child DisplayNode()" << endl;
	node1child->DisplayNode();
	cout << endl;
	// node 2 child SHOULD point to node 3
	node2child->DisplayNode();

	node2Ptr->b_IsLeaf();
	node3Ptr->b_IsLeaf();

	node2.GetItem(1);

	node2.FindItem(7);

	node3.RemoveItem();

	tree234.Insert(1);
	tree234.Insert(2);
	tree234.Insert(3);

	tree234.Insert(4);
	tree234.Insert(5);

    return 0;
}

