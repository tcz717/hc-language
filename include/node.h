#ifndef __NODE_H__
#define __NODE_H__
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
 
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
    virtual const std::string* ToString();
    virtual std::string& ToString(std::string& str);
    friend std::ostream& operator<< (std::ostream &os, Node &it);
};
 
class NExpression : public Node {
};
 
class NStatement : public Node {
};
 
class NInteger : public NExpression {
public:
    long long value;
    NInteger(long long value) : value(value) { }
    virtual std::string& ToString(std::string& str);
};
 
class NIdentifier : public NExpression {
public:
    std::string name;
    NIdentifier(const std::string& name) : name(name) { }
    virtual std::string& ToString(std::string& str);
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
    virtual std::string& ToString(std::string& str);
};
 
class NAssignment : public NExpression {
public:
    NIdentifier& lhs;
    NExpression& rhs;
    NAssignment(NIdentifier& lhs, NExpression& rhs) :
        lhs(lhs), rhs(rhs) { }
    virtual std::string& ToString(std::string& str);
};
 
class NBlock : public NStatement {
public:
    StatementList statements;
    NBlock() { }
    virtual std::string& ToString(std::string& str);
};
 
class NExpressionStatement : public NStatement {
public:
    NExpression& expression;
    NExpressionStatement(NExpression& expression) :
        expression(expression) { }
    virtual std::string& ToString(std::string& str);
};
 
class NVariableDeclaration : public NStatement {
public:
    NIdentifier& id;
    long long position;
    NExpression *assignmentExpr;

    //ident ident
    NVariableDeclaration(NIdentifier& id) :
        id(id), position(-1) { }
    NVariableDeclaration(NIdentifier& id, int pos) :
        id(id), position(pos) { }
    NVariableDeclaration(NIdentifier& id, NExpression *assignmentExpr) :
        id(id), position(-1), assignmentExpr(assignmentExpr) { }
    NVariableDeclaration(NIdentifier& id, int pos, NExpression *assignmentExpr) :
        id(id), position(pos), assignmentExpr(assignmentExpr) { }
};
#endif
