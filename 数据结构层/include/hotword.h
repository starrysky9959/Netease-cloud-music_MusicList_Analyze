#pragma once
#include <string>

class HotWord{
public:
    std::string word;
    int frequency;    
public:
    HotWord(){
        word = "\0";
        frequency = 0;      
    }

    HotWord(std::string word, int frequency) {
        this->word = word;
        this->frequency = frequency;
    }

    ~HotWord() {
    }
};



