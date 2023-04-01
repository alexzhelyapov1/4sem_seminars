# Description

This is my first pre-industrial C++ project. \
The text quest.

Now it is not completed, but it will be completed to 06.04.23


# Realisation

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