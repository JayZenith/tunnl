#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <optional>

#include "../include/lox/Interpreter.h"
#include "../include/lox/Scanner.h"
#include "../include/lox/Parser.h"


void run(std::string& contents){
    Scanner scanner(contents);
    Parser parser{scanner.scanTokens()};
    const auto statements = parser.parse();
    Interpreter I(std::cout);
    I.intepret(statements);
    
}

void readFile(std::string arg){
    std::string content;
    std::fstream input(arg, std::ios::in);
    std::stringstream strm;
    strm << input.rdbuf();
    content = strm.str();
    run(content);
}

void runPrompt(){
    std::cout << "C++ Lox Interpreter\n";
    std::string code;
    while(true){
        std::cout << "> ";
        if(std::getline(std::cin, code)){
            run(code);
            //had error = false;
        } else {
            std::cout << "\n";
            break;
        }
    }
}

int main(int argc, char* argv[]){

    if (argc > 2) {
        std::cout << "usage: lox [script]\n";
        exit(1);
    } else if (argc == 2) {
        readFile(argv[1]);
    } else {
        runPrompt();
    }
    
}