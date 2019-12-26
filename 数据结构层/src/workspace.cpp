#include "workspace.h"
using namespace std;

Workspace::Workspace(){
    musicList.reserve(500);
    INPUT_PATH = "assert/lyrics/test_2.txt";
    WORD_OUTPUT_PATH = "assert/output/word_output.txt";
    MUSIC_OUTPUT_PATH = "assert/output/music_output.txt";
    IGNORE_PATH = "assert/lyrics/ignore.txt";
    
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
        getline(ignoreFile, buffer, '\n');
        //ignoreTree.addNode(buffer);
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
        //while (!((len >= MAX_WORD_LEN) && (buffer[0] == '*'))) {
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
                    //word += ch;
                    word.push_back(ch);
                }
                else if ((ch >= 'A') && (ch <= 'Z')) {
                    //word += ch + 32;
                    word.push_back(ch + 32);
                }
                else{   //������󳤶ȵĲ��ֲ�����
                    if (word.size() >= MIN_WORD_LEN) {                        
                        //���ж��Ƿ�Ҫ����
                        //�µ�������µ�Ƶ�ʺ���Ŀ������ֻ����Ƶ��
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
    //��Ŀ�б�
    for (vector<string>::iterator it = musicList.begin(); it != musicList.end(); it++)
        output << *it;
    output.close();
    output.open(WORD_OUTPUT_PATH, ios::out);   
    //��������
    //output << T.searchNode(target) << endl;
    output << T.hotwordList.size() << endl;
    //���ʼ���Ŀ�б�
    for (auto it : T.hotwordList) {
        output << it.frequency << endl;
        output << it.word << endl;
        for (auto _it : it.musicList)
            output << _it;
    }
}
