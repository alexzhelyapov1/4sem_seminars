#include "auction.h"


Bet::Bet() : lot_(nullptr), price_(1), user_(nullptr){}
Bet::Bet(Lot& lot, const size_t price, User& user) : lot_(&lot), price_(price), user_(&user){}
// Bet(const Lot& lot, size_t price, User& user) : lot_(&lot), price_(price), user_(&user){}; -- Ошибка:
// cannot initialize a member subobject of type 'Lot *' with an rvalue of type 'const Lot *'. Почему она возникает? Мы не можем
// написать char* = const char*??

std::ostream& operator<< (std::ostream& s, const Bet& my_bet) {
    s << "\n--- Bet info: ---\n";
    s << "Lot name = " << my_bet.lot_->name_ << std::endl;      // А как сделать, чтобы был доступ, если поле lot->name_ приватное?
    s << "Price = " << my_bet.price_ << std::endl;
    s << "User name = " << my_bet.user_->name_ << std::endl;
    return s;
}



Lot::Lot(){}
Lot::Lot(std::string lot_name, size_t price) : name_(lot_name), price_(price){}
Lot::Lot(std::string lot_name) : Lot(lot_name, 1){}

std::ostream& operator<< (std::ostream& s, const Lot& lot) {
    s << "\n--- Lot info ---\n";
    s << "Lot name = " << lot.name_ << std::endl;
    s << "Current price = " << lot.price_ << std::endl;
    return s;
}

const void Lot::print_history() {     // Написал const, чтобы указать, что наш объект не должен меняться.
    std::cout << "History of bets for lot " << name_ << std::endl;
    for (const auto& item : bet_history_) {
        std::cout << item;
    }
}



User::User(std::string name) : name_(name){};

const void User::print_history() {
    std::cout << "History of bets for user " << name_ << std::endl;
    for (const auto& item : bet_history_) {
        std::cout << item;
    }
}

std::ostream& operator<< (std::ostream& s, const User& user) {
    s << "User name = \"" << user.name_ << "\", total bets = " << user.bet_history_.size() << std::endl;
    return s;
}



Auction::Auction(){};
const void Auction::print_users() {
    std::cout << "Users of auction:\n";
    for (const auto& item : users_) {
        std::cout << item;
    }
}

const void Auction::print_lots() {
    std::cout << "Lots of auction:\n";
    for (const auto& item : lots_) {
        std::cout << item;
    }
}

const void Auction::print_all() {
    this->print_lots();
    this->print_users();
}



int main() {
    Lot test_lot("test_name_lot");
    User test_user("alex");
    Bet test(test_lot, 5, test_user);
    std::cout << test;
    // User me = {};
    // User you("My name");
    // me.name_ = std::string("Alex");
}