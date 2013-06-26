//
//  SkipList.h
//  DataStructure
//
//  Created by Wang Chengwen on 13-6-3.
//  Copyright (c) 2013年 user. All rights reserved.
//

#ifndef __DataStructure__SkipList__
#define __DataStructure__SkipList__

#include <iostream>
#include "random.h"


using namespace std;

typedef struct Node {
    
public:
    Node(int level, int key, string value)
    :key(key), value(value)
    {
        forward = new struct Node*[level];
        for(int i = 0; i < level; i++)
        {
            forward[i] = NULL;
        }
        cout << "size: " << sizeof(*forward) << endl;
    }
    int key;
    string value;
    struct Node **forward;
}Node;

class SkipList {
    Random rnd_;
    int randLevel();
public:
    SkipList();
    ~SkipList();
    Node *head;
    int level;
    int length;
    
public:
    string Search(int key);
    void Insert(int key, string value);
    bool Delete(int key);
};



void testSkipList();

#endif /* defined(__DataStructure__SkipList__) */
