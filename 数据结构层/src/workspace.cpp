#include "..\include\workspace.h"
#include <Windows.h>
#include <codecvt>
using namespace std;

Workspace::Workspace(){
    musicList.reserve(500);
    INPUT_PATH = "assert/lyrics/test_2.txt";
    WORD_OUTPUT_PATH = "assert/output/word_output.txt";
    MUSIC_OUTPUT_PATH = "assert/output/music_output.txt";
    INFO_PATH = "assert/output/info_output.txt";
    IGNORE_PATH = "assert/lyrics/Trash.txt";
    
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
        string word;
        getline(ignoreFile, buffer, ' ');
        for (int i = 0; i < buffer.size(); ++i) {
            char ch = buffer[i];
            //保留小写
            if ((ch >= 'a') && (ch <= 'z')) {
                word.push_back(ch);
            }
            else if ((ch >= 'A') && (ch <= 'Z')) {
                word.push_back(ch + 32);
            }
            else {
                break;
            }
        }
        if (word.size() >= 1) {
            ignoreTree.addNode(word);
            //cout << word << endl;
        }
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
                    word.push_back(ch);
                }
                else if ((ch >= 'A') && (ch <= 'Z')) {
                    word.push_back(ch + 32);
                }
                else{   //超出最大长度的部分不保留
                    if (word.size() >= MIN_WORD_LEN) {                        
                        //先判断是否要忽略
                        //新单词则更新的频率和曲目，否则只更新频率
                        if (ignoreTree.searchNode(word) == 0) {                         
                            current.addNode(word);
                            //cout << musicList.size() << endl;
                            T.addNode(word, musicList.size());
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
                    current.addNode(word);
                    T.addNode(word, musicList.size());
                }
            }

            if (!inFile.eof()) {
                inFile.getline(buffer, MAX_BUFFER_LEN);
                size_t len = strlen(buffer);
            }
            else
            {
                break;
            }
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

    //输出曲目列表
    output.open(MUSIC_OUTPUT_PATH, ios::out);
    for (vector<string>::iterator it = musicList.begin(); it != musicList.end(); it++)
        output << *it;
    output.close();

    //输出单词及曲目列表

    output.open(WORD_OUTPUT_PATH, ios::out);         
    for (auto it : T.hotwordList) {
        output << it.frequency << endl;
        output << it.word << endl;
        for (vector<AppearedMusic>::iterator i = it.appearedMusics.begin(); i != it.appearedMusics.end(); ++i) {
            output << i->count << " " << musicList.at(i->index - 1);
            
        }
    }
    output.close();

    //输出统计信息
    output.open(INFO_PATH, ios::out);
    //output << T.searchNode(target) << endl;
    //output << "统计中忽略长度小于3的单词和所有非英文字母" << endl;
    //std::wstring_convert<codecvt_utf8<wchar_t> > conv;
    //std::wstring str = L"总词数：" + to_wstring(T.getWordSize());    
    //string narrowStr = conv.to_bytes(str);
    //output << narrowStr << endl;
    //
    ////output << "总词数：" << T.getWordSize() << endl;
    //str = L"不重复的单词数：" + to_wstring(T.hotwordList.size());
    //narrowStr = conv.to_bytes(str);
    //output << narrowStr << endl;
    ////output << "不重复的单词数：" << T.hotwordList.size() << endl;
    ////output << "曲目数量：" << musicList.size() << endl;
    //str = L"曲目数量：" + to_wstring(musicList.size());
    //narrowStr = conv.to_bytes(str);
    //output << narrowStr << endl;
    ////output << "要忽略的单词数量：" << ignoreTree.getWordSize() << endl;
    //str = L"要忽略的单词数量：" + to_wstring(ignoreTree.getWordSize());
    //narrowStr = conv.to_bytes(str);
    //output << narrowStr << endl;
    //string str = "总词数：" + to_string(T.getWordSize());
    ////output << "总词数：" << T.getWordSize() << endl;
    //output << str << endl;
    //str = "不重复的单词数：" + to_string(T.hotwordList.size());
    //
    ////output << "不重复的单词数：" << T.hotwordList.size() << endl;
    //output << str << endl;
    ////output << "曲目数量：" << musicList.size() << endl;
    //str = "曲目数量：" + to_string(musicList.size());
    //output << str << endl;
    ////output << "要忽略的单词数量：" << ignoreTree.getWordSize() << endl;
    //str = "要忽略的单词数量：" + to_string(ignoreTree.getWordSize());
    //output << str << endl;
    output << T.getWordSize() << endl;
    output << T.hotwordList.size() << endl;
    output << musicList.size() << endl;
    output << ignoreTree.getWordSize() << endl;
    output.close();
}
