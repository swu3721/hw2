#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(std::string rawWords)
{
    std::set<std::string> parsedWords;
    std::string currentWord = "";

    //For each char in rawWords
    for (char letter : rawWords) {
        //If not punctuation, add to currentWord
        if (isalnum(letter)) {
            currentWord += letter;
        } else if (currentWord.length() >= 2) {
            //If 2 characters or more, add to set and reset currentWord
            parsedWords.insert(currentWord);
            currentWord.clear();
        } else {
            currentWord.clear();
        }
    }


    //Check for left over words
    if (currentWord.length() >= 2) {
        parsedWords.insert(currentWord);
    }

    return parsedWords;





}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
