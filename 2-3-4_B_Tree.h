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
	
	TwoThreeFourNode* DisconnectChild(int childNum);
	
	TwoThreeFourNode* GetChild(int childNum);
	TwoThreeFourNode* GetParent();

	int InsertItem(DataItem* newItem);
	DataItem* RemoveItem();
	int GetNumItems();
	int FindItem(long key);
	void DisplayNode();
	bool b_IsLeaf();
	bool b_IsFull();

	DataItem* GetItem(int index);

	
private:
	static const int ORDER = 4;
	int numItems;
	TwoThreeFourNode* parent;

	DataItem* dataItemArray[ORDER - 1];
	TwoThreeFourNode* childArray[ORDER];

};

class Tree234
{
public:
	// TODO: implement Delete(). Inorder, PreOrder, and
	// PostOrder traversals recursively.
	// Default constructor
	Tree234(void);
	// Default destructor
	~Tree234(void);

	int Find(long key);
	void Insert(long dataValue);
	void Split(TwoThreeFourNode* inNode);
	TwoThreeFourNode* GetNextChild(TwoThreeFourNode* inNode, long inValue);
	bool IsEmpty();
	void DisplayTree();
	void DeleteItem(long key);


private:

	void RecursiveDisplayTree(TwoThreeFourNode* inNode, int level, int childNumber);
	DataItem* Delete(TwoThreeFourNode* rootPointer, long key);

	TwoThreeFourNode* root;
};
