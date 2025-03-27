cmake_minimum_required(VERSION 3.10)

project(TUNNL)

# C++17 is required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(tunnl_test src/main.cpp 
                   src/Scanner.cpp 
                   src/Token.cpp 
                   src/Parser.cpp
                   src/Interpreter.cpp
                   src/Environment.cpp
                   src/Expr/LiteralExpr.cpp
                   src/Expr/BinaryExpr.cpp
                   src/Expr/VarExpr.cpp
                   src/Stmt/PrintStmt.cpp
                   src/Stmt/VarStmt.cpp
                   src/Stmt/IfStmt.cpp
              )


add_executable(tunnl src/main.cpp 
                   src/Scanner.cpp 
                   src/Token.cpp 
                   src/Parser.cpp
                   src/Interpreter.cpp
                   src/Environment.cpp
                   src/Expr/LiteralExpr.cpp
                   src/Expr/BinaryExpr.cpp
                   src/Expr/VarExpr.cpp
                   src/Stmt/PrintStmt.cpp
                   src/Stmt/VarStmt.cpp
                   src/Stmt/IfStmt.cpp
              )

# Enable testing
enable_testing()
add_subdirectory(tests)