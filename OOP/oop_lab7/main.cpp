#include "TList.h"
#include <iostream>
#include "Foursquare.h"
#include "Octagon.h"
#include "Triangle.h"
#include "TNList.h"

void menu(void)
{
    std::cout << "Choose an operation:" << std::endl;
    std::cout << "1) Add Triangle" << std::endl;
    std::cout << "2) Add Foursquare" << std::endl;
    std::cout << "3) Add Octagon" << std::endl;
    std::cout << "4) Delete Figure" << std::endl;
    std::cout << "5) Print"  << std::endl;
    std::cout << "0) Exit" << std::endl;
}

int main(void)
{
    TNList<TList<Figure>, std::shared_ptr<Figure> > list;
    int act, index;
    Triangle tmp1;
    Foursquare tmp2;
    Octagon tmp3;

    do {
        menu();
        std::cin >> act;
        switch(act) {
            case 1:
                list.push(std::make_shared<Triangle>(std::cin));
                std::cout << "Item was added" << std::endl;
                break;
            case 2:
                list.push(std::make_shared<Foursquare>(std::cin));
                std::cout << "Item was added" << std::endl;
                break;
            case 3:
                list.push(std::make_shared<Octagon>(std::cin));
                std::cout << "Item was added" << std::endl;
                break;
            case 4:{
                std::cout << "Enter criteria" << std::endl;
                std::cout << "1) by type\n2) lesser than square\n";
                std::cin >> index;
                if (index == 1) {
                    std::cout << "1) Foursquare\n2) Octagon\n3) Triangle\n";
                    std::cout << "Enter type" << std::endl;
                    std::cin >> index;
                    list.removeByType(index);
                } else if (index == 2) {
                    double sqr = 0.0;
                    std::cout << "Enter square" << std::endl;
                    std::cin >> sqr;
                    list.removeLesser(sqr);
                } else {
                    break;
                }
                break;
            }
            case 5:
                list.print();
                break;
            case 0:
                break;
            default:
                std::cout << "Incorrect command" << std::endl;;
                break;
        }

    } while(act);

    return 0;
}
