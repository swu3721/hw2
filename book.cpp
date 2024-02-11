#include <iomanip>
#include <sstream>
#include "book.h"
#include "util.h"

//Constructor
Book::Book(const std::string category, const std::string name, double price, int qty, std::string ISBN, std::string author) :
    Product(category, name, price, qty) 
{
    ISBN_ = ISBN;
    author_ = author;

}

//keywords
std::set<std::string> Book::keywords() const {

    //Set to be returned
    std::set<std::string> words;

    //Product name
    std::set<std::string> productName = parseStringToWords(name_);
    //Book author
    std::set<std::string> authorName = parseStringToWords(author_);
    
    std::set<std::string>::iterator it;
    for (it = productName.begin(); it != productName.end(); ++it) { //For each word in productName, add to words
        std::string p = (*it); //Not modifying original data
        p = convToLower(p);
        p = trim(p);
        words.insert(p);
    }
    for (it = authorName.begin(); it != authorName.end(); ++it) { //For each word in authorName, add to words
        std::string a =(*it); //Not modifying original data
        a = convToLower(a);
        a = trim(a);
        words.insert(a);
    }
    //ISBN
    std::string is = ISBN_;
    is = trim(is);
    words.insert(is);

    return words;
}

//displayString Book
std::string Book::displayString() const {
    //Stringstream
    std::stringstream ss;
    //Adding all necessary info
    ss << name_  << "\n";
    ss << "Author: " << author_ << " ISBN: " << ISBN_ << "\n";
    ss << std::fixed << std::setprecision(2) << price_ << " " << std::to_string(qty_) << " left." << "\n"; //Make sure price is 2 decimal places

    
    return ss.str();
}

//dump
void Book::dump(std::ostream& os) const {
    Product::dump(os); //Print out basic info
    os << ISBN_ << "\n" << author_ << "\n"; //Add on category specific
}