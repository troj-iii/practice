

#include <iostream>

using namespace std;

// Forehead declaration.
void TestTree();

int main()
{
    return 0;
}

typedef int ElementType;
class _tNode;
typedef _tNode Node;
typedef Node* Tree;
typedef Tree Ancestor;

struct _tNode
{
    ElementType ele;
    _tNode* firstChild;
    _tNode* nextSibling;
};

// We need a root tree (original ancestor).
Ancestor CreateTree();
Node* LastChild(Node* parent);
void PreorderTraverseTree(Tree tree);
void PostorderTraverseTree(Tree tree);

void TestTree()
{
    Tree tree = CreateTree();
}

Ancestor CreateTree()
{
    Ancestor anc = new Node();
    anc->ele = 0;
    anc->firstChild = NULL;
    anc->nextSibling = NULL;
}
Node* LastChild(Node* parent)
{
    Node* lastChild = parent->firstChild;
    if(lastChild->nextSibling != NULL)
    {
        lastChild = lastChild->nextSibling;
    }
    return lastChild;
}
void PreorderTraverseTree(Tree tree, size_t dept)
{
    size_t nWhitespace = dept * 3;
    while(nWhitespace --)
    {
        cout << ' ';
    }
    cout << tree->ele;
    PreorderTraverseTree(tree->firstChild, dept + 1);
    Node* sibling = tree->nextSibling;
    while(sibling != NULL)
    {
        PreorderTraverseTree(tree, dept);
    }
}
void PreorderTraverseTree(Tree tree)
{
    PreorderTraverseTree(tree, 0);
}
void PostorderTraverseTree(Tree tree, size_t dept)
{
    PreorderTraverseTree(tree->firstChild, dept + 1);
    Node* sibling = tree->nextSibling;
    while(sibling != NULL)
    {
        PreorderTraverseTree(tree, dept);
    }

    size_t nWhitespace = dept * 3;
    while(nWhitespace --)
    {
        cout << ' ';
    }
    cout << tree->ele;
}

void PostorderTraverseTree(Tree tree)
{
    PostorderTraverseTree(tree, 0);
}
