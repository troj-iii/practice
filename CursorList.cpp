

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <assert.h>

#define IS_NULL(p, ret)\
    if(p == NULL) return ret;
using namespace std;

// Forehead declaration.
void TestCursorList();

int main()
{
    TestCursorList();
    return 0;
}


// Forehead declaration.
typedef size_t Position;
typedef size_t MemSize;

template<class T>
struct _tNode
{
    typedef T ElementType;
    ElementType ele;
    Position next;
};

typedef int ElementType;
typedef _tNode<ElementType> Node;
typedef Position List;
typedef Node GlobalList;
const MemSize MEM_SIZE = 1000;
static MemSize g_memSize = MEM_SIZE;
static GlobalList g_globalList[MEM_SIZE];

void initGlobalMem(/*MemSize nSize*/);
void DestoryGlobalMem();
//
void FreeCursor(Position p);
Position AllocCursor();

List CreateList();
void PushBack(ElementType ele, List list);
void printList(List list);
List MakeEmpty(List l);
bool IsEmpty(const List l);
bool IsLast(ElementType ele, const List l);
Position Find(ElementType ele, const List l);
void Delete(ElementType ele, List l);
Position FindPrevious(ElementType ele, const List l);
void Insert(ElementType ele, Position p, List l);
void DeleteList(List l);
Position Header(const List l);
Position First(const List l);
Position Advance(const Position p);
ElementType Retrieve(const Position p);


void TestCursorList()
{
    initGlobalMem();
    List list = CreateList();
    cout << "List Empty: " << boolalpha << IsEmpty(list) << endl;
    PushBack(8, list);
    printList(list);
    PushBack(7, list);
    PushBack(5, list);
    PushBack(1, list);
    PushBack(7, list);
    printList(list);

    cout << "List Empty: " << IsEmpty(list) << endl;
    PushBack(7, list);
    printList(list);
    //DeleteFirstMatch(7, list);
    //printList(list);
    //DeleteAllMatch(7, list);
    //printList(list);
    Insert(3, 2, list);
    printList(list);
    Position pos = Find(3, list);
    Insert(3, pos, list);
    printList(list);

    MakeEmpty(list);
    printList(list);
}
List CreateList()
{
    Position p = AllocCursor();
    g_globalList[p].ele = 0;
    g_globalList[p].next = 0;
    return p;
}
void PushBack(ElementType ele, List list)
{
    Position p = AllocCursor();
    g_globalList[p].next = g_globalList[list].next;
    g_globalList[p].ele = ele;
    g_globalList[list].next = p;
}
void printList(List list)
{
    assert(list != 0);
    for(Position i = g_globalList[list].next; i != 0; i = g_globalList[i].next)
    {
        cout << "  " << g_globalList[i].ele;
    }
    cout << endl;
}
List MakeEmpty(List l)
{
    if(l == 0) return 0;

    List delList = g_globalList[l].next;
    List lastList = delList;
    for(Position i = lastList; i != 0; i = lastList)
    {
        lastList = g_globalList[i].next;
        FreeCursor(i);
    }
    g_globalList[l].next = 0;
    return l;
}
bool IsEmpty(const List l)
{
    return g_globalList[l].next == 0;
}
bool IsLast(ElementType ele, const List l)
{
    Position p = Find(ele, l);
    return g_globalList[p].next == 0;
}
Position Find(ElementType ele, const List l)
{
    assert( l != 0);
    
    for(Position i = g_globalList[l].next; i != 0; i = g_globalList[i].next)
    {
        if(ele == g_globalList[i].ele)
        {
            return i;
        }
    }
    return 0;
}
void Delete(ElementType ele, List l)
{
    Position p = FindPrevious(ele, l);
    g_globalList[p].next = g_globalList[g_globalList[p].next].next;
    FreeCursor(p);
}
Position FindPrevious(ElementType ele, const List l)
{
    assert(l != 0);

    Position ret;
    for(Position i = g_globalList[l].next; i != 0; i = g_globalList[i].next)
    {
        if(ele == g_globalList[i].ele)
        {
            return ret;
        }
        ret = i;
    }
    return 0;
}
void Insert(ElementType ele, Position p, List l)
{
    assert(l);
    assert(p);

    Position elePos = AllocCursor();
    g_globalList[elePos].next = g_globalList[p].next;
    g_globalList[elePos].ele = ele;
    g_globalList[p].next = elePos;
}
void DeleteList(List l)
{
    Position p = l;
    while(p != 0)
    {
        Position tmp = g_globalList[p].next;
        FreeCursor(p);
        p = tmp;
    }
}
Position Header(const List l)
{
    return l;
}
Position First(const List l)
{
    return g_globalList[l].next;
}
Position Advance(const Position p)
{
    return g_globalList[p].next;
}
ElementType Retrieve(const Position p)
{
    return g_globalList[p].ele;
}

void initGlobalMem(/*MemSize nSize*/)
{
    //g_memSize = nSize;
    //g_globalList = (GlobalList)malloc(nSize*sizeof(Node));
    //::memset(g_GlobalList, 0, g_memSize*sizeof(Node));
    for(size_t i = 0; i < g_memSize; ++i)
    {
        g_globalList[i].next = i+1;
    }
    g_globalList[g_memSize-1].next = 0;
    //return g_globalList;
}
//
//void DestoryGlobalMem()
//{
//    free(g_GlobalList);
//}

void FreeCursor(Position p)
{
    assert(p < g_memSize);
    g_globalList[p].next = g_globalList[0].next;
    g_globalList[0].next = p;
}

Position AllocCursor()
{
    if(g_globalList[0].next == 0)
    {
        return 0;
    }
    Position ret = g_globalList[0].next;
    g_globalList[0].next = g_globalList[g_globalList[0].next].next;
    return ret;
}