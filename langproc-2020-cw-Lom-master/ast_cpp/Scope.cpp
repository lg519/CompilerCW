#include "../ast_hpp/ast.hpp"

extern int max_args_size;
static int starting_position = max_args_size + 4;

Scope::Scope()
: fp_offset(starting_position)
,symbol_table({})
,parent_scope(NULL)
,old_fp(0)
,start_label("")
,break_label("")
,is_loop(false)
{}


Scope::~Scope()
{   
    if(parent_scope != NULL)
    { 
        delete parent_scope;
    }       
}

void Scope::update_symbol_table(std::string id_)
{
    
    symbol_table.insert({id_,fp_offset});
    fp_offset += 4;
}

void Scope::update_symbol_table_param(std::string id_, int rel_offset)
{
    
    symbol_table.insert({id_,rel_offset});
    
}

void Scope::print_symbol_table() const
{
    std::cout << "//" << std::endl;
    for(auto it : symbol_table){
        std::cout<< it.first << " " << it.second << std::endl;
    }
    std::cout << "//" << std::endl;
}

int Scope::get_fp_offset(std::string id_)
{
    if(symbol_table.find(id_) == symbol_table.end())
    {
        //assuming variables are declared at least in the global scope
        if(parent_scope == NULL) return -1;
        return parent_scope->get_fp_offset(id_);
    }
    else
    {
        return symbol_table[id_];
    }
    
}

//int Scope::get_current_fp_offset() const
//{
//    return fp_offset;
//}


void Scope::update_fp_offset_and_symbol_table(int fp_offset_)
{
    
    
    for(auto& it : symbol_table){
        
        it.second += fp_offset_ - starting_position;
        
    }
    
    fp_offset += fp_offset_  - starting_position;
}
void Scope::update_parent_scope(Scope* parent_scope_)
{
    parent_scope = parent_scope_;
    parent_scope->update_fp_offset_and_symbol_table(fp_offset);
}

Scope* Scope::get_parent_scope()
{
    return parent_scope;
}

void Scope::update_start_label(std::string label_)
{
    
    if (parent_scope == NULL)
    {
        start_label = label_;
        is_loop = true;
    }
    else{
    
    if (parent_scope->get_is_loop()==false)
    {
        start_label = label_;
        is_loop = true;
    }
    }
    
}

void Scope::update_break_label(std::string label_)
{
    if (parent_scope == NULL)
    {
        break_label = label_;
        is_loop = true;
    }
    else{
    
    if (parent_scope->get_is_loop()==false)
    {
        break_label = label_;
        is_loop = true;
    }
    }
    
    
}
std::string Scope::get_start_label()
{
    if (start_label == ""){ return parent_scope->get_start_label();}
    return start_label;
}

std::string Scope::get_break_label()
{
    if (break_label == ""){ return parent_scope->get_break_label();}
    return break_label;
}
bool Scope::get_is_loop()
{
    return is_loop;
}


int Scope::get_old_fp() const
{
    return old_fp;
}

void Scope::update_old_fp(int old_fp_)
{
    old_fp = old_fp_;
}

void Scope::update_symbol_table_array(std::string id_, int size)
{
    symbol_table.insert({id_,fp_offset});
    fp_offset += 4*size;
}