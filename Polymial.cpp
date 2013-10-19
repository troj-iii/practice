#include <iostream>
#include <cstdlib>
#include <cstdarg>
#define IS_NULL(p, ret)\
    if(p == NULL) return ret;
using namespace std;
typedef unsigned int uint;
// Forehead declaration.
void TestPolynomial();
struct VectorPolymial;
struct ListPolymial;

typedef ListPolymial Item;
//typedef VectorPolymial* Polymial;
//typedef ListPolymial Polymial;
int main()
{
    TestPolynomial();
    return 0;
}
// The polynomial is a mathematic problem.
// So the element type using the double real can be OK.
// There isn't need to use template.
// Vector implement polynomial.
struct VectorPolymial
{
    double* dCoeffArr;
    uint     nHighPower;
};
// Forehead declaration.
// Vector polymial;
void FillVectorPolymialCoeff(VectorPolymial* pol, bool bOrder, uint num, ...);
VectorPolymial* CreateEmptyVectorPolymial(uint nHighPower);
VectorPolymial* PolymialAdd(const VectorPolymial* pol1, const VectorPolymial* pol2);
VectorPolymial* PolymialMul(const VectorPolymial* pol1, const VectorPolymial* pol2);
void printVectorPolymial(const VectorPolymial* pol);
// List polymial;
// ... represents coefficient and exponent.
void FillListPolymialCoeff(ListPolymial* pol, bool bOrder, uint num, ...);
ListPolymial* CreateEmptyListPolymial();
ListPolymial* PolymialAdd(const ListPolymial* pol1, const ListPolymial* pol2);
ListPolymial* PolymialMul(const ListPolymial* pol1, const ListPolymial* pol2);
void printListPolymial(const ListPolymial* pol);
void MakeEmpty(ListPolymial* pol);
void InsertItem(Item* item, ListPolymial* pol);
ListPolymial* CopyListPolymial(const ListPolymial* pol);
Item* EndItem(const ListPolymial* pol);
void TestPolynomial()
{
    //VectorPolymial* pVP1 = CreateEmptyVectorPolymial(3);
    //cout << "VP1: ";
    //printVectorPolymial(pVP1);
    //FillVectorPolymialCoeff(pVP1, true, 4, 11.0, 0.8,0.9, 32.0);
    //printVectorPolymial(pVP1);
    //VectorPolymial* pVP2 = CreateEmptyVectorPolymial(4);
    //FillVectorPolymialCoeff(pVP2, false, 4, 22.0, 0.0, 10.0, 25.0);
    //cout << "VP2: ";
    //printVectorPolymial(pVP2);

    //// plus
    //VectorPolymial* pVP = PolymialAdd(pVP1, pVP2);
    //cout << "Add result: ";
    //printVectorPolymial(pVP);
    //delete[] pVP->dCoeffArr;
    //delete pVP;
    //pVP = NULL;
    //// multiplus
    //pVP = PolymialMul(pVP1, pVP2);
    //cout << "Mul result: ";
    //printVectorPolymial(pVP);

    ////release memory.
    //delete[] pVP->dCoeffArr;
    //delete pVP;
    //pVP = NULL;

    //cout << "Delete VP1 CoeffArr" << endl;
    //delete[] pVP1->dCoeffArr;
    //cout << "Delete VP1" << endl;
    //delete pVP1;
    //cout << "Delete VP2" << endl;
    //delete[] pVP2->dCoeffArr;
    //delete pVP2;
    //cout << "Delete finish." << endl;

    // list polymial.

    ListPolymial* pVP1 = CreateEmptyListPolymial();
    cout << "VP1: ";
    printListPolymial(pVP1);
    FillListPolymialCoeff(pVP1, true, 2, 11.0, 2, 0.8, 6);
    printListPolymial(pVP1);
    ListPolymial* pVP2 = CreateEmptyListPolymial();
    FillListPolymialCoeff(pVP2, true, 3, 22.0, 2, 0.0, 3, 10.0, 7);
    cout << "VP2: ";
    printListPolymial(pVP2);

    // plus
    ListPolymial* pVP = PolymialAdd(pVP1, pVP2);
    cout << "Add result: ";
    printListPolymial(pVP);
    // multiplus
    pVP = PolymialMul(pVP1, pVP2);
    cout << "Mul result: ";
    printListPolymial(pVP);
}
// bOrder == true represents high to low, else low to high.
void FillVectorPolymialCoeff(VectorPolymial* pol, bool bOrder, uint num, ...)
{
    va_list args;
    va_start(args, num);

    if(bOrder)
    {
        uint nExponent = 0;
        while(nExponent <= pol->nHighPower && num -- != 0)
        {
            pol->dCoeffArr[nExponent ++ ] = va_arg(args, double);
        }
    }
    else
    {
        uint nExponent = pol->nHighPower + 1;
        while(nExponent -- != 0 && num -- != 0)
        {
            pol->dCoeffArr[nExponent ] = va_arg(args, double);
        }
    }
    va_end(args);
}
VectorPolymial* CreateEmptyVectorPolymial(uint nHighPower)
{
    VectorPolymial* pPolymial = new VectorPolymial();
    IS_NULL(pPolymial, NULL)
    pPolymial->nHighPower = nHighPower;
    pPolymial->dCoeffArr = new double[nHighPower+1];

    if(pPolymial->dCoeffArr == NULL)
    {
        delete pPolymial;
        pPolymial = NULL;
    }
    ::memset(pPolymial->dCoeffArr, 0, (pPolymial->nHighPower+1)*sizeof(double));

    return pPolymial;
}
VectorPolymial* PolymialAdd(const VectorPolymial* pol1, const VectorPolymial* pol2)
{
    const VectorPolymial* highPol = pol1->nHighPower > pol2->nHighPower ? pol1 : pol2;
    const VectorPolymial* lowPol = pol1->nHighPower <= pol2->nHighPower ? pol1 : pol2;
    VectorPolymial* pPolymial = new VectorPolymial();
    IS_NULL(pPolymial, NULL)

    pPolymial->nHighPower = highPol->nHighPower;
    pPolymial->dCoeffArr = new double[highPol->nHighPower+1];
    if(pPolymial->dCoeffArr == NULL)
    {
        delete pPolymial;
        return NULL;
    }
    ::memset(pPolymial->dCoeffArr, 0, (pPolymial->nHighPower+1)*sizeof(double));

    ::memcpy(pPolymial->dCoeffArr, lowPol->dCoeffArr, (lowPol->nHighPower+1)*sizeof(double));
    for(uint i = 0; i <= pPolymial->nHighPower; ++i)
    {
        pPolymial->dCoeffArr[i] += highPol->dCoeffArr[i];
    }
    return pPolymial;
}
VectorPolymial* PolymialMul(const VectorPolymial* pol1, const VectorPolymial* pol2)
{
    uint nHighPower = pol1->nHighPower + pol2->nHighPower;

    // the uint over flow.
    if(nHighPower < pol1->nHighPower || nHighPower < pol2->nHighPower)
    {
        return NULL;
    }

    VectorPolymial* pPolymial = new VectorPolymial();
    IS_NULL(pPolymial, NULL)

        pPolymial->nHighPower = nHighPower;
    pPolymial->dCoeffArr = new double[pPolymial->nHighPower+1];
    if(pPolymial->dCoeffArr == NULL)
    {
        delete pPolymial;
        return NULL;
    }
    ::memset(pPolymial->dCoeffArr, 0, (pPolymial->nHighPower+1)*sizeof(double));

    for(uint i = 0; i <= pol1->nHighPower; ++i)
    {
        for(uint j = 0; j <= pol2->nHighPower; ++j)
        {
            pPolymial->dCoeffArr[i+j] += pol1->dCoeffArr[i]*pol2->dCoeffArr[j];
        }
    }

    return pPolymial;
}

