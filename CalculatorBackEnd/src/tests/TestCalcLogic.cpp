#include "CppUTest/TestHarness.h"
#include "../production/include/CalcLogic.h"

#include <iostream>

using namespace std;

TEST_GROUP(TestCalcLogic){
    void setup(){
        // Init stuff
    }

    void teardown(){
        // Un-init stuff
    }};

TEST(TestCalcLogic, AddInput_1)
{

    CalcStandard calc;

    calc.add_num_to_main_field(CalcStandard::NUM1);
    calc.add_num_to_main_field(CalcStandard::NUM2);
    calc.add_num_to_main_field(CalcStandard::NUM3);
    calc.add_num_to_main_field(CalcStandard::NUM4);
    calc.add_num_to_main_field(CalcStandard::NUM5);
    calc.add_num_to_main_field(CalcStandard::NUM6);
    calc.add_num_to_main_field(CalcStandard::NUM7);
    calc.add_num_to_main_field(CalcStandard::NUM8);
    calc.add_num_to_main_field(CalcStandard::NUM9);
    calc.add_num_to_main_field(CalcStandard::NUM0);
    calc.add_num_to_main_field(CalcStandard::DOT);

    CHECK_EQUAL("1,234,567,890.", calc.get_main_field());

    calc.set_aux_field(".");
    calc.update_aux_field();

    CHECK_EQUAL(".1,234,567,890.", calc.get_aux_field());
}

TEST(TestCalcLogic, AddInput_CanAddOnlyOneDot_2)
{

    CalcStandard calc;

    calc.add_num_to_main_field(CalcStandard::DOT);

    CHECK_EQUAL("0.", calc.get_main_field());

    calc.add_num_to_main_field(CalcStandard::DOT);
    CHECK_EQUAL("0.", calc.get_main_field());
}

TEST(TestCalcLogic, AddInput_IfZero_ZeroStayes_3)
{

    CalcStandard calc;
    CHECK_EQUAL("0", calc.get_main_field());

    calc.add_num_to_main_field(CalcStandard::NUM0);

    CHECK_EQUAL("0", calc.get_main_field());
    calc.add_num_to_main_field(CalcStandard::NUM0);
    calc.add_num_to_main_field(CalcStandard::NUM0);
    calc.add_num_to_main_field(CalcStandard::NUM0);
    CHECK_EQUAL("0", calc.get_main_field());
}

TEST(TestCalcLogic, TestOperations_ADD_4)
{

    CalcStandard calc;
    CHECK_EQUAL("0", calc.get_main_field());
    CHECK_EQUAL("", calc.get_aux_field());

    calc.add_num_to_main_field(CalcStandard::NUM2);
    calc.add_num_to_main_field(CalcStandard::NUM3);
    CHECK_EQUAL("23", calc.get_main_field());

    calc.do_operation(CalcStandard::ADD);

    CHECK_EQUAL("0", calc.get_main_field());
    CHECK_EQUAL("23 + ", calc.get_aux_field());
}

TEST(TestCalcLogic, TestOperations_ADD_repeat_4)
{

    CalcStandard calc;
    CHECK_EQUAL("0", calc.get_main_field());
    CHECK_EQUAL("", calc.get_aux_field());

    calc.add_num_to_main_field(CalcStandard::NUM2);
    calc.add_num_to_main_field(CalcStandard::NUM3);
    CHECK_EQUAL("23", calc.get_main_field());

    calc.do_operation(CalcStandard::ADD);

    CHECK_EQUAL("0", calc.get_main_field());
    CHECK_EQUAL("23 + ", calc.get_aux_field());

    calc.do_operation(CalcStandard::ADD);
    CHECK_EQUAL("0", calc.get_main_field());
    CHECK_EQUAL("0 + ", calc.get_aux_field());
}

TEST(TestCalcLogic, TestOperations_Sub_5)
{

    CalcStandard calc;
    CHECK_EQUAL("0", calc.get_main_field());
    CHECK_EQUAL("", calc.get_aux_field());

    calc.add_num_to_main_field(CalcStandard::NUM2);
    calc.add_num_to_main_field(CalcStandard::NUM3);
    CHECK_EQUAL("23", calc.get_main_field());

    calc.do_operation(CalcStandard::SUB);

    CHECK_EQUAL("0", calc.get_main_field());
    CHECK_EQUAL("23 - ", calc.get_aux_field());
}

