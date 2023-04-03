# Description

This is my first pre-industrial C++ project. \
The text quest.

Now it is not completed, but it will be completed to 06.04.23


# Usage
To see cmds to use enter "help"


# Availabilities of game for now
You can crate rooms, objects and action. \
Now there are examples of actions, that can change current room (f.e. move_to_kitchen), can destroy objects (f.e. throw_cup).\
You can create other fluences to Engine in function Engine::handler(std::string)


# Realisation

### Compare cmds and strings

```!!!Operator==(string, string) redefined!!!```

It compares lowercase(string commands). So "HeLlo" = "hello"

### Engine
This is main singleton objects, which contains map of rooms, current position of player. 
Potentially can contain also health and other player parameters.

### Room
Conatins map of objects

### Objects
Contains map of actions, to this object

### Actions
The core of action, can change condition of Engine.

## Why I decided to use std::map?
User interacts with a game by console and choose objects or command. \

### For example
Game out:
```
Chose the object:
> Cup
> Door
> Bottle

: Bottle

Choose an action:
- drink_water
- throw_the_bottle

: drink_water
```


To get instantly object by the time O(1) we need to use std::map. (Because there are can be several objects of a same class, but with
different names).