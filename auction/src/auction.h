#ifndef AUCTION_H
#define AUCTION_H

#include <iostream>
#include <list>
#include <ostream>


class Bet;
class Lot;
class User;
class Auction;


class Bet {
    private:

    public:
    Lot* lot_;
    size_t price_;
    User* user_;

    Bet(); 
    Bet(Lot* lot, size_t price, User* user);
    Bet(Lot& lot, const size_t price, User& user);
    friend std::ostream& operator<< (std::ostream& s, const Bet& my_bet);

    friend User;
    friend Lot;
    friend Auction;
    friend std::ostream;
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
    const void new_bet(const Bet new_bet);

    friend std::ostream;
    friend Bet;
    friend User;
    friend Auction;
};


class User {
    private:
    
    public:
    std::string name_;
    std::list<Bet> bet_history_;

    User() = delete;
    User(const std::string name);
    const void print_history();
    friend std::ostream& operator<< (std::ostream& s, const User& user);
    const void new_bet(Bet new_bet);

    friend Bet;
    friend Lot;
    friend Auction;
    friend std::ostream;
};


class Auction {
    private:        // Все объекты хранятся в Аукционе
    std::list<Lot> lots_;
    std::list<User> users_;

    public:
    Auction();    // Хочется сделать, чтобы можно было создавать только один объект аукцион
    const int add_user(std::string name);   //?? Не вижу смысла писать const std::string, т.к. передается все равно копия, поэтому никакой дополнительной защиты это не принесет.
    const int add_user(User new_user);
    const bool user_exists(std::string name);
    const int add_lot(std::string name);
    const int add_lot(Lot new_lot);
    const bool lot_exists(std::string name);
    const void print_users();
    const void print_lots();
    const void print_all();
    const Lot get_lot(std::string name);
    const User get_user(std::string name);

    const int add_bet(std::string lot_name, std::string user_name, int price);

    friend std::ostream;
    friend Lot;
    friend Bet;
    friend User;

};

#endif




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