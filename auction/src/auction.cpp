#include "auction.h"


Bet::Bet() : lot_(nullptr), price_(1), user_(nullptr){}
Bet::Bet(Lot* lot, size_t price, User* user) : lot_(lot), price_(price), user_(user){};
Bet::Bet(Lot& lot, const size_t price, User& user) : lot_(&lot), price_(price), user_(&user){}
//?? Bet(const Lot& lot, size_t price, User& user) : lot_(&lot), price_(price), user_(&user){}; -- Ошибка:
// cannot initialize a member subobject of type 'Lot *' with an rvalue of type 'const Lot *'. Почему она возникает? Мы не можем
// написать char* = const char*??

std::ostream& operator<< (std::ostream& s, const Bet& my_bet) {
    s << "\n--- Bet info: ---\n";
    s << "Lot name = " << my_bet.lot_->name_ << std::endl;      //?? А как сделать, чтобы был доступ, если поле lot->name_ приватное?
    s << "Price = " << my_bet.price_ << std::endl;
    s << "User name = " << my_bet.user_->name_ << std::endl;
    return s;
}

const void Lot::new_bet(const Bet new_bet) {
    price_ = new_bet.price_;
    bet_history_.push_back(new_bet);
}



Lot::Lot(){}
Lot::Lot(std::string lot_name, size_t price) : name_(lot_name), price_(price){}
Lot::Lot(std::string lot_name) : Lot(lot_name, 1){}

std::ostream& operator<< (std::ostream& s, const Lot& lot) {
    s << "Lot name = " << lot.name_ << ", current price = " << lot.price_ << std::endl;
    return s;
}

const void Lot::print_history() {
    std::cout << "History of bets for lot = " << name_ << std::endl;
    std::cout << "Number of bets = " << bet_history_.size() << ". List:" << std::endl;
    for (const auto& item : bet_history_) {
        std::cout << item;
    }
    std::cout << std::endl;
}



User::User(std::string name) : name_(name){};

const void User::print_history() {
    std::cout << "History of bets for user = " << name_ << std::endl;
    std::cout << "Number of bets = " << bet_history_.size() << ". List:" << std::endl;
    for (const auto& item : bet_history_) {
        std::cout << item;
    }
    std::cout << std::endl;
}

std::ostream& operator<< (std::ostream& s, const User& user) {
    s << "User name = \"" << user.name_ << "\", total bets = " << user.bet_history_.size() << std::endl;
    return s;
}

const void User::new_bet(Bet new_bet) {
    bet_history_.push_back(new_bet);
}



Auction::Auction(){};

const int Auction::add_user(std::string name) { 
    User new_user(name);
    return this->add_user(new_user);
}

const int Auction::add_user(User new_user) {
    if (user_exists(new_user.name_)) {
        std::cout << "User " << new_user.name_ << " already exists!!\n";
        return -1;
    }

    users_.push_back(new_user);
    return 0;
}

const bool Auction::user_exists(std::string name) {
    for (const auto& iter : users_) {
        if (iter.name_ == name) return true;
    }
    return false;
}

const int Auction::add_lot(std::string name) {
    Lot new_lot(name);
    return this->add_lot(new_lot);
}

const int Auction::add_lot(Lot new_lot) {
    if (lot_exists(new_lot.name_)) {
        std::cout << "Lot " << new_lot.name_ << "already exists!!\n";
        return -1;
    }
    lots_.push_back(new_lot);
    return 0;
}

const bool Auction::lot_exists(std::string name) {
    for (const auto& iter : lots_) {
        if (iter.name_ == name) return true;
    }
    return false;
}

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
    print_lots();
    print_users();
}

const int Auction::add_bet(std::string lot_name, std::string user_name, int price) {
    Lot* current_lot = nullptr;
    User* current_user = nullptr;
    for (auto& iter : lots_) {
        if (iter.name_ == lot_name) {
            current_lot = &iter;
        }
    }
    if (current_lot->name_ == "-1") {
        std::cout << "Wrong name of lot! (" << lot_name << ")\n";
        return -1;
    }

    if (price <= current_lot->price_) {
        std::cout << "Too low price! (" << price << ") Current price = " << current_lot->price_ << std::endl;
        return -1;
    }
    
    for (auto& iter : users_) {
        if (iter.name_ == user_name) {
            current_user = &iter;
        }
    }
    if (current_user->name_ == "-1") {
        std::cout << "Wrong name of user (" << user_name << ")\n";
        return -1;
    }


    Bet new_bet(current_lot, price, current_user);
    current_lot->new_bet(new_bet);
    current_user->new_bet(new_bet);
    return 0;
}

const Lot Auction::get_lot(std::string name) {
    for (auto& item : lots_) {
        if (item.name_ == name) return item;
    }
    Lot bad_lot("-1");
    return bad_lot;
}

const User Auction::get_user(std::string name) {
    for (auto& item : users_) {
        if (item.name_ == name) return item;
    }
    User bad_user("-1");
    return bad_user;
}



int main() {
    Auction main_auction = {};
    Lot lot_1("Lot 1");
    Lot lot_2("Lot 2");
    User user_1("User 1");
    User user_2("User 2");
    main_auction.add_lot(lot_1);
    main_auction.add_lot(lot_2);
    main_auction.add_user(user_1);
    main_auction.add_user(user_2);
    main_auction.print_all();

    main_auction.add_bet(lot_1.name_, user_1.name_, 5);
    main_auction.add_bet(lot_1.name_, user_1.name_, 6);
    main_auction.add_bet(lot_1.name_, user_1.name_, 5);
    main_auction.add_bet(lot_2.name_, user_1.name_, 2);

    main_auction.print_all();

    Lot real_lot_1 = main_auction.get_lot(lot_1.name_);
    real_lot_1.print_history();

    User real_user_1 = main_auction.get_user(user_1.name_);
    real_user_1.print_history();

    // main_auction.get_lot(lot_1.name_).print_history();      //?? Почему не работает, если не создавать отдельный объект?

}