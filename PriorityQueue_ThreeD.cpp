#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

//Forehead Declaration.
void TestPriorityQueueArray();

int main()
{
    TestPriorityQueueArray();
    return 0;
}

// Type define

typedef size_t SizeType;
typedef int ElementType;
typedef ElementType* PriorityQueue;

static SizeType g_capcity = 0;
static SizeType g_size = 0;
static PriorityQueue g_queue;
const SizeType Default_Elements = 12;

PriorityQueue Initialize(SizeType MaxElements = Default_Elements);
void Destroy(PriorityQueue q);
void MakeEmpty(PriorityQueue q);
void Insert(ElementType ele, PriorityQueue q);
void DeleteMin(PriorityQueue q);
ElementType FindMin(PriorityQueue q);
bool IsEmpty(PriorityQueue q);
bool IsFull(PriorityQueue q);
SizeType Father(SizeType child);
SizeType FirstChild(SizeType father);
SizeType MinChild(SizeType father, PriorityQueue q);

void TestPriorityQueueArray()
{
    srand(time(0));
    const SizeType MaxEleNum = 10;
    PriorityQueue q = Initialize(MaxEleNum);
    int i = MaxEleNum;

    cout << "Insert: ";
    while(i --)
    {
        ElementType ele = rand()%MaxEleNum;
        cout << ele << "   ";
        Insert(ele, q);
    }
    cout << endl;

    cout << "Delete: ";
    while(++i < MaxEleNum)
    {
        cout << FindMin(q) << "   ";
        DeleteMin(q);
    }
    cout << "Finish." << endl;
}

PriorityQueue Initialize(SizeType MaxElements)
{
    g_capcity = MaxElements;
    return new ElementType[MaxElements];
}
void Destroy(PriorityQueue q)
{
    delete[] q;
}
void MakeEmpty(PriorityQueue q)
{
    g_size = 0;
}
void Insert(ElementType ele, PriorityQueue q)
{
    SizeType index = g_size;
    while(0 != index)
    {
        if(ele < q[Father(index)])
        {
            q[index] = q[Father(index)];
        }
        else
        {
            break;
        }
        index = Father(index);
    }
    q[index] = ele;
    ++g_size;
}
void DeleteMin(PriorityQueue q)
{
    if(g_size == 0) return;

    SizeType index = 0;
    SizeType maxEleIdx = g_size - 1;
    while(index < g_size)
    {
        SizeType child = MinChild(index, q);
        if(child == 0) break;

        if(q[maxEleIdx] < q[child])
        {
            q[index] = q[maxEleIdx];
            --g_size;
            return;
        }
        q[index] = q[child];
        index = child;
    }

    q[index] = q[maxEleIdx];
    --g_size;
}
ElementType FindMin(PriorityQueue q)
{
    return q[0];
}
bool IsEmpty(PriorityQueue q)
{
    return g_size == 0;
}
bool IsFull(PriorityQueue q)
{
    return g_size == g_capcity;
}

SizeType Father(SizeType child)
{
    return (child-1)/3;
}
SizeType FirstChild(SizeType father)
{
    return father*3 + 1;
}
SizeType MinChild(SizeType father, PriorityQueue q)
{
    SizeType firstChild = FirstChild(father);
    if(g_size <= firstChild) return 0;
    if(firstChild == g_size -1) return firstChild;
    if(firstChild == g_size - 2) 
    {
        return q[firstChild] < q[firstChild+1]? firstChild: firstChild+1;
    }

    SizeType ret = firstChild;
    ret = q[firstChild] < q[firstChild+1]?firstChild: firstChild+1;
    ret = q[ret] < q[firstChild+2] ? ret : firstChild+2;
    return ret;
}