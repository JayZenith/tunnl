#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <optional>

//#include "./tokenize.hpp"
//#include "../include/lox/Token.h"
#include "../include/lox/Interpreter.h"
#include "../include/lox/Scanner.h"
#include "../include/lox/Parser.h"



void run(std::string& contents){
    Scanner scanner(contents);
    //std::vector<Token> toks = scanner.scanTokens();
    Parser parser{scanner.scanTokens()};
        std::cout << "here" << std::endl;

    const auto statements = parser.parse();
    Interpreter I(std::cout);
    I.intepret(statements);
    //std::cout << "hi";   
    
}


void readFile(std::string& contents, std::string arg){
    std::fstream input(arg, std::ios::in);
    std::stringstream strm;
    strm << input.rdbuf();
    contents = strm.str();
    run(contents);
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
    /*
    if (argc > 2) {
        fmt::print("usage: lox [script]\n");
        exit(1);
    } else if (args == 2) {
        runFile(argv[1]);
    } else {
        runPrompt();
    }
    */

    std::string contents;
    //runPrompt();
    readFile(contents, "../input.test");
    //readFile(contents, argv[1]);
}