TEST(TestCalcLogic, TestOperations_Sub_repeat_5)
{

    CalcStandard calc;
    CHECK_EQUAL("0", calc.get_main_field());
    CHECK_EQUAL("", calc.get_aux_field());

    calc.add_num_to_main_field(CalcStandard::NUM2);
    calc.add_num_to_main_field(CalcStandard::NUM3);
    CHECK_EQUAL("23", calc.get_main_field());

    calc.do_operation(CalcStandard::SUB);

    CHECK_EQUAL("0", calc.get_main_field());
    CHECK_EQUAL("23 - ", calc.get_aux_field());

    calc.do_operation(CalcStandard::SUB);
    CHECK_EQUAL("0", calc.get_main_field());
    CHECK_EQUAL("0 - ", calc.get_aux_field());
}

TEST(TestCalcLogic, TestOperations_MUL_6)
{

    CalcStandard calc;
    CHECK_EQUAL("0", calc.get_main_field());
    CHECK_EQUAL("", calc.get_aux_field());

    calc.add_num_to_main_field(CalcStandard::NUM2);
    calc.add_num_to_main_field(CalcStandard::NUM3);
    CHECK_EQUAL("23", calc.get_main_field());

    calc.do_operation(CalcStandard::MUL);

    CHECK_EQUAL("0", calc.get_main_field());
    CHECK_EQUAL("23 * ", calc.get_aux_field());
}

TEST(TestCalcLogic, TestOperations_MUL_repeat_6)
{

    CalcStandard calc;
    CHECK_EQUAL("0", calc.get_main_field());
    CHECK_EQUAL("", calc.get_aux_field());

    calc.add_num_to_main_field(CalcStandard::NUM2);
    calc.add_num_to_main_field(CalcStandard::NUM3);
    CHECK_EQUAL("23", calc.get_main_field());

    calc.do_operation(CalcStandard::MUL);

    CHECK_EQUAL("0", calc.get_main_field());
    CHECK_EQUAL("23 * ", calc.get_aux_field());

    calc.do_operation(CalcStandard::MUL);
    CHECK_EQUAL("0", calc.get_main_field());
    CHECK_EQUAL("0 * ", calc.get_aux_field());
}

TEST(TestCalcLogic, TestOperations_DIV_7)
{

    CalcStandard calc;
    CHECK_EQUAL("0", calc.get_main_field());
    CHECK_EQUAL("", calc.get_aux_field());

    calc.add_num_to_main_field(CalcStandard::NUM2);
    calc.add_num_to_main_field(CalcStandard::NUM3);
    CHECK_EQUAL("23", calc.get_main_field());

    calc.do_operation(CalcStandard::DIV);

    CHECK_EQUAL("0", calc.get_main_field());
    CHECK_EQUAL("23 / ", calc.get_aux_field());
}

TEST(TestCalcLogic, TestOperations_DIV_repeat_7)
{

    CalcStandard calc;
    CHECK_EQUAL("0", calc.get_main_field());
    CHECK_EQUAL("", calc.get_aux_field());

    calc.add_num_to_main_field(CalcStandard::NUM2);
    calc.add_num_to_main_field(CalcStandard::NUM3);
    CHECK_EQUAL("23", calc.get_main_field());

    calc.do_operation(CalcStandard::DIV);

    CHECK_EQUAL("0", calc.get_main_field());
    CHECK_EQUAL("23 / ", calc.get_aux_field());

    calc.do_operation(CalcStandard::DIV);
    CHECK_EQUAL("0", calc.get_main_field());
    CHECK_EQUAL("0 / ", calc.get_aux_field());
}

TEST(TestCalcLogic, TestOperations_CE_8)
{

    CalcStandard calc;
    CHECK_EQUAL("0", calc.get_main_field());
    CHECK_EQUAL("", calc.get_aux_field());

    calc.add_num_to_main_field(CalcStandard::NUM9);
    calc.add_num_to_main_field(CalcStandard::NUM1);
    calc.set_aux_field("123");
    CHECK_EQUAL("91", calc.get_main_field());

    calc.do_operation(CalcStandard::CE);

    CHECK_EQUAL("0", calc.get_main_field());
    CHECK_EQUAL("123", calc.get_aux_field());
}

