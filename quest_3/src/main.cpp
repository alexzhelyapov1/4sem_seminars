#include <iostream>
#include "quest.h"
#include <list>

int main() 
{
    std::cout << "------Build game--------\n";
    std::shared_ptr<Engine> main_engine = build_game();
    std::cout << "------------------------\n";

    while (true)
    {
        main_engine->listen_cmd();
    }
}
