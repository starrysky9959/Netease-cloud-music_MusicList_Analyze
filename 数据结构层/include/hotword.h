#pragma once
#include <string>
#include <vector>

#define MAX_MUSIC_LEN 500

class AppearedMusic {
public:
    int index;
    int count;
public:
    AppearedMusic(int index) {
        this->index = index;
        count = 1;

    }
};

class HotWord{
public:
    std::string word;
    int frequency;
    std::vector<AppearedMusic> appearedMusics;
public:
    HotWord(){
        word = "\0";
        frequency = 0;      
        appearedMusics.reserve(MAX_MUSIC_LEN);
    }

    HotWord(std::string word, int frequency) {
        this->word = word;
        this->frequency = frequency;   
        appearedMusics.reserve(MAX_MUSIC_LEN);
    }

    ~HotWord() {
    }

    void setMusicList(std::vector<AppearedMusic> appeared) {
        for (int i = 0; i < appeared.size(); ++i) {
            appearedMusics.push_back(appeared[i]);
        }
    }

};