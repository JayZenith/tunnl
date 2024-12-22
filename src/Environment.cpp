#include "../include/lox/Environment.h"

#include "../include/lox/Token.h"

#include <iostream>
#include <cassert>

Environment::Environment() : enclosing(nullptr)
{}

Environment::Environment(Environment* enclosing) : enclosing(enclosing)
{
    assert(enclosing != nullptr);
}

void Environment::define(const std::string& name, const std::any& value)
{
    values.emplace(name, value);
}

void Environment::assign(const Token& name, const std::any& value)
{
    auto it = values.find(name.getText());
    if (it != values.end()) {
        it->second = value;
        return;
    }

    if (enclosing) {
        enclosing->assign(name, value);
        return;
    }

    std::cerr << "Undefined variable " << name.getText() << std::endl;
}

const std::any& Environment::get(const Token& name) const
{
    auto it = values.find(name.getText());
    if (it != values.end()) {
        return it->second;
    }

    if (enclosing) {
        return enclosing->get(name);
    }

    std::cerr << "Undefined variable " << name.getText() << std::endl;
}