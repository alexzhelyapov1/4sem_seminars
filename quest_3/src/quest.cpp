#include "quest.h"
#include "content.h"


// ---------------------------------------------------------------------------------------------------------------------
// Action
// ---------------------------------------------------------------------------------------------------------------------


Action::Action(std::string name, std::string after_action_msg) : name_(name), after_action_msg_(after_action_msg){}


std::string Action::name() const 
{
    return name_;
}


std::string Action::make_action() 
{
    std::cout << after_action_msg_ << std::endl;
    return "";
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
}


void Object::print_actions() const
{
    for (const auto& item : actions_)
    {
        std::cout << "- " << item.first << std::endl;
    }

    std::cout << std::endl;
}


std::string Object::make_action(const std::string& action_name) const
{
    if (actions_.find(action_name) == actions_.end())
    {
        std::cout << "No such action: " << action_name << std::endl;
        return "";
    }

    return actions_.at(action_name)->make_action();
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
}


void Room::delete_object(const std::string& object_name) 
{
    if (objects_.find(object_name) == objects_.end())
    {
        std::cout << "Can'r destroy object " << object_name << " (no such object)\n";
        return;
    }

    objects_.erase(objects_.find(object_name));
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

    return objects_.at(name);
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

            handler(object->make_action(action_name));
            return;
        }

        std::cout << "Unknown cmd " << key_word << std::endl;
        std::cout << "Enter \"help\" for help\n";
}


void Engine::handler(const std::string& cmd) 
{
    if (cmd.find(DESTROY_CMD) != std::string::npos)
    {
        current_room_->delete_object(cmd.substr(cmd.find("_") + 1));
    }

    if (cmd.find(MOVE_CMD) != std::string::npos)
    {
        move_to_room(cmd.substr(cmd.find("_") + 1));
    }
}


std::shared_ptr<Engine> Engine::getInstance()
{
    static Engine example;
    static std::shared_ptr<Engine> main_engine_ = std::make_shared<Engine>(example);

    return main_engine_;
}


// ---------------------------------------------------------------------------------------------------------------------
// Other functions
// ---------------------------------------------------------------------------------------------------------------------


bool operator==(const std::string& str1, const std::string& str2) 
{
    std::string str1_low = to_lower(str1);
    std::string str2_low = to_lower(str2);
    return strcmp(str1_low.data(), str2_low.data()) ? 0 : 1;
}


bool operator==(const std::string& str1, const char* str2) 
{
    std::string str1_low = to_lower(str1);
    std::string str2_low = to_lower(str2);
    return strcmp(str1_low.data(), str2_low.data()) ? 0 : 1;
}


std::string to_lower(const std::string& str) 
{
    int i = 0;
    std::string lower;
    while(str[i]) 
    {
        lower += tolower(str[i++]);
    }
    return lower;
}


std::shared_ptr<Engine> build_game() 
{
    std::shared_ptr<Engine> main_engine = Engine::getInstance();
    
    main_engine->add_room(std::shared_ptr<Room>(new Corridor()));
    main_engine->add_room(std::shared_ptr<Room>(new Kitchen()));

    main_engine->move_to_room("Kitchen"); 

    return main_engine;
}