TEST(TestCalcLogic, TestOperations_C_9)
{

    CalcStandard calc;
    CHECK_EQUAL("0", calc.get_main_field());
    CHECK_EQUAL("", calc.get_aux_field());

    calc.add_num_to_main_field(CalcStandard::NUM9);
    calc.add_num_to_main_field(CalcStandard::NUM1);
    calc.set_aux_field("123");
    CHECK_EQUAL("91", calc.get_main_field());

    calc.do_operation(CalcStandard::C);

    CHECK_EQUAL("0", calc.get_main_field());
    CHECK_EQUAL("", calc.get_aux_field());
}

TEST(TestCalcLogic, TestOperations_BACKSPACE_10)
{

    CalcStandard calc;
    CHECK_EQUAL("0", calc.get_main_field());
    CHECK_EQUAL("", calc.get_aux_field());

    calc.add_num_to_main_field(CalcStandard::NUM9);
    calc.add_num_to_main_field(CalcStandard::NUM1);
    calc.set_aux_field("123");
    CHECK_EQUAL("91", calc.get_main_field());

    calc.do_operation(CalcStandard::BACKSPACE);

    CHECK_EQUAL("9", calc.get_main_field());
    CHECK_EQUAL("123", calc.get_aux_field());

    calc.do_operation(CalcStandard::BACKSPACE);
    CHECK_EQUAL("0", calc.get_main_field());
    CHECK_EQUAL("123", calc.get_aux_field());

    calc.do_operation(CalcStandard::BACKSPACE);
    calc.do_operation(CalcStandard::BACKSPACE);
    CHECK_EQUAL("0", calc.get_main_field());
    CHECK_EQUAL("123", calc.get_aux_field());

    calc.set_main_field("-2");
    CHECK_EQUAL("-2", calc.get_main_field());
    calc.do_operation(CalcStandard::BACKSPACE);
    CHECK_EQUAL("0", calc.get_main_field());
}

TEST(TestCalcLogic, TestOperations_NEGATE_11)
{

    CalcStandard calc;
    CHECK_EQUAL("0", calc.get_main_field());
    CHECK_EQUAL("", calc.get_aux_field());

    calc.add_num_to_main_field(CalcStandard::NUM9);
    calc.add_num_to_main_field(CalcStandard::NUM1);
    calc.set_aux_field("123");
    CHECK_EQUAL("91", calc.get_main_field());

    calc.do_operation(CalcStandard::NEGATE);

    CHECK_EQUAL("-91", calc.get_main_field());
    CHECK_EQUAL("123", calc.get_aux_field());

    calc.do_operation(CalcStandard::NEGATE);
    CHECK_EQUAL("91", calc.get_main_field());
    CHECK_EQUAL("123", calc.get_aux_field());

    calc.set_main_field("0");
    calc.do_operation(CalcStandard::NEGATE);

    CHECK_EQUAL("0", calc.get_main_field());
    CHECK_EQUAL("123", calc.get_aux_field());
}

TEST(TestCalcLogic, TestOperations_EQUAL_12)
{

    CalcStandard calc;
    calc.set_main_field("12345");
    calc.set_aux_field("");
    CHECK_EQUAL("12345", calc.get_main_field());

    calc.do_operation(CalcStandard::EQUAL);

    CHECK_EQUAL("0", calc.get_main_field());
    CHECK_EQUAL("12345 = ", calc.get_aux_field());

    calc.do_operation(CalcStandard::EQUAL);
    //main_field = perform_calc(aux_field);CHECK_EQUAL("0", calc.get_main_field());
    CHECK_EQUAL("0 = ", calc.get_aux_field());
}

TEST(TestCalcLogic, TestOperations_EQUAL_13)
{

    CalcStandard calc;
    calc.set_main_field("12345");
    calc.set_aux_field("");
    CHECK_EQUAL("12345", calc.get_main_field());
    CHECK_EQUAL("", calc.get_aux_field());

    calc.do_operation(CalcStandard::ADD);

    CHECK_EQUAL("0", calc.get_main_field());
    CHECK_EQUAL("12345 + ", calc.get_aux_field());

    calc.do_operation(CalcStandard::EQUAL);
    CHECK_EQUAL("12,345", calc.get_main_field());
    CHECK_EQUAL("12345 + 0 = ", calc.get_aux_field());

    calc.add_num_to_main_field(CalcStandard::NUM3);
    CHECK_EQUAL("3", calc.get_main_field());
    CHECK_EQUAL("", calc.get_aux_field());

    calc.do_operation(CalcStandard::EQUAL);

    CHECK_EQUAL("0", calc.get_main_field());
    CHECK_EQUAL("3 = ", calc.get_aux_field());

    calc.add_num_to_main_field(CalcStandard::NUM5);
    calc.do_operation(CalcStandard::EQUAL);
    CHECK_EQUAL("0", calc.get_main_field());
    CHECK_EQUAL("5 = ", calc.get_aux_field());

    calc.add_num_to_main_field(CalcStandard::NUM9);
    calc.do_operation(CalcStandard::DIV);
    CHECK_EQUAL("9 / ", calc.get_aux_field());
    CHECK_EQUAL("0", calc.get_main_field());

    calc.do_operation(CalcStandard::SUB);
    CHECK_EQUAL("0 - ", calc.get_aux_field());


 
}

