#ifndef _TST_STACK_APP_H_
#define _TST_STACK_APP_H_

#include "tst_stack.hpp"
#include <string>

/*
 * 中缀表达式转为后缀表达式，并求解
 */
bool split_formula(char* str, TstList<std::string>& lst);
bool is_number(std::string& str);
bool is_right_formula(TstList<std::string>& lst);
bool mid_to_aft(TstList<std::string>& lst_mid_formula, TstList<std::string>& lst_aft_formula);
double str_to_num(std::string& str);
double calculate(TstList<std::string>& lst_aft_formula);

/*
 * 括号匹配
 */
bool match_bracket(char* str);

/*
 * 迷宫求解
 */

/*
 * 数制转换
 */

/*
 * 行编辑
 */


#endif