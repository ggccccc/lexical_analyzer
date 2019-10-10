#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

using namespace std;


enum LEXICAL_TYPE {
	LCINT, LKEYWORD, LIDENTIFIER, LTYPE, LBORDER, LUNKNOWN, LEOF, LOPERATOR, LBEGIN,
	LCFLOAT, LCDOUBLE, LCCHAR, LCSTRING, LCERROR, LOERROR
};//C开头的代表常数类型,LCERROR表示常数错误,LOERROR表示运算符错误，LWERROR表示单词错误,LNO表示空


struct WordInfo//综合属性
{
	LEXICAL_TYPE type;//词类型
	string value;//常量的值，或者关键字本身
	string word_string;
};

#endif