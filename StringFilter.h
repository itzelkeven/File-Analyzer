#ifndef STRINGFILTER_H
#define STRINGFILTER_H

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <istream>
#include <ostream>
using namespace std;

class StringFilter {
private:
    vector<string> _uniqueWords;
    vector<unsigned int> _wordCounts;
    unsigned int _totalWordCount;

public:
    StringFilter();
    void addWords(vector<string>);
    void printUniqueWordStats(ostream&);
    void printUniqueWordCounts(ostream&);
    vector<string> getUniqueWords();
};




#endif // STRINGFILTER_H