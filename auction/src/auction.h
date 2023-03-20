#ifndef AUCTION_H
#define AUCTION_H

#include <iostream>
#include <list>
#include <ostream>

class Bet;
class Lot;
class User;

class Bet {
    private:

    public:
    Lot* lot_;
    size_t price_;
    User* user_;

    Bet(); 
    Bet(Lot& lot, size_t price, User& user);
    friend std::ostream& operator<< (std::ostream& s, const Bet& my_bet);

    friend User;
    friend Lot;
};


class Lot {
    private:

    public:
    std::string name_;
    size_t price_;
    std::list<Bet> bet_history_;

    Lot();
    Lot(std::string lot_name, size_t price);
    Lot(std::string lot_name);

    friend std::ostream& operator<< (std::ostream& s, const Lot& lot);
    const void print_history();
    friend std::ostream;
    friend Bet;
    friend User;
};

class User {
    private:
    
    public:
    std::string name_;
    std::list<Bet> bet_history_;

    User() = delete;
    User(std::string name);
    const void print_history();
    friend std::ostream& operator<< (std::ostream& s, const User& user);

    friend Bet;
    friend Lot;
};

// class Bet {
//     private:
//     std::string lot_name_;
//     size_t price_;
//     std::string user_name_;

//     public:
//     Bet();
//     Bet(std::string lot_name, size_t price, std::string user_name);
//     friend std::ostream& operator<< (std::ostream& s, const Bet& my_bet);
// };


#endif