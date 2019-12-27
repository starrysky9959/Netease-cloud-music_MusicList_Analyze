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
    
    //��Ҫ���Եĵ��ʽ���Trie��
    ifstream ignoreFile;
    ignoreFile.open(IGNORE_PATH, ios::in);
    if (!ignoreFile) {
        cout << "�ļ�������\n";
        return;
    }
    else {
        cout << "�򿪳ɹ�\n";
    }

    while (!ignoreFile.eof()) {
        string buffer;
        string word;
        getline(ignoreFile, buffer, ' ');
        for (int i = 0; i < buffer.size(); ++i) {
            char ch = buffer[i];
            //����Сд
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

//���̿���
void Workspace::run(string target) {
    if (!input())
        return;
    if (!target.empty())
        cout << "Ҫ���ҵĵ��ʵĴ�ƵΪ��" << T.searchNode(target) << endl;
    printf("--------------------\n");
    T.preOrder();
    output(target);
    //T.printHotWords();
}

//�������ļ���������ʡ���Ŀ����Ϣ��������Trie��
bool Workspace::input() {
    ifstream inFile;
    ofstream outFile;
    inFile.open(INPUT_PATH, ios::in);
    outFile.open(WORD_OUTPUT_PATH, ios::out);
    if (!inFile) {
        cout << "�ļ�������\n";
        return false;
    }
    else {
        cout << "�򿪳ɹ�\n";
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
                //�������ʳ������޲��ټ�¼��ֱ��������һ���ָ���
                if (flag &&
                    (((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z'))))
                    continue;
                flag = false;
                //����Сд
                if ((ch >= 'a') && (ch <= 'z')) {
                    word.push_back(ch);
                }
                else if ((ch >= 'A') && (ch <= 'Z')) {
                    word.push_back(ch + 32);
                }
                else{   //������󳤶ȵĲ��ֲ�����
                    if (word.size() >= MIN_WORD_LEN) {                        
                        //���ж��Ƿ�Ҫ����
                        //�µ�������µ�Ƶ�ʺ���Ŀ������ֻ����Ƶ��
                        if (ignoreTree.searchNode(word) == 0) {                         
                            current.addNode(word);
                            //cout << musicList.size() << endl;
                            T.addNode(word, musicList.size());
                        }
                        word.clear();
                    }
                    //���ʷָ�
                    index = 0;
                }
                //��ǰ�����ѳ���ָ�����ȣ��������ֺ���
                if (index >= MAX_WORD_LEN)
                    flag = true;
            }

            if (index >= MIN_WORD_LEN) {
                //���ж��Ƿ�Ҫ����
                //�µ�������µ�Ƶ�ʺ���Ŀ������ֻ����Ƶ��
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

    //�����Ŀ�б�
    output.open(MUSIC_OUTPUT_PATH, ios::out);
    for (vector<string>::iterator it = musicList.begin(); it != musicList.end(); it++)
        output << *it;
    output.close();

    //������ʼ���Ŀ�б�

    output.open(WORD_OUTPUT_PATH, ios::out);         
    for (auto it : T.hotwordList) {
        output << it.frequency << endl;
        output << it.word << endl;
        for (vector<AppearedMusic>::iterator i = it.appearedMusics.begin(); i != it.appearedMusics.end(); ++i) {
            output << i->count << " " << musicList.at(i->index - 1);
            
        }
    }
    output.close();

    //���ͳ����Ϣ
    output.open(INFO_PATH, ios::out);
    //output << T.searchNode(target) << endl;
    //output << "ͳ���к��Գ���С��3�ĵ��ʺ����з�Ӣ����ĸ" << endl;
    //std::wstring_convert<codecvt_utf8<wchar_t> > conv;
    //std::wstring str = L"�ܴ�����" + to_wstring(T.getWordSize());    
    //string narrowStr = conv.to_bytes(str);
    //output << narrowStr << endl;
    //
    ////output << "�ܴ�����" << T.getWordSize() << endl;
    //str = L"���ظ��ĵ�������" + to_wstring(T.hotwordList.size());
    //narrowStr = conv.to_bytes(str);
    //output << narrowStr << endl;
    ////output << "���ظ��ĵ�������" << T.hotwordList.size() << endl;
    ////output << "��Ŀ������" << musicList.size() << endl;
    //str = L"��Ŀ������" + to_wstring(musicList.size());
    //narrowStr = conv.to_bytes(str);
    //output << narrowStr << endl;
    ////output << "Ҫ���Եĵ���������" << ignoreTree.getWordSize() << endl;
    //str = L"Ҫ���Եĵ���������" + to_wstring(ignoreTree.getWordSize());
    //narrowStr = conv.to_bytes(str);
    //output << narrowStr << endl;
    //string str = "�ܴ�����" + to_string(T.getWordSize());
    ////output << "�ܴ�����" << T.getWordSize() << endl;
    //output << str << endl;
    //str = "���ظ��ĵ�������" + to_string(T.hotwordList.size());
    //
    ////output << "���ظ��ĵ�������" << T.hotwordList.size() << endl;
    //output << str << endl;
    ////output << "��Ŀ������" << musicList.size() << endl;
    //str = "��Ŀ������" + to_string(musicList.size());
    //output << str << endl;
    ////output << "Ҫ���Եĵ���������" << ignoreTree.getWordSize() << endl;
    //str = "Ҫ���Եĵ���������" + to_string(ignoreTree.getWordSize());
    //output << str << endl;
    output << T.getWordSize() << endl;
    output << T.hotwordList.size() << endl;
    output << musicList.size() << endl;
    output << ignoreTree.getWordSize() << endl;
    output.close();
}
