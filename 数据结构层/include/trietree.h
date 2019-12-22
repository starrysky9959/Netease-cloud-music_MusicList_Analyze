#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "hotword.h"

#define TREE_SIZE 26
#define MAX_WORD_LEN 20
#define MIN_WORD_LEN 3

class Node{
public:
    int count;              //公共前缀子串词频
    bool isWord;            //到达该结点时是否是一个完整的单词
    Node *next[TREE_SIZE];  //后继结点
public:
    Node(){
        count = 0;
        isWord = false;
        for (size_t i = 0; i < TREE_SIZE; ++i)
            next[i] = nullptr;
    }
};

class TrieTree
{
private:
    Node *root;
    const int LIST_SIZE = 10;
    std::vector<HotWord> hotwordList;
public:
    
public:
    TrieTree();
    ~TrieTree();
    void addNode(std::string word);
    int searchNode(std::string word);
    void _preOrder(Node *head, int depth, char word[MAX_WORD_LEN + 2]);
    void preOrder();
    void printHotWords();
};