#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
 
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
    virtual const std::string* ToString()
    {
        auto str = new std::string;
        ToString(*str);
        return str;
    }
    virtual std::string& ToString(std::string& str)
    {
        return str+=std::string("Node");
    }
    friend std::ostream& operator<< (std::ostream &os, Node &it) 
    {
        const std::string *str=it.ToString();
        os<<*str<<std::endl;
        delete str;
        return os;
    }
};
 
class NExpression : public Node {
};
 
class NStatement : public Node {
};
 
class NInteger : public NExpression {
public:
    long long value;
    NInteger(long long value) : value(value) { }
    virtual std::string& ToString(std::string& str)
    {
        std::ostringstream os;
        os<<value;
        return str+=os.str();
    }
};
 
class NIdentifier : public NExpression {
public:
    std::string name;
    NIdentifier(const std::string& name) : name(name) { }
    virtual std::string& ToString(std::string& str)
    {
        return str+=name;
    }
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
    virtual std::string& ToString(std::string& str)
    {
        std::ostringstream os;
        os<<"op("<<op<<"){\nlhs:";
        std::string t=os.str();
        lhs.ToString(t);
        t+=",\nrhs:";
        rhs.ToString(t);
        t+="\n}\n";
        return str+=t;
    }
};
 
class NAssignment : public NExpression {
public:
    NIdentifier& lhs;
    NExpression& rhs;
    NAssignment(NIdentifier& lhs, NExpression& rhs) :
        lhs(lhs), rhs(rhs) { }
    virtual std::string& ToString(std::string& str)
    {
        str+="assignment:{\nlhs:";
        lhs.ToString(str);
        str+=",\nrhs:";
        rhs.ToString(str);
        str+="\n}\n";
        return str;
    }
};
 
class NBlock : public NStatement {
public:
    StatementList statements;
    NBlock() { }
    virtual std::string& ToString(std::string& str)
    {
        str+="block:[\n";
        StatementList::iterator iter;
        for(iter=statements.begin();iter!=statements.end();iter++)
        {
            (*iter)->ToString(str);
            str+=",\n";
        }
        str+="]\n";
        return str;
    }
    virtual const std::string* ToString()
    {
        std::string* str=new std::string("block:[\n");
        StatementList::iterator iter;
        for(iter=statements.begin();iter!=statements.end();iter++)
        {
            const std::string* in=(*iter)->ToString();
            *str+=*in+",\n";
            delete in;
        }
        *str+="]\n";
        return str;
    }
};
 
class NExpressionStatement : public NStatement {
public:
    NExpression& expression;
    NExpressionStatement(NExpression& expression) :
        expression(expression) { }
    virtual std::string& ToString(std::string& str)
    {
        return expression.ToString(str);
    }
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
        id(id), position(-1), assignmentExpr(assignmentExpr) { }
    NVariableDeclaration(NIdentifier& id, int pos, NExpression *assignmentExpr) :
        id(id), position(pos), assignmentExpr(assignmentExpr) { }
};
