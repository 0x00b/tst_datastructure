#include "tst_stack_app.h"

#include <assert.h>

///////////////////////////////////
/*
* �ѹ�ʽ�ַ�����ֳɵ���Ԫ�أ����ڶ�����
*/
bool split_formula(char* str, TstList<std::string>& lst)
{
	assert(str != NULL);

	std::string temp("");

	while (*str != 0)
	{
		if (*str == '+' || *str == '-' || *str == '*' || *str == '/' || *str == '(' || *str == ')')
		{
			temp = *str++;
			lst.push_back(temp);
		}
		else if (('0' <= *str && *str <= '9') || *str == '.')
		{
			do
			{
				temp += *str++;
			} while ((*str != 0 && (('0' <= *str && *str <= '9') || *str == '.')));

			lst.push_back(temp);
		}
		else if (*str == ' ')
		{
			str++;
		}
		else
		{
			return false;
		}
		temp.clear();
	}
	return true;
}

/*
* �жϴ�������
*/
bool is_number(std::string& str)
{
	if (!str.empty())
	{
		int point_count = 0;
		for (std::string::iterator it = str.begin(); it != str.end(); ++it)
		{
			if ((*it) < '0' || (*it) > '9' )
			{
				if ((*it) == '.')
				{
					if (point_count > 0)
					{
						return false;
					}
					point_count++;
				}
				else
				{
					return false;
				}
			}
		}
		return true;
	}
	return false;
}

/*
* �ж�һ�����ʽ����ȷ�ģ����磺3*��23+2������ȷ�ģ�����3��23+2���Ǵ���ġ�
*/
bool is_right_formula(TstList<std::string>& lst)
{
	return true;
}
/*
* ��׺���ʽת��׺���ʽ
*
* 1������ֱ�������������ʽ���С�
* 2������ "+","-" �����ȵ�������ջ�е�Ԫ�أ�����һ��Ԫ������Ҫ�����Ԫ�طŽ�������ʽ���У���ջʱ���� "(" ����ջ��Ϊֹ��Ȼ��ѵ�ǰ�ķ��ŷŽ�����ջ��
* 3������ "*","/","("����ֱ��ѹ������ջ��
* 4������ ")"�� ����Ҫ��������ջ�е�Ԫ�أ�ֱ���ҵ���֮��Ӧ��ǰ���"("Ϊֹ��
* 5����������ʽ������û��Ԫ��ʱ��һ�ε�������ջ�е�Ԫ�أ�ͬʱ�Ž��������ʽ�����С�
*/
bool mid_to_aft(TstList<std::string>& lst_mid_formula, TstList<std::string>& lst_aft_formula)
{
	TstStack<std::string> stk_formula;

	if (!is_right_formula(lst_mid_formula))
	{
		return false;
	}
	for (TstList<std::string>::iterator it = lst_mid_formula.begin(); it != lst_mid_formula.end(); ++it)
	{
		std::string& str = *it;

		if (is_number(str))
		{
			lst_aft_formula.push_back(str);
		}
		else if ('+' == str[0] || '-' == str[0])
		{
			while (!stk_formula.empty())
			{
				std::string& str_top = stk_formula.top();
				if (str_top[0] != '(')
				{
					lst_aft_formula.push_back(str_top);
					stk_formula.pop();
				}
				else
				{
					break;
				}
			}

			stk_formula.push(str);
		}
		else if ('*' == str[0] || '/' == str[0])
		{
			stk_formula.push(str);
		}
		else if ('(' == str[0])
		{
			stk_formula.push(str);
		}
		else if (')' == str[0])
		{
			std::string str_top("");
			while ((str_top = stk_formula.top())[0] != '(')
			{
				stk_formula.pop();
				lst_aft_formula.push_back(str_top);
			}
			stk_formula.pop();
		}
	}
	while (!stk_formula.empty())
	{
		lst_aft_formula.push_back(stk_formula.top());
		stk_formula.pop();
	}
	return true;
}
/*
 * �ַ���ת������Ӧ����ֵ
 */
double str_to_num(std::string& str)
{
	double result = 0.;
	double dpow = 10.0;
	bool point_flag = false;
	for (std::string::iterator it = str.begin(); it != str.end(); ++it)
	{
		if ('0' <= *it && *it <= '9')
		{
			if (!point_flag)
			{
				result = result * 10 + ((*it) - '0');
			}
			else
			{
				result += ((*it) - '0')/ dpow;
				dpow *= 10;
			}
		}
		else
		{
			if (*it == '.')
			{
				point_flag = true;
			}
		}
	}
	return result;
}
/*
 * ���ݺ�׺���ʽ���ֵ
 */
double calculate(TstList<std::string>& lst_aft_formula)
{
	if (lst_aft_formula.empty())
	{
		return 0.;
	}
	double result = 0.;
	double num1 = 0;
	double num2 = 0;
	TstStack<double> t_stk;
	for (TstList<std::string>::iterator it = lst_aft_formula.begin(); it != lst_aft_formula.end(); ++it)
	{
		std::string& ele = *it;
		if (is_number(ele))
		{
			t_stk.push(str_to_num(ele));
		}
		else 
		{
			num1 = t_stk.top();
			t_stk.pop();
			num2 = t_stk.top();
			t_stk.pop();
			switch (ele[0])
			{
				case '+':
				{
					result = num2 + num1;
				}break;
				case '-':
				{
					result = num2 - num1;
				}break;
				case '*':
				{
					result = num2 * num1;
				}break;
				case '/':
				{
					result = num2 / num1;
				}break;
				default:
					break;
			}
			t_stk.push(result);
		}
	}
	return t_stk.top();
}

/*--------------------------- ����ƥ�� -----------------------------*/

bool match_bracket(char* str)
{
	TstStack<char> c_stk;
	bool res = true;
	while (*str != 0)
	{
		if (*str == '(' || *str == '[' || *str == '{'  )
		{
			c_stk.push(*str);
		}
		else
		{
			switch (*str)
			{
				case ')':
				{
					if (c_stk.top() != '(')
					{
						res = false;
					}
				}break;

				case ']':
				{
					if (c_stk.top() != '[')
					{
						res = false;
					}
				}break;

				case '}':
				{
					if (c_stk.top() != '{')
					{
						res = false;
					}
				}break;

				default:
				{
					res = false; 
					break;
				}
			}
			if (!res)
			{
				break;
			}
			c_stk.pop();
		}
		str++;
	}
	return res;
}