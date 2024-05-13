//
// Created by Carlos R. Arias on 4/28/23.
//

#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
using std::string;
using std::ostream;


#include "tree_node.h"


enum TraversalType {INORDER, PREORDER, POSTORDER};


class Tree {
private:
    TreeNode* _root;
    Tree(const Tree& other);
    const Tree& operator=(const Tree& rhs);
public:
    Tree();
    ~Tree();
    bool BuildTree(const string& postfixExpression);
    string Traverse(TraversalType traversalType)const;
    double Evaluate()const;
    void StepByStepEvaluation(ostream& output, bool useLevel = false)const;
};

#endif //POSTFIX_TO_EXPRESSION_TREE_ASSIGNMENT_TREE_H
