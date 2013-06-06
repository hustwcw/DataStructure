//
//  main.cpp
//  DataStructure
//
//  Created by Wang Chengwen on 13-6-3.
//  Copyright (c) 2013年 user. All rights reserved.
//

#include <iostream>
#include "random.h"
#include "SkipList.h"
#include <sstream>
#include <string>
#include "ctime"

using namespace std;



int main(int argc, const char * argv[])
{
    SkipList skiplist;
    Random random(0xdeadbeef);
    clock_t start = clock();
    for (int i = 0; i < 10000; i++) {
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
    

    return 0;
}

