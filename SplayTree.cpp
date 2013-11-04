

#include <iostream>
#include <cstdlib>
#include <ctime>

#define IS_NULL(p, ret)\
    if(NULL == p) return ret;

using namespace std;

// Forehead declaration.
void TestSplayTree();

int main()
{
    TestSplayTree();
    return 0;
}

//      Splay tree:
// Tye tree
// Invented 1985
// Invented by Daniel Dominic Sleator and Robert Endre Tarjan

//       Time Comlexity in BIG O notation
//          Average    Worst case
// Space    O(n)       O(n)
// Search   O(log n)   amortized O(log n)
// Insert   O(log n)   amortized O(log n)
// Delete   O(log n)   amortized O(log n)

//class ElementType;
typedef int ElementType;
typedef size_t SizeType;
struct _tSplayTreeNode
{
    _tSplayTreeNode* left;
    _tSplayTreeNode* right;
    _tSplayTreeNode* parent;
    ElementType ele;
};

typedef _tSplayTreeNode Node;
typedef Node* SplayTree;
typedef SplayTree Tree;
typedef Tree Position;

Tree Find(ElementType ele, Tree tree);
Position FindMin(Tree tree);
Position FindMax(Tree tree);
Tree Splay(Position pos);
Position Locate(ElementType ele, Tree tree);
Tree Insert(ElementType ele, Tree tree);
Tree Delete(ElementType ele, Tree tree);
void printTree(Tree tree);
Position CreateNode(ElementType ele, Position parent)
{
    Position node = new Node();
    node->ele = ele;
    node->left = NULL;
    node->right = NULL;
    node->parent = parent;
    return node;
}

void TestSplayTree()
{
    srand(time(NULL));
    const int nRandomRange = 20;
    Tree tree = NULL;
    int nRand = 0;

    cout << "Insert Member: ";
#define INSERT\
    tree = Insert(nRand = rand()%nRandomRange, tree);\
    cout << nRand << "   ";

    INSERT;
    INSERT;
    INSERT;
    INSERT;
    INSERT;
    INSERT;
    INSERT;
    INSERT;
    INSERT;
    INSERT;
    INSERT;
    INSERT;
    cout << endl;

    cout << "First Insert: ";
    printTree(tree);
    cout << endl;

    cout << "Insert Member: ";
    INSERT;
    INSERT;
    INSERT;
    INSERT;
    INSERT;
    INSERT;
    INSERT;
    INSERT;
    INSERT;
    INSERT;
    INSERT;
    INSERT;
    cout << endl;

    cout << " Second Insert: ";
    printTree(tree);
    cout << endl;

    cout << "Delete Number: ";
    Position delPos = NULL;

#define DELETE\
    delPos = Delete(nRand = rand()%nRandomRange, tree);\
    cout << nRand << "   ";\
    cout << endl;\
    if(delPos != NULL) tree = delPos;\
    cout << "After Delete: ";\
    printTree(tree);\
    cout << endl;

    DELETE;
    DELETE;
    DELETE;
    DELETE;
    DELETE;
    DELETE;
    DELETE;
    DELETE;
    DELETE;
    DELETE;
    cout << endl;

    cout << "After Delete: ";
    printTree(tree);
    cout << endl;
}

Position Locate(ElementType ele, Tree tree)
{
    IS_NULL(tree, NULL);

    if(ele == tree->ele)
    {
        return tree;
    }
    else if(ele < tree->ele)
    {
        return Locate(ele, tree->left);
    }
    else
    {
        return Locate(ele, tree->right);
    }
}
Tree Find(ElementType ele, Tree tree)
{
    Position target = Locate(ele, tree);
    IS_NULL(target, NULL);

    tree = Splay(target);

    return tree;
}
Tree Insert(ElementType ele, Tree tree)
{
    if(NULL == tree)
    {
        return CreateNode(ele, NULL);
    }
    if(ele < tree->ele)
    {
        if(NULL == tree->left)
        {
            tree->left = CreateNode(ele, tree);

            tree = Splay(tree->left);
            return tree;
        }
        return Insert(ele, tree->left);
    }
    else if(tree->ele < ele)
    {
        if(NULL == tree->right)
        {
            tree->right = CreateNode(ele, tree);

            tree = Splay(tree->right);
            return tree;
        }
        return Insert(ele, tree->right);
    }
    while(NULL != tree->parent)
    {
        tree = tree->parent;
    }

    return tree;
}

