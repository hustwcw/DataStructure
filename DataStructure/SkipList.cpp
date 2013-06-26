//
//  SkipList.cpp
//  DataStructure
//
//  Created by Wang Chengwen on 13-6-3.
//  Copyright (c) 2013年 user. All rights reserved.
//

#include "SkipList.h"

#define kMaxLevel   12

SkipList::SkipList()
:rnd_(0xdeadbeef),
level(0),
length(0),
head(new Node(kMaxLevel, 0, ""))
{
}

SkipList::~SkipList()
{
    delete head;
}


string SkipList::Search(int key)
{
    Node *x = this->head;
    for (int i = this->level-1; i >= 0; i--) {
        while (x && x->forward[i] && x->forward[i]->key < key) {
            x = x->forward[i];
        }
    }
    x = x->forward[0];
    if (x && x->key == key) {
        return x->value;
    }
    else
    {
        return string("");
    }
}

void SkipList::Insert(int key, string value)
{
    Node *update[kMaxLevel];
    Node *x = this->head;
    for (int i = this->level-1; i >= 0; i--) {
        while (x && x->forward[i] && x->forward[i]->key < key) {
            x = x->forward[i];
        }
        update[i] = x;
    }
    x = x->forward[0];
    if (x && x->key == key) {
        x->value = value;
    }
    else
    {
        int newLevel = randLevel();
        if (newLevel > this->level) {
            for (int i = this->level; i < newLevel; i++) {
                update[i] = this->head;
            }
            this->level = newLevel;
        }
        x = new Node(newLevel, key, value);
        for (int i = 0; i < newLevel; i++) {
            x->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = x;
        }
        this->length++;
    }
}

bool SkipList::Delete(int key)
{
    
}


int SkipList::randLevel()
{
    static const unsigned int kBranching = 4;
    int level = 1;
    while (level < kMaxLevel && ((rnd_.Next() % kBranching) == 0)) {
        level++;
    }
    
    return level;
}



void testSkipList()
{
    SkipList skiplist;
    Random random(0xdeadbeef);
    clock_t start = clock();
    for (int i = 0; i < 1000; i++) {
        int rand = random.Next();
        //        stringstream ss;
        //        ss << rand << "value";
        skiplist.Insert(rand, "value");
    }
    cout << clock() - start << endl;
    cout << "length: " << skiplist.length << endl;
    for (int i = 1990; i < 2000; i++) {
        string value = skiplist.Search(i);
        if (value.length()) {
            cout << i << endl;
        }
        else
        {
            //            cout << "not found" << endl;
        }
    }
}