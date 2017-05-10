#pragma once


class DataItem
{
public:
	// should the data be private?
	long data;
	// Default constructor
	DataItem(void);

	// Default destructor
	~DataItem(void);

	void DisplayItem();
};

class Node
{
public:
	void ConnectChild(int childNum, Node child);
	Node* DisconnectChild(int childNum);
	Node* GetChild(int childNum);
	Node* GetParent();
	int GetNumItems();

	int insertItem(DataItem newItem);





private:
	const int ORDER = 4;
	int numItems;
	Node* parent;
	// TODO: clean up java syntax
	// Node* childArray[] = new Node[ORDER];
	// DataItem dataItemArray[] = new DataItem[ORDER - 1];


};