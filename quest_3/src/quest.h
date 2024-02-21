#ifndef QUEST
#define QUEST


#include <iostream>
#include <string>
#include <map>
#include <list>

#define DESTROY_CMD std::string("destroy")
#define MOVE_CMD    std::string("moveto")


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

    std::string         name() const;
    virtual std::string make_action();
};



class Object 
{
    std::string                                     name_;
    std::shared_ptr<Action>                         action_;
    std::map<std::string, std::shared_ptr<Action>>  actions_;

  public:

    Object();
    Object(const std::string& name);
    Object(const std::string& name, std::shared_ptr<Action> action);

    std::string name() const;
    void        print_actions() const;
    void        add_action(const std::shared_ptr<Action> new_action);
    std::string make_action(const std::string& action_name) const;

    friend Room;
};



class Room
{
    std::string name_;
    std::map<std::string, std::shared_ptr<Object>> objects_;

  public:

    Room();
    Room(const std::string& name);

    std::string             name() const;
    void                    print_objects() const;
    void                    printf_all_actions_in_room() const;
    void                    add_object(const std::shared_ptr<Object> new_object);
    void                    delete_object(const std::string& object_name);
    std::shared_ptr<Object> get_object(const std::string& name) const;

    friend Engine;
};



class Engine 
{
    Engine(){}
    std::shared_ptr<Room>                         current_room_;
    std::map<std::string, std::shared_ptr<Room>>  rooms_;

    void add_room(const std::shared_ptr<Room>new_room);

  public:
    // Engine(Engine&) = delete;    // Can't disable
    Engine& operator=(const Engine&) = delete;


    static std::shared_ptr<Engine>  getInstance();
    void                            choose_object();
    void                            listen_cmd();
    void                            rooms() const;
    void                            move_to_room(const std::string& room_name);
    void                            handler(const std::string& cmd);


    friend std::shared_ptr<Engine>  build_game();
};


std::shared_ptr<Engine> build_game();
std::string to_lower(const std::string& str);





#endif


// Content.h Ask question