void printVectorPolymial(const VectorPolymial* pol)
{
    uint i = 0;
    cout << pol->dCoeffArr[i] << 'X' << i;

    for( ++i; i<=pol->nHighPower; ++i)
    {
        cout << " + " << pol->dCoeffArr[i] << 'X' << i;
    }
    cout << endl;
}
// list implement polymial.
// In order to do operation conveniently, we create it in desc order.
struct ListPolymial
{
    double dCoeff;
    uint nExponent;
    Item* next;
};

typedef Item* ptrToItem;
typedef Item* NextItem;
ListPolymial* CreateEmptyListPolymial()
{
    ListPolymial* pol = new ListPolymial();
    IS_NULL(pol, NULL)
    pol->dCoeff = 0.0;
    pol->nExponent = 0;
    pol->next = NULL;
    return pol;
}
// bOrder is not used in list polymial.
void FillListPolymialCoeff(ListPolymial* pol, bool bOrder, uint num, ...)
{
    if(pol == NULL) return;
    va_list args;
    va_start(args, num);

    MakeEmpty(pol);

    while(num -- != 0)
    {
        double dCoeff = va_arg(args, double);
        uint nExponent = va_arg(args, uint);
        if(dCoeff == 0)
        {
            continue;
        }

        Item* newItem = new Item();
        if(newItem == NULL)
        {
            va_end(args);
            return;
        }
        newItem->dCoeff = dCoeff;
        newItem->nExponent = nExponent;
        newItem->next = NULL;
        InsertItem(newItem, pol);
    }
    va_end(args);
}

