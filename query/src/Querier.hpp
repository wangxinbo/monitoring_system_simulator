//
//  Querier.hpp
//  monitorTest
//
//  Created by Xinbo Wang on 12/5/16.
//  Copyright © 2016 Xinbo Wang. All rights reserved.
//

#ifndef Querier_hpp
#define Querier_hpp

#include "Printer.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <time.h>
#include <iostream>
#include <cstdlib>
#include <cctype>


/*
 * This class provides the functions that enable users to query the usage of the specified CPU in the
 * specified server during a given period. The query operation can retrieve the needed information in O(1)
 * time. This fast query is achieved by directly calculating the offset of the first queried time in the
 * data file. Since C++ does not provide offset operation based on lines, and only provides the offset operation
 * based on character. So, my offset calculation works under several assumtions on the data file. First, a file
 * only contains the usage information of one CPU in one server during one day. Second, each line only contains
 * information at a particular time instance (per-minute basis), e.g., the first line records the CPU usage at 
 * 00:00 of a day, the second line records the CPU usage at 00:01 etc. Third, each line has the same number of
 * characters, which is 33. The maximum number is achieved by data sample like "1414689783 192.168.255.255 0 100\n".
 * When the data at a line does not contains 33 characters, dummy space characters are appended at the end of the
 * line.
 */
class Querier {
public:
    /*
     * This is the constructor of Querier class that initializes all member variables.
     *
     * @param dirIn: the data path of directory that contains fake data. The default directory is current directory.
     * @param serverNbIn: the number of servers in the monitoring system. The default number is 1000
     * @param cpuPerSeverIn: the number of CPUs per server. The default number of CPU per server is 2.
     */
    Querier(std::string dirIn = "", int serverNbIn = 1000, int cpuPerSeverIn = 2);
    
    /*
     * This method provides the API for query operation. It will takes a string with pre-defined format as input 
     * command, parses the command, and print the records for CPU usage on a server during a given time period.
     * The command must be in the form: QUERY IP cpu_id time_start time_end. Time_start and time_end should be
     * specified in the format YYYY-MM-DD HH:MM where YYYY is a four digit year, MM is a two digit month (i.e.,
     * 01 to 12), DD is the day of the month (i.e., 01 to 31), HH is the hour of the day, and MM is the minute
     * of an hour.
     *
     * @param command: a string that contains the query command.
     * @return whether the query operaion succeeds or not.
     */
    bool query(std::string command);
    
private:
    std::string directory; // The data path of directory that contains the fake data.
    int serverNb; // The number of servers in the monitoring system.
    int cpuNbPerSever; // The number of CPUs per sever.
    std::string maxIpAddr; // The (exclusive) upper bound of IP address of servers. Assuming the IP address start from 192.168.0.0, and increases one by one.
    
    /*
     * This method prepares the data retrieval by finding the data file that records the CPU usage of the specified
     * CPU of the specified server on the specified date. It will calculate the offsets of the start time and end
     * time in the data file, so that the data can be retrieved directly at the line that stores the information
     * for the start time instance.
     *
     * @param inputs: an array of strings, each string contains a piece of information that is parsed from the command.
     * @return whether the data preparation is successful or not.
     */
    bool retrieve(std::vector<std::string>& inputs);
    
    /*
     * This method calculates the offset of a given time instance in a data file. The offset is in terms of the
     * number of lines between the first line in the data file and the line that contains the information of the
     * given day time instance. The calculation is based on the assumptions mentioned for this class. The offset
     * can be simply calculated by HOUR * 60 + MINUTE, where HOUR is the hour of the given day time, and MINUTE 
     * is the minute of the given day time.
     *
     * @param dayTime: the time instance of interest.
     * @return the offset of the line that contains the data of the given day time.
     */
    int calOffset(std::string dayTime);
    
    /*
     * This method retrieves the data recorded between the start time and end time that are specified in the
     * command. This is achieved by reading the data between the two offsets of the start and end time instances.
     * The retrieved information is printed on the screen.
     *
     * @param myfile: the file stream that contains the fake data on a given date.
     * @param offset1: the offset of line that records the information of start time.
     * @param offset2: the offset of line that records the information of end time.
     */
    void retrieveBlock(std::ifstream& myfile, int offset1, int offset2);
    
    /*
     * This method takes the timestamp and returns the readable time. in the format YYYY-MM-DD HH:MM where YYYY
     * is a four digit year, MM is a two digit month (i.e., 01 to 12), DD is the day of the month (i.e., 01 to 31),
     * HH is the hour of the day, and MM is the minute of an hour.
     *
     * @param rawtime: the timestamp that is in UNIX time.
     * @return the readable time as a string.
     */
    std::string timeStampToHReadble(const long rawtime);
    
    /*
     * This method compare the input IP address with the upper bound of IP addresses of servers, and evaluate 
     * whether the input IP address falls into the valid range, which is between [192.168.0.0 to 'maxIpAddr').
     *
     * @param ip: the IP address of the server of interest.
     * @return whether the query IP is valid or not.
     */
    bool isValidIp(std::string ip);
};
#endif /* Querier_hpp */
