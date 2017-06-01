// 2-3-4_B_Tree.h
// Brian Keppinger

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
	// void DestroyDI();

private:
	// void DestroyDataItem(DataItem* &dataItemPointer);
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
	int FindIndex(long key);
	void DisplayNode();
	bool b_IsLeaf();
	bool b_IsFull();

	void Remove(long key);
	void RemoveFromLeaf(int index);
	void RemoveFromNonLeaf(int index);
	void BorrowFromPrevious(int index);
	void BorrowFromNext(int index);
	void Merge(int index);
	void Fill(int index);
	int GetPredecessor(int index);
	int GetSuccessor(int index);
	int FindKey(int key);

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
	// Default constructor
	Tree234(void);
	// Default destructor
	~Tree234(void);

	int Find(long key);
	void Insert(long dataValue);
	void Split(TwoThreeFourNode* inNode);
	TwoThreeFourNode* GetNextChild(TwoThreeFourNode* inNode, long inValue);
	bool IsEmpty();
	void DisplayPreOrder();
	void DisplayInOrder();
	void DisplayPostOrder();

	void RemoveFromTree(long key);

private:

	// Recursive PreOrder Traversal
	void RecursivePreOrderTraversal(TwoThreeFourNode* inNode, int level, int childNumber);
	void RecursiveInOrderTraversal(TwoThreeFourNode* inNode, int level, int childNumber);
	void RecursivePostOrderTraversal(TwoThreeFourNode* inNode, int level, int childNumber);

	TwoThreeFourNode* root;
};
