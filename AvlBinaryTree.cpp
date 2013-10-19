

#include <iostream>
#include <cstdlib>
#include <ctime>


#define IS_NULL(p, ret)\
	if(NULL == p) return ret;

#define MAX(a, b)\
    ((a) > (b) ? (a) : (b));
using namespace std;

// Forehead declaration.
void TestAvlBinaryTree();
int main()
{
    TestAvlBinaryTree();
    return 0;
}

// Forehead declaration.

// Abstract from Wikipedia
//In an AVL tree, the heights of the two child subtrees of any node differ by at most one; 
//if at any time they differ by more than one, rebalancing is done to restore this property.

typedef size_t SizeType;
//class ElementType;
typedef int ElementType;
struct _tAvlBinaryTreeNode
{
	ElementType ele;
	_tAvlBinaryTreeNode* left;
	_tAvlBinaryTreeNode* right;
	SizeType nHeight;
};

typedef _tAvlBinaryTreeNode Node;
typedef Node* AvlTree;
typedef Node* Position;
typedef AvlTree Tree;

Tree MakeEmpty(Tree tree);
Position Find(ElementType ele, Tree tree);
Position FindMin(Tree tree);
Position FindMax(Tree tree);
Tree Insert(ElementType ele, Tree tree);
Tree Delete(ElementType ele, Tree tree);
ElementType Retrieve(Position pos);
void printTree(Tree tree);
Position CreateNode(ElementType ele, Position left = NULL, Position right = NULL, SizeType nHeight = 1);

void TestAvlBinaryTree()
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
    //INSERT;
    //INSERT;
    //INSERT;
    //INSERT;
    //INSERT;
    //INSERT;
    //INSERT;
    //INSERT;
    //INSERT;
    //INSERT;
    //INSERT;
    //INSERT;
    cout << endl;

    cout << " Second Insert: ";
    printTree(tree);
    cout << endl;

    cout << "Delete Number: ";
#define DELETE\
    tree = Delete(nRand = rand()%nRandomRange, tree);\
    cout << nRand << "   ";

    DELETE;
    DELETE;
    DELETE;
    DELETE;
    DELETE;
    //DELETE;
    //DELETE;
    //DELETE;
    //DELETE;
    //DELETE;
    cout << endl;

    cout << "After Delete: ";
    printTree(tree);
    cout << endl;

}

Tree MakeEmpty(Tree tree)
{
	IS_NULL(tree, NULL);
	
	MakeEmpty(tree->left);
	MakeEmpty(tree->right);
	
	delete tree;
}

Position Find(ElementType ele, Tree tree)
{
	IS_NULL(tree, NULL);
	
	if(ele == tree->ele)
	{
		return tree;
	}
	else if(ele < tree->ele)
	{
		return Find(ele, tree->left);
	}
	else
	{
		return Find(ele, tree->right);
	}
}

Position FindMin(Tree tree)
{
	IS_NULL(tree, NULL);
	
	while(NULL != tree->left)
	{
		tree = tree->left;
	}
	
	return tree;
}

Position FindMax(Tree tree)
{
	IS_NULL(tree, NULL);
	
	while(NULL != tree->right)
	{
		tree = tree->right;
	}
	
	return tree;
}

SizeType Height(Position pos);

Tree SingleRotateWithLeft(Tree tree);
Tree SingleRotateWithRight(Tree tree);
Tree DoubleRotateWithLeft(Tree tree);
Tree DoubleRotateWithRight(Tree tree);

const SizeType OperationInsert = 2;
const SizeType OperationLeft = -1;
const SizeType OperationRight = 1;
const SizeType OperationNone = 0;


