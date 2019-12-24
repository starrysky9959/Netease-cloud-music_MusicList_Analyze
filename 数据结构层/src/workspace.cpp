#include "workspace.h"
using namespace std;

Workspace::Workspace(){
    INPUT_PATH = "assert/lyrics/test_2.txt";
    OUTPUT_PATH = "assert/lyrics/output.txt";
    IGNORE_PATH = "assert/lyrics/ignore.txt";
    
    //��Ҫ���Եĵ��ʽ���Trie��
    ifstream ignoreFile;
    ignoreFile.open(IGNORE_PATH, ios::in);
    if (!ignoreFile) {
        cout << "�ļ�������\n";
    }
    else {
        cout << "�򿪳ɹ�\n";
    }

    while (!ignoreFile.eof()) {
        string buffer;
        getline(ignoreFile, buffer, '\n');
        ignoreTree.addNode(buffer);
    }
}


Workspace::~Workspace(){
}

//���̿���
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

//�������ļ���������ʡ���Ŀ����Ϣ��������Trie��
void Workspace::input(TrieTree &T) {
    ifstream inFile;
    ofstream outFile;
    inFile.open(INPUT_PATH, ios::in);
    outFile.open(OUTPUT_PATH, ios::out);
    if (!inFile) {
        cout << "�ļ�������\n";
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
                        //word[index] = '\0';                    
                        outFile << word << endl;

                        //cout << word << endl;

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
            cout << musicName << endl;
        }        
    }
    inFile.close();
    outFile.close();
}
