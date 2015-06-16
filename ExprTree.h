#pragma once
#include <stdexcept>
#include <iostream>
using namespace std;
class ExprTreeNode;
template <typename DataType>
class ExprTree {
public:
	ExprTree(); //Default constructor, creates an empty tree.
	ExprTree(const ExprTree&); //Copy constructor, calls the default constructor and assignment operator.
	ExprTree* operator=(const ExprTree&); //Assignment operator, calls isEquivalent to avoid self-assignment.
	~ExprTree(); //Destructor.
	void build(); //Calls clear then builds a tree based on a single line of input.
	//Requires: Console window input consisting of only single-digit numbers and arithmatic operators, separated by whitespace on a single line.
	//Result: An expression tree to evaluate the input as a single expression in Polish Notation.
	void expression() const; //Outputs the tree in infix notation.
	//Requires: Nothing, will output "NULL" if tree is empty.
	//Result: The input expression converted to infix notation with parentheses around all but the outermost operation.
	DataType evaluate() const; //Evaluates the stored expression.
	//Requires: A non-empty tree, will throw an exception if the tree is empty.
	//Result: The value of the expression, in the same data type as the tree.
	void clear(); //Erases the tree.
	//Requires: Nothing, will do nothing if the tree is empty.
	//Result: An empty tree, identical in form to one made by the default constructor.
	void commute(); //Reverses the tree.
	//Requires: Nothing, will do nothing if the tree is empty.
	//Result: A reversed tree which will evaluate to the same result as initially if it contains only + and *.
	bool isEquivalent(const ExprTree&) const; //Relational operator that checks for equality; functionally identical to overloading ==.
	//Requires: A second tree of the same DataType.
	//Result: Returns 1 if the trees are identical and 0 otherwise.
	bool isEmpty() const; //Checks whether the tree is empty.
	//Requires: Nothing.
	//Result: Returns 1 if the tree is empty and 0 otherwise.
	void showStructure() const; //Outputs the entire tree structure for debug purposes.
	//Requires: Nothing.
	//Result: The tree in the form it's stored in.
private:
	void showHelper(ExprTreeNode*, int) const; //Recursive helper for showStructure.
	//Requires: Nothing.
	//Result: Recursively outputs the tree.
	ExprTreeNode* buildHelper(); //Recursive helper for build.
	//Requires: Valid single-line input.
	//Result: Recursively creates the tree.
	DataType evaluateHelper(const ExprTreeNode*) const; //Recursive helper for evaluate.
	//Requires: A pointer to a node which contains an operator.
	//Result: Recursively conducts the operations contained in the tree.
	DataType charConverter(const char) const; //Converts char into number for evaluateHelper to make the code cleaner.
	//Requires: A character which contains a digit 0-9.
	//Result: Returns that digit as a DataType.
	void clearHelper(ExprTreeNode*); //Recursive helper for clear.
	//Requires: Non-empty tree.
	//Result: Recursively deletes the tree.
	bool isEquivalentHelper(const ExprTreeNode*, const ExprTreeNode*) const; //Recursive helper for isEquivalent.
	//Requires: 2 nodes, each from different trees.
	//Returns: 1 if the nodes have identical dataItems as do all their children, 0 otherwise.
	ExprTreeNode *root; //Pointer to the root node of the tree.
};
class ExprTreeNode {
	template<typename DataType>
	friend class ExprTree;
private:
	char dataItem; //The value stored in the node.
	ExprTreeNode *left, *right; //Pointers to the child nodes.
};
template <typename DataType>
ExprTree<DataType>::ExprTree()
{
	root = NULL;
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
	return isEquivalentHelper(root, other->root);
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
		if (rightLeafDT) //Division by 0 guard.
			return leftLeafDT / rightLeafDT;
		else
			return leftLeafDT;
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
