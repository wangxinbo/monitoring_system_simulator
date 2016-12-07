#include <iostream>
#include "src/Generator.hpp"
#include "src/Printer.hpp"
#include <string>

int main(int argc, const char * argv[]) {
     std::string dir = "./";
     if(argc < 2)
     Printer::getInstance().print("Do you want to generate fake data in current diretory? Y/N");
     else {
     dir = argv[1];
     Printer::getInstance().print("Do you want to generate fake data in \"" + dir + "\" diretory? Y/N");
     }
     char answer;
     std::cin >> answer;
     while(tolower(answer) != 'y') {
     Printer::getInstance().print("Please enter the destination directory: ");
     std::cin >> dir;
     Printer::getInstance().print("Do you want to generate fake data in \"" + dir + "\" diretory? Y/N");
     std::cin >> answer;
     }
     
     Generator generator(dir);
     generator.generate();
   
     return 0;
}
