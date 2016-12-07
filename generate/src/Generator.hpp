//
//  Generator.hpp
//  monitorTest
//
//  Created by Xinbo Wang on 12/5/16.
//  Copyright © 2016 Xinbo Wang. All rights reserved.
//

#ifndef Generator_hpp
#define Generator_hpp

#include "Printer.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <time.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h> 

/*
 * This class provides the functions that generate the fake data for CPU usage of servers in the monitoring system.
 */
class Generator {
public:
    
    /*
     * This is the constructor of Generator class that initializes all member variables.
     *
     * @param dirIn: the data path of directory that contains fake data. The default directory is current directory.
     * @param serverNbIn: the number of servers in the monitoring system. The default number is 1000
     * @param cpuPerSeverIn: the number of CPUs per server. The default number of CPU per server is 2.
     */
    Generator(std::string dirIn = "", int serverNbIn = 1000, int cpuPerSeverIn = 2);
    
    /*
     * This method generates the fake data for all CPUs of all servers on a given date.
     */
    void generate();
    
private:
    std::string directory;
    int serverNb;
    int cpuNbPerSever;
    
    /*
     * The method generates the fake data for a CPU of a server on a given date.
     *
     * @param server: the ID of a server, with range [0, 999].
     * @param cpu: the ID of CPU of the server, with range [0, 1].
     */
    void dataFaker(int server, int cpu);
    
    /*
     * This method takes a string of readable date, and generate the timestamp for it.
     * 
     * @param datetime: the date and day time.
     * @return the timestamp in UNIX time.
     */
    unsigned long strToTimestamp(std::string datetime);
};

#endif /* Generator_hpp */
