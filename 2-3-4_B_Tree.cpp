// 2-3-4_B_Tree.cpp
// Brian Keppinger

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
#include <algorithm>

using namespace std;

// Data Item ----------/
// Default constructor
DataItem::DataItem(void)
{
	data = NULL;
}

// Default destructor
DataItem::~DataItem(void)
{
	cout << "Destroying Data Item" << endl;
}

/*
void DataItem::DestroyDataItem(DataItem* &dataItemPointer)
{
	if (dataItemPointer != nullptr)
	{
		delete dataItemPointer;
		dataItemPointer = nullptr;
	}
}
*/
void DataItem::DisplayItem()
{
	if (data != NULL)
	{
		cout << data << " ";
	}
	else
	{
		return;
	}
}
// end DataItem -------------------/

// TwoThreeFourNode -------/
TwoThreeFourNode::TwoThreeFourNode(void)
{
	dataItemArray[ORDER - 1] = nullptr;
	childArray[ORDER] = nullptr;
}

TwoThreeFourNode::~TwoThreeFourNode(void)
{
	// DestroyTwoThreeFourNode();
}

int TwoThreeFourNode::InsertItem(DataItem* inItem)
{
	numItems++;
	long newKey = inItem->data;
	
	// start on right, examine items, if item null, go left one cell.
	// if not null, get its key. if its bigger, shift it right.
	// insert new item. return index to new item. all items have been shifted,
	// insert new item.
	for (int i = ORDER - 2; i >= 0; i--)
	{
		if (dataItemArray[i] == nullptr)
		{
			continue;
		}
		else
		{
			long currentKey = dataItemArray[i]->data;
			if (currentKey > newKey)
			{
				// shift current key right
				dataItemArray[i + 1] = dataItemArray[i];
			}
			else
			{
				dataItemArray[i + 1] = inItem;
				// return index to inItem
				return i + 1;
			}
		} // end else not null
	} // end for
	// all items have been shifted, insert inItem
	dataItemArray[0] = inItem;

	// delete the dataItem pointer
	// delete inItem;

	return 0;
} // end InsertItem()

// removes largest item 
DataItem* TwoThreeFourNode::RemoveItem()
{
	// assumes node is not empty
	DataItem* temp = dataItemArray[numItems - 1];
	dataItemArray[numItems - 1] = nullptr;
	numItems--;

	return temp;
} // end RemoveItem()

// Connect child node to this node
void TwoThreeFourNode::ConnectChild(int childNum, TwoThreeFourNode* child)
{
	// test this
	childArray[childNum] = child;

	if (child != nullptr)
	{
		child->parent = this;
	}
} // end ConnectChild()

TwoThreeFourNode* TwoThreeFourNode::DisconnectChild(int childNum)
{
	TwoThreeFourNode* tempNode = childArray[childNum];
	childArray[childNum] = nullptr;
	
	return tempNode;
} // end DisconnectChild()

TwoThreeFourNode* TwoThreeFourNode::GetChild(int childNum)
{
	if (childArray[childNum] != nullptr)
	{
		return childArray[childNum];
	}
	else
	{
		return nullptr;
	}
} // end GetChild()

TwoThreeFourNode* TwoThreeFourNode::GetParent()
{
	// parent isn't currently pointing to anything need to fix.
	return parent;
} // end GetParent()


int TwoThreeFourNode::GetNumItems()
{
	return numItems;
} // end GetNumItems()

int TwoThreeFourNode::FindItem(long key)
{
	for (int i = 0; i <= ORDER - 1; i++)
	{
		if (dataItemArray[i] == nullptr)
		{
			// if dataItemArray[0] is nullptr, we are at a leaf and there will
			// not be a dataItemArray[1]
			break;
		}
		else if (dataItemArray[i]->data == key)
		{
			return dataItemArray[i]->data;
		}
	}

	return -1;
}

// Returns index of item being searched for
int TwoThreeFourNode::FindIndex(long key)
{
	for (int i = 0; i <= ORDER - 1; i++)
	{
		if (dataItemArray[i] == nullptr)
		{
			// if dataItemArray[0] is nullptr, we are at an empty leaf
			break;
		}
		else if (dataItemArray[i]->data == key)
		{
			return i;
		}
	}

	return -1;
}

