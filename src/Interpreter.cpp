#include "../include/lox/Interpreter.h"


#include "../include/lox/Lox.h"



#include "../include/lox/Expr/LiteralExpr.h"
#include "../include/lox/Expr/VarExpr.h"


#include "../include/lox/Stmt/PrintStmt.h"
#include <any>
#include <cassert>
#include <cmath>
#include <ctime>
#include <memory>
#include <ostream>
#include <iostream>


namespace
{
std::string stringify(const std::any& object)
{
    if (!object.has_value()) {
        return "nil";
    }

    if (object.type() == typeid(bool)) {
        return std::any_cast<bool>(object) ? "true" : "false";
    }

    if (object.type() == typeid(double)) {
        double n = std::any_cast<double>(object);
        if (std::trunc(n) == n) { // is int
            return std::to_string((int)n);
        } else {
            return std::to_string(n); // TODO: don't print trailing zeros
        }
    }

    if (object.type() == typeid(std::string)) {
        return std::any_cast<std::string>(object);
    }

    return "";
}
} // end of anonymous namespace


// returns Unix time in seconds
// std::any clock(Interpreter&, const std::vector<std::any>&)
// {
//     std::time_t t = std::time(nullptr);
//     return static_cast<double>(t);
// }

// Interpreter::Interpreter(std::ostream& out) : out(out) , globals(std::make_unique<Environment>()), globalEnvironment(globals.get())
// {
//     // globals->define("clock", Callable{0, &clock});
//     // environment = std::move(globals);
// }




Interpreter::Interpreter(std::ostream& out) 
    : out(out)
{  }

Interpreter::~Interpreter() = default;

void Interpreter::intepret(const std::vector<std::unique_ptr<Stmt>>& statements)
{
   // try {
        for (const auto& ptr : statements) {
            assert(ptr != nullptr);
            execute(*ptr); //due to being pointers 
        }
    // } catch (RuntimeError error) {
    //     Lox::ReportRuntimeError(error);
    // }
}

// Environment& Interpreter::getGlobalsEnvironment()
// {
//     assert(globalEnvironment);
//     return *globalEnvironment;
// }

void Interpreter::execute(const Stmt& stmt)
{
    //PrintStmt is derived from Stmt
    //PrintStmt has an accept function passing
    //in the StmtVisitor an the type of visitor 
    stmt.accept(*this);
}


//MAKE SURE NOT NULL BY CALLING PrintStmt.cpo
std::any Interpreter::evaluate(const Expr& expr)
{
    return expr.accept(*this);
}




std::any Interpreter::visitLiteralExpr(const LiteralExpr& expr)
{
    return expr.getLiteral();
}


//ith EXECUTE we get here 
std::any Interpreter::visitPrintStmt(const PrintStmt& stmt)
{
    //evaluate makes sure not NULL
    auto value = evaluate(stmt.getExpr());
    //fmt::print(out, "{}\n", stringify(value));
    //we know what to do here 
    std::cout << stringify(value) << std::endl;
    return {};
}





// This simulates "finally" keyword usage in executeBlock of Java version
// "execute" can throw "ReturnException" and we need to unwind the stack
// and return to previous enviroment on each scope exit
// Interpreter::EnterEnviromentGuard::EnterEnviromentGuard(Interpreter& i,
//                                                         std::unique_ptr<Environment> env) :
//     i(i)
// {
//     previous = std::move(i.environment);
//     i.environment = std::move(env);
// }

// Interpreter::EnterEnviromentGuard::~EnterEnviromentGuard()
// {
//     i.environment = std::move(previous);
// }

