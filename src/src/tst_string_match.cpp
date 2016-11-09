#include "tst_string_match.h"
#include <string.h>
#include <assert.h>

int Index(char* str, char* obj)
{
	int i = 0, j = 0;
	int str_len = strlen(str);
	int obj_len = strlen(obj);

	while (i < str_len && j < obj_len)
	{
		if (str[i] == obj[j])
		{
			i++;
			j++;
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
	}
	if (j >= obj_len)
	{
		return i - obj_len;
	}
	return -1;
}

/* KMP算法的精髓在于next数组的求解 ，与主串没有任何关系*/
static void NEXT(char* str, int str_len, int* next)
{
	int i = 1, j = 0;
	/* 假设有串 ：abcdffd，则前两个字符的next值是可以确定的，i=1,j=0,则下面的循环第一次执行 next[i] = j时，i=2，所以循环的内容是从第3个字符的next开始算起*/
	next[0] = -1;
	if (str_len > 1)
	{
		next[1] = (str[0] == str[1]) ? -1 : 0;
	}
	while (i < str_len - 1)
	{
		if (j == -1 || str[i] == str[j])
		{
			i++;
			j++;
			next[i] = j;
		}
		else
		{
			j = next[j];
		}
	}
}
int KMP(char* str, char* obj)
{
	assert(str != NULL && obj != NULL);

	int obj_len = strlen(obj);
	int str_len = strlen(str);
	int* next = new int[obj_len];
	int i = 0, j = 0;
	int pos = -1;
	NEXT(obj, obj_len, next);

	while (i < str_len && j < obj_len)
	{
		if (j==-1 || str[i] == obj[j])
		{
			i++;
			j++;
		}
		else
		{
			j = next[j];
		}
	}
	if (j >= obj_len)
	{
		pos = i - obj_len;
	}
	delete[] next;
	return pos;
}
