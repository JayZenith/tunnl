#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <optional>

#include "./tokenize.hpp"


void readFile(std::string&contents, std::string arg){
    std::fstream input(arg, std::ios::in);
    std::stringstream strm;
    strm << input.rdbuf();
    contents = strm.str();
}

int main(int argc, char* argv[]){
    std::string contents;
    readFile(contents, "../input.test");
    //readFile(contents, argv[1]);
    std::cout << contents << std::endl;
}