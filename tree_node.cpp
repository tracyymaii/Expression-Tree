/**
 * Title:		Lab 04 - postfix_to_expression_tree_assignment.cpp
 * Purpose:		Takes in a postfix version of a math function, and creates a
 *              tree based on it. Using the tree, all normal math functions
 *              can be completed.
 * Author:		Tracy Mai
 * Date:		May 05, 2024
 */

#include "tree_node.h"
#include <math.h>

/**
 * TreeNode Constructor
 * Creates a TreeNode for numbers read in the postfix equation.
 * @param value
 * @return none
 */
TreeNode::TreeNode(string value) {
    this->leftChild = nullptr;
    this->rightChild = nullptr;
    this->parent = nullptr;
    id = -1;
    isOperand = true;
    operatorType = '#';
    this->value = stod(value);
    this->stringValue = value;
}

/**
 * TreeNode Constructor
 * Creates a TreeNode for operators read in the postfix equation.
 * @param value
 * @return none
 */
TreeNode::TreeNode(char opertor, TreeNode *leftChild, TreeNode *rightChild) {
    this->leftChild = leftChild;
    this->rightChild = rightChild;
    this->leftChild->parent = this;
    this->rightChild->parent = this;
    parent = nullptr;
    id = -1;
    isOperand = false;
    operatorType = opertor;

    switch (opertor) {
        case '+':
            value = leftChild->value + rightChild->value;
            stringValue = value;
            break;
        case '-':
            value = leftChild->value - rightChild->value;
            stringValue = value;
            break;
        case '*':
            value = leftChild->value * rightChild->value;
            stringValue = value;
            break;
        case '/':
            value = leftChild->value / rightChild->value;
            stringValue = value;
            break;
        case '^':
            value = pow(leftChild->value, rightChild->value);
            stringValue = value;
        default:
            break;
    }
}

/**
 * TreeNode Copy Constructor
 * Constructs a deep copy of the other TreeNode. If the TreeNode has children,
 * it traverses through those and makes it into a deep copy too.
 * @param other TreeNode
 * @returns nothing
 */
TreeNode::TreeNode(const TreeNode& other) {

    this->id = other.id;
    this->isOperand = other.isOperand;
    this->operatorType = other.operatorType;
    this->value = other.value;
    this->stringValue = other.stringValue;
    this->parent = nullptr;

    if (other.isOperand) {
        this->leftChild = nullptr;
        this->rightChild = nullptr;
        return;
    }

    this->leftChild = new TreeNode(*other.leftChild);
    this->rightChild = new TreeNode(*other.rightChild);
    this->leftChild->parent = this;
    this->rightChild->parent = this;
}

/**
 * TreeNode Copy Assignment Operator
 * Enables the deep copy assignment with the operator.
 * @param rhs TreeNode
 * @return *this to make copies
 */
const TreeNode& TreeNode::operator=(const TreeNode& rhs) {

    if (this == &rhs) {
        return *this;
    }

    delete this->leftChild;
    delete this->rightChild;

    this->leftChild = new TreeNode(*rhs.leftChild);
    this->rightChild = new TreeNode(*rhs.rightChild);
    this->parent = rhs.parent;
    this->id = rhs.id;
    this->isOperand = rhs.isOperand;
    this->operatorType = rhs.operatorType;
    this->value = rhs.value;
    this->stringValue = rhs.stringValue;

    return *this;
}

/**
* TreeNode Destructor
* Deletes and allocates the memory for each TreeNode and their children.
* @param none
* @returns none
*/
TreeNode:: ~TreeNode() {

    if (isOperand) {
        return;
    }

    delete this->leftChild;
    delete this->rightChild;
}
