#ifndef STRINGCOUNTER_H
#define STRINGCOUNTER_H
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <istream>
#include <ostream>
using namespace std;

class StringCounter {
private:
    vector<string> _allWords;
    vector<unsigned int> _letterCounts;
    unsigned int _totalLetterCount;

public:
    StringCounter();
    void readAllWords(istream&, string);
    void printLetterCounts(ostream&);
    void printLetterStats(ostream&);
    vector<string> getAllWords();
};


#endif