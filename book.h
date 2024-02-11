#include "product.h"

class Book: public Product {
    public:
        //Constructor
        Book(const std::string category, const std::string name, double price, int qty, std::string ISBN, std::string author);
        std::set<std::string> keywords() const; //Keywords?
        std::string displayString() const;
        void dump(std::ostream& os) const;
    private:
        std::string ISBN_; //ISBN and author
        std::string author_;
};