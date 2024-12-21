cmake_minimum_required(VERSION 3.10)

project(C++Interpreter)

# C++17 is required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(lox src/main.cpp 
                   src/Scanner.cpp 
                   src/Token.cpp 
                   src/Parser.cpp
                   src/Interpreter.cpp
                   src/Expr/LiteralExpr.cpp
                   src/Expr/BinaryExpr.cpp
                   src/Stmt/PrintStmt.cpp
              )

