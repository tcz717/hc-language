#include <iostream> 
#include <cstdlib>
#include "node.h" 
extern NBlock* programBlock; 
extern int yyparse(); 

int main(int argc, char **argv) 
{ 
    yyparse(); 
    std::cout << *programBlock << std::endl; 
    system("pause");
    return 0; 
}