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

typedef struct Point_
{
	int x;
	int y;
	Point_(int x_, int y_) { x = x_; y = y_; }
}Point;

typedef struct Maze_
{	
	const static int n = 10;
	int mz[n][n];
}Maze;

/*
 * �Թ����
 */
bool maze_out(Maze& mz, int n, Point& start, TstStack<Point>& trail);

/*
 * ����ת��
 */
void num_conversion(int num, int cv, TstStack<char>& stk);

/*
 * �б༭
 */
void edit_row();

#endif