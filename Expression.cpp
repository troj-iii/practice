

#include <iostream>
#include <string>
#include <stack>
#include <cassert>

using namespace std;

// Forehead declaration.
void TestEpr();
int StringStrip(string& inout, char c = ' ');

int main()
{
    TestEpr();
    return 0;
}

enum OperatorEnum
{
    OperatorErr,
    OperatorAdd,
    OperatorSub,
    OperatorMul,
    OperatorDiv,
    OperatorBraceLeft,
    OperatorBraceRight
};

enum NodeTypeEnum
{
    NodeTypeData,
    NodeTypeOperator
};

enum OperationEnum
{
    OperationErr,
    OperationPop,
    OperationPush
};

enum MathLevlEnum
{
    MathLevelLow,
    MathLevelEqual,
    MathLevelHigh
};

struct _tNode
{
    string data_;
    NodeTypeEnum eType;
    OperatorEnum eOpr;
};

// Forehead declaration.
bool InfixToPostfix(const string& postfix, string& infix);
bool PostfixToInfix(const string& infix, string& postfix);
bool findNextOperator(const string& src, size_t nBeg, size_t& nPos, OperatorEnum& eOpr);
OperationEnum PopOrPush(OperatorEnum eOprStack, OperatorEnum eOprEpr);
bool PopAndPushStack(stack<_tNode>& operandStack, stack<_tNode>& operatorStack, const _tNode& operandNode, const _tNode& operatorNode);
bool PopLastStack(stack<_tNode>& operandStack, stack<_tNode>& operatorStack);
bool IsOperator(const string& tmp, OperatorEnum& eOpr);
MathLevlEnum CompareMathLevel(OperatorEnum c1, OperatorEnum c2);

void TestEpr()
{
    string infix = "3.5 + 6.4 + 2.3 * 5 + (4 + 5) * 3.2";
    string postfix = "3.5 6.4 + 2.3 5 * + 4 5 + 3.2 * +";

    cout << "infix: " << infix << endl;
    string tmp;
    if(InfixToPostfix(infix, tmp))
    {
        cout << "call InfixToPostfix: " << tmp << endl;
    }
    cout << endl;
    cout << "postfix: " << postfix << endl;
    if(PostfixToInfix(postfix, tmp))
    {
        cout << "call PostfixToInfix: " << tmp << endl;
    }
    cout << endl;
}

bool InfixToPostfix(const string& infix, string& postfix)
{
    stack<_tNode> operatorStack;
    stack<_tNode> operandStack;
    postfix.clear();

    for(size_t i = 0; i < infix.size();)
    {
        size_t nPos = 0;
        OperatorEnum eOpr = OperatorErr;
        if(findNextOperator(infix, i, nPos, eOpr))
        {
            _tNode node;
            node.data_ = infix.substr(i, nPos - i);
            StringStrip(node.data_);
            node.eType = NodeTypeData;
            _tNode operatorNode;
            operatorNode.data_ = infix.substr(nPos, 1);
            StringStrip(operatorNode.data_);
            operatorNode.eType = NodeTypeOperator;
            operatorNode.eOpr = eOpr;
            if(node.data_.empty())
            {
                if(operatorNode.eOpr == OperatorBraceLeft)
                {
                    operatorStack.push(operatorNode);
                    i = nPos + 1;
                    continue;
                }
                else
                {
                    if(operatorStack.empty())
                    {
                        operatorStack.push(operatorNode);
                    }
                    else
                    {
                        _tNode topOperand = operandStack.top();
                        operandStack.pop();
                        PopAndPushStack(operandStack, operatorStack, topOperand, operatorNode);
                    }
                    i = nPos + 1;
                    continue;
                }
            }

            if(operatorStack.empty())
            {
                operatorStack.push(operatorNode);
                operandStack.push(node);
            }
            else
            {
                OperationEnum eOperation = PopOrPush(operatorStack.top().eOpr, eOpr);
                if(eOperation == OperationPop)
                {
                    if(eOpr == OperatorBraceRight)
                    {
                        PopAndPushStack(operandStack, operatorStack, node, operatorNode);
                        if(operatorStack.top().eOpr == OperatorBraceRight)
                        {
                            operatorStack.pop();
                            operatorStack.pop();
                        }
                    }
                    else
                    {
                        string tmp = operandStack.top().data_ + " ";
                        operandStack.pop();
                        tmp += node.data_ + " ";
                        tmp += operatorStack.top().data_ + " ";
                        operatorStack.pop();
                        _tNode oldNode;
                        oldNode.data_ = tmp;
                        oldNode.eType = NodeTypeData;
                        if(!operatorStack.empty())
                        {
                            PopAndPushStack(operandStack, operatorStack, oldNode, operatorNode);
                        }
                        else
                        {
                            operatorStack.push(operatorNode);
                            operandStack.push(oldNode);
                        }
                    }
                }
                else if(eOperation == OperationPush)
                {
                    _tNode operatorNode;
                    operatorNode.data_ = infix.substr(nPos, 1);
                    operatorNode.eType = NodeTypeOperator;
                    operatorNode.eOpr = eOpr;
                    operatorStack.push(operatorNode);
                    operandStack.push(node);
                }
                else
                {
                    return false;
                }
            }
            i = nPos + 1;
        }
        else
        {
            string tmp = infix.substr(i);
            StringStrip(tmp);
            if(!tmp.empty())
            {
                _tNode node;
                node.data_ = tmp;
                node.eType = NodeTypeData;
                operandStack.push(node);
                PopLastStack(operandStack, operatorStack);
            }

            postfix = operandStack.top().data_;
            break;
        }
    }
    if(!operandStack.size() == 1)
    {
        postfix = operandStack.top().data_;
    }
    return true;
}

