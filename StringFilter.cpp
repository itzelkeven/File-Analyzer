#include "StringFilter.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

// Class Constructor
StringFilter::StringFilter() {
    _uniqueWords = vector<string>();
    _wordCounts = vector<unsigned int>();
    _totalWordCount = 0;
}

// Reads through file and adds all words found in the file and also updates the total word count
void StringFilter::addWords(vector<string> allWords) {
    _totalWordCount = allWords.size();
    _uniqueWords.push_back(allWords.at(0));
    _wordCounts.push_back(1);
    for (int i = 1; i < (int)allWords.size(); i++) {
        bool isUnique = true;
        for (int j = 0; j < (int)_uniqueWords.size(); j++) {
            if (allWords[i] == _uniqueWords[j]) {
                isUnique = false;
                _wordCounts[j] += 1;
                break;
            }
        }
        if (isUnique) {
            _uniqueWords.push_back(allWords[i]);
            _wordCounts.push_back(1);
        }
        
    }
}

void StringFilter::printUniqueWordCounts(ostream& output) {
    string maxWord;
    int maxWordLength(0), maxCount(0), maxNum(0);

    for(int i = 0; i < (int)_uniqueWords.size(); i++){
        if((int)_uniqueWords[i].length() > maxWordLength){
            maxWordLength = _uniqueWords[i].length();
        }
    }

    // Find the maximum number of digits in the largest number overall
    for (int i = 0; i < (int)_wordCounts.size(); i++){
        if((int)_wordCounts[i] > maxCount){
            maxCount = _wordCounts[i];
        }
    }

    maxNum = to_string(maxCount).length();


    // Setup formatting for displaying back to the user in alphabetical order
    string tempWord;
    int tempInt;
    for (int i = 0; i < (int)_uniqueWords.size(); i++){
        for (int j = 0; j < (int)_uniqueWords.size() - i - 1; j++){
            if (_uniqueWords[j] > _uniqueWords[j + 1]) {
                // Swap words
                tempWord = _uniqueWords[j];
                _uniqueWords[j] = _uniqueWords[j + 1];
                _uniqueWords[j + 1] = tempWord;

                // Swap corresponding integers
                tempInt = _wordCounts[j];
                _wordCounts[j] = _wordCounts[j + 1];
                _wordCounts[j + 1] = tempInt;
            }
        }
    }
    
    // Display information to the user
    for (int i = 0; i < (int)_uniqueWords.size(); i++) {
        output << setw(maxWordLength) << left << _uniqueWords[i] << " : " << right << setw(maxNum) << _wordCounts[i] << endl;
    }
}


void StringFilter::printUniqueWordStats(ostream& output) {
    unsigned int maxCount = 0, minCount = 1000000;
    int maxLength = 0, minLength = 0,maxNumLen = 0;
    string maxWord, minWord;
    // Iterate through the unique words in _uniqueWords and store statistics about the words
    for (unsigned int i = 0; i < _uniqueWords.size(); i++) {
        if (_wordCounts[i] > maxCount) {
            maxCount = _wordCounts[i];
            maxWord = _uniqueWords[i];
        }
        if (_wordCounts[i] < minCount) {
            minCount = _wordCounts[i];
            minWord = _uniqueWords[i];
        }
    }
    // Set Up and compare which words have the greater amount of characters to setup format
    if (maxWord.length() > minWord.length()) {
        maxLength = maxWord.length();
    }
    else {
        maxLength = minWord.length();
    }

    // Set RHS parameters for proper formatting using count of words
    if(to_string(maxCount).length() > to_string(minCount).length()){
        maxNumLen = to_string(maxCount).length();
    } 
    else {
        maxNumLen = to_string(minCount).length();
    }

    // Calculate min and max percentages of least and most frequent words and display them to the user
    double maxPercent = ((double)maxCount / (double)_totalWordCount) * 100;
    double minPercent = ((double)minCount / (double)_totalWordCount) * 100;
    output << " Most Frequent Word: " << left << setw(maxLength + 1) << maxWord << " " << right << setw(maxNumLen) << maxCount << " (" << fixed << setprecision(3) << maxPercent << "%)" <<endl;
    output << "Least Frequent Word: " << left << setw(maxLength + 1) << minWord << " " << right << setw(maxNumLen) << minCount << " (" << fixed << setprecision(3) << minPercent << "%)" << endl;
}

// Returns _uniqueWords vector to be able to use it within the program.
vector<string> StringFilter::getUniqueWords() {
    return _uniqueWords;
}