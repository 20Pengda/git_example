#include <iostream>
#include <stdlib.h>
#include <cmath>
#include "SkipList.h"
using namespace std;
double SkipList::my_rand()
{
    s = (16807 * s) % 2147483647ULL;
    return (s + 0.0) / 2147483647ULL;
}

int SkipList::randomLevel()
{
    int result = 1;
    while (result < MAX_LEVEL && my_rand() < 1/exp(1))
    {
        ++result;
    }
    return result;
}
void SkipList::Insert(int key, int value)
{
    SKNode* update[MAX_LEVEL];
    SKNode* node = head;
    for(int i = level-1; i>=0; --i)
    {
        while(node->forwards[i]->key<key)
            node = node->forwards[i];
        update[i] = node;
    }
    node = node->forwards[0];
    if(node->key == key)
        node->val = value;
    else
    {
        int v = randomLevel();
        if(v>level)
        {
            for(int i = level; i<v; ++i)
                update[i] = head;
            level = v;
        }
        node = new SKNode(key,value,NORMAL);
        for(int i = 0; i<v; ++i)
        {
            node->forwards[i] = update[i]->forwards[i];
            update[i]->forwards[i] = node;
        }
    }
}

int SkipList::Search(int key)
{
    SKNode* node = head;
    int path = 0;
    for(int i = level-1; i>=0; --i)
    {
        while(node->forwards[i]->key < key)
        {
            if(node->type == HEAD){}
//                cout<<i+1<<",h ";
            else{}
 //               cout<<i+1<<","<<node->key<<" ";
            path += 1;
            node = node->forwards[i];
        }
        if(node->type == HEAD){}
//            cout<<i+1<<",h ";
        else{}
 //           cout<<i+1<<","<<node->key<<" ";
        path += 1;
    }

    node = node->forwards[0];
    path += 1;
    if(node->type == HEAD){}
 //       cout<<"1"<<",h ";
    else if(node->type == SKNodeType::NIL){}
 //       cout<<"1"<<",N ";
    else{}
  //      cout<<"1"<<","<<node->key<<" ";
    if(node->key == key){}
   //     cout<<node->val<<endl;
        else {}
 //       cout<<"Not Found"<<endl;
    return path;
}

void SkipList::Delete(int key)
{
    SKNode* update[MAX_LEVEL];
    SKNode* node = head;
    for(int i = level-1; i>=0; --i)
    {
        while(node->forwards[i]->key<key)
            node = node->forwards[i];
        update[i] = node;
    }
    node = node->forwards[0];
    if(node->key == key)
    {
        for(int i = 0; i<level; ++i)
        {
            if(update[i]->forwards[i]->key != key)
                break;
            update[i]->forwards[i] = node->forwards[i];
        }
        while(level>0 && head->forwards[level-1]->type == SKNodeType::NIL)
            --level;
    }
}

void SkipList::Display()
{
    for (int i = MAX_LEVEL - 1; i >= 0; --i)
    {
        std::cout << "Level " << i + 1 << ":h";
        SKNode *node = head->forwards[i];
        while (node->type != SKNodeType::NIL)
        {
            std::cout << "-->(" << node->key << "," << node->val << ")";
            node = node->forwards[i];
        }

        std::cout << "-->N" << std::endl;
    }
}
