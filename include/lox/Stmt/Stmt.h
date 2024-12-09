#pragma once

#include "../Stmt/StmtVisitor.h"

#include <any>


class Stmt {
public:
    virtual ~Stmt() = default;

    // TODO: figure out a way to accept template visitors? (complicated!)
    virtual std::any accept(StmtVisitor<std::any>& visitor) const = 0;
};