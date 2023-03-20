#include <iostream>
#include <map>
#include <vector>

/*
ТЗ: написать классы для аукциона. Есть аукцион, лоты и пользователи. У лота есть история ставок, от какого пользователя, с какой ценой.
У пользователя есть история ставок на разные лоты аналогично. Можно отменять ставки.
*/

class Lot{
    private:
    std::string name_;
    int price_ = 1;

    public:
    Lot(){};
    Lot(std::string name) : name_(name), price_(1){};
    Lot(std::string name, const int price) : name_(name), price_(price){};

    int price() const {
        return price_;
    }

    int new_bet() {
        price_++;
        return price_;
    }

    int new_bet(int new_price) {
        if (new_price < price_) {
            std::cout << "You can't set lesser price!\n";
            return -1;
        }
        price_ = new_price;
        return new_price;
    }

    std::string name() const {
        return name_;
    }
};

class User{
    private:
    int user_id_;

    public:
    User(){};
    User(const int id) : user_id_(id){};
    
};

class Auction{
    private:
    std::map<std::string, Lot> lots_;     // Make on map
    std::vector<User> users_;

    public:
    Auction(){};
    Auction(std::map<std::string, Lot> lots) : lots_(lots){};

    friend std::ostream& operator<<(std::ostream& s, const Auction& auction) {
        int i = 1;
        for (const auto& [key, item] : auction.lots_) {
            s << "Lot #" << i << ": \"" << item.name() + "\"" + std::string("               ", 0, 15 - item.name().length()) << item.price() << "\n";
            i++;
        }
        return s;
    }

    int new_bet(std::string name) {
        for (auto& lot : lots_) {
            if (lot.name() == name) {
                return lot.new_bet();
            }
        }
        std::cout << "No such lot! (\"" << name << "\")\n";
        return -1;
    }

    // int new_bet(std::string name, int new_price) {
    //     for (auto& lot : lots_) {
    //         if (lot.name() == name) {
    //             return lot.new_bet(new_price);
    //         }
    //     }
    //     std::cout << "No such lot! (\"" << name << "\")\n";
    //     return -1;
    // }
};



int main() {
    std::vector<Lot> vector1{Lot("car"), Lot("house"), Lot("water"), Lot("bottle"), Lot("smartphone")};
    //Auction auction(vector1);

    std::map<std::string, Lot> map1{{"car", Lot("car")}, {"house", Lot("house")}, {"water", Lot("water")}};
    Auction auction(map1);
    // auction.new_bet("house", 5);
    // auction.new_bet("asd", 5);
    std::cout << auction;
}





-----------
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


class Bet {
    private:
    Lot* lot_;
    size_t price_;
    User* user_;

    public:
    Bet() : lot_(nullptr), price_(1), user_(nullptr){}; 
    Bet(Lot& lot, size_t price, User& user) : lot_(&lot), price_(price), user_(&user){};
    // Bet(const Lot& lot, size_t price, User& user) : lot_(&lot), price_(price), user_(&user){}; -- Ошибка:
    // cannot initialize a member subobject of type 'Lot *' with an rvalue of type 'const Lot *'. Почему она возникает? Мы не можем
    // написать char* = const char*??

    friend std::ostream& operator<< (std::ostream& s, const Bet& my_bet) {
        s << "\n--- Bet info: ---\n";
        s << "Lot name = " << my_bet.lot_->name_ << std::endl;
        s << "Price = " << my_bet.price_ << std::endl;
        s << "User name = " << my_bet.uesr_->name_ << std::endl;
        return s;
    }
};


class Lot {
    private:
    std::string name_;
    size_t price_;
    std::list<Bet> bet_history_;

    public:
    Lot(){};
    Lot(std::string lot_name, size_t price) : name_(lot_name), price_(price){};
    Lot(std::string lot_name) : Lot(lot_name, 1){};

    friend std::ostream& operator<< (std::ostream& s, const Lot& lot) {
        s << "\n--- Lot info ---\n";
        s << "Lot name = " << lot.name_ << std::endl;
        s << "Current price = " << lot.price_ << std::endl;
        return s;
    }

    const void print_history() {     // Написал const, чтобы указать, что наш объект не должен меняться.
        std::cout << "History of bets for lot " << name_ << std::endl;
        for (const auto& item : bet_history_) {
            std::cout << item;
        }
    }

    friend Bet;
};


class User {
    private:
    std::string name_;
    std::list<Bet> bet_history_;
    
    public:
    User() = delete;
    User(std::string name) : name_(name){};

    const void print_history() {
        std::cout << "History of bets for user " << name_ << std::endl;
        for (const auto& item : bet_history_) {
            std::cout << item;
        }
    }

    friend std::ostream& operator<< (std::ostream& s, const User& user) {
        s << "User name = \"" << user.name_ << "\", total bets = " << user.bet_history_.size() << std::endl;
    }

    // int new_bet(Lot lot, int price) {
    //     Bet()
    // }
};


class Auction {
    private:
    std::list<Lot> lots_;
    std::list<User> users_;

    public:
    Auction(){};    // Хочется сделать, чтобы можно было создавать только один объект аукцион
    const void print_users() {
        std::cout << "Users of auction:\n";
        for (const auto& item : users_) {
            std::cout << item;
        }
    }

    const void print_lots() {
        std::cout << "Lots of auction:\n";
        for (const auto& item : lots_) {
            std::cout << item;
        }
    }

    const void print_all() {
        print_lots();
        print_users();
    }

};


int main() {
    Bet test(Lot("test_name_lot"), 5, User("alex"));
    std::cout << test;
    // User me = {};
    // User you("My name");
    // me.name_ = std::string("Alex");
}