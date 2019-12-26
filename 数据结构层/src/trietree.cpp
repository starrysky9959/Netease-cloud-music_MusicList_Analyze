#include "trietree.h"
using namespace std;

bool myrule(HotWord w1, HotWord w2) {
    if (w1.frequency > w2.frequency)
        return true;
    else    
        return false;    
}

TrieTree::TrieTree() {
    root = new WordNode();
    hotwordList.reserve(HOTWORDLIST_SIZE * 100);
}

TrieTree::~TrieTree() {
    delete root;
}

//添加单词结点
void TrieTree::addNode(string word) {
    WordNode *p = root;
    int index;
    for (int i = 0; i < word.length(); ++i) {
        index = word[i] - 'a';
        if (p->next[index] == nullptr) {
            p->next[index] = new WordNode();
        }
        p = p->next[index];
    }
    p->count++;
    p->isWord = true;
    wordSize++;
}

//添加单词结点且更新曲目索引表
void TrieTree::addNode(string word, const string musicName) {
    WordNode *p = root;
    int index;
    for (int i = 0; i < word.length(); ++i) {
        index = word[i] - 'a';
        if (p->next[index] == nullptr) {
            p->next[index] = new WordNode();
        }
        p = p->next[index];
    }
    p->count++;    
    p->musicList.emplace_back(musicName);
    p->isWord = true;
    wordSize++;
}



//查到单词，返回词频，无该单词则返回0
int TrieTree::searchNode(string word) {
    WordNode *p = root;
    int index;
    for (int i = 0; i < word.length(); ++i) {
        index = word[i] - 'a';
        if (p->next[index] == nullptr) {
            return 0;
        }
        p = p->next[index];
    }
    return p->count;
}

//前序遍历，可按字典序输出整棵树
//同时记录所有单词
void TrieTree::_preOrder(WordNode *head, string &word) {
    if (head == nullptr)
        return;
    if (head->isWord) {
        HotWord tempword(word, head->count);
        tempword.setMusicList(head->musicList);
        hotwordList.emplace_back(tempword);
        //cout << word << "    " << head->count<<endl;
        //printf("%s%5d\n", word, head->count);     
    }
    for (int i = 0; i < TREE_SIZE; ++i)
        if (head->next[i] != nullptr) {
            word.push_back(i + 'a');
            _preOrder(head->next[i], word);
            word.pop_back();
        }
}

//前序遍历的入口函数
void TrieTree::preOrder() {
    hotwordList.clear();
    string word;    
    _preOrder(root, word);
    sort(hotwordList.begin(), hotwordList.end(), myrule);
}

//
//void TrieTree::_clear(WordNode *head) {
//    for (int i = 0; i < TREE_SIZE; ++i)
//        if (head->next[i] != nullptr) 
//            _clear(head->next[i]);                  
//    delete head;
//}
//
//void TrieTree::clear() {
//    for (int i = 0; i < TREE_SIZE; ++i)
//        if (root->next[i] != nullptr) 
//            _clear(root->next[i]);            
//}

//打印高频单词
void TrieTree::printHotWords() {
    for (int i = 0; i < HOTWORDLIST_SIZE; ++i) {
        HotWord temp = hotwordList[i];
        //cout<<temp.word<<"     "<<temp.frequency<<endl;
        //cout << "出现曲目：\n";
        for (size_t j = 0; j < temp.musicList.size(); ++j) {
            //cout << temp.musicList[j] << endl;
        }
    }
}
