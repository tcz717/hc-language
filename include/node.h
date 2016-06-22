#include <iostream>
#include <vector>
 
class CodeGenContext;
class NStatement;
class NExpression;
class NVariableDeclaration;
 
typedef std::vector<NStatement*> StatementList;
typedef std::vector<NExpression*> ExpressionList;
typedef std::vector<NVariableDeclaration*> VariableList;
 
class Node {
public:
    virtual ~Node() {}
};
 
class NExpression : public Node {
};
 
class NStatement : public Node {
};
 
class NInteger : public NExpression {
public:
    long long value;
    NInteger(long long value) : value(value) { }
};
 
class NIdentifier : public NExpression {
public:
    std::string name;
    NIdentifier(const std::string& name) : name(name) { }
};
 
class NMethodCall : public NExpression {
public:
    const NIdentifier& id;
    ExpressionList arguments;
    NMethodCall(const NIdentifier& id, ExpressionList& arguments) :
        id(id), arguments(arguments) { }
    NMethodCall(const NIdentifier& id) : id(id) { }
};
 
class NBinaryOperator : public NExpression {
public:
    NExpression& lhs;
    int op;
    NExpression& rhs;
    NBinaryOperator(NExpression& lhs, int op, NExpression& rhs) :
        lhs(lhs), op(op), rhs(rhs) { }
};
 
class NAssignment : public NExpression {
public:
    NIdentifier& lhs;
    NExpression& rhs;
    NAssignment(NIdentifier& lhs, NExpression& rhs) :
        lhs(lhs), rhs(rhs) { }
};
 
class NBlock : public NStatement {
public:
    StatementList statements;
    NBlock() { }
};
 
class NExpressionStatement : public NStatement {
public:
    NExpression& expression;
    NExpressionStatement(NExpression& expression) :
        expression(expression) { }
};
 
class NVariableDeclaration : public NStatement {
public:
    NIdentifier& id;
    int position;
    NExpression *assignmentExpr;

    //ident ident
    NVariableDeclaration(NIdentifier& id) :
        id(id), position(-1) { }
    NVariableDeclaration(NIdentifier& id, int pos) :
        id(id), position(pos) { }
    NVariableDeclaration(NIdentifier& id, NExpression *assignmentExpr) :
        id(id), assignmentExpr(assignmentExpr)
        { 
            position=-1;
        }
    NVariableDeclaration(NIdentifier& id, int pos, NExpression *assignmentExpr) :
        id(id), position(pos), assignmentExpr(assignmentExpr) { }
};
