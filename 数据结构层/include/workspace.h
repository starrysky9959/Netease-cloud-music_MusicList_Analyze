#pragma once
#include "trietree.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>

#define MAX_BUFFER_LEN 1024

class Workspace
{
private:
    TrieTree T;             //全部单词的Trie树
    TrieTree ignoreTree;    //要忽略的单词
    //GDB和g++路径不一样
    //GDB路径:"assert/lyrics/lyrics.txt"
    //g++路径
    std::string INPUT_PATH;
    std::string OUTPUT_PATH;
    std::string IGNORE_PATH;
public:
    Workspace();
    ~Workspace();
    void run();

private:
    void input(TrieTree &T);
};

