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
	// Default constructor
	Node(void);

	// Default destructor
	~Node(void);

	void ConnectChild(int childNum, Node child);
	Node* DisconnectChild(int childNum);
	Node* GetChild(int childNum);
	Node* GetParent();
	int GetNumItems();

	int InsertItem(DataItem newItem);
	
	Node *parent;




private:
	static const int ORDER = 4;
	int numItems;
	Node* parent;

	DataItem dataItemArray[ORDER - 1];
	Node* childArray[ORDER];

};