const char Char_Whitespace = ' ';
bool PostfixToInfix(const string& postfix, string& infix)
{
    stack<_tNode> operatorStack;
    stack<_tNode> operandStack;
    OperatorEnum eOprPrev = OperatorAdd;

    for(size_t i = 0; i < postfix.size();)
    {
        size_t nOffset = postfix.find(Char_Whitespace, i);
        string tmp;
        if(nOffset == string::npos)
        {
            tmp = postfix.substr(i);
        }
        else
        {
            tmp = postfix.substr(i, nOffset - i);
        }
        StringStrip(tmp);
        OperatorEnum eOpr= OperatorErr;
        if(IsOperator(tmp, eOpr))
        {
            _tNode topOperandNode = operandStack.top();
            operandStack.pop();
            _tNode topOperandNode2 = operandStack.top();
            operandStack.pop();
            switch(CompareMathLevel(eOpr, eOprPrev))
            {
            case MathLevelEqual:
            case MathLevelLow:
                {
                    _tNode node;
                    node.data_ = topOperandNode.data_ + " " + tmp + " " + topOperandNode2.data_;
                    node.eType = NodeTypeData;
                    operandStack.push(node);
                }
                break;
            case MathLevelHigh:
                {
                    _tNode node;
                    node.data_ = string("(") + topOperandNode.data_ + string(")") 
                        + " " + tmp + " " + 
                        string("(") + topOperandNode2.data_ + ")";
                    node.eType = NodeTypeData;
                    operandStack.push(node);
                }
                break;
            default:
                return false;
            }
            eOprPrev = eOpr;
        }
        else
        {
            _tNode node;
            node.data_ = tmp;
            node.eType = NodeTypeData;
            operandStack.push(node);
        }
        if(nOffset == string::npos)
        {
            break;
        }
        i = nOffset + 1;
    }

    infix = operandStack.top().data_;
    return true;
}

bool PopLastStack(stack<_tNode>& operandStack, stack<_tNode>& operatorStack)
{
    _tNode node = operandStack.top();
    operandStack.pop();
    while(!operatorStack.empty() && !operandStack.empty())
    {
        string tmp = node.data_ + " ";
        tmp += operandStack.top().data_ + " ";
        operandStack.pop();
        tmp += operatorStack.top().data_ + " ";
        operatorStack.pop();
        node.data_ = tmp;
    }
    operandStack.push(node);
    return operandStack.empty();
}

