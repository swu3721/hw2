#include "datastore.h"
#include <set>
#include <map>


class MyDataStore: public DataStore {
    public:
        MyDataStore(); //Empty constructor
        ~MyDataStore();
        void addProduct(Product* p); //Add product to database
        void addUser(User* u); //Add user to database
        std::vector<Product*> search(std::vector<std::string>& terms, int type); //Search
        void dump(std::ostream& ofile); //Dump?
        std::set<Product*> getProducts(); // Access products
        std::set<User*> getUsers(); // Access users
        std::map<std::string, std::set<Product*>> getKeywords(); // Access keywords
        void addToCart(Product* p, std::string username); //Add to cart
        void viewCart(std::string username); //View cart of user
        void buyCart(std::string username); //Buy cart of user


    private:
        std::set<Product*> products_; //Products
        std::set<User*> users_; //Users
        std::map<std::string, User*> usernames_; //Usernames for each user
        std::map<User*, std::vector<Product*>> carts_; //Map for user's carts
        std::map<std::string, std::set<Product*>> keywords_; //Map for 1 keyword to all products with keyword
};