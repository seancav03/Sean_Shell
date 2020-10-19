#include "process.h"
#include "parser.h"

#include <iostream>
#include <csignal>

//declare func
std::vector<Process> parseString(std::string& input);

//declare input string variable here so memory can be released on Cntr C
std::string input;

//handled Cntr C signal from User
void signal_handler( int signal_num ) {
    //user sent signal to quit with Cntr C
    std::cout << "\nShell Exiting..." << '\n';
    exit(signal_num);
}

int main(int argc, char *argv[]) {
    //register Cntr C signal handler
    signal(SIGINT, signal_handler);
    //constantly loop asking for input:
    input = "";
    while(!std::cin.eof()){
        std::cout << "> ";
        std::getline(std::cin, input);
        if(!std::cin.eof()){
            try {
                std::vector<Process> processes = parseString(input);
                int i = 0;
                for(Process p : processes){
                    std::cout << "----------------\n" << "Process: " << i << "\n----------------\n";
                    std::cout << processes.at(i) << '\n';
                    i++;
                }
            } catch(const std::invalid_argument& msg){
                std::cout << msg.what() << '\n';
            }
        }
        input = "";
    }
    std::cout << '\n';  //if user hits Cntr D, stop shell with new line

    return 0;
}

