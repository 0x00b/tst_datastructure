#ifndef _TST_STACK_APP_H_
#define _TST_STACK_APP_H_

#include "tst_stack.hpp"
#include <string>

/*
 * ��׺���ʽתΪ��׺���ʽ�������
 */
bool split_formula(char* str, TstList<std::string>& lst);
bool is_number(std::string& str);
bool is_right_formula(TstList<std::string>& lst);
bool mid_to_aft(TstList<std::string>& lst_mid_formula, TstList<std::string>& lst_aft_formula);
double str_to_num(std::string& str);
double calculate(TstList<std::string>& lst_aft_formula);

/*
 * ����ƥ��
 */
bool match_bracket(char* str);

/*
 * �Թ����
 */

/*
 * ����ת��
 */

/*
 * �б༭
 */


#endif