void TwoThreeFourNode::DisplayNode()
{
	for (int i = 0; i < ORDER - 1; i++)
	{
		if (dataItemArray[i] != nullptr)
		{
			dataItemArray[i]->DisplayItem();
		}
	}
}

// NOTE: this can potentially return true when a node isn't connected...
bool TwoThreeFourNode::b_IsLeaf()
{
	return (childArray[0] == nullptr) ? true : false;
}

DataItem* TwoThreeFourNode::GetItem(int index)
{
	return dataItemArray[index];
}

bool TwoThreeFourNode::b_IsFull()
{
	return (numItems == ORDER - 1) ? true : false;
}

// ===============================================
// Tree234
// =======

Tree234::Tree234(void)
{
	root = NULL;
}

Tree234::~Tree234(void)
{
	cout << "Destroying tree." << endl;
	// DestroyTree();
}

// Returns the value if found, otherwise returns -1
// Could cause problems if the key value actually is -1
int Tree234::Find(long key)
{
	TwoThreeFourNode* current = root;
	int childNumber;
	
	while (true)
	{
		// if found
		if ((childNumber = current->FindItem(key)) != -1)
		{
			return childNumber;
		}
		// can't find it
		else if (current->b_IsLeaf())
		{
			return -1;
		}
		// search deeper
		else
		{
			current = GetNextChild(current, key);
		}
	} // end while
} // end Find()

void Tree234::Insert(long dataValue)
{
	TwoThreeFourNode* current;
	DataItem* newDataItem;
	newDataItem = new DataItem;
	newDataItem->data = dataValue;

	// in case root is empty,
	TwoThreeFourNode* newNode;
	newNode = new TwoThreeFourNode;

	bool iterate = true;

	if (IsEmpty())
	{
		root = newNode;
		root->InsertItem(newDataItem);
	}
	else
	{
		current = root;

		while (iterate)
		{
			// if node is full, split it
			if (current->b_IsFull())
			{
				// split
				Split(current);
				// back up one level
				current = current->GetParent();
				// search
				current = GetNextChild(current, dataValue);
				// NOTE: current gets nuked upon exiting this loop
			}
			// else if node is leaf, go insert
			else if (current->b_IsLeaf())
			{
				iterate = false;
				// break;
			}
			else
			{
				// else node is not full and not a leaf
				// go to next level
				current = GetNextChild(current, dataValue);
			}
		} // end while

		current->InsertItem(newDataItem);
	} // end else
	// delete tempDataItemPtr;
} // end Insert()

bool Tree234::IsEmpty()
{
	return (root == NULL);
} // end IsEmpty()

void Tree234::Split(TwoThreeFourNode* inNode)
{
	// assume node is full
	DataItem* itemB;
	DataItem* itemC;
	TwoThreeFourNode* parent;
	TwoThreeFourNode* child2;
	TwoThreeFourNode* child3;

	int itemIndex;

	// remove items from node
	itemC = inNode->RemoveItem();
	itemB = inNode->RemoveItem();
	// remove children
	child2 = inNode->DisconnectChild(2);
	child3 = inNode->DisconnectChild(3);

	// make new node
	//TwoThreeFourNode newRight;
	TwoThreeFourNode* newRightPtr = new TwoThreeFourNode;

	if (inNode == root)
	{
		// create new node and have root point to it
		root = new TwoThreeFourNode;
		// inNode->parent = root
		parent = root;
		root->ConnectChild(0, inNode);
	}
	else
	{
		parent = inNode->GetParent();
	}
	// put itemB into parent of node being split
	itemIndex = parent->InsertItem(itemB);
	int numParentItems = parent->GetNumItems();

	for (int i = numParentItems - 1; i > itemIndex; i--)
	{
		TwoThreeFourNode* temp = parent->DisconnectChild(i);
		parent->ConnectChild(i + 1, temp);
	}

	// connect newRight to parent
	parent->ConnectChild(itemIndex + 1, newRightPtr);

	// handle new right
	newRightPtr->InsertItem(itemC);
	newRightPtr->ConnectChild(0, child2);
	newRightPtr->ConnectChild(1, child3);
} // end Split()


