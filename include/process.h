#ifndef _PROCESS_H_
#define _PROCESS_H_

#include <string>
#include <iostream>
#include <vector>

/**
 * Represents an executable process with arguments
 * @author Sean Cavalieri
 */
class Process {
    private:
        std::string command;    //the command for the process (first argument)
        std::vector<std::string> args;  //the arguments for the process
    public:
        Process();
        Process(const Process& copy);
        ~Process();

    //set the command for this process
    void setCommand(const std::string &command);

    //get the command for this process
    const std::string& getCommand() const;

    //add an argument to the list of args
    void addArgument(const std::string &arg);

    //get read only version of the arguments
    const std::vector<std::string>& getArguments() const;

    //get read only version of an argument at index
    const std::string& getArgument(int index) const;

    //clear process data
    void clear();

    //overload casting this process to a string to provide custom formatting of process string
    operator std::string() const;

    //overloads the << operator to allow output to a stream
    friend std::ostream& operator<<(std::ostream &out, const Process &p);

};


#endif