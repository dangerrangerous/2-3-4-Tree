

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
	cout << "Data: " << data << " ";
}
// end DataItem -------------------/

// Node -------/
Node::Node(void)
{
	//
}

Node::~Node(void)
{
	// DestroyNode();
}

int Node::InsertItem(DataItem inItem)
{
	numItems++;
	long newKey = inItem.data;
}