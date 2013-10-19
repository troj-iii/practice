
#include <iostream>
#define IS_NULL(p, ret)\
    if(NULL == p) return ret

using namespace std;

// Forehead declaration.
void TestSimpleBinaryTree();

int main()
{
    TestSimpleBinaryTree();
}

// Declaration.
// The tree's minimum node locate on the leftest.
// The tree's maximum node locate on the rightest.
//class ElementType;

typedef int ElementType;
struct BinaryNode
{
    ElementType ele;
    BinaryNode* left;
    BinaryNode* right;
};

typedef size_t SizeType;
typedef BinaryNode Node;
typedef Node* Position;
typedef Node* Tree;

Tree MakeEmpty(Tree tree);
Position Find(ElementType ele, Tree tree);
Position FindMin(Tree tree);
Position FindMax(Tree tree);
Tree Insert(ElementType ele, Tree tree);
void Delete(ElementType ele, Tree tree);
ElementType Retrieve(Position pos);
Position CreateNode(ElementType ele, Position left = NULL, Position right = NULL);

void TestSimpleBinaryTree()
{
    Tree ancestor;
    Insert(10, ancestor);
    Insert(12, ancestor);
    Insert(15, ancestor);
    Insert(11, ancestor);
    Insert(16, ancestor);
    Insert(13, ancestor);
    Insert(17, ancestor);
    Insert(11, ancestor);
    Insert(10, ancestor);
    Insert(11, ancestor);

    Delete(16, ancestor);
    MakeEmpty(ancestor);
}

Tree MakeEmpty(Tree tree)
{
    if(NULL != tree)
    {
        MakeEmpty(tree->left);
        MakeEmpty(tree->right);
        delete tree;
    }
    return NULL;
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

    while(tree->left)
    {
        tree = tree->left;
    }

    return tree;
}
Position FindMax(Tree tree)
{
    IS_NULL(tree, NULL);

    while(tree->right)
    {
        tree = tree->right;
    }

    return tree;
}
Tree Insert(ElementType ele, Tree tree)
{
    if(NULL == tree)
    {
        return CreateNode(ele);
    }

    if(ele < tree->ele)
    {
        return Insert(ele, tree->left);
    }
    else
    {
        return Insert(ele, tree->right);
    }
}

void MoveData(Position delPos)
{
    if(NULL == delPos->left && NULL == delPos->right)
    {
        return;
    }
    else if(NULL == delPos->right)
    {
        delPos->ele = delPos->left->ele;
        return MoveData(delPos->left);
    }

    delPos->ele = delPos->right->ele;
    return MoveData(delPos->right);
}
void Delete(ElementType ele, Tree tree)
{
    if(NULL == tree) return;

    if(ele == tree->ele)
    {
        MoveData(tree);
    }
    else if(ele < tree->ele)
    {
        return Delete(ele, tree->left);
    }
    else
    {
        return Delete(ele, tree->right);
    }
}

ElementType Retrieve(Position pos)
{
    return pos->ele;
}

Position CreateNode(ElementType ele, Position left, Position right)
{
    Position node = new Node();
    node->ele = ele;
    node->left = left;
    node->right = right;

    return node;
}