TwoThreeFourNode* Tree234::GetNextChild(TwoThreeFourNode* inNode, long inValue)
{
	// assumes node is not empty and not a leaf
	int numItems = inNode->GetNumItems();
	int j;

	for (j = 0; j < numItems; j++)
	{
		if (inValue < inNode->GetItem(j)->data)
		{
			// less than so return left child
			return inNode->GetChild(j);
		}
	} // end for
	// greater so return right child
	return inNode->GetChild(j);
} // end GetNextChild()

void Tree234::DisplayPreOrder()
{
	if (root == nullptr)
		return;

	RecursivePreOrderTraversal(root, 0, 0);
	cout << endl;
}

void Tree234::DisplayInOrder()
{
	if (root == nullptr)
		return; 

	RecursiveInOrderTraversal(root, 0, 0);
	cout << endl;
}

void Tree234::DisplayPostOrder()
{
	if (root == nullptr)
		return;

	RecursivePostOrderTraversal(root, 0, 0);
	cout << endl;
}

// Recursive PreOrder Traversal
void Tree234::RecursivePreOrderTraversal(TwoThreeFourNode* inNode, int level, int childNumber)
{
	cout << "Level: " << level << " " << "Child: " << childNumber << " " << endl;
	inNode->DisplayNode();
	cout << endl;

	// recursive call for each child of this node
	int numItems = inNode->GetNumItems();
	for (int i = 0; i < numItems + 1; i++)
	{
		// if these pointers need to be deleted just let me know.
		TwoThreeFourNode* nextNode = inNode->GetChild(i);

		if (nextNode != nullptr)
		{
			RecursivePreOrderTraversal(nextNode, level + 1, i);
		}
		else
		{
			return;
		}
	}
} // end RecursivePreOrderTraversal()

void Tree234::RecursiveInOrderTraversal(TwoThreeFourNode* inNode, int level, int childNumber)
{
	
	if (inNode == nullptr)
		return;

	int numItems = inNode->GetNumItems();
	RecursiveInOrderTraversal(inNode->GetChild(0), level, childNumber);
	inNode->DisplayNode();
	for (int i = 1; i <= numItems; i++)
	{
		RecursiveInOrderTraversal(inNode->GetChild(i), level, childNumber);
	}

} // end RecursiveInOrderTraversal()

void Tree234::RecursivePostOrderTraversal(TwoThreeFourNode* inNode, int level, int childNumber)
{
	if (inNode == nullptr)
		return;

	int numItems = inNode->GetNumItems();
	for (int i = 0; i <= numItems; i++)
	{
		RecursivePostOrderTraversal(inNode->GetChild(i), level, childNumber);
	}

	inNode->DisplayNode();

} // end RecursivePostOrderTraversal()

int TwoThreeFourNode::FindKey(int key)
{
	int index = 0;
	while (index < numItems && dataItemArray[index]->data < key)
	{
		index++;
	}
	return index;
}

void TwoThreeFourNode::Remove(long key)
{
	int index = FindKey(key);

	// Key is in this node
	if (index < numItems && dataItemArray[index]->data == key)
	{
		if (b_IsLeaf())
		{
			RemoveFromLeaf(index);
		}
		else
		{
			RemoveFromNonLeaf(index);
		}
	}
	// Key is not in this node
	else
	{
		if (b_IsLeaf())
		{
			cout << "The Key " << key << " is not in the tree" << endl;
			return;
		}

		// Is the key present in the sub tree rooted with the last child of this node
		bool flag = ((index == numItems) ? true : false);

		// If the child where the key is supposed to exist has less than - keys
		// call fill.
		if (childArray[index]->numItems < ORDER - 2)
		{
			Fill(index);
		}
		
		// If the last child has been merged, it must have merged with the prev
		// child, so recursively remove previous child. Otherwise recursively
		// remove index'th child which now has at least 2 keys
		if (flag && index > numItems)
		{
			childArray[index - 1]->Remove(key);
		}
		else
		{
			childArray[index]->Remove(key);
		}

		return;
	}
}

