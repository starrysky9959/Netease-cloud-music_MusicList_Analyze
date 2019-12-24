#include "workspace.h"
using namespace std;

Workspace::Workspace(){
    INPUT_PATH = "assert/lyrics/test_2.txt";
    OUTPUT_PATH = "assert/lyrics/output.txt";
    IGNORE_PATH = "assert/lyrics/ignore.txt";
    
    //对要忽略的单词建立Trie树
    ifstream ignoreFile;
    ignoreFile.open(IGNORE_PATH, ios::in);
    if (!ignoreFile) {
        cout << "文件不存在\n";
    }
    else {
        cout << "打开成功\n";
    }

    while (!ignoreFile.eof()) {
        string buffer;
        getline(ignoreFile, buffer, '\n');
        ignoreTree.addNode(buffer);
    }
}


Workspace::~Workspace(){
}

//流程控制
void Workspace::run() {
    input(T);
    //T.preOrder();
    //string target;
    //cin >> target;
    //T.addNode(target);
    //cout<<T.searchNode(target)<<endl;
    //T.preOrder();
    printf("--------------------\n");
    T.preOrder();
    T.printHotWords();
}

//从输入文件分离出单词、曲目名信息，并建立Trie树
void Workspace::input(TrieTree &T) {
    ifstream inFile;
    ofstream outFile;
    inFile.open(INPUT_PATH, ios::in);
    outFile.open(OUTPUT_PATH, ios::out);
    if (!inFile) {
        cout << "文件不存在\n";
    }
    else {
        cout << "打开成功\n";
    }
  
    bool flag = false;
    char ch;    
    char buffer[MAX_BUFFER_LEN];
    string musicName = "";       

    while (!inFile.eof()) {
        TrieTree current;
        inFile.getline(buffer, MAX_BUFFER_LEN);
        size_t len = strlen(buffer);
        //while (!((len >= MAX_WORD_LEN) && (buffer[0] == '*'))) {
        while (buffer[0] != '*') {
            int index = 0;
            string word;
            for (int i = 0; i < len; ++i) {
                ch = buffer[i];
                //超出单词长度上限不再记录，直到遇到下一个分隔符
                if (flag &&
                    (((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z'))))
                    continue;
                flag = false;
                //保留小写
                if ((ch >= 'a') && (ch <= 'z')) {
                    //word += ch;
                    word.push_back(ch);
                }
                else if ((ch >= 'A') && (ch <= 'Z')) {
                    //word += ch + 32;
                    word.push_back(ch + 32);
                }
                else{   //超出最大长度的部分不保留
                    if (word.size() >= MIN_WORD_LEN) {
                        //word[index] = '\0';                    
                        outFile << word << endl;

                        //cout << word << endl;

                        //先判断是否要忽略
                        //新单词则更新的频率和曲目，否则只更新频率
                        if (ignoreTree.searchNode(word) == 0) {
                            if (current.searchNode(word) == 0) {
                                current.addNode(word);
                                T.addNode(word, musicName);
                            }
                            else {
                                T.addNode(word);
                            }
                        }
                        word.clear();
                    }
                    //单词分隔
                    index = 0;
                }
                //当前单词已超过指定长度，超出部分忽略
                if (index >= MAX_WORD_LEN)
                    flag = true;
            }

            if (index >= MIN_WORD_LEN) {
                //先判断是否要忽略
                //新单词则更新的频率和曲目，否则只更新频率
                if (ignoreTree.searchNode(word) == 0) {
                    if (current.searchNode(word) == 0) {
                        current.addNode(word);
                        T.addNode(word, musicName);
                    }
                    else {
                        T.addNode(word);
                    }
                }
            }
            inFile.getline(buffer, MAX_BUFFER_LEN);
            size_t len = strlen(buffer);
        }

        if (!inFile.eof()) {
            getline(inFile, musicName, '\n');
            cout << musicName << endl;
        }        
    }
    inFile.close();
    outFile.close();
}
