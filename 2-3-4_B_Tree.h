#pragma once


class DataItem
{
public:
	// should the data be private?
	long data;

	// prev

	// next


	// Default constructor
	DataItem(void);

	// Default destructor
	~DataItem(void);

	void DisplayItem();
};

class TwoThreeFourNode
{
public:
	// Default constructor
	TwoThreeFourNode(void);

	// Default destructor
	~TwoThreeFourNode(void);

	
	void ConnectChild(int childNum, TwoThreeFourNode* child);
	
	TwoThreeFourNode DisconnectChild(int childNum);
	
	TwoThreeFourNode GetChild(int childNum);
	TwoThreeFourNode GetParent();

	int InsertItem(DataItem* newItem);
	DataItem RemoveItem();
	int GetNumItems();
	int FindItem(long key);
	void DisplayNode();
	bool b_IsLeaf();
	bool b_IsFull();

	DataItem GetItem(int index);

	
private:
	static const int ORDER = 4;
	int numItems;
	TwoThreeFourNode* parent;

	DataItem* dataItemArray[ORDER - 1];
	TwoThreeFourNode* childArray[ORDER];

};