// -
void TwoThreeFourNode::RemoveFromLeaf(int index)
{
	delete(dataItemArray[index]);
	dataItemArray[index] = nullptr;
	// shift items after index backwards one to remove the item
	for (int i = index + 1; i < numItems - 1; i++)
	{
		dataItemArray[i - 1] = dataItemArray[i];
	}

	numItems--;

	return;
}

void TwoThreeFourNode::RemoveFromNonLeaf(int index)
{

	// cases:
	// 2a if elements left child has at least two keys, replace the element with
	// its predecessor.
	// 2b if both children only have 1 key, merge the right into the left and
	// delete key from the left.

	// 3 If key is not in internal node, find the key. To ensure all of the nodes
	// descended through have at least two keys, do one of the following before
	// descending into a node. Eventually case 1 or 2 will be arrived at
	// a) if the child node has only 1 key and has a sibling with at least 2 keys,
	// move a key from the sibling into the parent.
	/*
		b) if both the child node and its immediate sibling have only 1 key each,
		merge the child node with one of the siblings and move an element down 
		from the parent into the merged node. This key must be the middle key
		in the node. Free the node whose keys were merged into another node
	*/

	int key = dataItemArray[index]->data;

	// If the child that precedes key (childArray[index]) has at least 2 keys
	// find the predecessor of key in the subtree rooted at childArray[index]
	// Replace key by predecessor, recursively delete predecessor in childArray[index]
	if (childArray[index]->numItems >= ORDER - 2)
	{
		long predecessor = GetPredecessor(index);
		dataItemArray[index]->data = predecessor;
		childArray[index]->Remove(predecessor);
	}

	// If the leftChild has less than 2 keys, examine the rightChild.
	// If rightChild has at least 2 keys, find the successor and replace
	// k, recursively delete successor.
	else if(childArray[index + 1]->numItems >= ORDER - 2)
	{
		long successor = GetSuccessor(index);
		dataItemArray[index]->data = successor;
		childArray[index + 1]->Remove(successor);
	}

	// If both child and right child only have 1 key, merge key and 
	// right child into child. Remove key from child after merge.
	else
	{
		Merge(index);
		childArray[index]->Remove(key);
	}

	return;
}

int TwoThreeFourNode::GetPredecessor(int index)
{
	TwoThreeFourNode* current = childArray[index];

	while (!current->b_IsLeaf())
	{
		current = current->childArray[current->numItems];
	}

	// return the last key of the leaf
	return current->dataItemArray[numItems - 1]->data;
}

int TwoThreeFourNode::GetSuccessor(int index)
{
	TwoThreeFourNode* current = childArray[index + 1];
	while (!current->b_IsLeaf())
	{
		current = current->childArray[0];
	}

	// return first key of the leaf
	return current->dataItemArray[0]->data;
}

// Borrows a key from left sibling and inserts it into childArray[index]
void TwoThreeFourNode::BorrowFromPrevious(int index)
{
	TwoThreeFourNode* child = childArray[index];
	TwoThreeFourNode* leftSibling = childArray[index - 1];

	// Last key from leftSibling goes up to parent and key[index-1] from parent
	// is inserted as the first key in child[index]. Sibling loses one key and
	// child gains one key.

	// Move all keys in childArray[index] one step ahead
	for (int i = child->numItems- 1; i >= 0; i--)
	{
		child->dataItemArray[i + 1] = dataItemArray[i];
	}

	// Setting child's first key equal to dataItemArray[index-1] from the current node
	child->dataItemArray[0] = dataItemArray[index - 1];

	// Moving sibling's last child as childArray[index]'s first child
	if (!b_IsLeaf())
	{
		child->childArray[0] = leftSibling->childArray[numItems];
	}

	// Move key from sibling to the parent
	dataItemArray[index - 1] = leftSibling->dataItemArray[leftSibling->numItems- 1];

	child->numItems += 1;
	leftSibling->numItems -= 1;
}

