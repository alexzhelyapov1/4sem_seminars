#include "quest.h"


// ---------------------------------------------------------------------------------------------------------------------
// Action
// ---------------------------------------------------------------------------------------------------------------------


Action::Action(std::string name, std::string after_action_msg) : name_(name), after_action_msg_(after_action_msg)
{
    // std::cout << "Created action: " << name_ << ", after action = " << after_action_msg_ << std::endl;
}


std::string Action::name() const 
{
    return name_;
}


void Action::make_action() 
{
    // std::cout << "Making action " << after_action_msg_ << std::endl;
    std::cout << after_action_msg_ << std::endl;
}


// ---------------------------------------------------------------------------------------------------------------------
// Object
// ---------------------------------------------------------------------------------------------------------------------


Object::Object() : name_(""){};
Object::Object(const std::string& name) : name_(name){};


Object::Object(const std::string& name, std::shared_ptr<Action> action) : name_(name), action_(action)
{
    actions_.insert(std::pair<std::string, std::shared_ptr<Action>>(action->name(), action));
}


std::string Object::name() const
{
    return name_;
}


void Object::add_action(const std::shared_ptr<Action> new_action) 
{
    action_ = new_action;
    actions_.insert(std::pair<std::string, std::shared_ptr<Action>>(new_action->name(), new_action));

    // std::cout << "Action list for object " << name_ << ": ";
    // for (const auto& item : actions_) {
    //     std::cout << item.first << ", ";
    // }
    // std::cout << std::endl;

    // std::cout << "Added action: " << action_->name() << std::endl;
}


void Object::print_actions() const
{
    for (const auto& item : actions_)
    {
        std::cout << "- " << item.first << std::endl;
    }

    std::cout << std::endl;
}


void Object::make_action(const std::string& action_name) const
{
    if (actions_.find(action_name) == actions_.end())
    {
        std::cout << "No such action: " << action_name << std::endl;
        return;
    }

    actions_.at(action_name)->make_action();
}


// ---------------------------------------------------------------------------------------------------------------------
// Room
// ---------------------------------------------------------------------------------------------------------------------


Room::Room() : name_(""){};
Room::Room(const std::string& name) : name_(name){};


std::string Room::name() const 
{
    return name_;
}


void Room::add_object(const std::shared_ptr<Object> new_object) 
{
    if (objects_.find(new_object->name()) != objects_.end()) {
        std::cout << "This object already exists! (" << new_object->name() << ")" << std::endl;
        return;
    }

    objects_.insert(std::pair<std::string, std::shared_ptr<Object>>(new_object->name(), new_object));
    // std::cout << "Added object: " << new_object->name() << ", to room: " << name_ << std::endl;
}


void Room::print_objects() const 
{
    for (auto& item : objects_) {
        std::cout <<  "- " + item.first + "\n";
    }
}


std::shared_ptr<Object> Room::get_object(const std::string& name) const  
{
    if (objects_.find(name) == objects_.end()) {
        std::cout << "No object: " << name << ", in room: " << name_ << std::endl;
        return nullptr;
    }

    // std::cout << "Found object " << name << ", success!\n";

    return objects_.at(name);
}



// ---------------------------------------------------------------------------------------------------------------------
// Engine
// ---------------------------------------------------------------------------------------------------------------------


void Engine::add_room(const std::shared_ptr<Room> new_room) 
{
    if (rooms_.find(new_room->name()) != rooms_.end()) {
        std::cout << "Room: " << new_room->name() << ", already exists!" << std::endl;
        return;
    }

    rooms_.insert(std::pair<std::string, std::shared_ptr<Room>> (new_room->name(), new_room));
    // std::cout << "Added room: " << new_room->name() << std::endl;
}


void Engine::move_to_room(const std::string& room_name) 
{
    if (rooms_.find(room_name) == rooms_.end()) {
        std::cout << "No such room: " << room_name << std::endl;
        return;
    }

    current_room_ = rooms_.at(room_name);
    std::cout << "Moved to room: " << current_room_->name() << std::endl;
}


void Engine::rooms() const
{
    std::cout << "Rooms: ";
    for (const auto& item : rooms_) {
        std::cout << item.first << " ";
    }
    std::cout << std::endl;
}


std::shared_ptr<Engine> build_game() 
{
    std::shared_ptr<Engine> main_engine = Engine::getInstance();
    
    main_engine->add_room(std::shared_ptr<Room>(new Corridor()));
    main_engine->add_room(std::shared_ptr<Room>(new Kitchen()));

    main_engine->move_to_room("Kitchen"); 

    return main_engine;
}


void Engine::listen_cmd()
{
    std::string key_word;

    std::cout << "Enter cmd or choose object: ";
    std::cin >> key_word;

        if (key_word == "help")
        {
            std::cout << "------------------------------\n";
            std::cout << "Where are you? -> where_am_i\n";
            std::cout << "Objects in room? -> objects\n";
            std::cout << "All rooms -> rooms\n";
            std::cout << "Show all actions in a room - show_all_actions\n";
            std::cout << "Exit to main choice - show_all_actions\n";
            std::cout << "------------------------------\n";
            return;
        }

        if (key_word == "where_am_i")
        {
            std::cout << "You are in a room: " << current_room_->name() << std::endl;
            return;
        }
        
        if (key_word == "objects")
        {
            current_room_->print_objects();
            return;
        }

        if (key_word == "show_all_actions")
        {
            current_room_->printf_all_actions_in_room();
            return;
        }

        if (key_word == "rooms")
        {
            rooms();
            return;
        }

        if (current_room_->objects_.find(key_word) != current_room_->objects_.end())
        {
            std::shared_ptr<Object> object = current_room_->get_object(key_word);
            if (!object) return;

            std::cout << "Actions for object " << key_word << ": " << std::endl;
            object->print_actions();

            std::cout << "Choose action: ";
            std::string action_name;
            std::cin >> action_name;

            if (action_name == "exit") return;

            object->make_action(action_name);
            return;
        }

        std::cout << "Unknown cmd " << key_word << std::endl;
        std::cout << "Enter \"help\" for help\n";
}


std::shared_ptr<Engine> Engine::getInstance()
{
    static Engine example;
    static std::shared_ptr<Engine> main_engine_ = std::make_shared<Engine>(example);

    // std::cout << &main_engine_;
    return main_engine_;
    // return std::make_shared<Engine>(Engine::getInstance());
}


void Room::printf_all_actions_in_room() const
{
    for (const auto& object : objects_)
    {
        std::cout << "> " << object.first << ":\n";

        for (const auto& action : object.second->actions_)
        {
            std::cout <<  "    - " << action.first << std::endl;
        }
    }
}
