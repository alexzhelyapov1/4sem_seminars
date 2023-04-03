#ifndef QUEST
#define QUEST


#include <iostream>
#include <string>
#include <map>
#include <list>

#define DESTROY_CMD std::string("destroy")
#define MOVE_CMD std::string("moveto")


// ---------------------------------------------------------------------------------------------------------------------
// Parent classes
// ---------------------------------------------------------------------------------------------------------------------

class Room;
class Object;
class Action;
class Engine;

// ---------------------------------------------------------------------------------------------------------------------


class Action
{
  protected:
    std::string name_;
    std::string after_action_msg_;

  public:

    Action() : name_(""){}
    Action(std::string name, std::string after_action_msg);

    std::string name() const;
    virtual std::string make_action();
};



class Object 
{
    std::string name_;
    std::shared_ptr<Action> action_;
    std::map<std::string, std::shared_ptr<Action>> actions_;

  public:

    Object();
    Object(const std::string& name);
    Object(const std::string& name, std::shared_ptr<Action> action);

    std::string name() const;
    void print_actions() const;
    void add_action(const std::shared_ptr<Action> new_action);
    std::string make_action(const std::string& action_name) const;

    friend Room;
    friend Engine;
};



class Room
{
    std::string name_;
    std::map<std::string, std::shared_ptr<Object>> objects_;

  public:

    Room();
    Room(const std::string& name);

    std::string name() const;
    void print_objects() const;
    void printf_all_actions_in_room() const;
    void add_object(const std::shared_ptr<Object> new_object);
    void delete_object(const std::string& object_name);
    std::shared_ptr<Object> get_object(const std::string& name) const;

    friend Engine;
};



class Engine 
{
    Engine(){}
    std::shared_ptr<Room> current_room_;
    std::map<std::string, std::shared_ptr<Room>> rooms_;

    void add_room(const std::shared_ptr<Room> new_room);

  public:
    // Engine(Engine&) = delete;    // Can't disable
    Engine& operator=(const Engine&) = delete;

    std::string target_requered;

    static std::shared_ptr<Engine> getInstance();
    void choose_object();
    void listen_cmd();
    void rooms() const;
    void move_to_room(const std::string& room_name);
    void handler(const std::string& cmd);

    friend Action;
    friend std::shared_ptr<Engine> build_game();
};


std::shared_ptr<Engine> build_game();
std::string to_lower(const std::string& str);


// ---------------------------------------------------------------------------------------------------------------------
// Objects for the game
// ---------------------------------------------------------------------------------------------------------------------


class Throw : public Action 
{
    std::string object_name_;

  public:
    Throw() : Action("throw", ""){}
    Throw(std::string object_name) : Action("throw_" + object_name, "You broke a " + object_name + 
          "... You have escaped from death! (It was poisened)"), object_name_(object_name){}

    std::string make_action() override
    {
        std::cout << after_action_msg_ << std::endl;
        return DESTROY_CMD + "_" + object_name_;
    }
};


class Move : public Action
{
    std::string target_;
  public:
    Move(std::string target) : Action("go_to_" + target, ""), target_(target){}
    std::string make_action() override
    {
        return MOVE_CMD + "_" + target_;
    }
};


class Yell_At_It : public Action
{
  public:
    Yell_At_It() : Action("yell_at_it", "You yelled at it, it is offended..."){}
    Yell_At_It(std::string target) : Action("yell_at_" + target, "You yelled at " + target + ", it is offended..."){}
};


class Drink_Water_Bad : public Action
{
  public:
    Drink_Water_Bad() : Action(std::string("drink_water"), 
                                          std::string("Water was poisened, you need to take antidot from kitchen!")){}
};


class Bad_Cup : public Object 
{
  public:
    Bad_Cup() : Object("bad_cup")
    {
        add_action(std::shared_ptr<Action>(new Drink_Water_Bad()));
        add_action(std::shared_ptr<Action>(new Throw("bad_cup")));
    }
};


class Skrimmer : public Action
{
  public:
    Skrimmer() : Action(std::string("peek_into_a_hole"), std::string("There's a creepy animal, you are scared!")){};
};


class Hole : public Object
{
  public:
    Hole() : Object("hole", std::shared_ptr<Action>(new Skrimmer())){};
};


class Door_To_Kitchen : public Object
{
  public:
    Door_To_Kitchen() : Object("door_to_kitchen")
    {
        add_action(std::shared_ptr<Action>(new Move("Kitchen")));
        add_action(std::shared_ptr<Action>(new Drink_Water_Bad()));
    }
};


class Door_To_Corridor : public Object
{
  public:
    Door_To_Corridor() : Object("door_to_corridor")
    {
        add_action(std::shared_ptr<Action>(new Move("Corridor")));
        add_action(std::shared_ptr<Action>(new Yell_At_It("door")));
    }
};


class Corridor : public Room 
{
    public:
      Corridor() : Room("Corridor")
      {
        add_object(std::shared_ptr<Object>(new Bad_Cup()));
        add_object(std::shared_ptr<Object>(new Hole()));
        add_object(std::shared_ptr<Object>(new Door_To_Kitchen()));
        add_object(std::shared_ptr<Object>(new Object("mirror", std::shared_ptr<Action>(new Action("look_into", 
                                                      "WoW!! You are beautifull!!! Good luck in the game)")))));
      }
};


class Kitchen : public Room 
{
    public:
      Kitchen() : Room("Kitchen")
      {
        add_object(std::shared_ptr<Object>(new Bad_Cup()));
        add_object(std::shared_ptr<Object>(new Hole()));
        add_object(std::shared_ptr<Object>(new Door_To_Corridor()));
      }
};




#endif