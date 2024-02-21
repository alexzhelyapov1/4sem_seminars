#ifndef CONTENT
#define CONTENT


#include "quest.h"


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