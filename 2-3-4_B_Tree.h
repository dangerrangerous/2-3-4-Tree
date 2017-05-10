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

	/*
	void ConnectChild(int childNum, TwoThreeFourNode child);
	TwoThreeFourNode* DisconnectChild(int childNum);
	TwoThreeFourNode* GetChild(int childNum);
	TwoThreeFourNode* GetParent();
	int GetNumItems();
	*/
	int InsertItem(DataItem* newItem);
	void DisplayNode();
	
private:
	static const int ORDER = 4;
	int numItems;
	TwoThreeFourNode* parent;

	DataItem* dataItemArray[ORDER - 1];
	TwoThreeFourNode* childArray[ORDER];

};