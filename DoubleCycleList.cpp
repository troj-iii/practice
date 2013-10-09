
#include <iostream>
#include <iomanip>

using namespace std;

// Forehead declaration.
void TestDoubleCycleList();

int main()
{
	TestDoubleCycleList();
	return 0;
}

template <class T>
struct DoubleCycleListNode
{
	typedef T ElementType;
	typedef size_t ListSize;
	typedef DoubleCycleListNode Node;
	typedef DoubleCycleListNode* ptrNode;
	typedef DoubleCycleListNode* Position;
	
	ElementType ele;
	Position previous;
	Position next;
};

typedef int ElementType;
typedef size_t ListSize;
typedef DoubleCycleListNode<ElementType> Node;
typedef Node* DoubleList;
typedef Node* Position;
typedef DoubleList DoubleCycleList;
typedef DoubleCycleList List;


// Forehead declaration.
List CreateList();
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
void TestDoubleCycleList()
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

List CreateList()
{
	Node* node = new Node();
	node->ele = 0;
	node->previous = node;
	node->next = node;
	return node;
}

int PushBack(ElementType ele, List list)
{
	IS_NULL(list, -1);
	
	Node* node = new Node();
	node->ele = ele;
	Node* head = list;
	if(head->next == head)
	{
		head->next = node;
		head->previous = node;
		node->next = head;
		node->previous = head;
	}
	else
	{
		head->previous->next = node;
		node->next = head;
		node->previous = head->previous;
		head->previous = node;
	}
	return 0;
}

int Insert(ElementType ele, Position pos, List list)
{
	IS_NULL(list, -1);
	
	if(pos == NULL)
	{
		PushBack(ele, list);
	}
	else
	{
		Node* node = new Node();
		node->ele = ele;
		node->next = pos->next;
		node->previous = pos;
		pos->next->previous = node;
		pos->next = node;
	}
	return 0;
}

Position Tail(List list)
{
	IS_NULL(list, NULL);
	
	return list->previous;
}

int Insert(ElementType ele, ListSize pos, List list)
{
	IS_NULL(list, -1);
	
	Node* head = list;
	ListSize i = pos;
	for(; pos != 0 && head->next != list; head = head->next, --i);
	if(head->next == list && i != 0)
	{
		return -1;
	}
	
	Node* node = new Node();
	node->ele = ele;
	node->next = head->next;
	node->previous = head;
	head->next->previous = node;
	head->next = node;
	return 0;
}

List MakeEmpty(List list)
{
	Node* head = list;
	while(head != NULL && head->next != list)
	{
		Node* newList = head->next;
		head->previous->next = newList;
		newList->previous = head->previous;
		delete head;
		list = newList;
	}
	return list;
}

bool empty(List list)
{
	return list->next == list;
}

bool IsTail(Position pos, List list)
{
	return pos == list->previous;
}

Position Find(ElementType ele, List list)
{
	IS_NULL(list, NULL)
	
	for(Node* head = list->next; head != list; head = head->next)
	{
		if(head->ele == ele)
		{
			return head;
		}
	}
	
	return NULL;
}

bool DeleteFirstMatch(ElementType ele, List list)
{
	Node* node = Find(ele, list);
	IS_NULL(node, false)
	node->next->previous = node->previous;
	node->previous->next = node->next;
	delete node;
	return true;
}

void DeleteAllMatch(ElementType ele, List list)
{
	if(list == NULL) return;
	
	for(Node* head = list->next; head != list;)
	{
		if(head->ele == ele)
		{
			head->next->previous = head->previous;
			head->previous->next = head->next;
			Node* node = head->next;
			delete head;
			head = node;
		}
		else
		{
			head = head->next;
		}
	}
	return;
}

Position FindPrevious(ElementType ele, List list)
{
	Position pos = Find(ele, list);
	IS_NULL(pos, NULL)
	
	return pos->previous;
}

void DestoryList(List list)
{
	Node* head = list;
	Node* node = list->next;
	while(node != head)
	{
		Node* next = node->next;
		delete node;
		node = next;
	}
	
	head->previous = head;
	head->next = head;
}

Position Advance(Position pos, List list)
{
	IS_NULL(pos, NULL)
	IS_NULL(list, NULL)
	
	return pos->previous;
}

void printList(List list)
{
	if(list == NULL) return;
	List l = list->next;
	while(l != list) 
	{
		cout << l->ele << "  ";
		l = l->next;
	}
	cout << endl;
}











