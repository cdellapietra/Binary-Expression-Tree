//
//  bet.h
//  proj4
//
//  Created by Corey Della Pietra on 10/26/15.
//  Copyright (c) 2015 Corey Della Pietra. All rights reserved.
//

#ifndef proj4_bet_h
#define proj4_bet_h
#include <string>

using namespace std;

class BET {
public:
    
    BET();
    BET(const string postfix);
    BET(const BET&);
    ~BET();
    
    bool buildFromPostfix(const string postfix);
    const BET & operator= (const BET&);
    void printInfixExpression();
    void printPostfixExpression();
    size_t size();
    size_t leaf_nodes();
    bool empty();
    
private:
    
    struct BinaryNode {
        string element;
        BinaryNode *left;
        BinaryNode *right;
        
        BinaryNode(const string& ele, BinaryNode* l = nullptr, BinaryNode* r = nullptr)
            : element{ele}, left{l}, right{r} {}
        
        BinaryNode(string&& ele, BinaryNode* l = nullptr, BinaryNode* r = nullptr)
            : element{move(ele)}, left{l}, right{r} {}
    };
    
    BinaryNode* root;
    
    void printInfixExpression(BinaryNode *n);
    void makeEmpty(BinaryNode* &t);
    BinaryNode* clone(BinaryNode *t) const;
    void printPostfixExpression(BinaryNode *n);
    size_t size(BinaryNode *t);
    size_t leaf_nodes(BinaryNode *t);
    
};

#endif
