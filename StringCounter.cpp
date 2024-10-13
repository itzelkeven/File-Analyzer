#include "StringCounter.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;


// Class Constructor
StringCounter::StringCounter(){
    _allWords = vector<string>();
    _letterCounts = vector<unsigned int>(26, 0);
    _totalLetterCount = 0;
}

/*Reads all words, skips punctuation, and adds it to the vector _allWords*/
void StringCounter::readAllWords(istream& input, string punct) {
    char c;
    string word;
    punct = c;
    /*Checks whether the character c is found within the string punctuation
         * If it is found, the expression evaluates to true
         * if not found, it evaluates to false.
         * skips punctutuion if found, capitlizes and adds character to string word */
    while (input.get(c)) {
        for (unsigned int i = 0; i < punct.length(); i++) {
            if (c == punct[i]) {
                break;
            }
            else if (isalpha(c)) {
                word += toupper(c);
            }
            // If the character is a whitespace and if the string word is not empty, make it a word and add to _allWords
            // Then clear string word to start over
            else if (isspace(c) && word.length() > 0) {
                _allWords.push_back(word);
                word.clear();
            }
        }
    }
    // Safety case which makes sure that 'word' is actually empty before starting the process over again
    if (word.length() > 0) {
        _allWords.push_back(word);
    }
}

// Show letter occurrences to user
void StringCounter::printLetterCounts(ostream& output) {
   string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
   int maxSize(0);
   // Iterate through each word in _allWords and increment the counter of letters in the _letterCounts vector through index searchhing
    for (int i = 0; i < (int)_allWords.size(); i++){
        for(int j = 0; j < (int)_allWords[i].length(); j++){
            _letterCounts[_allWords[i][j] - 'A']++;
        }
    }
    // Setup formatting using the the longest string with the greatest number of characters
    for (int i = 0; i < (int)_letterCounts.size(); i++){
        if((int)_letterCounts[i] > maxSize){
            maxSize = _letterCounts[i];
        }
    }

    string lCount = to_string(maxSize);
    int maxLength = lCount.length();

    // Print out occurrence of each letter using the alphabet string and _letterCounts vector by matching their indexes
    for(int i = 0; i < 26; i++){
        output << left << alphabet[i] << " : " << right << setw(maxLength) << _letterCounts[i] << endl;
    }
}

// Show letter statistics to user
void StringCounter::printLetterStats(ostream& output) {
    int maxCount = 0;
    int minCount = 1000000000;
    int maxAlign = 0;
    char maxLetter, minLetter;
    double maxPercentage, minPercentage;
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    // Iterate through _letterCounts vector and check to see which letter had the hiighest and lowerst occurrence
    for (int i = 0; i < (int)_letterCounts.size(); i++) {
        _totalLetterCount += _letterCounts[i];
        if ((int)_letterCounts[i] > maxCount) {
            maxCount = _letterCounts[i];
            maxLetter = alphabet[i];

        }
        if ((int)_letterCounts[i] < minCount) {
            minCount = _letterCounts[i];
            minLetter = alphabet[i];
        }
    }

    // Set up proper formatting using alignment variables and comparing minCount and maxCount lengths
    if(to_string(maxCount).length() > to_string(minCount).length()){
        maxAlign = to_string(maxCount).length();
    } 
    else {
        maxAlign = to_string(minCount).length();
    }


    // Calculate percentages of the most frequent and least frequent letters and display them to the user
    maxPercentage = ((double)maxCount / (double)_totalLetterCount) * 100;
    minPercentage = ((double)minCount / (double)_totalLetterCount) * 100; 
    output << " Most Frequent Letter: " << left << setw(maxAlign) << maxLetter << " " << right << setw(maxAlign) << maxCount << " (" << fixed << setprecision(3) << maxPercentage << "%)" << endl;
    output << "Least Frequent Letter: " << left << setw(maxAlign) << minLetter << " " << right << setw(maxAlign) << minCount << " (" << fixed << setprecision(3) << minPercentage << "%)" << endl;
    


}

// Function returns _allWords vector
vector<string> StringCounter::getAllWords() {
    
    return _allWords;
}


