#include <iostream>
#include <memory>
#include <cstdlib>
#include <cstring>
#include "Triangle.h"
#include "Foursquare.h"
#include "Octagon.h"
#include "TList.h"

void menu()
{
    std::cout << "Choose an operation:" << std::endl;
    std::cout << "1) Add triangle" << std::endl;
    std::cout << "2) Add foursquare" << std::endl;
    std::cout << "3) Add octagon" << std::endl;
    std::cout << "4) Delete figure from list" << std::endl;
    std::cout << "5) Print list"  << std::endl;
    std::cout << "6) Sort list by qsort" << std::endl;
    std::cout << "0) Exit" << std::endl;
}

int main(void)
{
    int32_t act = 0;
    TList<Figure> list;
    std::shared_ptr<Figure> ptr;
    do {
        menu();
        std::cin >> act;
        switch(act) {
            case 1:
                ptr = std::make_shared<Triangle>(std::cin);
                list.Push(ptr);
                break;
            case 2:
                ptr = std::make_shared<Foursquare>(std::cin);
                list.Push(ptr);
                break;
            case 3:
                ptr = std::make_shared<Octagon>(std::cin);
                list.Push(ptr);
                break;
            case 4:
                ptr = list.Pop();
                break;
            case 5:
                std::cout << list << std::endl;
                break;
            case 9:
                for(auto i : list) {
                    i->Print();
                }     
                break;
            case 6:
                std::cout << "1) using regular sort" << std::endl; 
                std::cout << "2) to parallel" << std::endl;
                std::cin >> act;
                if (act == 1) {
                    list.Sort();
                } else if (act == 2) {
                    list.ParSort();
                } else {
                    std::cout << "Unknown command" << std::endl;
                    break;
                }
                break;
            case 0:
                break;
            default:
                std::cout << "Incorrect command" << std::endl;;
                break;
        }
    } while (act);
    return 0;
}
