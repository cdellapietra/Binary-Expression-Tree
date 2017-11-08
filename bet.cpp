//
//  bet.cpp
//  proj4
//
//  Created by Corey Della Pietra on 11/9/15.
//  Copyright © 2015 Corey Della Pietra. All rights reserved.
//

#include "bet.h"
#include <iostream>
#include <sstream>
#include <stack>


// check if token is operator
bool is_op(const string& s)
{ return(s == "+" || s == "-" || s == "*" || s == "/"); }


// determine highest precedence of two operators
int preced(const string& s) {
    if(s == "+" || s == "-")
        return 0;
    if(s == "*" || s == "/")
        return 1;
    else return 2;
}


///////////////////////////////////////////////////////
///////////// constructors / destructor ///////////////
///////////////////////////////////////////////////////


BET::BET() : root(nullptr) {}


BET::BET(const string postfix) {
    
    string token;
    istringstream ss(postfix);
    
    bool success = true;
    
    stack<BinaryNode*> s;
    
    BinaryNode* n;
    
    while(ss >> token) {
        if(!is_op(token)) {
            // create node with operand as element
            // and push to stack
            n = new BinaryNode(token);
            s.push(n);
        }
        
        else {
            // get two operands
            if(s.empty()) {
                success = false;
                break;
            }
            
            BinaryNode* r = s.top();
            s.pop();
            
            if(s.empty()) {
                success = false;
                break;
            }
            
            BinaryNode* l = s.top();
            s.pop();
            
            // create node with operator as element and
            // operands as children then push to stack
            n = new BinaryNode(token, l, r);
            s.push(n);
        }
    }
    
    if(s.size() != 1)
        success = false;
    
    if(success)
        root = s.top();
    else cout << "Wrong postfix expression" << endl;
}


BET::BET(const BET& rhs) : root{nullptr}
{ root = clone(rhs.root); }


BET::~BET()
{ makeEmpty(root); }


///////////////////////////////////////////////////////
////////////// public member functions ////////////////
///////////////////////////////////////////////////////


bool BET::buildFromPostfix(const string postfix) {
    
    string token;
    istringstream ss(postfix);
    
    bool success = true;
    
    stack<BinaryNode*> s;
    
    BinaryNode* n;
    
    if(!empty())
        makeEmpty(root);
    
    while(ss >> token) {
        if(!is_op(token)) {
            // create node with operand as element
            // and push to stack
            n = new BinaryNode(token);
            s.push(n);
        }
        
        else {
            // get two operands
            if(s.empty()) {
                success = false;
                break;
            }
            
            BinaryNode* r = s.top();
            s.pop();
            
            if(s.empty()) {
                success = false;
                break;
            }
            
            BinaryNode* l = s.top();
            s.pop();
            
            // create node with operator as element and
            // operands as children then push to stack
            n = new BinaryNode(token, l, r);
            s.push(n);
        }
    }
    
    if(s.size() != 1)
        success = false;
    
    if(success)
        root = s.top();
    else cout << "Wrong postfix expression" << endl;
    
    return success;
}


const BET& BET::operator= (const BET& rhs) {
    
    if(this != &rhs) {
        makeEmpty(this->root);
        root = clone(rhs.root);
    }
    
    return *this;
}


void BET::printInfixExpression()
{ printInfixExpression(root); cout << endl; }


void BET::printPostfixExpression()
{ printPostfixExpression(root); cout << endl; }


size_t BET::size()
{ return(size(root)); }


size_t BET::leaf_nodes()
{ return(leaf_nodes(root)); }


bool BET::empty()
{ return(root == nullptr); }


///////////////////////////////////////////////////////
///////////// private member functions ////////////////
///////////////////////////////////////////////////////


void BET::printInfixExpression(BinaryNode *n) {
    
    if(n != nullptr) {
        
        // if precedence of element is greater than children, subtree needs parens
        if(is_op(n->element) && preced(n->left->element) < preced(n->element)) {
            cout << "( ";
            printInfixExpression(n->left);
            cout << ") ";
        }
        
        else printInfixExpression(n->left);
        
        cout << n->element << " ";

        if(is_op(n->element) && preced(n->element) >= preced(n->right->element)) {
            cout << "( ";
            printInfixExpression(n->right);
            cout << ") ";
        }
        
        else printInfixExpression(n->right);
    }
}


void BET::makeEmpty(BinaryNode* &t) {
    
    if(t != nullptr) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    
    t = nullptr;
}


BET::BinaryNode* BET::clone(BinaryNode *t) const {
    
    if(t == nullptr)
        return nullptr;
    else
        return new BinaryNode { t->element, clone(t->left), clone(t->right) };
}


void BET::printPostfixExpression(BinaryNode *n) {
    
    if(n != nullptr) {
        if(is_op(n->element)) {
            printPostfixExpression(n->left);
            printPostfixExpression(n->right);
            cout << n->element << " ";
        }
        
        else cout << n->element << " ";
    }
}

size_t BET::size(BinaryNode *t) {
    
    if(t == nullptr)
        return 0;
    return(size(t->left) + size(t->right) + 1);
}


size_t BET::leaf_nodes(BinaryNode *t) {
    
    if(t == nullptr)
        return 0;
    if(t->left == nullptr && t->right == nullptr)
        return 1;
    return(leaf_nodes(t->left) + leaf_nodes(t->right));
}

