#include "process.h"

#include <sstream>

Process::Process() { }
Process::Process(const Process& copy) {
    this->setCommand(copy.getCommand());
    std::vector<std::string> copyArgs = copy.getArguments();
    for(std::string strArg : copyArgs){
        this->addArgument(strArg);
    }
}
Process::~Process() {
    this->clear();
}

void Process::setCommand(const std::string &command) {
    this->command = command;
}

const std::string& Process::getCommand() const {
    return this->command;
}

void Process::addArgument(const std::string &arg) {
    args.push_back(arg);
}

const std::vector<std::string>& Process::getArguments() const {
    return this->args;
}

const std::string& Process::getArgument(int index) const {
    return this->args.at(index);
}

void Process::clear() {
    this->command = "";
    this->args.clear();
}

Process::operator std::string() const {
    std::string str = "Command: " + this->command + '\n';
    str += "Arguments:\n";
    for(unsigned int i = 0; i < this->args.size(); i++) {
        str += std::to_string(i) + ": " + this->getArgument(i) + '\n';
    }
    return str;
}

std::ostream& operator<<(std::ostream &out, const Process &p) {
    return out << std::string(p);
}