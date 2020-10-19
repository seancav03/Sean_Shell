#include "process.h"

#include <iostream>

//Parse the inputted string into Process Objects
std::vector<Process> parseString(std::string& input) {
    std::vector<Process> processes;

    //start by splitting the string into components:
    //  1. anything is quotes is one component
    //  2. separate words into components (splitting words from |, <, and > while not in quotes)
    //  3. inter-process tokens are components (|, <, and > while not in quotes)

    std::vector<std::string> components;
    std::string curComp;   //the current component being build
    char quote = ' ';
    for(unsigned int i = 0; i < input.length(); i++){
        if(quote != ' '){ 
            //currently working within a quoted section
            if(input.at(i) == quote){
                //finish component if something was in the complete quotes
                if(curComp.length() > 0){
                    std::string comp(curComp);
                    components.push_back(comp);
                    curComp = "";
                }
                quote = ' ';
            } else {
                curComp += input.at(i);
            }
        } else if(input.at(i) == '"' || input.at(i) == '\''){
            quote = input.at(i);
            //don't store the quote, move on.
        } else if(input.at(i) == '|' || input.at(i) == '<' || input.at(i) == '>') {
            //inter-process token found. Submit on its own, splitting from word prior if necessary
            if(curComp.length() > 0){
                //submit the word before this token
                std::string comp(curComp);
                components.push_back(comp);
                curComp = "";
            }
            //submit this current token
            curComp += input.at(i);
            std::string comp(curComp);
            components.push_back(comp);
            curComp = "";
        } else if(input.at(i) == ' '){
            //split components on spaces
            if(curComp.length() > 0){
                std::string comp(curComp);
                components.push_back(comp);
                curComp = "";
            }
            
        } else {
            //this is a normal character. Add it
            curComp += input.at(i);
        }
    }
    //put any remaining content in as last component
    if(curComp.length() > 0){
        std::string comp(curComp);
        components.push_back(comp);
        curComp = "";
    }
    //now check if the quotes were finished
    if(quote != ' '){
        throw std::invalid_argument("Mismatched Quotes");
    }

    Process process;
    bool firstLoop = true;
    for(std::string comStr : components){
        if(comStr == "|" || comStr == "<" || comStr == ">"){
            processes.push_back(process);   //copies object with copy constructor into vector array
            process.clear();    //clear same object to use again
            firstLoop = true;   //prepare for next Process
        } else {
            if(firstLoop){
                process.setCommand(comStr);
                firstLoop = false;
            } else {
                process.addArgument(comStr);
            }
        }
    }
    if(process.getCommand() != ""){
        processes.push_back(process);   //Push the last process onto the back of the vector array
    }

    return processes;
}