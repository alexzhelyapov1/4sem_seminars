#include "quest.h"



std::string Action::name() const 
{
    return name_;
}



std::string Action::make_action() 
{
    // std::cout << "Making action " << after_action_msg_ << std::endl;
    return after_action_msg_;
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
    std::cout << "Added action: " << action_->name() << ", after action: " << action_->make_action() << ", to object: " << name_ << std::endl;
}



std::string Object::action() const {
    return action_->name();
}



std::string Object::make_action() 
{
    return action_->make_action();
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

    std::cout << "Found object " << name << ", success!\n";

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


void Engine::set_current_room(const std::string& room_name) 
{

    if (rooms_.find(room_name) == rooms_.end()) {
        std::cout << "No such room: " << room_name << std::endl;
        return;
    }


    current_room_ = rooms_.at(room_name);
    std::cout << "Current room is: " << current_room_->name() << std::endl;

}



std::shared_ptr<Engine> build_game() 
{
    std::shared_ptr<Engine> main_engine(new Engine());


    std::list<std::string> room_names = {std::string("Room"),    std::string("Corridor1"), 
                                         std::string("Kitchen"), std::string("Bedroom")};



    // Need to add objects to rooms


    for (auto& item : room_names) 
    {
        std::shared_ptr<Room> room_ptr(new Room(item));

        main_engine->add_room(room_ptr);
    }

    
    main_engine->add_room(std::shared_ptr<Room>(new Corridor()));

    main_engine->set_current_room("Corridor");



    return main_engine;
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

    std::cout << current_room_->get_object(temp)->make_action() << std::endl;
}