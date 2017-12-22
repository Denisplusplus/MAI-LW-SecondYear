#include "TList.h"
#include <iostream>

void menu(void) {
  std::cout << "1) Insert an octagon" << std::endl;
  std::cout << "2) Print list" << std::endl;
  std::cout << "3) Delete the last octagon from list" << std::endl;
  std::cout << "0) Exit" << std::endl;
}

int main(void) {
  TList list;
  int choise;
  Octagon tmp, item;

  do {
    menu();
    std::cin >> choise;
    switch(choise) {
    case 1:{
      std::cout << "Enter an octagon's side" << std::endl;
      std::cin >> tmp;
      if (list.push(tmp))
        std::cout << "Item was added" << std::endl;
      else
        std::cout << "Item was not added" << std::endl;
      break;
    }
    case 2:
      std::cout << list;
      break;
    case 3:
      item = list.pop();
      if (!(item == -1.0))
        std::cout << "Item was removed. It contained:"
                  << std::endl << item;
      else
        std::cout << "Item was not removed" << std::endl;
      break;
    }
  } while(choise != 0);
  
  return 0;
}