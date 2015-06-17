#include "ExprTree.h"

template <typename DataType>
ExprTree<DataType>::ExprTree()
{
	root = NULL;
}
template <typename DataType>
ExprTree<DataType>::ExprTree(const ExprTree<DataType>& other)
{
	root = NULL;
	*this = other;
}
template <typename DataType>
ExprTree<DataType>& ExprTree<DataType>::operator=(const ExprTree<DataType>& other)
{
	if (isEquivalent(other))
		return *this;
	clear();
	root = assignHelper(root, other.root);
	return *this;
}
template <typename DataType>
ExprTree<DataType>::~ExprTree()
{
	clear();
	delete root;
}
template <typename DataType>
void ExprTree<DataType>::build()
{
	clear();
	root = buildHelper();
	return;
}

template <typename DataType>
void ExprTree<DataType>::expression() const
{
	expressionHelper(root);
}

template <typename DataType>
void ExprTree<DataType>::expressionHelper(ExprTreeNode *p) const
{

	if (p->left != NULL)
	{
		if (p != root)
			cout << '(' << ' '; // outputs left parentheses before leftmost operand in small operation unless root

		expressionHelper(p->left); // traverses left subtree
		cout << p->dataItem << ' '; // outputs operators
		expressionHelper(p->right); // traverses right subtree

		if (p != root)
			cout << ')' << ' '; // outputs right parentheses after rightmost operand in small operation unless root
	}

	else if (p->left == NULL)
		cout << p->dataItem << ' '; // outputs operands

	if (p == root)
		cout << ' ' << endl; // outputs newline when tree traversal is finished
}

template <typename DataType>
DataType ExprTree<DataType>::evaluate() const
{
	return evaluateHelper(root);
}

template <typename DataType>
void ExprTree<DataType>::clear()
{
	if (NULL == root)
		return;
	clearHelper(root);
	root = NULL;
	return;
}
template <typename DataType>
bool ExprTree<DataType>::isEquivalent(const ExprTree& other) const
{
	if (NULL == root && NULL == other.root) //The helper cannot handle being given null pointers, handle those cases separately first the case of both trees being empty.
		return 1;
	else if (NULL == root && NULL != other.root) //Then the two cases of one empty and one non-empty.
		return 0;
	else if (NULL != root && NULL == other.root)
		return 0;
	else
		return isEquivalentHelper(root, other.root);
}
template <typename DataType>
bool ExprTree<DataType>::isEmpty() const
{
	if (NULL == root)
		return 1;
	else
		return 0;
}
template <typename DataType>
void ExprTree<DataType>::showStructure() const
{
	if (isEmpty())
		cout << "Empty tree" << endl;
	else
	{
		cout << endl;
		showHelper(root, 1);
		cout << endl;
	}
	return;
}
template <typename DataType>
void ExprTree<DataType>::showHelper(ExprTreeNode *p, int level) const
{
	int j; // Loop counter
	if (p != 0)
	{
		showHelper(p->right, level + 1); // Output right subtree
		for (j = 0; j < level; j++) // Tab over to level
			cout << "\t";
		cout << " " << p->dataItem; // Output dataItem
		if ((p->left != 0) && // Output "connector"
			(p->right != 0))
			cout << "<";
		else if (p->right != 0)
			cout << "/";
		else if (p->left != 0)
			cout << "\\";
		cout << endl;
		showHelper(p->left, level + 1); // Output left subtree
	} //Not sure why putting a return statement here screws everything up but it does so I'm omitting it.
}
template <typename DataType>
ExprTreeNode* ExprTree<DataType>::assignHelper(ExprTreeNode *here, const ExprTreeNode* other)
{
	here = new ExprTreeNode;
	here->dataItem = other->dataItem;
	here->left = NULL;
	here->right = NULL;
	if (NULL != other->left) //If the node being copied is not a leaf recurse to copy its left child.
		here->left = assignHelper(here->left, other->left);
	if (NULL != other->right) //Likewise for the right child.
		here->right = assignHelper(here->right, other->right);
	return here;
}
template <typename DataType>
ExprTreeNode* ExprTree<DataType>::buildHelper()
{
	char ch;
	do
		cin.get(ch);
	while (' ' == ch || '\t' == ch); //Reads in the next character until it finds one that isn't whitespace.
	ExprTreeNode *newNode;
	newNode = new ExprTreeNode;
	newNode->dataItem = ch; //Stores the new character as the current node's data.
	if ('+' == ch || '-' == ch || '*' == ch || '/' == ch) //A node will have children iff it contains an operator.
	{
		newNode->left = buildHelper();
		newNode->right = buildHelper();
	}
	else //If the node contains a value it is a leaf so the pointers should be null.
	{
		newNode->left = NULL;
		newNode->right = NULL;
	}
	return newNode;
}
template <typename DataType>
DataType ExprTree<DataType>::evaluateHelper(const ExprTreeNode* here) const
{
	char leftLeafCH = here->left->dataItem;
	char rightLeafCH = here->right->dataItem;
	DataType leftLeafDT, rightLeafDT;
	if ('+' == leftLeafCH || '-' == leftLeafCH || '*' == leftLeafCH || '/' == leftLeafCH) //If the left child node contains an operation recurse to find its value.
		leftLeafDT = evaluateHelper(here->left);
	else //Otherwise the left child contains a value so convert it from character to DataType. 
		leftLeafDT = charConverter(leftLeafCH);
	if ('+' == rightLeafCH || '-' == rightLeafCH || '*' == rightLeafCH || '/' == rightLeafCH) //Same for the right child node, recurse if it's an operator.
		rightLeafDT = evaluateHelper(here->right);
	else //Convert it to a DataType if it's not. 
		rightLeafDT = charConverter(rightLeafCH);

	switch (here->dataItem) //Carry out the operation stored in this node.
	{
	case '+':
		return leftLeafDT + rightLeafDT;
	case '-':
		return leftLeafDT - rightLeafDT;
	case '*':
		return leftLeafDT * rightLeafDT;
	case '/':
		if (rightLeafDT == 0) //Division by 0 guard.
			throw logic_error("Division by zero");
		else
			return leftLeafDT/rightLeafDT;
	}

}
template<typename DataType>
DataType ExprTree<DataType>::charConverter(const char ch) const
{
	switch (ch)
	{
	case '1':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	case '7':
		return 7;
	case '8':
		return 8;
	case '9':
		return 9;
	default:
		return 0;
	}
}
template <typename DataType>
void ExprTree<DataType>::clearHelper(ExprTreeNode* here)
{
	if (NULL != here->left)
		clearHelper(here->left);
	if (NULL != here->right)
		clearHelper(here->right);
	delete here;
	return;
}
template <typename DataType>
bool ExprTree<DataType>::isEquivalentHelper(const ExprTreeNode* here, const ExprTreeNode* other) const
{
	if (here->dataItem != other->dataItem)
		return 0;
	if (NULL == here->left && NULL != other->left)
		return 0;
	if (NULL != here->left && NULL == other->left)
		return 0;
	if (!(isEquivalentHelper(here->left, other->left)))
		return 0;
	if (NULL == here->right && NULL != other->right)
		return 0;
	if (NULL != here->right && NULL == other->right)
		return 0;
	if (!(isEquivalentHelper(here->right, other->right)))
		return 0;
	return 1;
}
