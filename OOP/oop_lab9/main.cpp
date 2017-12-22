#include <iostream>
#include <memory>
#include <cstdlib>
#include <cstring>
#include <random>
#include "Triangle.h"
#include "Foursquare.h"
#include "Octagon.h"
#include "TList.h"
#include "TNList.h"


int main(void)
{
    TList<Figure> list;
    typedef std::function<void(void)> Command;
    TNList<std::shared_ptr<Command>> nlist;
    std::mutex mtx;

    Command cmdInsert = [&]() {
        std::lock_guard<std::mutex> guard(mtx);

        uint32_t seed = std::chrono::system_clock::now().time_since_epoch().count();

        std::default_random_engine generator(seed);
        std::uniform_int_distribution<int> distFigureType(1, 3);
        std::uniform_int_distribution<int> distFigureParam(1, 10);
        for (int i = 0; i < 5; ++ i) {
            std::cout << "Command: Insert" << std::endl;

            switch(distFigureType(generator)) {
                case 1: {
                    std::cout << "Inserted Triangle" << std::endl;

                    int side_a = distFigureParam(generator);
                    int side_b = distFigureParam(generator);
                    int side_c = distFigureParam(generator);

                    std::shared_ptr<Figure> ptr = std::make_shared<Triangle>(Triangle(side_a, side_b, side_c));
                    list.PushFirst(ptr);
                    break;
                }

                case 2: {
                    std::cout << "Inserted Octagon" << std::endl;

                    int side = distFigureParam(generator);
                    std::shared_ptr<Figure> ptr = std::make_shared<Octagon>(Octagon(side));
                    list.PushFirst(ptr);

                    break;
                }

                case 3: {
                    std::cout << "Inserted Foursquare" << std::endl;
                    int side = distFigureParam(generator);
                    std::shared_ptr<Figure> ptr = std::make_shared<Foursquare>(Foursquare(side));

                    list.PushFirst(ptr);

                    break;
                }
            }
        }
    };


    Command cmdRemove = [&]() {
        std::lock_guard<std::mutex> guard(mtx);

        std::cout << "Command: Remove" << std::endl;

        if (list.IsEmpty()) {
            std::cout << "List is empty" << std::endl;
        } else {
            uint32_t seed = std::chrono::system_clock::now().time_since_epoch().count();

            std::default_random_engine generator(seed);
            std::uniform_int_distribution<int> distSquare(1, 150);
            double sqr = distSquare(generator);
            std::cout << "Lesser than " << sqr << std::endl;

            for (int32_t i = 0; i < 5; ++i) {
                auto iter = list.begin();
                for (int32_t k = 0; k < list.GetLength(); ++k) {
                    if (iter->Square() < sqr) {
                        list.Pop(k);
                        break;
                    }
                    ++iter;
                }
            }
        }
    };

    Command cmdPrint = [&]() {
        std::lock_guard<std::mutex> guard(mtx);

        std::cout << "Command: Print" << std::endl;
        if(!list.IsEmpty()) {
            std::cout << list << std::endl;
        } else {
            std::cout << "List is empty." << std::endl;
        }
    };
    nlist.Push(std::shared_ptr<Command>(&cmdInsert, [](Command*){}));
    nlist.Push(std::shared_ptr<Command>(&cmdPrint, [](Command*){}));
    nlist.Push(std::shared_ptr<Command>(&cmdRemove, [](Command*){}));
    nlist.Push(std::shared_ptr<Command>(&cmdPrint, [](Command*){}));
    

    while (!nlist.IsEmpty()) {
        std::shared_ptr<Command> cmd = nlist.Top();
        std::future<void> ft = std::async(*cmd);
        ft.get();
        nlist.Pop();
    }

    return 0;
}