Tree Delete(ElementType ele, Tree tree)
{
    Position node = Find(ele, tree);
    IS_NULL(node, NULL);
    tree = node;

    Position maxNode = FindMax(tree->left);
    if(NULL != maxNode)
    {
        if(maxNode->parent == tree)
        {
            maxNode->right = tree->right;
            if(NULL != tree->right)
            {
                tree->right->parent = maxNode;
            }
        }
        else
        {
            maxNode->parent->right = maxNode->left;
            if(NULL != maxNode->left)
            {
                maxNode->left->parent = maxNode->parent;
            }

            maxNode->left = tree->left;
            maxNode->right = tree->right;
            if(NULL != maxNode->left)
            {
                maxNode->left->parent = maxNode;
            }
            if(NULL != maxNode->right)
            {
                maxNode->right->parent = maxNode;
            }
        }
        maxNode->parent = NULL;
        delete tree;
        tree = maxNode;
    }
    else
    {
        Position minNode = FindMin(tree->right);
        if(NULL != minNode)
        {
            if(minNode->parent == tree)
            {
                minNode->left = tree->left;
                if(NULL != tree->left)
                {
                    tree->left->parent = minNode;
                }
            }
            else
            {
                minNode->parent->left = minNode->right;
                if(NULL != minNode->right)
                {
                    minNode->right->parent = minNode->parent;
                }

                minNode->left = tree->left;
                if(NULL != minNode->left)
                {
                    minNode->left->parent = minNode;
                }
                minNode->right = tree->right;
                if(NULL != minNode->right)
                {
                    minNode->right->parent = minNode;
                }
            }
            minNode->parent = NULL;

            delete tree;
            tree = minNode;
        }
        else
        {
            delete tree;
            return NULL;
        }
    }

    return tree;
}

Position SingleRotateWithLeftZigZig(Position pos, Position parent)
{
    pos->parent = parent->parent;
    pos->parent->left = pos;

    if(NULL != pos->right)
    {
        pos->right->parent = parent;
    }
    parent->left = pos->right;

    parent->parent = pos;
    pos->right = parent;

    return pos;
}
Position SingleRotateWithLeftZigZag(Position pos, Position parent)
{
    pos->parent = parent->parent;
    parent->parent->left = pos;

    if(NULL != pos->left)
    {
        pos->left->parent = parent;
    }
    parent->right = pos->left;

    parent->parent = pos;
    pos->left = parent;

    return pos;
}

Position SingleRotateWithRightZigZag(Position pos, Position parent)
{
    pos->parent = parent->parent;
    parent->parent->right = pos;

    if(NULL != pos->right)
    {
        pos->right->parent = parent;
    }
    parent->left = pos->right;

    parent->parent = pos;
    pos->right = parent;

    return pos;
}

Position SingleRotateWithRightZigZig(Position pos, Position parent)
{
    pos->parent = parent->parent;
    parent->parent->right = pos;

    if(NULL != pos->left)
    {
        pos->left->parent = parent;
    }
    parent->right = pos->left;

    parent->parent = pos;
    pos->left = parent;

    return pos;
}

Tree Splay(Position pos)
{
    IS_NULL(pos, NULL);
    IS_NULL(pos->parent, pos);

    while(NULL != pos->parent)
    {
        if(NULL == pos->parent->parent)
        {
            Position parent = pos->parent;
            if(pos == pos->parent->left)
            {
                pos->parent = NULL;
                parent->left = pos->right;

                parent->parent = pos;
                if(NULL != pos->right)
                {
                    pos->right->parent = parent;
                }
                pos->right = parent;

            }
            else
            {
                pos->parent = NULL;
                parent->right = pos->left;

                parent->parent = pos;

                if(NULL != pos->left)
                {
                    pos->left->parent = parent;
                }
                pos->left = parent;
            }
            return pos;
        }
        if(pos == pos->parent->left && pos->parent == pos->parent->parent->left)
        {
            SingleRotateWithLeftZigZig(pos, pos->parent);
        }
        else if(pos == pos->parent->left && pos->parent == pos->parent->parent->right)
        {
            SingleRotateWithRightZigZag(pos, pos->parent);
        }
        else if(pos == pos->parent->right && pos->parent == pos->parent->parent->left)
        {
            SingleRotateWithLeftZigZag(pos, pos->parent);
        }
        else
        {
            SingleRotateWithRightZigZig(pos, pos->parent);
        }
    }
    return pos;
}

Position FindMin(Tree tree)
{
    while(tree != NULL)
    {
        Position node = tree->left;
        if(NULL == node)
        {
            break;
        }
        tree = node;
    }
    return tree;
}

Position FindMax(Tree tree)
{
    while(tree != NULL)
    {
        Position node = tree->right;
        if(NULL == node)
        {
            break;
        }
        tree = node;
    }
    return tree;
}

void printTree(Tree tree)
{
    if(NULL == tree) return;

    printTree(tree->left);
    cout << tree->ele << "   ";
    printTree(tree->right);
}
