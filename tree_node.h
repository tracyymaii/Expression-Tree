/**
 * Title:		Lab 04 - postfix_to_expression_tree_assignment.cpp
 * Purpose:		Takes in a postfix version of a math function, and creates a
 *              tree based on it. Using the tree, all normal math functions
 *              can be completed.
 * Author:		Tracy Mai
 * Date:		May 05, 2024
 */


#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <string>

using std::string;

class TreeNode {
public:
    TreeNode(const TreeNode& other);
    const TreeNode& operator=(const TreeNode& rhs);
    TreeNode* leftChild;
    TreeNode* rightChild;
    TreeNode* parent;
    int id;
    double value;
    string stringValue;
    bool isOperand;
    char operatorType;

    TreeNode(string value);
    TreeNode(char opertor, TreeNode* leftChild, TreeNode* rightChild);
    ~TreeNode();
};


#endif //POSTFIX_TO_EXPRESSION_TREE_ASSIGNMENT_TREE_NODE_H
