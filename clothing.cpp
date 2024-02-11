#include <iomanip>
#include <sstream>
#include "clothing.h"
#include "util.h"

//Constructor
Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand) :
    Product(category, name, price, qty) 
{
    size_ = size;
    brand_ = brand;

}

//keywords
std::set<std::string> Clothing::keywords() const {
    //Set to be returned
    std::set<std::string> words;

    //Product name
    std::set<std::string> productName = parseStringToWords(name_);

    std::set<std::string>::iterator it;
    for (it = productName.begin(); it != productName.end(); ++it) { //For each word in productName, add to words
        std::string p = (*it); //Not modifying original data
        p = convToLower(p);
        p = trim(p);
        words.insert(p);
    }
    //Brand
    std::set<std::string> brandName = parseStringToWords(brand_); 
    for (it = brandName.begin(); it != brandName.end(); ++it) { //For each word in productName, add to words
        std::string b = (*it); //Not modifying original data
        b = convToLower(b);
        b = trim(b);
        words.insert(b);
    }

    return words;
}

//displayString
std::string Clothing::displayString() const {
    //Stringstream
    std::stringstream ss;
    //Adding all necessary info
    ss << name_  << "\n";
    ss << "Size: " << size_ << " Brand: " << brand_ << "\n";
    ss << std::fixed << std::setprecision(2) << price_ << " " << std::to_string(qty_) << " left." << "\n"; //Make sure price is 2 decimal places


    return ss.str();
}

//dump
void Clothing::dump(std::ostream& os) const {
    Product::dump(os); //Print out basic info
    os << size_ << "\n" << brand_ << "\n"; //Add on category specific
}