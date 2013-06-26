//
//  BinaryTree.cpp
//  DataStructure
//
//  Created by JTangWang on 13-6-26.
//  Copyright (c) 2013年 user. All rights reserved.
//

#include "BinaryTree.h"


using namespace std;


// 非递归中序遍历二叉树，不使用栈
void Tree_Print(tree *T)
{
	node *t = T->root;
	while(t)
    {
        while (t->left)
        {
            t = t->left;
        }
        cout << t->key << " ";
        if (t->right)
        {
            t = t->right;
            continue;
        }
        // 输出当前节点后返回父节点
        while(1)
        {
            // 如果是从左节点返回到父节点，则需要输出父节点，并将右节点设为当前需要遍历的节点，如果右节点为空则需要返回到父节点；
            // 如果是从右节点返回到父节点，则说明父节点已经输出，
            if(t == t->parent->left && t->parent->right)
            {
                cout<<t->parent->key<<' ';
                t = t->parent->right;
                break;
            }
            if(t == t->parent->left && t->parent->right == NULL)
                cout<<t->parent->key<<' ';
            
            t = t->parent;
            if(t == T->root)
            {
                cout<<endl;
                return;
            }
        }
    }
}

/*input:0=NIL
 12 7 3
 15 8 0
 4 10 0
 10 5 9
 2 0 0
 18 1 4
 7 0 0
 14 6 2
 21 0 0
 5 0 0
 */
void testBinaryTree()
{
    int i;
    int nodeData[11][3]={0,0,0,
        12, 7, 3,
        15, 8, 0,
        4, 10, 0,
        10, 5, 9,
        2, 0, 0,
        18, 1, 4,
        7, 0, 0,
        14, 6, 2,
        21, 0, 0,
        5, 0, 0};
    node A[11];
    for(i = 1; i <= 10; i++)
    {
        int key, left, right;
        key = nodeData[i][0];
        left = nodeData[i][1];
        right = nodeData[i][2];
        A[i].key = key;
        if(left)
        {
            A[i].left = &A[left];
            A[left].parent = &A[i];
        }
        else
        {
            A[i].left = NULL;
        }
        if(right)
        {
            A[i].right = &A[right];
            A[right].parent = &A[i];
        }
        else
        {
            A[i].right = NULL;
        }
    }
    tree *T = new tree();
    T->root = &A[6];
    Tree_Print(T);
}
