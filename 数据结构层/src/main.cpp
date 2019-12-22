#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip>
#include <time.h>
#include "trietree.h"

using namespace std;

#define MAX_BUFFER_LEN 2048

TrieTree T;

void input(){
    ifstream inFile;
    ofstream outFile;
    //GDB和g++路径不一样
    //GDB路径
    // inFile.open("assert/lyrics/lyrics.txt", ios::in);
    //g++路径
    inFile.open("assert/lyrics/lyrics.txt", ios::in);
    outFile.open("assert/lyrics/output.txt", ios::out);
    if (!inFile){
        cout<<"文件不存在\n";
    }else{
        cout<<"打开成功\n"; 
    }
    char ch;
    /*int max = 0;*/
    char buffer[MAX_BUFFER_LEN];
    while (!inFile.eof()){
        inFile.getline(buffer, MAX_BUFFER_LEN);
        int len = strlen(buffer);
        int index = 0;
        char word[MAX_WORD_LEN + 1];
        for (int i = 0; i < len; ++i){
            ch = buffer[i];
            //保留小写
            if ((ch >= 'a') && (ch <= 'z')){
                word[index++] = ch;
            }else if ((ch >= 'A') && (ch <= 'Z')){
                word[index++] = ch + 32;   
            }
            else{   //超出最大长度的部分不保留
                if (index >= MIN_WORD_LEN){
                    if (index > MAX_WORD_LEN)
                        word[MAX_WORD_LEN] = '\0';
                    else
                        word[index] = '\0';   
                     outFile<<word<<endl;
                     T.addNode(word);
                }
                index = 0;            
            } 
        }
        if (index >= MIN_WORD_LEN){
            if (index > MAX_WORD_LEN)
                word[MAX_WORD_LEN] = '\0';
            else
                word[index] = '\0';   
             outFile<<word<<endl;
            T.addNode(word);
        }    
    }   
    inFile.close();    
}
int main(){

    
    string target;
    //cin>>target;
    clock_t begin = clock();
    input();
    //cout<<T.searchNode(target)<<endl;
    T.preOrder();
    printf("--------------------\n");
    T.printHotWords();
    clock_t end = clock();
    cout<<static_cast<double>(end - begin) / CLOCKS_PER_SEC * 1000<<"ms"<<endl;
    system("pause");
}