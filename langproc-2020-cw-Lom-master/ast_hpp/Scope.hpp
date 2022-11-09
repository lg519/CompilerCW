#ifndef Scope_hpp
#define Scope_hpp



#include <iostream>
#include <unordered_map>
#include <string>

class Scope
{
protected:
    std::unordered_map<std::string,int> symbol_table;
    Scope* parent_scope;
    std::string start_label;
    std::string break_label;
    bool is_loop;

    int fp_offset;
    int old_fp;

public:

    Scope();
    
   
    virtual ~Scope();

    void update_symbol_table(std::string id_);

    void print_symbol_table() const;

    int get_fp_offset(std::string id_);

    //int get_current_fp_offset() const;

    void update_fp_offset_and_symbol_table(int fp_offset_);

    void update_parent_scope(Scope* parent_scope_);

    void update_symbol_table_param(std::string id_, int rel_offset);

    int get_old_fp() const;

    void update_old_fp(int old_fp_);

    void update_symbol_table_array(std::string id_, int size);
    
    Scope* get_parent_scope();

    void update_start_label(std::string label_);

    void update_break_label(std::string label_);

    std::string get_start_label();

    std::string get_break_label();

    bool get_is_loop();
};

#endif

