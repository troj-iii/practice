

#include <iostream>
#include <string>

using namespace std;

// Forehead declaration.
void TestExpressionTree();

int main()
{
    TestExpressionTree();
    return 0;
}

template <class _tT>
struct ExpTreeNode
{
    typedef _tT ElementType;
    ElementType ele;
    ExpTreeNode<ElementType>* left;
    ExpTreeNode<ElementType>* right;
};

// Forehead declaration.
enum ExpEnum
{
    InfixExp,
    PostfixExp
};

enum NodeTypeEnum
{
    NodeTypeOperatorAdd,
    NodeTypeOperatorSub,
    NodeTypeOperatorMul,
    NodeTypeOperatorDiv,
    NodeTypeData,
};

struct EleNode
{
    string data_;
    NodeTypeEnum type_;
};
typedef size_t SizeType;
typedef ExpTreeNode<EleNode> Node;
typedef Node* ExpTree;
ExpTree CreateExpressionTree(const string& infix, ExpEnum eExp);
void printExpressionTree(const ExpTree tree, ExpEnum eExp);
Node* NextNode(const string& expression, SizeType& nBeg);
int StringStrip(string& inout, char c = ' ');
NodeTypeEnum GetElementTyep(const string& tmp);
Node* CreateNode(const Node::ElementType& ele, Node* left = NULL, Node* right = NULL);

Node* CreateNode(const Node::ElementType& ele, Node* left, Node* right)
{
    Node* node = new Node;
    node->ele = ele;
    node->left = left;
    node->right = right;
    return node;
}

void TestExpressionTree()
{
    string postfix = "a b c d e f g h i j + * + * + * + * *";
    ExpTree tree = CreateExpressionTree(postfix, PostfixExp);
    printExpressionTree(tree, PostfixExp);
}

const SizeType Num_Max_Array = 10;
ExpTree CreateExpressionTree(const string& infix, ExpEnum eExp)
{
    Node** assistArray = new Node*[Num_Max_Array];
    Node* ancestor = NULL;
    if(eExp == PostfixExp)
    {
        SizeType i = 0;
        Node* node = NULL;
        SizeType topArrayIndex = 0;
        while((node = NextNode(infix, i)) != NULL)
        {
            if(node->ele.type_ == NodeTypeData)
            {
                assistArray[topArrayIndex ++ ] = node;
            }
            else
            {
                ancestor = node;
                node->right = assistArray[-- topArrayIndex];
                node->left = assistArray[-- topArrayIndex];
                assistArray[topArrayIndex ++ ] = node;
            }
        }
    }
    delete[] assistArray;
    return ancestor;
}

const char Char_Whitespace = ' ';
Node* NextNode(const string& expression, SizeType& nBeg)
{
    SizeType nEleBeg = nBeg;
    SizeType nEleEnd = nBeg;
    bool bGot = false;
    SizeType i = nBeg;
    for(; i < expression.size(); ++i)
    {
        if(!bGot && expression[i] == Char_Whitespace)
        {
            continue;
        }
        else if(!bGot)
        {
            bGot = true;
            nEleBeg = i;
        }
        else if(expression[i] == Char_Whitespace)
        {
            nEleEnd = i;
            break;
        }
    }
    nBeg = i;

    if(bGot)
    {
        string tmp;
        if(i == expression.size())
        {
            tmp = expression.substr(nEleBeg);
        }
        tmp = expression.substr(nEleBeg, nEleEnd - nEleBeg);
        EleNode ele = {tmp, GetElementTyep(tmp)};

        return CreateNode(ele);
    }
    return NULL;
}

