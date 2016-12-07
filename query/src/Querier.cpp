#include "Querier.hpp"

Querier::Querier(std::string dirIn, int serverNbIn, int cpuNbPerSeverIn): directory(dirIn), serverNb(serverNbIn), cpuNbPerSever(cpuNbPerSeverIn) {
    int maxSubnet = this->serverNb / 256;
    int maxRes = this->serverNb % 256;
    std::ostringstream os;
    os << "192.168." << maxSubnet << '.' << maxRes;
    this->maxIpAddr = os.str();
    if(!this->directory.empty()) {
        if(this->directory.back() != '/')
            this->directory.push_back('/');
    }
}

bool Querier::query(std::string command) {
    std::istringstream is(command);
    std::vector<std::string> inputs;
    for(int i = 0; i < 6; i++) {
        std::string temp;
        is >> temp;
        if(temp.empty()) break;
        inputs.push_back(temp);
    }
    if(inputs.size() < 6) {
        Printer::getInstance().print("Please enter enough arguments.");
        return false;
    }
    else if(!isValidIp(inputs[0])) {
        Printer::getInstance().print("Please enter a valid IP address. A valid IP address is between 192.168.0.0 and " + this->maxIpAddr + " (EXCLUSIVE)");
        return false;
    }
    else if (inputs[2] != "2014-10-31" || inputs[4] != "2014-10-31") {
        Printer::getInstance().print("Please enter a valid date, i.e., 2014-10-31.");
        return false;
    }
    else if (inputs[1] > "1") {
        Printer::getInstance().print("Please enter a valid CPU number. A valid CPU number is 0 or 1");
        return false;
    }
    else {
        return retrieve(inputs);
    }
}

bool Querier::retrieve(std::vector<std::string>& inputs) {
    std::ostringstream osFilename;
    osFilename << inputs[0] << '_' << inputs[1] << ".txt";
    std::string filename = osFilename.str();
    std::ifstream myfile(this->directory + filename);
    if(myfile.is_open()) {
        int offset1 = calOffset(inputs[3]);
        int offset2 = calOffset(inputs[5]);
        if(offset1 < 0 || offset2 < 0 || offset1 > offset2) {
            Printer::getInstance().print("Please enter valid day time, e.g. HH [0~24), MM [0,60).");
            return false;
        }
        std::ostringstream os;
        os << "CPU" << inputs[1] << " usage on " << inputs[0] << ':';
        Printer::getInstance().print(os.str());
        retrieveBlock(myfile, offset1, offset2);
        
        myfile.close();
        return true;
    }
    else {
        Printer::getInstance().print("Please enter valid file path/name!");
        return false;
    }
}

int Querier::calOffset(std::string dayTime) {
    if(dayTime.size() != 5) return -1;
    else if(!std::isdigit(dayTime[0]) || !std::isdigit(dayTime[1]) || !std::isdigit(dayTime[3]) || !std::isdigit(dayTime[4])) return -1;
    int hour = std::atoi(dayTime.substr(0, 2).c_str());
    int minu = std::atoi(dayTime.substr(3, 2).c_str());
    if(hour >= 24 || minu >= 60) return -1;
    return hour * 60 + minu;
}

void Querier::retrieveBlock(std::ifstream& myfile, int offset1, int offset2) {
    myfile.seekg(offset1 * 33); // Each line has the same number of characters, i.e. 33. So we can directly read the specific line by setting the offset.
    std::string line;
    std::ostringstream os;
    for(int i = offset1; i <= offset2; i++) {
        std::getline(myfile, line);
        std::istringstream is(line);
        std::string temp;
        std::vector<std::string> info;
        for(int i = 0; i < 4; i++) {
            is >> temp;
            info.push_back(temp);
        }
        os << '(' << timeStampToHReadble(std::atol(info[0].c_str())) << ',' << info[3] << "%)" << (i < offset2 ? ", " : "");
    }
    Printer::getInstance().print(os.str());
}

std::string Querier::timeStampToHReadble(const long rawtime)
{
    struct tm* dt;
    dt = gmtime(&rawtime);
    char buff[80];
    strftime(buff, 80, "%Y-%m-%d %H:%M", dt);
    return std::string(buff);
}

bool Querier::isValidIp(std::string ip) {
    int i = 0, j = 0;
    std::string ip1 = ip, ip2 = this->maxIpAddr;
    while(i < ip1.size() || j < ip2.size()) {
        long num1 = 0, num2 = 0;
        while(i < ip1.size() && isdigit(ip1[i])) {
            num1 = num1*10 + (int)(ip1[i]-'0');
            i++;
        }
        while(j < ip2.size() && isdigit(ip2[j])) {
            num2 = num2*10 + (int)(ip2[j]-'0');
            j++;
        }
        if(num1 > num2) return false;
        else if(num1 < num2) return true;
        i++;
        j++;
    }
    return false;
}
