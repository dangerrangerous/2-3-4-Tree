

#include "stdafx.h"
#include "2-3-4_B_Tree.h"
#include <iostream>

// DataItem
using namespace std;

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
