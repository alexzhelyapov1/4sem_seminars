// 4 комнаты
// 5 предметов

// Создать пустую комнату с водой для начала


#ifndef QUEST
#define QUEST

#include <iostream>
#include <string>
#include <map>
#include <list>


class Action
{
    std::string name_;
    std::string after_action_;

  public:

    Action() : name_(""){}
    Action(std::string name, std::string after_action) : name_(name), after_action_(after_action)
    {
        std::cout << "Created action: " << name_ << ", after action = " << after_action_ << std::endl;
    }

    std::string name() const;
    std::string make_action();
};


class Object 
{

    std::string name_;
    std::shared_ptr<Action> action_;

  public:


    Object();
    Object(const std::string& name);

    std::string name() const;
    void add_action(const std::shared_ptr<Action> new_action);
    std::string action() const;
    std::string make_action();

};



class Room
{

    std::string name_;
    std::map<std::string, std::shared_ptr<Object>> objects_;

  public:


    Room();
    Room(const std::string& name);

    std::string name() const;
    void add_object(const std::shared_ptr<Object> new_object);
    std::string objects() const;
    std::shared_ptr<Object> get_object(const std::string& name) const;

};




class Cup : public Object 
{

  public:

    Cup(std::string name) : Object(name){};

};



class Engine 
{

    std::shared_ptr<Room> current_room_;
    std::map<std::string, std::shared_ptr<Room>> rooms_;


  public:

    void add_room(const std::shared_ptr<Room> new_room);
    void set_current_room(const std::string& room_name);
    void where_am_i();
    void what_can_i_see();

};


std::shared_ptr<Engine> build_game();

#endif