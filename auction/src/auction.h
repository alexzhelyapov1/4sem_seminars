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
    User(std::string name);
    const void print_history();
    friend std::ostream& operator<< (std::ostream& s, const User& user);

    friend Bet;
    friend Lot;
    friend Auction;
    friend std::ostream;
};


class Auction {
    private:
    std::list<Lot> lots_;
    std::list<User> users_;

    public:
    Auction();    // Хочется сделать, чтобы можно было создавать только один объект аукцион
    const void print_users();
    const void print_lots();
    const void print_all();

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