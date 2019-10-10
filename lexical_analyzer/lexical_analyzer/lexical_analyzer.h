#pragma once
#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include<iostream>
#include<fstream>
#include<string>
#include<set>
#include"utils.h"
using namespace std;


class LexicalAnalyzer {
private:
	set<string> OPERATORS = { "+","-","*","/","=,","==",">",">=","<","<=","!=" };
	set<string> KEYWORDS = 
	{ 
		"auto", "break", "case", "char", "const", "continue",
		"default", "do", "double", "else", "enum", "extern",
		"float", "for", "goto", "if", "int", "long",
		"register", "return", "short", "signed", "sizeof", "static",
		"struct", "switch", "typedef", "union", "unsigned", "void",
		"volatile", "while" 
	};
	//set<string> TYPES = { "int","void" };
	set<string> PRE_OPERATORS = { "+","-" };
	set<char> BORDERS = { '(',')','{','}',',',';' };
	ifstream code_reader_;
	ofstream lexical_analyser_printer_;
	unsigned int line_counter_;
	bool print_detail_;
	unsigned int step_counter_;
	bool IsLetter(const unsigned char ch);
	bool IsDigital(const unsigned char ch);//�Ƿ�����
	bool IsSingleCharOperator(const unsigned char ch);//�Ƿ񵥷��������
	bool IsDoubleCharOperatorPre(const unsigned char ch);//�Ƿ�˫���������
	bool IsBlank(const unsigned char ch);//�Ƿ��ǿհ׷�
	unsigned char GetNextChar();//��ȡ�ַ����е���һ���ַ���ͬʱ����������
	void PrintDetail(WordInfo word);//��ӡ�ʷ�������Ϣ
	WordInfo GetBasicWord();


public:
	LexicalAnalyzer();
	~LexicalAnalyzer();
	bool IsReadyToAnalyze(bool show_detail = true, const string code_filename = "./raw_data/test.cpp");//�ļ��Ƿ����
};

#endif