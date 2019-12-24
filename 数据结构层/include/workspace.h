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
    TrieTree T;             //ȫ�����ʵ�Trie��
    TrieTree ignoreTree;    //Ҫ���Եĵ���
    //GDB��g++·����һ��
    //GDB·��:"assert/lyrics/lyrics.txt"
    //g++·��
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

