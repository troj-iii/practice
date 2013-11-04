
#include <iostream>
#include <ctime>
#include <cstdlib>

#define IS_NULL(p, ret) \
    if(NULL == p) return ret;

using namespace std;

//Forehead declaration
void TestLeftHeapPriorityQueue();

int main()
{
    TestLeftHeapPriorityQueue();
    return 0;
}

typedef size_t SizeType;
typedef int ElementType;
typedef struct LeftHeap
{
    ElementType ele;
    LeftHeap* left;
    LeftHeap* right;
    SizeType npl;
}* LeftHeapPriorityQueue, Node;
typedef LeftHeapPriorityQueue PriorityQueue;
typedef Node* Position;

// The priority queue property:
// Every node has an s-value which is the distance to the nearest leaf. 
// In contrast to a binary heap, a leftist tree attempts to be very unbalanced. 
// In addition to the heap property, 
// leftist trees are maintained so the right descendant of each node has the lower s-value.
// The leftist tree was invented by Clark Allan Crane.

Position CreateNode(ElementType ele);
PriorityQueue Insert(ElementType ele, PriorityQueue q);
PriorityQueue DeleteMin(PriorityQueue q);
ElementType FindMin(PriorityQueue q);
PriorityQueue MakeEmpty(PriorityQueue q);
PriorityQueue Merge(PriorityQueue q1, PriorityQueue q2);

void TestLeftHeapPriorityQueue()
{
    srand(time(0));
    const SizeType MaxEleNum = 10;
    PriorityQueue q = NULL;
    int i = MaxEleNum;

    cout << "Insert: ";
    while(i --)
    {
        ElementType ele = rand()%MaxEleNum;
        cout << ele << "   ";
        q = Insert(ele, q);
    }
    cout << endl;

    cout << "Delete: ";
    while(++i < MaxEleNum)
    {
        cout << FindMin(q) << "   ";
        q = DeleteMin(q);
    }
    cout << "Finish." << endl;
}

Position CreateNode(ElementType ele)
{
    Position node = new Node;
    node->ele = ele;
    node->left = NULL;
    node->right = NULL;
    node->npl = 0;

    return node;
}
PriorityQueue Insert(ElementType ele, PriorityQueue q)
{
    PriorityQueue insertQ = CreateNode(ele);
    return Merge(insertQ, q);
}
PriorityQueue DeleteMin(PriorityQueue q)
{
    IS_NULL(q, NULL);
    PriorityQueue leftSubQueue = q->left;
    PriorityQueue rightSubQueue = q->right;
    delete q;
    return Merge(leftSubQueue, rightSubQueue);
}
ElementType FindMin(PriorityQueue q)
{
    return q->ele;
}
PriorityQueue MakeEmpty(PriorityQueue q)
{
    IS_NULL(q, NULL);

    MakeEmpty(q->left);
    MakeEmpty(q->right);
    delete q;
    return NULL;
}
PriorityQueue SwapChild(PriorityQueue q)
{
    IS_NULL(q, NULL);

    PriorityQueue subQueue = q->left;
    q->left = q->right;
    q->right = subQueue;

    return q;
}
SizeType UpdateNPL(PriorityQueue q)
{
    if(NULL == q->left || NULL == q->right)
    {
        q->npl = 0;
    }
    else
    {
        q->npl = q->left->npl < q->right->npl ? q->left->npl : q->right->npl;
        ++q->npl;
    }

    return q->npl;
}
PriorityQueue Merge(PriorityQueue q1, PriorityQueue q2)
{
    IS_NULL(q1, q2);
    IS_NULL(q2, q1);

    if(q2->ele < q1->ele)
    {
        PriorityQueue q = q1;
        q1 = q2;
        q2 = q;
    }

    if( q1->right != NULL && q1->right->ele < q2->ele)
    {
        q1->right = Merge(q1->right, q2);
    }
    else
    {
        q2->right = Merge(q1->right, q2->right);
        q1->right = q2;
    }

    UpdateNPL(q1);

    if(q1->npl == 0)
    {
        if(q1->left == NULL)
        {
            SwapChild(q1);
        }
    }
    else
    {
        if(q1->left->npl < q1->right->npl)
        {
            SwapChild(q1);
        }
    }

    return q1;
}