bool PopAndPushStack(stack<_tNode>& operandStack, stack<_tNode>& operatorStack, const _tNode& operandNode, const _tNode& operatorNode)
{
    OperationEnum eOperation = PopOrPush(operatorStack.top().eOpr, operatorNode.eOpr);
    if(eOperation == OperationPop)
    {
        string tmp = operandNode.data_ + " ";
        tmp += operandStack.top().data_ + " ";
        operandStack.pop();
        tmp += operatorStack.top().data_ + " ";
        operatorStack.pop();
        _tNode node;
        node.data_ = tmp;
        node.eType = NodeTypeData;
        if(operatorStack.empty())
        {
            operatorStack.push(operatorNode);
            operandStack.push(node);
        }
        else
        {
            return PopAndPushStack(operandStack, operatorStack, node, operatorNode);
        }
    }
    else if(eOperation == OperationPush)
    {
        operatorStack.push(operatorNode);
        operandStack.push(operandNode);
        return true;
    }
    else
    {
        return false;
    }
}

MathLevlEnum CompareMathLevel(OperatorEnum c1, OperatorEnum c2)
{
    MathLevlEnum eRet;
    int nDelta = int(c1) - int(c2);
    if(nDelta < -1)
    {
        eRet = MathLevelLow;
    }
    else if(nDelta == -1)
    {
        if(c1 == OperatorAdd ||
            c1 == OperatorMul)
        {
            eRet = MathLevelEqual;
        }
        else
        {
            eRet = MathLevelLow;
        }
    }
    else if(nDelta == 0)
    {
        eRet = MathLevelEqual;
    }
    else if(nDelta == 1)
    {
        if(c1 == OperatorAdd ||
            c1 == OperatorMul)
        {
            eRet = MathLevelHigh;
        }
        else
        {
            eRet = MathLevelEqual;
        }
    }
    else if(nDelta > 1)
    {
        eRet = MathLevelHigh;
    }
    return eRet;
}

OperationEnum PopOrPush(OperatorEnum eOprStack, OperatorEnum eOprEpr)
{
    switch(eOprEpr)
    {
    case OperatorAdd:
    case OperatorSub:
        if(eOprStack == OperatorBraceLeft)
        {
            return OperationPush;
        }
        else
        {
            return OperationPop;
        }
        break;
    case OperatorMul:
    case OperatorDiv:
        if(eOprStack == OperatorAdd ||
            eOprStack == OperatorSub)
        {
            return OperationPush;
        }
        else if(eOprStack == OperatorBraceLeft)
        {
            return OperationPush;
        }
        else
        {
            return OperationPop;
        }
        break;
    case OperatorBraceLeft:
        return OperationPush;
        break;
    case OperatorBraceRight:
        if(eOprStack == OperatorBraceLeft)
        {
            return OperationPush;
        }
        else
        {
            return OperationPop;
        }
        break;
    default:
        break;
    }

    return OperationErr;
}

const char Char_Add = '+';
const char Char_Sub = '-';
const char Char_Mul = '*';
const char Char_Div = '/';
const char Char_Left_Brace = '(';
const char Char_Right_Brace = ')';

bool IsOperator(const string& tmp, OperatorEnum& eOpr)
{
    bool bRet = true;
    switch(tmp[0])
    {
    case Char_Add:
        eOpr = OperatorAdd;
        break;
    case Char_Sub:
        eOpr = OperatorSub;
        break;
    case Char_Mul:
        eOpr = OperatorMul;
        break;
    case Char_Div:
        eOpr = OperatorDiv;
        break;
    default:
        bRet = false;
        eOpr = OperatorErr;
        break;
    }
    return bRet;
}

bool findNextOperator(const string& src, size_t nBeg, size_t& nPos, OperatorEnum& eOpr)
{
    assert(nBeg < src.size());

    size_t i = nBeg;
    for(; i < src.size(); ++i)
    {
        bool bIsBreak = true;
        switch(src[i])
        {
        case Char_Add:
            eOpr = OperatorAdd;
            break;
        case Char_Sub:
            eOpr = OperatorSub;
            break;
        case Char_Mul:
            eOpr = OperatorMul;
            break;
        case Char_Div:
            eOpr = OperatorDiv;
            break;
        case Char_Left_Brace:
            eOpr = OperatorBraceLeft;
            break;
        case Char_Right_Brace:
            eOpr = OperatorBraceRight;
            break;
        default:
            bIsBreak = false;
            break;
        }
        if(bIsBreak)
        {
            nPos = i;
            return true;
        }
    }
    nPos = string::npos;
    eOpr = OperatorErr;
    return false;
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