Tree Insert(ElementType ele, Tree tree)
{
    if(NULL == tree)
    {
        tree = CreateNode(ele);
    }
    else
    {
        if(ele < tree->ele)
        {
            tree->left = Insert(ele, tree->left);

            if(Height(tree->left) - Height(tree->right) == 2)
            {
                if(Height(tree->left->left) > Height(tree->left->right))
                {
                    tree = SingleRotateWithLeft(tree);
                }
                else
                {
                    tree = DoubleRotateWithLeft(tree);
                }
            }
        }
        else if(tree->ele < ele)
        {
            tree->right = Insert(ele, tree->right);

            if(Height(tree->right) - Height(tree->left) == 2)
            {
                if(Height(tree->right->right) > Height(tree->right->left))
                {
                    tree = SingleRotateWithRight(tree);
                }
                else
                {
                    tree = DoubleRotateWithRight(tree);
                }
            }
        }
    }

    tree->nHeight = MAX(Height(tree->left), Height(tree->right)) + 1;
    return tree;
}
Position MoveData(Position parent, int nLeftOrRight)
{
    Position& node = nLeftOrRight == OperationLeft ? parent->left : parent->right;
    if(NULL == node)
    {
        ;
    }
    else 
    {
        if(NULL == node->left && NULL == node->right)
        {
            delete node;
            node = NULL;
        }
        else if(NULL == node->left)
        {
            node->ele = node->right->ele;
            node = MoveData(node, OperationRight);
        }
        else if(NULL == node->right)
        {
            node->ele = node->left->ele;
            node = MoveData(node, OperationLeft);
        }
    }
    
    if(nLeftOrRight == OperationLeft && Height(parent->right) - Height(parent->left) == 2)
    {
        if(Height(parent->right->right) > Height(parent->right->left))
        {
            parent = SingleRotateWithRight(parent);
        }
        else
        {
            parent = DoubleRotateWithRight(parent);
        }
    }
    else if(nLeftOrRight == OperationRight && Height(parent->left) - Height(parent->right) == 2)
    {
        if(Height(parent->left->left) >Height(parent->left->right))
        {
            parent = SingleRotateWithLeft(parent);
        }
        else
        {
            parent = DoubleRotateWithLeft(parent);
        }
    }

    return parent;
}
Tree Delete(ElementType ele, Tree tree)
{
    IS_NULL(tree, NULL);

    if(ele == tree->ele)
    {
        if(NULL == tree->left && NULL == tree->right)
        {
            delete tree;
            return NULL;
        }
        else if(NULL == tree->left)
        {
            tree->ele = tree->right->ele;
            tree = MoveData(tree, OperationRight);
        }
        else
        {
            tree->ele = tree->left->ele;
            tree = MoveData(tree, OperationLeft);
        }
    }
    else if(ele < tree->ele)
    {
        tree->left = Delete(ele, tree->left);

        if(Height(tree->right) - Height(tree->left) == 2)
        {
            if(Height(tree->right->right) > Height(tree->right->left))
            {
                tree = SingleRotateWithRight(tree);
            }
            else
            {
                tree = DoubleRotateWithRight(tree);
            }
        }
    }
    else if(tree->ele < ele)
    {
        tree->right = Delete(ele, tree->right);

        if(Height(tree->left) - Height(tree->right) == 2)
        {
            if(Height(tree->left->left) > Height(tree->left->right))
            {
                tree = SingleRotateWithLeft(tree);
            }
            else
            {
                tree = DoubleRotateWithLeft(tree);
            }
        }
    }

    tree->nHeight = MAX(Height(tree->left), Height(tree->right)) + 1;
    return tree;
}

ElementType Retrieve(Position pos)
{
	return pos->ele;
}

Position CreateNode(ElementType ele, Position left, Position right, SizeType nHeight)
{
	Position node = new Node();
	node->ele = ele;
	node->left = left;
	node->right = right;
	node->nHeight = nHeight;
	
	return node;
}

Tree SingleRotateWithLeft(Tree tree)
{
    Position node = tree->left;
    tree->left = tree->left->right;
    node->right = tree;

    -- tree->nHeight;
    return node;
}

Tree SingleRotateWithRight(Tree tree)
{
    Position node = tree->right;
    tree->right = tree->right->left;
    node->left = node;

    -- tree->nHeight ;
    return node;
}
Tree DoubleRotateWithLeft(Tree tree)
{
    Position node = tree->left->right;

    tree->left->right = node->left;
    tree->left = node->right;

    node->left = tree->left;
    node->right = tree;
    -- tree->nHeight;
    ++ node->nHeight;

    return node;
}
Tree DoubleRotateWithRight(Tree tree)
{
    Position node = tree->right->left;

    tree->right->left = node->right;
    tree->right = node->left;

    node->left = tree;
    node->right = tree->right;
    -- tree->nHeight;
    ++ node->nHeight;

    return node;
}

SizeType Height(Position pos)
{
    IS_NULL(pos, 0);

    return pos->nHeight;
}

void printTree(Tree tree)
{
    if(NULL == tree) return;

    printTree(tree->left);
    cout << tree->ele << "   ";
    printTree(tree->right);
}












