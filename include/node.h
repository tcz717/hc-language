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
    virtual std::string& ToString(std::string& str) const;
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
    virtual std::string& ToString(std::string& str) const;
};
 
class NIdentifier : public NExpression {
public:
    std::string name;
    NIdentifier(const std::string& name) : name(name) { }
    virtual std::string& ToString(std::string& str) const;
};
 
class NControlStatement : public NStatement {
public:
    const NIdentifier* name;
    NControlStatement(NIdentifier* name = NULL) :
        name(name) { }
};

class NLoop : public NControlStatement {
public:
    NStatement& body;
    NLoop(NStatement& body) : NControlStatement(), body(body) { }
    NLoop(NIdentifier* name,NStatement& body) : NControlStatement(name), body(body) { }
    virtual std::string& ToString(std::string& str) const;
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
    virtual std::string& ToString(std::string& str) const;
};
 
class NAssignment : public NExpression {
public:
    NIdentifier& lhs;
    NExpression& rhs;
    NAssignment(NIdentifier& lhs, NExpression& rhs) :
        lhs(lhs), rhs(rhs) { }
    virtual std::string& ToString(std::string& str) const;
};
 
class NBlock : public NStatement {
public:
    StatementList statements;
    NBlock() { }
    virtual std::string& ToString(std::string& str) const;
};
 
class NExpressionStatement : public NStatement {
public:
    NExpression& expression;
    NExpressionStatement(NExpression& expression) :
        expression(expression) { }
    virtual std::string& ToString(std::string& str) const;
};
 
class NVariableDeclaration : public NStatement {
public:
    NIdentifier& id;
    long long position;
    NExpression *assignmentExpr;

    NVariableDeclaration(NIdentifier& id, NExpression *assignmentExpr = NULL) :
        id(id), position(-1), assignmentExpr(assignmentExpr) { }
    NVariableDeclaration(NIdentifier& id, int pos, NExpression *assignmentExpr = NULL) :
        id(id), position(pos), assignmentExpr(assignmentExpr) { }

    virtual std::string& ToString(std::string& str) const;
};
#endif
