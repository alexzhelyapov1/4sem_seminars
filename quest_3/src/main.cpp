#include <iostream>
#include "quest.h"
#include <list>

int main() 
{
    // std::shared_ptr<Action> cup_action(new Action(std::string("Drink water"), std::string("You broke a cup")));


    // std::shared_ptr<Cup> main_cup(new Cup("Main cup"));
    // main_cup->add_action(cup_action);


    // std::shared_ptr<Cup> little_cup(new Cup("Little cup"));
    // little_cup->add_action(cup_action);


    // std::shared_ptr<Room> main_room(new Room("Main room"));
    // main_room->add_object(main_cup);
    // main_room->add_object(little_cup);


    // std::cout << main_room->objects() << std::endl;


    // std::cout <<  main_room->get_object("Main cup")->make_action() << std::endl;


    std::shared_ptr<Engine> main_engine = build_game();
    main_engine->where_am_i();
    main_engine->what_can_i_see();



    // std::string name1 = "apple";
    // Object test1 = Object(name1);
    // std::cout << test1.name() << std::endl;
    // test1.action();

    // std::string name_room = "room1";
    // Room new_room = Room(name_room);
    // std::cout << new_room.name() << std::endl;
}



// void build_game1() 
// {
//     std::list<std::string> room_names = {std::string("entrance hall"), std::string("corridor"), 
//                                          std::string("room"),          std::string("bedroom"),
//                                          std::string("bathroom"),      std::string("kitchen")};
    
//     std::map<std::string, std::shared_ptr<Room>> rooms;


//     for (auto& item : room_names) 
//     {
//         std::shared_ptr<Room> room_ptr(new Room(item));
//         rooms.insert(std::pair<std::string, std::shared_ptr<Room>>(item, room_ptr));
//         std::cout << room_ptr->name() << std::endl;
//     }
// }