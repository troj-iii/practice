
// Binomial heap is a cute and mediate heap.
// I will implement after i think out the algorithm.

#include <iostream>

#define IS_NULL(p, ret)\
    if(NULL == p) return ret;

using namespace std;

// Forehead declaration.
void TestBinomialTree();

int main()
{
    TestBinomialTree();
    return 0;
}

typedef int ElementType;
typedef size_t SizeType;

SizeType Max_Node = 32;
struct BinomialNode
{
    ElementType ele;
    BinomialNode* firstChild;
    BinomialNode* nextSibling;
};

struct BinomialTree
{
    SizeType size;
    SizeType capacity;
    BinomialNode* holder;
};
static int BitMask[32] = 
{
    0x1, 0x2, 0x4, 0x8,
    0x10, 0x20, 0x40, 0x80,
    0x100, 0x200, 0x400, 0x800,
    0x1000, 0x2000, 0x4000, 0x8000,
    0x10000, 0x20000, 0x40000, 0x80000,
    0x100000, 0x200000, 0x400000, 0x800000,
    0x1000000, 0x2000000, 0x4000000, 0x8000000,
    0x10000000, 0x20000000, 0x40000000, 0x80000000
};

class BinomialBit
{
public:
    static const SizeType END = -1;
    SizeType BitsNum()
    {
        return bitNum_;
    }
    void Init(SizeType n)
    {
        data_ = n;
        bitNum_ = 0;
        curIdx_ = -1;
        for (int i = 0; i < 32; i ++)
        {
            if(BitMask[i]&data_ != 0)
            {
                ++bitNum_;
            }
        }
    }
    // descend order. e.g. 5 -- (0    1      0   1)
    //                              second     first
    SizeType NextOne()
    {
        if(curIdx_ == 31)
        {
            return -1;
        }

        ++curIdx_;

        while(BitMask[curIdx_] < data_ && BitMask[curIdx_]&data_ == 0) curIdx_++;

        return curIdx_;
    }
private:
    SizeType data_;
    SizeType bitNum_;
    SizeType curIdx_;
};
typedef BinomialNode Node;
typedef Node* Position;
typedef BinomialTree* PriorityQueue;

PriorityQueue Initialize(SizeType maxOrder);
PriorityQueue Insert(ElementType ele, PriorityQueue q);
PriorityQueue Merge(PriorityQueue q1, PriorityQueue q2);
ElementType FindMin(PriorityQueue q);
PriorityQueue DeleteMin(PriorityQueue q);

void TestBinomialTree()
{

}

PriorityQueue Initialize(SizeType maxOrder)
{
    if(maxOrder > 32)
    {
        maxOrder = 32;
    }

    PriorityQueue q = new BinomialTree();
    IS_NULL(q, NULL);

    q->size = 0;
    q->capacity = maxOrder;
    q->holder = new BinomialNode[q->capacity];
    if(NULL == q->holder)
    {
        delete q;
        return NULL;
    }

    return q;
}
PriorityQueue Insert(ElementType ele, PriorityQueue q)
{
    PriorityQueue newQ = Initialize(1);

    return Merge(newQ, q);
}
PriorityQueue Merge(PriorityQueue q1, PriorityQueue q2)
{
    IS_NULL(q1, q2);
    IS_NULL(q2, q1);
}

ElementType FindMin(PriorityQueue q)
{
    IS_NULL(q, 0);

    BinomialBit b;
    b.Init(q->size);

    SizeType i = b.NextOne();
    SizeType minEle = i;
    for(i = b.NextOne(); i != BinomialBit::END; i = b.NextOne())
    {
        if(q->holder[i].ele < q->holder[minEle].ele)
        {
            minEle = i;
        }
    }

    return q->holder[i].ele;
}
PriorityQueue DeleteMin(PriorityQueue q)
{

}