void TwoThreeFourNode::BorrowFromNext(int index)
{
	TwoThreeFourNode* child = childArray[index];
	TwoThreeFourNode* rightSibling = childArray[index + 1];

	// dataItemArray[index] is inserted as the last key in dataItemArray[index]
	child->dataItemArray[(child->numItems) + 1] = dataItemArray[index];

	// rightSibling's first child is inserted as the last child into childArray[index]
	if (!child->b_IsLeaf()) 
	{
		child->childArray[(child->numItems)+1] = rightSibling->childArray[0];
	}

	// the first key from sibling is inserted into dataItemArray[index]
	dataItemArray[index] = rightSibling->dataItemArray[0];

	// Move all keys in sibling one step behind
	for (int i = 1; i < rightSibling->numItems; i++)
	{
		rightSibling->dataItemArray[i - 1] = rightSibling->dataItemArray[i];
	}

	// remove the last key in the array so there are no duplicates
	rightSibling->RemoveItem();


	// Move the child pointers one step behind
	if (!rightSibling->b_IsLeaf())
	{
		for (int i = 1; i <= rightSibling->numItems; i++)
		{
			rightSibling->childArray[i - 1] = rightSibling->childArray[i];
		}
	}

	// Increase key counts
	child->numItems++;

	return;
}

// Merge childArray[index] with childArray[index+1], then free 
// childArray[index+1] after merging
void TwoThreeFourNode::Merge(int index)
{
	TwoThreeFourNode* child = childArray[index];
	TwoThreeFourNode* rightSibling = childArray[index + 1];

	// Pull key from current node and insert it into the numItems-th position
	child->dataItemArray[child->numItems] = dataItemArray[index];

	// Copy the keys from sibling to child
	// NOTE: this is kind of a dirty hack since keys aren't being moved towards array 
	// position 0. Could be unnecessary but it's safer, still need to test more cases.
	// Since n will not be larger than 3 this nested for loop is acceptable. However, if 
	// this were a B tree like the one CouchDB uses, n could upwards of 1 Million.
	for (int i = 0; i < ORDER - 1; i++)
	{
		if (rightSibling->dataItemArray[i] != nullptr)
		{
			for (int j = 0; j < ORDER - 1; j++)
			{
				if (child->dataItemArray[j] == nullptr)
				{
					child->dataItemArray[j] = rightSibling->dataItemArray[i];
				}
			} // end inner for
		} // end if
	} // end outter for
	
	// Copy the child pointers
	if (!child->b_IsLeaf())
	{
		for (int i = 0; i <= rightSibling->numItems; i++)
		{
			child->childArray[i + numItems] = rightSibling->childArray[i];
		}
	}

	// Move all keys after index in the current node one step before to fill gap
	for (int i = index + 1; i < numItems; i++)
	{
		dataItemArray[i - 1] = dataItemArray[i];
		dataItemArray[i] = nullptr;
	}

	// Move child pointers after index+1 in current node one step before
	for (int i = index + 2; i <= numItems; i++)
	{
		childArray[i - 1] = childArray[i];
		childArray[i] = nullptr;
	}



	child->numItems += rightSibling->numItems+1;
	numItems--;

	rightSibling = nullptr;
	delete(rightSibling);

	return;
}

// Fills child with keys by borrowing from previous or next
void TwoThreeFourNode::Fill(int index)
{
	// If previous child has more than 2 keys, borrow a key
	if (index != 0 && childArray[index - 1]->numItems >= ORDER - 2)
	{
		BorrowFromPrevious(index);
	}

	// If the next child has more than 2 keys borrow a key
	else if (index != numItems && childArray[index + 1]->numItems >= ORDER - 2)
	{
		BorrowFromNext(index);
	}

	// Merge child with its sibling, if last child merge with previous or next
	// sibling
	else
	{
		if (index != numItems)
			Merge(index);
		else
			Merge(index - 1);
	}

	return;
}

void Tree234::RemoveFromTree(long key)
{
	if (!root)
	{
		cout << "tree is empty." << endl;
		return;
	}

	// Call remove function for root
	root->Remove(key);

	// If root node has 0 keys, make its first child as new root, otherwise set root 
	// as NULL
	if (root->GetNumItems() == 0)
	{
		TwoThreeFourNode* temp = root;
		if (root->b_IsLeaf())
		{
			root = NULL;
		}
		else
		{
			root = root->GetChild(0);
		}

		// Free the old root
		delete temp;
	}

	return;
}