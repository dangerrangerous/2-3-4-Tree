

#include "stdafx.h"
#include "2-3-4_B_Tree.h"
#include <iostream>

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
	// DestroyDataItem();
}

void DataItem::DisplayItem()
{
	cout << data << " ";
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
	for (int i = 0; i < numItems; i++)
	{
		dataItemArray[i]->DisplayItem();
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

void Tree234::DisplayTree()
{
	RecursiveDisplayTree(root, 0, 0);
}

void Tree234::RecursiveDisplayTree(TwoThreeFourNode* inNode, int level, int childNumber)
{
	cout << "Level: " << level << " " << "Child: " << childNumber << " " << endl;
	inNode->DisplayNode();
	cout << endl;

	// recursive call for each child of this node
	int numItems = inNode->GetNumItems();
	for (int i = 0; i < numItems + 1; i++)
	{
		TwoThreeFourNode* nextNode = inNode->GetChild(i);

		if (nextNode != nullptr)
		{
			RecursiveDisplayTree(nextNode, level + 1, i);
		}
		else
		{
			return;
		}
	}
} // end RecursiveDisplayTree()

void Tree234::DeleteItem(long key)
{
	Delete(root, key);
} // end DeleteItem()

/*
DataItem* Tree234::Delete(TwoThreeFourNode* rootPointer, long key)
{
	TwoThreeFourNode* current = rootPointer;

	bool keyIsInTree;
	// Handle 3 cases.

	// Case 1: Item is in leaf and there are at least 2 keys in the node
	// Find the node and index of the key

	// check that key is in the tree
	if (Find(key) != -1)
	{
		keyIsInTree = true;
	}
	else
	{
		keyIsInTree = false;
	}

	int index = current->FindIndex(key);

	// Key is in this node
	if (index < 3 && current->dataItemArray[index]->data == key)
	{

	}
	// temp for test
	return 0;
}
*/

void TwoThreeFourNode::Remove(long key)
{
	int index = FindIndex(key);

	// Key is in this node
	if (index < ORDER - 1 && dataItemArray[index]->data == key)
	{
		if (b_IsLeaf)
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
		if (b_IsLeaf)
		{
			cout << "The Key " << key << " is not in the tree" << endl;
			return;
		}

		// stuff goes here

	}
}

// -
void TwoThreeFourNode::RemoveFromLeaf(int index)
{
	// shift items after index backwards one to remove the item
	for (int i = index + 1; i < ORDER - 1; i++)
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



}
// Merge()

int TwoThreeFourNode::GetPredecessor(int index)
{
	TwoThreeFourNode* current = childArray[index];

	while (!current->b_IsLeaf())
	{
		current = current->childArray[current->numItems];

		// return the last key of the leaf
		return current->dataItemArray[numItems- 1]->data;
	}
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

}