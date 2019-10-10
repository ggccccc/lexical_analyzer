#pragma once
#ifndef UTILS_H
#define UTILS_H
#define chars_num 49

#include <string>

using namespace std;


enum LEXICAL_TYPE {
	LCINT, LKEYWORD, LIDENTIFIER, LTYPE, LBORDER, LUNKNOWN, LEOF, LOPERATOR, LBEGIN,
	LCFLOAT, LCDOUBLE, LCCHAR, LCSTRING, LCERROR, LOERROR
};//C��ͷ�Ĵ���������,LCERROR��ʾ��������,LOERROR��ʾ���������LWERROR��ʾ���ʴ���,LNO��ʾ��


struct WordInfo//�ۺ�����
{
	LEXICAL_TYPE type;//������
	string value;//������ֵ�����߹ؼ��ֱ���
};





#endif