
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

// Forehead decleration.
void TestList();
int main()
{
	TestList();
	return 0;
}

// Data structure
template<class T>
struct DataStruct
{
	typedef T ElementType;
	typedef DataStruct* ptrDataStruct;
	typedef ptrDataStruct Position;

	ElementType ele;
	Position next;
};

typedef DataStruct<int> Node;
typedef Node* List;
typedef int ElementType;
typedef Node* Position;
typedef size_t ListSize;

List CreateList()
{
	Node* header = new Node();
	header->ele = 0;
	header->next = NULL;
	return header;
}

// Forehead Declaration.
Position Tail(List list);
int PushBack(ElementType ele, List list);
int Insert(ElementType ele, Position pos, List list);
int Insert(ElementType ele, ListSize pos, List list);
List MakeEmpty(List list);
bool empty(List list);
bool IsTail(Position pos, List list);
Position Find(ElementType ele, List list);
bool DeleteFirstMatch(ElementType ele, List list);
void DeleteAllMatch(ElementType ele, List list);
Position FindPrevious(ElementType ele, List list);
void DestoryList(List list);
Position Advance(Position pos, List list);
void printList(List list);

#define IS_NULL(list, ret)\
	if(list == NULL) return ret;

void TestList()
{
	List list = CreateList();
	cout << "List Empty: " << boolalpha << empty(list) << endl;
	PushBack(8, list);
	printList(list);
	PushBack(7, list);
	PushBack(5, list);
	PushBack(1, list);
	PushBack(7, list);
	printList(list);
	
	cout << "List Empty: " << empty(list) << endl;
	PushBack(7, list);
	printList(list);
	DeleteFirstMatch(7, list);
	printList(list);
	DeleteAllMatch(7, list);
	printList(list);
	Insert(3, 2, list);
	printList(list);
	Position pos = Find(3, list);
	Insert(3, pos, list);
	printList(list);
	
	DestoryList(list);
	printList(list);
	
}

Position Tail(List list)
{
	IS_NULL(list, NULL)
	Position tail = list;
	while(tail->next != NULL) tail = tail->next;
	return tail;
}

int PushBack(ElementType ele, List list)
{
	Position tail = Tail(list);
	IS_NULL(tail, -1)
	Node* node = new Node();
	node->ele = ele;
	node->next = NULL;
	tail->next = node;
	return 0;
}

int Insert(ElementType ele, Position pos, List list)
{
	IS_NULL(list, -1)
	if(Tail(list) != Tail(pos)) return -1;
	
	Node* node = new Node();
	node->ele = ele;
	node->next = pos->next;
	pos->next = node;
	return 0;
}

int Insert(ElementType ele, ListSize pos, List list)
{
	while(list != NULL && pos-- != 0) list = list->next;
	
	IS_NULL(list, -1)
	
	Node* node = new Node();
	node->ele = ele;
	node->next = list->next;
	list->next = node;
	return 0;
}

List MakeEmpty(List list)
{
	IS_NULL(list, NULL)
	List l = list;
	while(l->next != NULL) 
	{
		List newList = l->next;
		delete l;
		l = newList;
	}
}

bool empty(List list)
{
	// we should throw an exception here.
	IS_NULL(list, true)
	return list->next == NULL;
}

bool IsTail(Position p, List list)
{
	Node* node = Tail(list);
	IS_NULL(node, false)
	if(p == node)
	{
		return true;
	}
	
	return false;
}

Position Find(ElementType ele, List list)
{
	IS_NULL(list, NULL)
	
	Node* node = list->next;
	while(node != NULL) 
	{
		if(node->ele == ele)
		{
			return node;
		}
		node = node->next;
	}
	return NULL;
}

bool DeleteFirstMatch(ElementType ele, List list)
{
	IS_NULL(list, false)
	Node* previous = list;
	Node* node = list->next;
	while(node != NULL) 
	{
		if(node->ele == ele)
		{
			previous->next = node->next;
			delete node;
			return true;
		}
		node = node->next;
		previous = previous->next;
	}
	return false;
}

void DeleteAllMatch(ElementType ele, List list)
{
	if(list == NULL) return;
	Node* previous = list;
	Node* node = list->next;
	while(node != NULL) 
	{
		if(node->ele == ele)
		{
			previous->next = node->next;
			delete node;
			node = previous->next;
			continue;
		}
		node = node->next;
		previous = previous->next;
	}
}

Position FindPrevious(ElementType ele, List list)
{
	IS_NULL(list, NULL)
	Node* node = list;
	while(node->next != NULL) 
	{
		if(node->next->ele == ele)
		{
			return node;
		}
		node = node->next;
	}
	return NULL;
}

void DestoryList(List list)
{
	if(list == NULL) return;
	List newList = list->next;
	while(list != NULL) 
	{
		delete list;
		list = newList;
	}
}

Position Advance(Position pos, List list)
{
	if(pos == list)
	{
		return NULL;
	}
	while(list != NULL)
	{
		if(list->next == pos)
		{
			return list;
		}
		list = list->next;
	}
	return NULL;
}

void printList(List list)
{ 
	if(list == NULL) return;
	List l = list->next;
	while(l != NULL) 
	{
		cout << l->ele << "  ";
		l = l->next;
	}
	cout << endl;
}
