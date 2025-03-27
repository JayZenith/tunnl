#include "../../include/tunnl/Stmt/VarStmt.h"

#include <cassert>

VarStmt::VarStmt(Token name, std::unique_ptr<Expr> expr) :
    name(std::move(name)), expr(std::move(expr))
{
    assert(this->name.getType() == TokenType::IDENTIFIER);
}

std::any VarStmt::accept(StmtVisitor<std::any>& visitor) const
{
    return visitor.visitVarStmt(*this);
}
