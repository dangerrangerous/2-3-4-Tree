

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
}

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

// smelly syntax.
// NOTE: This clears the child array of the node but the disconnected node still
// contains a pointer to parent... which we may want to remove.
TwoThreeFourNode TwoThreeFourNode::DisconnectChild(int childNum)
{
	TwoThreeFourNode tempNode = *childArray[childNum];
	childArray[childNum] = nullptr;
	
	return tempNode;
}

TwoThreeFourNode* TwoThreeFourNode::GetChild(int childNum)
{
	if (childArray[childNum] != nullptr)
	{
		return childArray[childNum];
	}
	else
	{
		cout << "child is null" << endl;
		// return something
	}
}

TwoThreeFourNode* TwoThreeFourNode::GetParent()
{
	// parent isn't currently pointing to anything need to fix.
	return parent;
}


int TwoThreeFourNode::GetNumItems()
{
	//  testing
	cout << "GetNumItems() returned " << numItems << endl;

	return numItems;
}

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

DataItem TwoThreeFourNode::GetItem(int index)
{
	return *dataItemArray[index];
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
	root = new TwoThreeFourNode;
}

Tree234::~Tree234(void)
{
	cout << "Destroying tree." << endl;
	// DestroyTree();
}

int Tree234::Find(long key)
{
	TwoThreeFourNode* current = root;
	int childNumber;
	
	while (true)
	{
		// if found
		if (childNumber = current->FindItem(key) != -1)
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
	TwoThreeFourNode* current = root;
	DataItem tempDataItem; 
	tempDataItem.data = dataValue;
	DataItem* tempDataItemPtr = &tempDataItem;


	while (true)
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
		}
		// else if node is leaf, go insert
		else if (current->b_IsLeaf())
		{
			break;
		}
		else
		{
			// else node is not full and not a leaf
			// go to next level
			current = GetNextChild(current, dataValue);
		}
		
		current->InsertItem(tempDataItemPtr);
	}
} // end Insert()

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
	child2 = &inNode->DisconnectChild(2);
	child3 = &inNode->DisconnectChild(3);

	// make new node
	TwoThreeFourNode newRight;
	TwoThreeFourNode* newRightPtr = &newRight;

	if (inNode == root)
	{
		// create new node and have root point to it
		root = new TwoThreeFourNode;
		parent = root;
		root->ConnectChild(0, inNode);
	}
	else
	{
		parent = inNode->GetParent();
	}

	itemIndex = parent->InsertItem(itemB);
	int numParentItems = parent->GetNumItems();

	for (int i = numParentItems - 1; i > itemIndex; i++)
	{
		TwoThreeFourNode* temp = &parent->DisconnectChild(i);
		parent->ConnectChild(i + 1, temp);
	}

	// connect newRight to parent
	parent->ConnectChild(itemIndex + 1, newRightPtr);

	// handle new right
	newRight.InsertItem(itemC);
	newRight.ConnectChild(0, child2);
	newRight.ConnectChild(1, child3);
} // end Split()


TwoThreeFourNode* Tree234::GetNextChild(TwoThreeFourNode* inNode, long inValue)
{
	// assumes node is not empty and not a leaf
	int numItems = inNode->GetNumItems();

	for (int j = 0; j < numItems; j++)
	{
		if (inValue < inNode->GetItem(j).data)
		{
			return inNode->GetChild(j);
		}
	}
} // end GetNextChild()


