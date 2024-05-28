/**
 * Title:		Lab 04 - postfix_to_expression_tree_assignment.cpp
 * Purpose:		Takes in a postfix version of a math function, and creates a
 *              tree based on it. Using the tree, all normal math functions
 *              can be completed.
 * Author:		Tracy Mai
 * Date:		May 05, 2024
 */

#include "tree.h"
#include <stack>
#include <iostream>
#include <iomanip>

using std::stringstream;
using std::stack;
using std::setprecision;
using std::fixed;

/**
 * Tree Constructor
 * Constructs an empty tree.
 * @param none
 * @return none
 */
Tree::Tree() {
    _root = nullptr;
}

/**
 * Tree Copy Constructor
 * Constructs a deep copy of the other Tree. If the TreeNode has children,
 * it traverses through those and makes it into a deep copy too, with the
 * TreeNode constructor.
 * @param other Tree
 * @returns nothing
 */
Tree::Tree(const Tree& other) {
    this->_root = new TreeNode(*other._root);
}

/**
 * Tree Assignment Operator
 * Enables the deep copy assignment with the operator.
 * @param rhs Tree
 * @return *this to make copies
 */
const Tree& Tree::operator=(const Tree& rhs) {
    if (this == &rhs) {
        return *this;
    }

    delete _root;

    this->_root = new TreeNode(*rhs._root);
    return *this;
}

/**
* TreeNode Destructor
* Deletes and allocates the memory for the tree.
* @param none
* @returns none
*/
Tree::~Tree() {
    delete _root;
}

/**
 * Build Tree
 * Builds the tree based on the given postfix expression.
 * Details will be explained within the function.
 * @param postfixExpression
 * @return
 */
bool Tree::BuildTree(const string& postfixExpression) {

    stack<TreeNode*> tree;
    string multiDigit = "";

    string trimmedPost = trim(postfixExpression);

    for (size_t i = 0; i < trimmedPost.length(); ++i) {

        /**
         * Ensures that all parts of the number is saved and used as one unit
         * and gets pushed onto the stack.
         */
        if (isdigit(trimmedPost.at(i)) || trimmedPost.at(i) == '.') {
            multiDigit.push_back(trimmedPost.at(i));

        } else if (isspace((trimmedPost.at(i))) != 0 && isdigit(trimmedPost.at(i-1)) ) {
            TreeNode* pointerNode = new TreeNode(multiDigit);
            tree.push(pointerNode);
            multiDigit = "";

        /**
         * When an operator is seen a new parent node is created. The two nodes
         * already on the stack pop off and become the operator's children.
         */
        } else if (trimmedPost.at(i) == '+' || trimmedPost.at(i) == '-'
                   || trimmedPost.at(i) == '*'|| trimmedPost.at(i) == '/' || trimmedPost.at(i) == '^') {

            TreeNode* rightChild = tree.top();
            tree.pop();
            TreeNode* leftChild = tree.top();
            tree.pop();

            TreeNode* parent = new TreeNode(trimmedPost.at(i), leftChild, rightChild);
            tree.push(parent);
        }
    }
    _root = tree.top();


    /**
     * Helper function that assigned the id to the Tree.
     */
    IdHelper(_root, 0);
    return true;
}

/**
 * IdHelper
 * Uses Pre-Order traversal to assign the id to every TreeNode.
 * @param node
 * @param id
 * @return the last index the traversal left off on
 */
int Tree::IdHelper(TreeNode* node, int id) {

    node->id = id;
    id++;

    if (node->isOperand) {
        return id;
    }

    int indexFromLeft = IdHelper(node->leftChild, id);
    return IdHelper(node->rightChild, indexFromLeft);
}

/**
 * Traverse
 * Traverses through the tree based on the traversal type given.
 * @param traversalType
 * @return the string representation of the traversal.
 */
string Tree::Traverse(TraversalType traversalType)const {

    if (traversalType == INORDER) {
        return trim(InOrder(_root));

    } else if (traversalType == PREORDER) {
        return trim(PreOrder(_root));

    } else {
        return trim(PostOrder(_root));
    }
}

/**
 * PreOrder
 * Completes a PreOrder traversal on the given node.
 * @param node
 * @return a string representation of the PreOrder traversal.
 */
string Tree::PreOrder(const TreeNode* node)const {
    stringstream ss;

    if (node->isOperand) {
        ss << node->stringValue << " ";
        return ss.str();
    }

    ss << node->operatorType << " ";
    ss << PreOrder(node->leftChild);
    ss << PreOrder(node->rightChild);
    return  ss.str();
}

/**
 * PostOrder
 * Completes a PostOrder traversal on the given node.
 * @param node
 * @return a string representation of the PostOrder traversal.
 */
string Tree::PostOrder(const TreeNode* node)const {
    stringstream ss;

    if (node->isOperand) {
        ss << node->stringValue << " ";
        return ss.str();
    }

    ss << PostOrder(node->leftChild);
    ss << PostOrder(node->rightChild);
    ss << node->operatorType << " ";

    return  ss.str();
}

/**
 * InOrder
 * Completes a InOrder traversal on the given node.
 * @param node
 * @return a string representation of the InOrder traversal.
 */
string Tree::InOrder(const TreeNode* node)const {
    stringstream ss;

    if (node->isOperand) {
        ss << node->stringValue << " ";
        return ss.str();
    }

    ss << InOrder(node->leftChild);
    ss << node->operatorType << " ";
    ss << InOrder(node->rightChild);

    return  ss.str();
}

/**
 * Evaluate
 * Returns the value of the tree. Calculation for nodes have been defined
 * in the TreeNode class.
 * @return
 */
double Tree::Evaluate()const {
    return _root->value;
}

/**
 * Step By Step Evaluation
 * Uses a recursive helper function, Helper Format, to complete the
 * Step By Step Evaluation.
 * @param output
 * @param useLevel
 */
void Tree::StepByStepEvaluation(ostream& output, bool useLevel)const {
    HelperFormat(_root, 0, output, useLevel);
}

/**
 * Helper Format
 * Recursive helper function for Step By Step Evaluation.
 * Uses a PreOrder traversal to print out every step of the function and
 * formats accordingly to the useLevel boolean.
 * @param node
 * @param depth
 * @param output
 * @param useLevel
 * @return none
 */
void Tree::HelperFormat(TreeNode* node, int depth, ostream& output, bool useLevel)const {

    if (useLevel) {
        for (int i = 0; i < depth; i++) {
            output << "\t";
        }
    }

    output << "{\"value\":" << fixed << setprecision(2) << node->value
           << ", \"operator\":\"" << node->operatorType << "\", \"operand\":";

    if (node->isOperand) {
        output << "true";
    } else {
        output << "false";
    }

    if (!useLevel) {
        output << ", \"id\":" << node->id << ", \"parent\":";

        if (node->parent != nullptr) {
            output << (node->parent)->id << "}\n";
        } else {
            output << "-1" << "}\n";
        }

    } else {
        output << "}\n";
    }

    if (!(node->isOperand)) {
        HelperFormat(node->leftChild, depth+1, output, useLevel);
        HelperFormat(node->rightChild, depth+1, output, useLevel);
    }
}

/**
 * trim
 * Trims excess whitespace.
 * @param str
 * @param whitespace
 * @return the string with no excess whitespace.
 */
string trim(const string& str, const string& whitespace){
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == string::npos)
        return ""; // no content
    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;
    return str.substr(strBegin, strRange);
}
