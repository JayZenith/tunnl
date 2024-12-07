#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <optional>

//#include "./tokenize.hpp"
//#include "../include/lox/Token.h"
#include "../include/lox/Scanner.h"


void run(std::string& contents){
    //Lox::Tokenize tokenizer{contents};
    

    //std::vector<Lox::Token> tokens = scanner.scanTokens();
    
}


void readFile(std::string& contents, std::string arg){
    std::fstream input(arg, std::ios::in);
    std::stringstream strm;
    strm << input.rdbuf();
    contents = strm.str();
    std::cout << "von: " << contents << std::endl;
    Scanner scanner(contents);
    std::vector<Token> toks = scanner.scanTokens();
    std::cout << "hi";
    //run(contents);
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
    readFile(contents, "../input.test");
        //readFile(contents, argv[1]);
    //Tokenize tokenizer(contents);
    //std::vector<Token>TokenType = tokenizer.tokenize();
}