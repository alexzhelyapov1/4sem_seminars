#include "quest.h"



std::string Action::name() const 
{
    return name_;
}



void Action::make_action() 
{
    // std::cout << "Making action " << after_action_msg_ << std::endl;
    std::cout << after_action_msg_ << std::endl;
}



Object::Object() : name_(""){};
Object::Object(const std::string& name) : name_(name){};



std::string Object::name() const
{
    return name_;
}



void Object::add_action(const std::shared_ptr<Action> new_action) 
{
    action_ = new_action;
    std::cout << "Added action: " << action_->name() << std::endl;
}



std::string Object::action() const {
    return action_->name();
}



void Object::make_action() 
{
    action_->make_action();
}



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
    std::cout << "Added object: " << new_object->name() << ", to room: " << name_ << std::endl;

}



std::string Room::objects() const 
{

    // std::string info =  "Objects in " + name_ + ":\n"; 
    std::string info = {};

    for (auto& item : objects_) {
        info += "- " + item.first + "\n";
    }

    return info;

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



void Engine::add_room(const std::shared_ptr<Room> new_room) 
{

    if (rooms_.find(new_room->name()) != rooms_.end()) {
        std::cout << "Room: " << new_room->name() << ", already exists!" << std::endl;
        return;
    }


    rooms_.insert(std::pair<std::string, std::shared_ptr<Room>> (new_room->name(), new_room));
    std::cout << "Added room: " << new_room->name() << std::endl;

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
    std::string temp;

    // std::cout << "Enter cmd:\n";
    std::cin >> temp;

        if (temp == "help")
        {
            std::cout << "------------------------------\n";
            std::cout << "Where are you? -> where_am_i\n";
            std::cout << "Objects in room? -> objects\n";
            std::cout << "Choose object -> choose object\n";
            std::cout << "All rooms -> rooms\n";
            std::cout << "------------------------------\n";
            return;
        }

        if (temp == "where_am_i")
        {
            std::cout << "You are in a room: " << current_room_->name() << std::endl;
            return;
        }
        
        if (temp == "objects")
        {
            std::cout << current_room_->objects() << std::endl;
            return;
        }

        if (temp == "choose")
        {
            std::cin >> temp;
            current_room_->get_object(temp)->make_action();
            return;
        }

        if (temp == "rooms")
        {
            rooms();
            return;
        }

        std::cout << "Unknown cmd " << temp << std::endl;
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



void Engine::where_am_i() 
{
    std::cout << "You are in a room: " << current_room_->name() << std::endl;
}



void Engine::what_can_i_see() 
{
    std::cout << "In the room there are: " << std::endl;

    std::cout << current_room_->objects() << std::endl;
}



void Engine::choose_object()
{   
    std::cout << "Choose object in a room:\n";
    std::cout << current_room_->objects();

    std::string temp;
    std::cin >> temp;

    current_room_->get_object(temp)->make_action();
}