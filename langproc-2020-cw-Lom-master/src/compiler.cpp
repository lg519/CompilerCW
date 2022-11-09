#include<iostream>
#include "../ast_hpp/ast.hpp"

int main()
{
	const node* AST = NULL;
    AST = parseAST();

    
    
    //std::cout << "parse completed" << std::endl;
    //AST->print(std::cout);
    //std::cout << "print completed" << std::endl;

    //std::cout << std::endl << std::endl << std::endl;

    AST->compile(std::cout);
    //std::cout << "compile completed" << std::endl;
    
}
