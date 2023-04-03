# Description

This is my first pre-industrial C++ project. \
The text quest.

Now it is not completed, but it will be completed to 06.04.23


# Usage
To see cmds to use enter "help"


# Availabilities of game for now
You can crate rooms, objects and action. 
Now there are examples of actions, that can change room (f.e. move_to_kitchen), can destroy objects (f.e. throw_cup).


# Realisation

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
```

User input:
```
Bottle
```

To get instantly object by the time O(1) we need to use std::map. (Because there are can be several objects of a same class, but with
different names).