void printInfixExpressionTree(const ExpTree tree, SizeType leftBrace, SizeType rightBrace);
int CompareMathLevel(NodeTypeEnum left, NodeTypeEnum right);
int CompareMathLevel(NodeTypeEnum left, NodeTypeEnum right)
{
    if(left == NodeTypeData || right == NodeTypeData)
    {
        return 0;
    }

    int nRet;
    int nDelta = int(left) - int(right);

    if(nDelta < -1)
    {
        nRet = -1;
    }
    else if(nDelta == -1)
    {
        if(left == NodeTypeOperatorAdd ||
            left == NodeTypeOperatorMul)
        {
            nRet = 0;
        }
        else
        {
            nRet = -1;
        }
    }
    else if(nDelta == 0)
    {
        nRet = 0;
    }
    else if(nDelta == 1)
    {
        if(left == NodeTypeOperatorAdd ||
            left == NodeTypeOperatorMul)
        {
            nRet = 1;
        }
        else
        {
            nRet = 0;
        }
    }
    else if(nDelta > 1)
    {
        nRet = 1;
    }
    return nRet;
}

void printInfixExpressionTree(const ExpTree tree, SizeType nBrace, bool bIsLeftChild)
{
    if(tree->left->left != NULL )
    {
        SizeType leftAdd = 0;

        if(CompareMathLevel(tree->ele.type_, tree->left->ele.type_) == 1)
        {
            ++ leftAdd;
        }
        if(bIsLeftChild)
        {
            printInfixExpressionTree(tree->left, nBrace + leftAdd, true);
        }
        else
        {
            printInfixExpressionTree(tree->left, leftAdd, false);
        }
    }

    SizeType nNumBrace = nBrace;
    if(bIsLeftChild)
    {
        while(nNumBrace -- )
        {
            cout << '(';
        }
        cout << tree->left->ele.data_;
        cout << tree->ele.data_;
        cout << tree->right->ele.data_;
    }
    else
    {
        cout << tree->left->ele.data_;
        cout << tree->ele.data_;
        cout << tree->right->ele.data_;
        while(nNumBrace --)
        {
            cout << ')';
        }
    }

    if(tree->right->right != NULL)
    {
        SizeType rightAdd = 0;

        if(CompareMathLevel(tree->ele.type_, tree->right->ele.type_) == 1)
        {
            ++ rightAdd;
        }
        if(bIsLeftChild)
        {
            printInfixExpressionTree(tree->right, rightAdd, true);
        }
        else
        {
            printInfixExpressionTree(tree->right, nBrace + rightAdd, false);
        }
    }

}
void printExpressionTree(const ExpTree tree, ExpEnum eExp)
{
    if(eExp == PostfixExp)
    {
        printInfixExpressionTree(tree, 0, false);
    }
}

int StringStrip(string& inout, char c)
{
    size_t nInSize = inout.size();
    string instr = inout;
    size_t i = 0;
    for(; i < nInSize; ++i)
    {
        if(instr[i] == c)
        {
            instr[i] = 0;
        }
    }
    size_t nOffset = 0;
    i = 0;
    for(; i + nOffset < nInSize; ++i)
    {
        if(nOffset != 0)
        {
            if(instr[i+nOffset] == 0)
            {
                ++nOffset;
            }
            if(i + nOffset >= nInSize)
            {
                break;
            }
            instr[i] = instr[i+nOffset];
        }
        else if(instr[0] == 0)
        {
            ++nOffset;
            if(i + nOffset >= nInSize)
            {
                break;
            }
            instr[i] = instr[i+nOffset];
        }
    }
    inout = instr.substr(0, i);
    return nOffset;
}


const char Char_Add = '+';
const char Char_Sub = '-';
const char Char_Mul = '*';
const char Char_Div = '/';
const char Char_Left_Brace = '(';
const char Char_Right_Brace = ')';

NodeTypeEnum GetElementTyep(const string& tmp)
{
    NodeTypeEnum eNodeType;
    switch(tmp[0])
    {
    case Char_Add:
        eNodeType = NodeTypeOperatorAdd;
        break;
    case Char_Sub:
        eNodeType = NodeTypeOperatorSub;
        break;
    case Char_Mul:
        eNodeType = NodeTypeOperatorMul;
        break;
    case Char_Div:
        eNodeType = NodeTypeOperatorDiv;
        break;
    default:
        eNodeType = NodeTypeData;
        break;
    }
    return eNodeType;
}