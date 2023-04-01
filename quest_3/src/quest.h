#ifndef QUEST
#define QUEST

// Хочется добавить выбор объекта -> выбор действия с объектом



#include <iostream>
#include <string>
#include <map>
#include <list>


// ---------------------------------------------------------------------------------------------------------------------
// Parent classes
// ---------------------------------------------------------------------------------------------------------------------

class Room;
class Object;
class Action;

// ---------------------------------------------------------------------------------------------------------------------



class Action
{
    std::string name_;
    std::string after_action_msg_;

  public:

    Action() : name_(""){}
    Action(std::string name, std::string after_action_msg) : name_(name), after_action_msg_(after_action_msg)
    {
        std::cout << "Created action: " << name_ << ", after action = " << after_action_msg_ << std::endl;
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
    Object(const std::string& name, std::shared_ptr<Action> action) : name_(name), action_(action){
        std::cout << "Added action (" << action_->name() << ", " << action_->make_action() << ")\n";
    }

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



class Engine 
{
    std::shared_ptr<Room> current_room_;
    std::map<std::string, std::shared_ptr<Room>> rooms_;


  public:

    std::string target_requered;

    void add_room(const std::shared_ptr<Room> new_room);
    void set_current_room(const std::string& room_name);
    void where_am_i();
    void what_can_i_see();
    void choose_object();


    friend Action;
};



std::shared_ptr<Engine> build_game();



// ---------------------------------------------------------------------------------------------------------------------
// Objects for the game
// ---------------------------------------------------------------------------------------------------------------------

class Corridor;
class Bad_Cup;
class Drink_Water_Bad;

// ---------------------------------------------------------------------------------------------------------------------


class Drink_Water_Bad : public Action
{
  public:
    Drink_Water_Bad() : Action(std::string("Drink water"), std::string("Water was poisened, you need to take antidot from kitchen!")){}
};


class Bad_Cup : public Object 
{
  public:
    Bad_Cup() : Object("bad_cup", std::shared_ptr<Action>(new Drink_Water_Bad())){}
};


class Skrimmer : public Action
{
  public:
    Skrimmer() : Action(std::string("Peek into a hole"), std::string("There's a creepy animal, you are scared!")){};
};


class Hole : public Object
{
  public:
    Hole() : Object("hole", std::shared_ptr<Action>(new Skrimmer())){};
};



class Corridor : public Room {
    public:
      Corridor() : Room("Corridor"){
        add_object(std::shared_ptr<Object>(new Bad_Cup()));
        add_object(std::shared_ptr<Object>(new Hole()));
      }

};



#endif