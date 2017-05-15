

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

TwoThreeFourNode TwoThreeFourNode::GetChild(int childNum)
{
	if (childArray[childNum] != nullptr)
	{
		return *childArray[childNum];
	}
	else
	{
		cout << "child is null" << endl;
		
	}
}

TwoThreeFourNode TwoThreeFourNode::GetParent()
{
	// parent isn't currently pointing to anything need to fix.
	return *parent;
}


int TwoThreeFourNode::GetNumItems()
{
	//  testing
	cout << "GetNumItems() returned " << numItems << endl;

	return numItems;
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