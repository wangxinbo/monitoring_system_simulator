#include <iostream>
#include "src/Printer.hpp"
#include "src/Querier.hpp"
#include <string>

int main(int argc, const char * argv[]) {
    std::string dir = "./";
    if(argc < 2)
        Printer::getInstance().print("Are you sure fake data is in current diretory? Y/N");
    else {
        dir = argv[1];
        Printer::getInstance().print("Are you sure fake data is in \"" + dir + "\" diretory? Y/N");
    }
    char answer;
    std::cin >> answer;
    while(std::tolower(answer) != 'y') {
        Printer::getInstance().print("Please enter the source directory: ");
        std::cin >> dir;
        Printer::getInstance().print("Do you want to generate fake data in \"" + dir + "\" diretory? Y/N");
        std::cin >> answer;
    }
    
    
    Querier querier(dir);
    while(true) {
        Printer::getInstance().print("Please enter your command (DO NOT REVISE AFTER PASTE): ");
        std::string temp, line;
        std::cin >> temp;
        std::getline(std::cin, line);
        if(temp.substr(0, 4) == "EXIT") break;
        if(temp != "QUERY" || line.empty()) continue;
        querier.query(line);
    }
    
    return 0;
}
