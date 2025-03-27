#pragma once

#include <any>

#include <memory>

#include "Expr.h"
#include "ExprVisitor.h"
#include "../Token.h"

class VarExpr : public Expr {
public:
    VarExpr(Token name);
    std::any accept(ExprVisitor<std::any>& visitor) const override;

    const Token& getName() const { return name; }
private:
    Token name;
};