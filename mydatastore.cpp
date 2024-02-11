#include "mydatastore.h"
#include "util.h"

MyDataStore::MyDataStore() {

}

MyDataStore::~MyDataStore() {
    //carts_.clear(); //Just in case
    //keywords_.clear();
    //Deleting products
    for (Product* p : products_) {
        delete p;
    }
    

    for (User* u : users_) {
        delete u;
    }

}

void MyDataStore::addProduct(Product* p) {
    products_.insert(p); //Add products to product

    //Adding to keywords
    std::set<std::string> keywordP = p->keywords();
    std::set<std::string>::iterator it;
    for (it = keywordP.begin(); it != keywordP.end(); ++it) { //For each keyword in p
        std::map<std::string, std::set<Product*>>::iterator iter = keywords_.find((*it)); //Find the keyword in keywords_
        if(iter != keywords_.end()) { //If found, insert product to that set
            (iter->second).insert(p);
        } else {
            //Make a set for products
            std::set<Product*> prods;
            prods.insert(p);
            keywords_.insert(std::make_pair((*it), prods)); //Insert new pair of keyword and current prod to keywords_
        }
    }

}

void MyDataStore::addUser(User* u) {
    users_.insert(u);

    //Make a cart for the user
    std::vector<Product*> userCart;
    carts_.insert(std::make_pair(u, userCart));

    //Add username to username_
    std::string username = convToLower(u->getName());
    usernames_.insert(std::make_pair(username, u));
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    //Search results
    std::vector<Product*> results;
    

    if (type == 0) { //AND search
        
        std::set<Product*> searchResults = products_; //For each search result (starting with all products)

        for (std::string term : terms) { //For each term

            std::map<std::string, std::set<Product*>>::iterator it = keywords_.find(term); //Find the term in keyword_
            if (it != keywords_.end()) { //If found
                //Intersect the products with the current search terms
                searchResults = setIntersection(searchResults, (it->second));
            }
        }

        //Add to vector results after found
        std::set<Product*>::iterator it;
        for (it = searchResults.begin(); it != searchResults.end(); ++it) {
            results.push_back(*it);
        }

        
    } else if (type == 1) { //OR search Must use setUnion
        
        std::set<Product*> searchResults; //Search results
        for(std::string term : terms) { // For each term
            
            std::map<std::string, std::set<Product*>>::iterator it = keywords_.find(term); //Find the term in keyword_
            if (it != keywords_.end()) { //If found
                searchResults = setUnion(searchResults, (it->second)); //Make a union of search results and the products with the keyword
            }
        }

        std::set<Product*>::iterator it;
        for (it = searchResults.begin(); it != searchResults.end(); ++it) {
            results.push_back(*it);
        }


    }
    return results;

}

void MyDataStore::dump(std::ostream& ofile) {
    ofile << "<products>" << std::endl;
    for (Product* prod : products_) {
        prod->dump(ofile);
    }
    ofile << "</products>" << std::endl;
    ofile << "<users>" << std::endl;
    for (User* user : users_) {
        user->dump(ofile);
    }
    ofile << "</users>" << std::endl;
}

std::set<Product*> MyDataStore::getProducts() {
    return products_;
}

std::set<User*> MyDataStore::getUsers() {
    return users_;
}

std::map<std::string, std::set<Product*>> MyDataStore::getKeywords() {
    return keywords_;
}

void MyDataStore::addToCart(Product* p, std::string username) {
    User* user; //User
    std::map<std::string, User*>::iterator it = usernames_.find(username);
    if (it != usernames_.end()) { //If user with given username is found
        user = it->second; //Set user to the correct user

        //Find the user's cart
        std::map<User*, std::vector<Product*>>::iterator iter = carts_.find(user);
        if (iter != carts_.end()) {
            (iter->second).push_back(p); //Add the product to the end of the cart
            
        } else {
            std::cout << "Invalid request" << std::endl;
        }
    } else {
        std::cout << "Invalid request" << std::endl;
    }


    
    
}

void MyDataStore::viewCart(std::string username) {
    User* user;

    std::map<std::string, User*>::iterator it = usernames_.find(username);
    if (it != usernames_.end()) { //If user with given username is found
        user = it->second; //Set user to the correct user

        //Find cart
        std::map<User*, std::vector<Product*>>::iterator iter = carts_.find(user);
        if (iter != carts_.end()) { // If found
            for (size_t i = 0; i < (iter->second).size(); i++) {
                std::cout << "Item " << (i + 1) << std::endl << (iter->second)[i]->displayString() << std::endl;
            }
        }

    } else {
        std::cout << "Invalid username" << std::endl;
    }

}

void MyDataStore::buyCart(std::string username) {
    User* user;

    std::map<std::string, User*>::iterator it = usernames_.find(username);
    if (it != usernames_.end()) { //If user with given username is found
        user = it->second; //Set user to the correct user

        std::map<User*, std::vector<Product*>>::iterator it = carts_.find(user); //Get to the user's cart 
        if (it != carts_.end()) {
            
            std::vector<Product*>::iterator iter = (it->second).begin(); //Iterator for the product in the cart
            while (iter != (it->second.end())) { //Iterator loop for vector but because im erasing an element its weird
                
                if ((user->getBalance() - (*iter)->getPrice()) >= 0 && (*iter)->getQty() > 0) { //If in stock and user balance is doable
                    user->deductAmount((*iter)->getPrice()); //Deduct amount
                    (*iter)->subtractQty(1); //Subtract 1 from quantity?
                    (it->second).erase(iter); //Erase the item from user's cart
                    //No iterate because the erased element will then become where the iterator iter is now pointing
                } else {
                    ++iter; //If not erased, iterate
                }
                
            }
            
        }
    } else {
        std::cout << "Invalid username" << std::endl;
    }



}