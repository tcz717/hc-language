#include "node.h"
const std::string* Node::ToString()
{
    auto str = new std::string;
    ToString(*str);
    return str;
}
std::ostream& operator<< (std::ostream &os, Node &it) 
{
    const std::string *str=it.ToString();
    os<<*str<<std::endl;
    delete str;
    return os;
}


std::string& Node::ToString(std::string& str)
{
    return str+=std::string("Node");
}
std::string& NInteger::ToString(std::string& str)
{
    std::ostringstream os;
    os<<value;
    return str+=os.str();
}
std::string& NIdentifier::ToString(std::string& str)
{
    return str+=name;
}
std::string& NBinaryOperator::ToString(std::string& str)
{
    std::ostringstream os;
    os<<"op("<<op<<"){\nlhs:";
    std::string t=os.str();
    lhs.ToString(t);
    t+=",\nrhs:";
    rhs.ToString(t);
    t+="\n}";
    return str+=t;
}
std::string& NAssignment::ToString(std::string& str)
{
    str+="assignment:{\nlhs:";
    lhs.ToString(str);
    str+=",\nrhs:";
    rhs.ToString(str);
    str+="\n}";
    return str;
}
std::string& NBlock::ToString(std::string& str)
{
    str+="block:[\n";
    StatementList::iterator iter;
    for(iter=statements.begin();iter!=statements.end();iter++)
    {
        (*iter)->ToString(str);
        str+=",\n";
    }
    str+="]";
    return str;
}
std::string& NExpressionStatement::ToString(std::string& str)
{
    return expression.ToString(str);
}
