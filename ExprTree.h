#pragma once
#include <stdexcept>
#include <iostream>
using namespace std;

template <typename DataType>
class ExprTree {
public:

	ExprTree();	//Default constructor, creates an empty tree.

	ExprTree(const ExprTree&); //Copy constructor, calls the default constructor and assignment operator.

	ExprTree& operator=(const ExprTree&); //Assignment operator, calls isEquivalent to avoid self-assignment.

	~ExprTree(); //Destructor.

	void build(); //Calls clear then builds a tree based on a single line of input.
	//Requires: Console window input consisting of only single-digit numbers and arithmatic operators, separated by whitespace on a single line.
	//Result: An expression tree to evaluate the input as a single expression in Polish Notation.

	void expression() const; //Outputs the tree in infix notation.
	//Requires: Nothing, will output "NULL" if tree is empty.
	//Result: The input expression converted to infix notation with parentheses around all but the outermost operation.

	DataType evaluate() const throw (logic_error); //Evaluates the stored expression.
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

	void showStructure() const; //Outputs the entire tree structure for debug purposes.
	//Requires: Nothing.
	//Result: The tree in the form it's stored in.

private:
	
	void showHelper(ExprTreeNode, int) const; //Recursive helper for showStructure.
	//Requires: Nothing.
	//Result: Recursively outputs the tree.

	ExprTreeNode buildHelper(); //Recursive helper for build.
	//Requires: Valid single-line input.
	//Result: Recursively creates the tree.

	ExprTreeNode *root; //Pointer to the root node of the tree.

};

class ExprTreeNode {
	template<typename DataType>
	friend class ExprTree<DataType>;
public:

	~ExprTreeNode(); //Destructor

private:
		
	ExprTreeNode(char ch='\0', ExprTreeNode *left=NULL, ExprTreeNode *right=NULL); //Constructor for the tree nodes with default parameters.

	char dataItem; //The value stored in the node.

	ExprTreeNode *left, *right; //Pointers to the child nodes.
	};

template <typename DataType>
ExprTree<DataType>::ExprTree()
{
	root = NULL;
}

template <typename DataType>
void ExprTree<DataType>::build()
{
	clear();
	root = buildHelper();
	return;
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
	int j;									 // Loop counter

	if (p != 0)
	{
		showHelper(p->right, level + 1);	// Output right subtree
		for (j = 0; j < level; j++)			// Tab over to level
			cout << "\t";
		cout << " " << p->dataItem;			// Output dataItem
		if ((p->left != 0) &&				// Output "connector"
			(p->right != 0))
			cout << "<";
		else if (p->right != 0)
			cout << "/";
		else if (p->left != 0)
			cout << "\\";
		cout << endl;
		showHelper(p->left, level + 1);		// Output left subtree
	}	//Not sure why putting a return statement here screws everything up but it does so I'm omitting it.
}

template <typename DataType>
ExprTreeNode* ExprTree<DataType>::buildHelper()
{
	char ch;
	do
		cin.get(ch);
	while (' ' == ch || '\t' == ch);
	ExprTreeNode *newNode;
	newNode = new ExprTreeNode;
	newNode->dataItem = ch;
	if ('+' == ch || '-' == ch || '*' == ch || '/' == ch)
	{
		newNode->left = buildHelper();
		newNode->right = buildHelper();
	}
	else
	{
		newNode->left = NULL;
		newNode->right = NULL;
	}
	return newNode;
}
ExprTreeNode::ExprTreeNode(char ch, ExprTreeNode *leftptr, ExprTreeNode *rightptr)
{
	dataItem = ch;
	left = leftptr;
	right = rightptr;
}
ExprTreeNode::~ExprTreeNode()
{
	delete left;
	delete right;
}
