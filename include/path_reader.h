#ifndef PATH_READER_H
#define PATH_READER_H
#include <iostream>
#include <fstream>
#include <string>
class path_reader
{
  private:

  public:
    std::string getPath(std::string name);
};

std::string path_reader::getPath(std::string name){
  std::ifstream file("./PATH.txt");
  if (!file) {
    return "Error";
  }

  std::string line;
  while (std::getline(file, line)) {
    if(line == "\".\\\\bin\\\\" + name + ".exe\"")
    return line;
  }
  file.close();
  return "Error";
}


#endif