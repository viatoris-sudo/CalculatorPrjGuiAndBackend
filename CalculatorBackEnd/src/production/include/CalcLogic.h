
#pragma once
#include <string>
using namespace std;

void add_commas(string str_to_change, string &ret_str);
int remove_str_from_str(string &str, const string str_to_remove);
void delete_appending_zeros(string &result);

class CalcStandard
{
private:
    string main_field;
    string aux_field;
    bool is_eq_repeat;
    bool was_operation;
    bool should_delete;

public:
    typedef enum bttns
    {

        NUM0 = 0,
        NUM1,
        NUM2,
        NUM3,
        NUM4,
        NUM5,
        NUM6,
        NUM7,
        NUM8,
        NUM9,
        DOT,
        
    }bttns_t;

    typedef enum operations
    {
        NEGATE,
        PERCENT,
        CE,
        C,
        BACKSPACE,
        DIV,
        MUL,
        SUB,
        ADD,
        EQUAL,

        SQRT,
        SQR,

    } operations_t;

    CalcStandard();
    ~CalcStandard();

    string perform_calc(string expression);
    void add_num_to_main_field(bttns_t num);
    void do_operation(operations_t operation);

    string get_main_field() const
    {
        return main_field;
    }
    string get_aux_field() const
    {
        return aux_field;
    }
    void set_main_field(string str)
    {
        main_field = str;
    }
    void set_aux_field(string str)
    {
        aux_field = str;
    }
    void update_aux_field()
    {
        aux_field += main_field;
    }
};