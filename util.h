#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{

    std::set<T> intersection; //Return this at end

    typename std::set<T>::iterator iter; //Iterator

    for (iter = s2.begin(); iter != s2.end(); ++iter) { //For each in smaller one
        if (s1.find((*iter)) != s1.end()) { //Find operator (logn)
            intersection.insert((*iter)); //If found, add to intersection set
        }
    }
    
    return intersection;



}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
    //Start with the bigger set to save time
    std::set<T> big;
    std::set<T> other;
    if (s1.size() > s2.size()) {
        big = s1;
        other = s2;
    } else {
        big = s2;
        other = s1;
    }

    std::set<T> unionSet = big; //Union set starting with bigger set
    typename std::set<T>::iterator iter; //Iterator

    for (iter = other.begin(); iter != other.end(); ++iter) { //For each item in the smaller
        if (unionSet.find(*iter) == unionSet.end()) { //If not in other set,
            unionSet.insert(*iter); //insert
        }
    }

    //Return
    return unionSet;

}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
