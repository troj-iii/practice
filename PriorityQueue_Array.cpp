
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
static SizeType g_size = 1;
static PriorityQueue g_queue;
const SizeType Default_Elements = 16;

PriorityQueue Initialize(SizeType MaxElements = Default_Elements);
void Destroy(PriorityQueue q);
void MakeEmpty(PriorityQueue q);
void Insert(ElementType ele, PriorityQueue q);
void DeleteMin(PriorityQueue q);
ElementType FindMin(PriorityQueue q);
bool IsEmpty(PriorityQueue q);
bool IsFull(PriorityQueue q);

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
PriorityQueue Initialize(SizeType maxElements)
{
    g_capcity = maxElements + 1;
    return new ElementType[maxElements];
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
    if(g_size == g_capcity) return;
    SizeType index = g_size;
    while(1 != index)
    {
        if(ele < q[index>>1])
        {
            q[index] = q[index>>1];
        }
        else
        {
            break;
        }
        index >>= 1;
    }
    q[index] = ele;
    ++g_size;
}

void DeleteMin(PriorityQueue q)
{
    if(g_size == 1) return;
    SizeType index = 3;
    SizeType maxEleIdx = g_size - 1;
    while(index < g_size)
    {
        if(q[index - 1] < q[index])
        {
            --index;
        }

        if(q[maxEleIdx] < q[index])
        {
            q[index] = q[maxEleIdx];
            --g_size;
            return;
        }
        q[index>>1] = q[index];
        index = index*2 + 1;
    }
    q[index>>1] = q[maxEleIdx];
    --g_size;
    return;
}
ElementType FindMin(PriorityQueue q)
{
    if(g_size == 1) return 0x7fffffff;
    return q[1];
}
bool IsEmpty(PriorityQueue q)
{
    return g_size == 1;
}
bool IsFull(PriorityQueue q)
{
    return g_size == g_capcity;
}