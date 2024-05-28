/**
 * Title:		Lab 04 - postfix_to_expression_tree_assignment.cpp
 * Purpose:		Takes in a postfix version of a math function, and creates a
 *              tree based on it. Using the tree, all normal math functions
 *              can be completed.
 * Author:		Tracy Mai
 * Date:		May 05, 2024
 */

#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
#include <sstream>
using std::string;
using std::ostream;
using std::stringstream;

#include "tree_node.h"

enum TraversalType {INORDER, PREORDER, POSTORDER};

class Tree {
private:
    TreeNode* _root;
    Tree(const Tree& other);
    const Tree& operator=(const Tree& rhs);
    string PreOrder(const TreeNode* node)const;
    string PostOrder(const TreeNode* node)const;
    string InOrder(const TreeNode* node)const;
    void HelperFormat(TreeNode* node, int depth, ostream& output, bool useLevel)const;
    int IdHelper(TreeNode* node, int id);

public:
    Tree();
    ~Tree();
    bool BuildTree(const string& postfixExpression);
    string Traverse(TraversalType traversalType)const;
    double Evaluate()const;
    void StepByStepEvaluation(ostream& output, bool useLevel = false)const;
};

string trim(const string& str, const string& whitespace = " \t");

#endif //POSTFIX_TO_EXPRESSION_TREE_ASSIGNMENT_TREE_H
