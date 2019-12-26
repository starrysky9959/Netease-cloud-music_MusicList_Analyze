#include "workspace.h"
using namespace std;

Workspace::Workspace(){
    musicList.reserve(500);
    INPUT_PATH = "assert/lyrics/test_2.txt";
    WORD_OUTPUT_PATH = "assert/output/word_output.txt";
    MUSIC_OUTPUT_PATH = "assert/output/music_output.txt";
    IGNORE_PATH = "assert/lyrics/ignore.txt";
    
    //对要忽略的单词建立Trie树
    ifstream ignoreFile;
    ignoreFile.open(IGNORE_PATH, ios::in);
    if (!ignoreFile) {
        cout << "文件不存在\n";
        return;
    }
    else {
        cout << "打开成功\n";
    }

    while (!ignoreFile.eof()) {
        string buffer;
        getline(ignoreFile, buffer, '\n');
        //ignoreTree.addNode(buffer);
    }
}

Workspace::~Workspace(){
}

//流程控制
void Workspace::run(string target) {
    if (!input())
        return;
    if (!target.empty())
        cout << "要查找的单词的词频为：" << T.searchNode(target) << endl;
    printf("--------------------\n");
    T.preOrder();
    output(target);
    //T.printHotWords();
}

//从输入文件分离出单词、曲目名信息，并建立Trie树
bool Workspace::input() {
    ifstream inFile;
    ofstream outFile;
    inFile.open(INPUT_PATH, ios::in);
    outFile.open(WORD_OUTPUT_PATH, ios::out);
    if (!inFile) {
        cout << "文件不存在\n";
        return false;
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
            if (!musicName.empty())
                musicList.emplace_back(musicName);            
        }        
    }
    inFile.close();
    outFile.close();
    return true;
}

void Workspace::output(string target) {
    ofstream output;
    output.open(MUSIC_OUTPUT_PATH, ios::out);
    //曲目列表
    for (vector<string>::iterator it = musicList.begin(); it != musicList.end(); it++)
        output << *it;
    output.close();
    output.open(WORD_OUTPUT_PATH, ios::out);   
    //单词总数
    //output << T.searchNode(target) << endl;
    output << T.hotwordList.size() << endl;
    //单词及曲目列表
    for (auto it : T.hotwordList) {
        output << it.frequency << endl;
        output << it.word << endl;
        for (auto _it : it.musicList)
            output << _it;
    }
}
