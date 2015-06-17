/*------------------------------------------------------------*\
Expression Tree
06/17/15
System Srchitect: Anthony Mauro
Data Architect: Bejamin Ciaglo
Developer: Mark Stiles
\*------------------------------------------------------------*/
/**************************************************************\
Dates compiled and results:
06/08/15 - Testing build, buildHelper, showStructure, and
showHelper:
- Was able to compile and show correct output.

06/10/15 - Testing Evaluate, and evaluateHelper:
- First compile, recieved minor syntax error.
- Fixed error, correct output was produced.

06/14/15 - Testing expression:
- First attempt gave wrong output.
- Fixed, recieved correct output.

06/16/15 - Final testing:
- Finished code, tested everything together, all
outputs were correct.
\**************************************************************/

#ifndef EXPRTREE_H
#define EXPRTREE_H

#pragma once
#include <stdexcept>
#include <iostream>
using namespace std;
class ExprTreeNode;

template <typename DataType>

class ExprTree {
public:
	ExprTree(); //Default constructor, creates an empty tree.
	ExprTree(const ExprTree<DataType>&); //Copy constructor, calls the default constructor and assignment operator.
	ExprTree<DataType>& operator=(const ExprTree<DataType>&); //Assignment operator, calls isEquivalent to avoid self-assignment.
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
	ExprTreeNode* assignHelper(ExprTreeNode*, const ExprTreeNode*); //Recursive helper for the assignment operator.
	//Requires: A null Node pointer and a non-null Node pointer from an existing tree.
	//Result: Recursively deep copies the data and structure of the existing tree.
	ExprTreeNode* buildHelper(); //Recursive helper for build.
	//Requires: Valid single-line input.
	//Result: Recursively creates the tree.
	void ExprTree<DataType>::expressionHelper(ExprTreeNode *p) const; //Recursively outputs tree in infix from root given as parameter
	//Requires: highest root (where to start)
	//Result: Recursively outputs tree in infix notation from root
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

#endif
