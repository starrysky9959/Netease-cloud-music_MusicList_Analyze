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
    int count;              //����ǰ׺�Ӵ���Ƶ
    bool isWord;            //����ý��ʱ�Ƿ���һ�������ĵ���
    Node *next[TREE_SIZE];  //��̽��
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