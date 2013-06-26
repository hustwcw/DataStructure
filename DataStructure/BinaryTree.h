//
//  BinaryTree.h
//  DataStructure
//
//  Created by JTangWang on 13-6-26.
//  Copyright (c) 2013年 user. All rights reserved.
//

#ifndef __DataStructure__BinaryTree__
#define __DataStructure__BinaryTree__

#include <iostream>
struct node
{
    int key;
    node *left;
    node *right;
    node *parent;
    node(){}
    node(int x):key(x),left(NULL),right(NULL){}
};


struct tree
{
    node *root;
    tree():root(NULL){}
};


void testBinaryTree();


#endif /* defined(__DataStructure__BinaryTree__) */