void MakeEmpty(ListPolymial* pol)
{
    while(pol->next != NULL)
    {
        ListPolymial* leftPol = pol->next;
        delete pol;
        pol = leftPol;
    }
    pol->dCoeff = 0;
    pol->nExponent = 0;
    pol->next = NULL;
}

ListPolymial* PolymialAdd(const ListPolymial* pol1, const ListPolymial* pol2)
{
    IS_NULL(pol1, NULL)
    IS_NULL(pol2, NULL)
    ListPolymial* pol = CreateEmptyListPolymial();
    Item* end = pol;
    Item* item1 = pol1->next, *item2 = pol2->next;
    do
    {
        if(item1 != NULL && item2 != NULL)
        {
            Item* item = new Item();
            if(item1->nExponent == item2->nExponent)
            {
                item->dCoeff = item1->dCoeff + item2->dCoeff;
                item->nExponent = item1->nExponent;

                item1 = item1->next;
                item2 = item2->next;
            }
            else if(item1->nExponent > item2->nExponent)
            {
                item->dCoeff = item1->dCoeff;
                item->nExponent = item1->nExponent;
                item1 = item1->next;
            }
            else
            {
                item->dCoeff = item2->dCoeff;
                item->nExponent = item2->nExponent;
                item2 = item2->next;
            }
            InsertItem(item, pol);
        }
        else if(item1 != NULL)
        {
            Item* end = EndItem(pol);
            while(item1 != NULL)
            {
                Item* item = new Item();
                item->dCoeff = item1->dCoeff;
                item->nExponent = item1->nExponent;
                item->next = NULL;
                end->next = item;
                end = item;
                item1 = item1->next;
            }
        }
        else if(item2 != NULL)
        {
            while(item2 != NULL)
            {
                Item* item = new Item();
                item->dCoeff = item2->dCoeff;
                item->nExponent = item2->nExponent;
                item->next = NULL;
                end->next = item;
                end = item;
                item2 = item2->next;
            }
        }
    }
    while(item1 != NULL || item2 != NULL);

    return pol;
}
void InsertItem(Item* item, ListPolymial* pol)
{
    if(pol == NULL || item == NULL || item->dCoeff == 0)
    {
        return;
    }
    NextItem nextItem = pol;
    bool bIsExist = false;
    while(nextItem != NULL)
    {
        if(nextItem->next == NULL)
        {
            break;
        }
        else
        {
            if(nextItem->next->nExponent < item->nExponent)
            {
                break;
            }
            else if(nextItem->next->nExponent == item->nExponent)
            {
                bIsExist = true;
                break;
            }
            else
            {
                nextItem = nextItem->next;
            }
        }
    }
    if(bIsExist)
    {
        nextItem->dCoeff = item->dCoeff;
        nextItem->nExponent = item->nExponent;
        delete item;
        item = nextItem;
    }
    else
    {
        item->next = nextItem->next;
        nextItem->next = item;
    }
}

ListPolymial* CopyListPolymial(const ListPolymial* pol)
{
    IS_NULL(pol, NULL)
    ListPolymial* srcPol = pol->next;

    ListPolymial* desPol = CreateEmptyListPolymial();
    Item* endItem = desPol;
    while(srcPol != NULL)
    {
        Item* item = new Item();
        item->dCoeff = srcPol->dCoeff;
        item->nExponent = srcPol->nExponent;
        item->next = NULL;
        endItem->next = item;
        endItem = item;
        srcPol = srcPol->next;
    }
    return desPol;
}

ListPolymial* PolymialMul(const ListPolymial* pol1, const ListPolymial* pol2)
{
    ListPolymial* pol = CreateEmptyListPolymial();
    NextItem tmp = NULL;
    for(NextItem i = pol1->next; i != NULL; i = i->next)
    {
        for(NextItem j = pol2->next; j != NULL; j = j->next)
        {
            tmp = new Item();
            tmp->dCoeff = i->dCoeff * j->dCoeff;
            tmp->nExponent = i->nExponent + j->nExponent;
            tmp->next = NULL;
            InsertItem(tmp, pol);
        }
    }
    return pol;
}

Item* EndItem(const ListPolymial* pol)
{
    if(pol == NULL || pol->next == NULL) return NULL;
    Item* end = pol->next;
    while(end->next != NULL)
    {
        end = end->next;
    }
    return end;
}

void printListPolymial(const ListPolymial* pol)
{
    if(pol == NULL) return;
    NextItem next = pol->next;
    if(next != NULL)
    {
        cout << next->dCoeff << "X" << next->nExponent;
        next = next->next;
    }
    while(next != NULL)
    {
        cout << " + " << next->dCoeff << "X" << next->nExponent;
        next = next->next;
    }
    cout << endl;
}







