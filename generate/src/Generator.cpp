#include "Generator.hpp"

Generator::Generator(std::string dirIn, int serverNbIn, int cpuNbPerSeverIn): directory(dirIn), serverNb(serverNbIn), cpuNbPerSever(cpuNbPerSeverIn) {
    if(serverNb > 1000) {
        Printer::getInstance().print("Invalid number - the number of servers exceed the limit!");
        return;
    }
    srand(time(NULL));
    if(!this->directory.empty()) {
        if(this->directory.back() != '/')
            this->directory.push_back('/');
    }
}

void Generator::generate() {
    for(int server = 0; server < this->serverNb; server++) {
        for(int cpu = 0; cpu < this->cpuNbPerSever; cpu++) {
            dataFaker(server, cpu);
        }
    }
}

void Generator::dataFaker(int server, int cpu) {
    int dummySpace = 0; // Append some dummy spaces at the end of each line so that each line has the same number of characters. In this way, we can read a specific line by using seekg() to skip a predictable number of characters. This seems to be the only way of reading specific line in C++.
    std::string subnet = std::to_string(server / 256);
    dummySpace += (3 - subnet.size());
    std::string res = std::to_string(server % 256);
    dummySpace += (3 - res.size());
    std::ostringstream osIp, osSuffix;
    osIp << "192.168." << subnet << '.' << res;
    osSuffix << '_' << cpu << ".txt";
    std::string ip = osIp.str();
    std::string suffix = osSuffix.str();
    std::string filename = ip + suffix;
    std::ofstream myfile(this->directory + filename);
    for(int hour = 0; hour < 24; hour++) {
        for(int minu = 0; minu < 60; minu++) {
            struct tm mytime = {0};
            mytime.tm_year = 2014 - 1900; // Assume the date is fixed.
            mytime.tm_mon = 10 - 1;
            mytime.tm_mday = 31;
            mytime.tm_hour = hour;
            mytime.tm_min = minu;
            unsigned long timestamp = timegm(&mytime);
            std::string cpuUsage = std::to_string(rand() % 101);
            int dummyCpuUsageNb = 3 - cpuUsage.size();
            myfile << timestamp << " " << ip << " " << cpu << " " << cpuUsage << std::string(dummySpace + dummyCpuUsageNb, ' ') << "\n";
        }
    }
    myfile.close();
}

