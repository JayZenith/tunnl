#include "../../include/tunnl/Stmt/PrintStmt.h"

#include <cassert>


PrintStmt::PrintStmt(std::unique_ptr<Expr> expr) : expr(std::move(expr))
{
    assert(this->expr != nullptr);
}

std::any PrintStmt::accept(StmtVisitor<std::any>& visitor) const
{
    return visitor.visitPrintStmt(*this);
}