TEST(TestCalcLogic, TestOperations_PerformCalc_14)
{

    CalcStandard calc;
    string result = calc.perform_calc("12 + 10 = ");
    CHECK_EQUAL("22", result);

    result = calc.perform_calc("1,012 + 10 = ");
    CHECK_EQUAL("1022", result);

    result = calc.perform_calc("1,012 * 10 = ");
    CHECK_EQUAL("10120", result);

    result = calc.perform_calc("1,012 / 10,,0 = ");
    CHECK_EQUAL("10.12", result);

    result = calc.perform_calc("43 / 0 = ");
    CHECK_EQUAL("Can't divide by zero", result);

    result = calc.perform_calc("43 - 44 = ");
    CHECK_EQUAL("-1", result);

    result = calc.perform_calc("4000 * 10 = ");
    CHECK_EQUAL("40000", result);
}


TEST(TestCalcLogic, TestOperations_AddCommas_15)
{

    string str_with_no_commas = "-123123.123123";
    string result = "";
    add_commas(str_with_no_commas, result);
    CHECK_EQUAL("-123,123.123123", result);


    str_with_no_commas = "123123.123123";
     result = "";
    add_commas(str_with_no_commas, result);
    CHECK_EQUAL("123,123.123123", result);
}


TEST(TestCalcLogic, CommasInAuxField_16)
{

    CalcStandard calc;

    calc.add_num_to_main_field(CalcStandard::NUM1);
    calc.add_num_to_main_field(CalcStandard::NUM2);
    calc.add_num_to_main_field(CalcStandard::NUM3);
    calc.add_num_to_main_field(CalcStandard::NUM4);
    calc.add_num_to_main_field(CalcStandard::NUM5);
    calc.add_num_to_main_field(CalcStandard::NUM6);
    calc.add_num_to_main_field(CalcStandard::NUM7);
    calc.add_num_to_main_field(CalcStandard::NUM8);
    calc.add_num_to_main_field(CalcStandard::NUM9);
    calc.add_num_to_main_field(CalcStandard::NUM0);
    calc.add_num_to_main_field(CalcStandard::DOT);

    CHECK_EQUAL("1,234,567,890.", calc.get_main_field());

    calc.do_operation(CalcStandard::ADD);
    CHECK_EQUAL("0", calc.get_main_field());
    CHECK_EQUAL("1,234,567,890. + ", calc.get_aux_field());

    calc.add_num_to_main_field(CalcStandard::NUM1);
    calc.add_num_to_main_field(CalcStandard::NUM2);
    calc.do_operation(CalcStandard::NEGATE);
    CHECK_EQUAL("-12", calc.get_main_field());

    calc.do_operation(CalcStandard::EQUAL);

    CHECK_EQUAL("1,234,567,878", calc.get_main_field());
    CHECK_EQUAL("1,234,567,890. + -12 = ", calc.get_aux_field());
}


TEST(TestCalcLogic, ExprRes_Oper_NewNum_Eq_17)
{

    CalcStandard calc;

    calc.add_num_to_main_field(CalcStandard::NUM1);
    calc.do_operation(CalcStandard::ADD);
    calc.add_num_to_main_field(CalcStandard::NUM2);
    calc.do_operation(CalcStandard::EQUAL);

    CHECK_EQUAL("3", calc.get_main_field());
    CHECK_EQUAL("1 + 2 = ", calc.get_aux_field());

    calc.do_operation(CalcStandard::MUL);
    calc.add_num_to_main_field(CalcStandard::NUM4);

    CHECK_EQUAL("4", calc.get_main_field());
    CHECK_EQUAL("3 * ", calc.get_aux_field());

    calc.do_operation(CalcStandard::EQUAL);
    CHECK_EQUAL("12", calc.get_main_field());
    CHECK_EQUAL("3 * 4 = ", calc.get_aux_field());
}