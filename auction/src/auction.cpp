#include "auction.h"

/*
ТЗ: написать классы для аукциона. Есть аукцион, лоты и пользователи. У лота есть история ставок, от какого пользователя, с какой ценой.
У пользователя есть история ставок на разные лоты аналогично. Можно отменять ставки.

Моя реализация:
Лоты может создавать только объект аукцион.
Пользователь может ставить новую ставку на любой лот.
Сейчас ошибки будут обрабатываться через возвращаемые значения. В следующих версиях планирую перейти на try\catch\throw.
Но не будет ли это еще более громоздко?
Список ставок будет хранится как стэк объектов "ставка" = "имя лота, ставка, имя пользователя"
*/



Bet::Bet() : lot_(nullptr), price_(1), user_(nullptr){}
Bet::Bet(Lot& lot, size_t price, User& user) : lot_(&lot), price_(price), user_(&user){}
// Bet(const Lot& lot, size_t price, User& user) : lot_(&lot), price_(price), user_(&user){}; -- Ошибка:
// cannot initialize a member subobject of type 'Lot *' with an rvalue of type 'const Lot *'. Почему она возникает? Мы не можем
// написать char* = const char*??

std::ostream& operator<< (std::ostream& s, const Bet& my_bet) {
    s << "\n--- Bet info: ---\n";
    s << "Lot name = " << my_bet.lot_->name_ << std::endl;
    s << "Price = " << my_bet.price_ << std::endl;
    s << "User name = " << my_bet.user_->name_ << std::endl;
    return s;
}


// Bet::Bet(){};
// Bet::Bet(std::string lot_name, size_t price, std::string user_name) : lot_name_(lot_name), price_(price), user_name_(user_name){}
// std::ostream& operator<< (std::ostream& s, const Bet& my_bet) {
//     s << "\n--- Bet info: ---\n";
//     s << "Lot name = " << my_bet.lot_name_ << std::endl;
//     s << "Price = " << my_bet.price_ << std::endl;
//     s << "User name = " << my_bet.user_name_ << std::endl;
//     return s;
// }


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

// class Lot {
//     private:
//     std::string name_;
//     size_t price_;
//     std::list<Bet> bet_history_;

//     public:
//     Lot(){};
//     Lot(std::string lot_name, size_t price) : name_(lot_name), price_(price){};
//     Lot(std::string lot_name) : Lot(lot_name, 1){};

//     friend std::ostream& operator<< (std::ostream& s, const Lot& lot) {
//         s << "\n--- Lot info ---\n";
//         s << "Lot name = " << lot.name_ << std::endl;
//         s << "Current price = " << lot.price_ << std::endl;
//         return s;
//     }

//     const void print_history() {     // Написал const, чтобы указать, что наш объект не должен меняться.
//         std::cout << "History of bets for lot " << name_ << std::endl;
//         for (const auto& item : bet_history_) {
//             std::cout << item;
//         }
//     }

//     friend Bet;
// };

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

// int new_bet(Lot lot, int price) {
//     Bet()
// }

// class User {
//     private:
//     std::string name_;
//     std::list<Bet> bet_history_;
    
//     public:
//     User() = delete;
//     User(std::string name) : name_(name){};

//     const void print_history() {
//         std::cout << "History of bets for user " << name_ << std::endl;
//         for (const auto& item : bet_history_) {
//             std::cout << item;
//         }
//     }

//     friend std::ostream& operator<< (std::ostream& s, const User& user) {
//         s << "User name = \"" << user.name_ << "\", total bets = " << user.bet_history_.size() << std::endl;
//     }

//     // int new_bet(Lot lot, int price) {
//     //     Bet()
//     // }
// };

//--------------------------

// Auction::Auction(){};    // Хочется сделать, чтобы можно было создавать только один объект аукцион
// const void Auction::print_users() {
//     std::cout << "Users of auction:\n";
//     for (const auto& item : users_) {
//         std::cout << item;
//     }
// }

// const void Auction::print_lots() {
//     std::cout << "Lots of auction:\n";
//     for (const auto& item : lots_) {
//         std::cout << item;
//     }
// }

// const void Auction::print_all() {
//     print_lots();
//     print_users();
// }


// class Auction {
//     private:
//     std::list<Lot> lots_;
//     std::list<User> users_;

//     public:
//     Auction(){};    // Хочется сделать, чтобы можно было создавать только один объект аукцион
//     const void print_users() {
//         std::cout << "Users of auction:\n";
//         for (const auto& item : users_) {
//             std::cout << item;
//         }
//     }

//     const void print_lots() {
//         std::cout << "Lots of auction:\n";
//         for (const auto& item : lots_) {
//             std::cout << item;
//         }
//     }

//     const void print_all() {
//         print_lots();
//         print_users();
//     }

// };


int main() {
    Lot test_lot("test_name_lot");
    User test_user("alex");
    // Bet test(Lot("test_name_lot"), 5, User("alex"));
    // std::cout << test;
    // User me = {};
    // User you("My name");
    // me.name_ = std::string("Alex");
}