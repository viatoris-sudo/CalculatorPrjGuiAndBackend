#include "include/CalcLogic.h"
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

CalcStandard::CalcStandard() : main_field("0"), aux_field(""), is_eq_repeat(false), was_operation(false), should_delete(false)
{
    // Конструктор
}

CalcStandard::~CalcStandard()
{
    // Деструктор
}

void CalcStandard::add_num_to_main_field(bttns_t num)
{

    is_eq_repeat = false;
    if (should_delete)
    {
        should_delete = false;
        main_field = "0";
        aux_field = "";
    }

    string s_no_comma = main_field;

    remove_str_from_str(s_no_comma, ",");
    remove_str_from_str(s_no_comma, "-");
    remove_str_from_str(s_no_comma, ".");

    if (s_no_comma.length() >= 16)
    {
        return;
    }

    remove_str_from_str(main_field, ",");
    // Добавление числа к главному полю

    switch (num)
    {
    case NUM0:
        if (main_field == "0")
        {
            break;
        }
        main_field += "0";
        break;
    case NUM1:
    case NUM2:
    case NUM3:
    case NUM4:
    case NUM5:
    case NUM6:
    case NUM7:
    case NUM8:
    case NUM9:
        if (main_field == "0")
        {
            main_field = to_string(num);
            break;
        }

        main_field += to_string(num);
        break;
    case DOT:
        if (main_field.find('.') != std::string::npos)
        {
            break;
        }
        main_field += ".";
        break;
    default:
        break;
    }

    add_commas(main_field, main_field);
}

void CalcStandard::do_operation(operations_t operation)
{
    if (operation != CalcStandard::NEGATE && operation != CalcStandard::BACKSPACE)
    {
        is_eq_repeat = false;
        if (should_delete)
        {
            should_delete = false;
            aux_field = "";
        }
    }

    switch (operation)
    {
    case PERCENT:

        break;
    case CE:
        main_field = "0";
        break;
    case C:
        aux_field = "";
        main_field = "0";
        was_operation = false;
        break;
    case BACKSPACE:
        if (main_field.size() == 1 || main_field.size() == 2 && main_field[0] == '-')
            main_field = "0";
        else
            main_field.pop_back();
        break;
    case DIV:
        was_operation = true;
        aux_field = main_field;
        aux_field += " / ";
        main_field = "0";
        break;
    case MUL:
        was_operation = true;
        aux_field = main_field;
        aux_field += " * ";
        main_field = "0";
        break;
    case SUB:
        was_operation = true;
        aux_field = main_field;
        aux_field += " - ";
        main_field = "0";
        break;
    case ADD:
        was_operation = true;
        aux_field = main_field;
        aux_field += " + ";
        main_field = "0";
        break;
    case EQUAL:

        if (is_eq_repeat)
        {
            size_t index = aux_field.find(' ');

            if (index != std::string::npos)
            {
                aux_field.replace(0, index + 1, "");
            }

            aux_field = main_field + " " + aux_field;

            main_field = perform_calc(aux_field);
            add_commas(main_field, main_field);
            return;
        }

        if (was_operation)
        {
            aux_field.append(main_field);
            aux_field.append(" = ");
            main_field = perform_calc(aux_field);
            add_commas(main_field, main_field);
            is_eq_repeat = true;
            should_delete = true;
            was_operation = false;
        }
        else
        {
            aux_field = "";
            aux_field.append(main_field);
            aux_field.append(" = ");
            main_field = "0";
        }

        break;

    case NEGATE:
        if (main_field[0] == '0' && main_field.size() == 1)
        {
            return;
        }
        if (main_field.size() > 1 && main_field[0] == '-')
        {
            main_field.erase(0, 1);
        }
        else
        {
            main_field = "-" + main_field;
        }
        break;

    default:

        break;
    }
}

string CalcStandard::perform_calc(string expression)
{
    // Парсим строку
    string to_remove = ",";
    remove_str_from_str(expression, to_remove);
    string l_val = "";
    string r_val = "";
    string operation = "";

    int spacePos = expression.find(' ');
    if (spacePos != std::string::npos)
    {
        l_val = expression.substr(0, spacePos);
        expression.replace(0, spacePos + 1, "");
    }

    spacePos = expression.find(' ');
    if (spacePos != std::string::npos)
    {
        operation = expression.substr(0, spacePos);
        expression.replace(0, spacePos + 1, "");
    }

    spacePos = expression.find(' ');
    if (spacePos != std::string::npos)
    {
        r_val = expression.substr(0, spacePos);
    }

    double l_val_d = stod(l_val);
    double r_val_d = stod(r_val);
    double result = 0;

    // выбираем нужную операцию
    if (operation.find('*') != std::string::npos)
    {
        result = l_val_d * r_val_d;
    }
    else if (operation.find('+') != std::string::npos)
    {
        result = l_val_d + r_val_d;
    }
    else if (operation.find('-') != std::string::npos)
    {
        result = l_val_d - r_val_d;
    }
    else if (operation.find('/') != std::string::npos)
    {
        if (r_val_d != 0)
            result = l_val_d / r_val_d;
        else
        {
            string result_str = "Can't divide by zero";
            delete_appending_zeros(result_str);
            return result_str;
        }
    }

    // ФОрмируем строку для ответа и конец
    string result_str = std::to_string(result);
    delete_appending_zeros(result_str);
    return result_str;
}

void add_commas(string str_to_change, string &ret_str)
{
    if (str_to_change[0] == 'C')
    {
        return;
    }

    bool is_negative = false;
    if (str_to_change.find('-') != std::string::npos)
    {
        is_negative = true;

        string to_remove = "-";
        remove_str_from_str(str_to_change, to_remove);
    }

    string new_displ = "";
    int counter = 0;
    int dot_ind = -1;

    dot_ind = str_to_change.find('.');

    for (int i = str_to_change.length() - 1; i >= 0; --i)
    {
        new_displ = str_to_change[i] + new_displ;
        counter++;
        if (i >= dot_ind && dot_ind != std::string::npos)
        {
            counter = 0;
        }
        else if (counter == 3)
        {
            new_displ = "," + new_displ;
            counter = 0;
        }
    }

    if (new_displ[0] == ',')
        new_displ.erase(0, 1); // Удаляет 1 символ с позиции 0

    if (is_negative)
        new_displ = '-' + new_displ;

    ret_str = new_displ;
}

int remove_str_from_str(string &str, const string str_to_remove)
{
    size_t how_many_deleted = erase_if(str, [&str_to_remove](char c)
                                       { return str_to_remove.find(c) != std::string::npos; });

    return (int)how_many_deleted;
}

void delete_appending_zeros(string &result)
{ // Убираем лишние нули и точку, если число целое
    if (result.find('.') != std::string::npos)
    {
        result.erase(result.find_last_not_of('0') + 1);
        if (result.back() == '.')
        {
            result.pop_back(); // Удаляем точку, если нет десятичной части
        }
    }
}