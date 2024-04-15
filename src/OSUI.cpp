#include <iostream>
#include "../include/path_reader.h"

int main() {
    for(;;){
      std::cout<<"HappyBug@HappyBugsComputer:~$ ";
      std::string command;
      std::getline(std::cin, command);
      if(command == "exit"){
        break;
      }
      path_reader reader;
      std::string path = reader.getPath(command);
      if(path == "Error"){
        std::cout<<"Error: command not found"<<std::endl;
      }else{
        system(path.c_str());
      }
    }
}
