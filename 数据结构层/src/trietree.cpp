#include "trietree.h"
using namespace std;

bool myrule(HotWord w1, HotWord w2) {
    if (w1.frequency > w2.frequency)
        return true;
    else    
        return false;    
}

TrieTree::TrieTree() {
    root = new Node();
    hotwordList.reserve(LIST_SIZE);
}

TrieTree::~TrieTree() {
    delete root;
}

void TrieTree::addNode(string word) {
    Node *p = root;
    int index;
    for (int i = 0; i < word.length(); ++i) {
        index = word[i] - 'a';
        if (p->next[index] == nullptr) {
            p->next[index] = new Node();
        }
        p = p->next[index];
    }
    p->count++;
    p->isWord = true;
}

//查到单词，返回词频，无该单词则返回0
int TrieTree::searchNode(string word) {
    Node *p = root;
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

void TrieTree::_preOrder(Node *head, int depth, char word[MAX_WORD_LEN + 2]) {
    if (head->isWord) {
        word[depth] = '\0';
        if (hotwordList.size() < LIST_SIZE) {
            HotWord tempword(word, head->count);
            hotwordList.emplace_back(tempword);
        }
        else {
            sort(hotwordList.begin(), hotwordList.end(), myrule);
            if (head->count > hotwordList.back().frequency) {
                hotwordList.pop_back();
                HotWord tempword(word, head->count);
                hotwordList.emplace_back(tempword);
            }
        }
        //printf("%s%5d\n", word, head->count);     
    }
    for (int i = 0; i < TREE_SIZE; ++i)
        if (head->next[i] != nullptr) {
            word[depth] = i + 'a';
            _preOrder(head->next[i], depth + 1, word);
        }
}

void TrieTree::preOrder() {
    char word[MAX_WORD_LEN + 2];
    _preOrder(root, 0, word);
}

void TrieTree::printHotWords() {
    for (int i = 0; i < hotwordList.size(); ++i) {
        cout<<hotwordList[i].word<<"     "<<hotwordList[i].frequency<<endl;
    }
}