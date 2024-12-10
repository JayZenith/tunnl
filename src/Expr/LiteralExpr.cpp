#include "../../include/lox/Expr/LiteralExpr.h"


LiteralExpr::LiteralExpr(std::any literal) : literal(std::move(literal))
{}

std::any LiteralExpr::accept(ExprVisitor<std::any>& visitor) const
{
    return visitor.visitLiteralExpr(*this);
}

