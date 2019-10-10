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
	bool IsDigital(const unsigned char ch);//是否数字
	bool IsSingleCharOperator(const unsigned char ch);//是否单符号运算符
	bool IsDoubleCharOperatorPre(const unsigned char ch);//是否双符号运算符
	bool IsBlank(const unsigned char ch);//是否是空白符
	unsigned char GetNextChar();//获取字符流中的下一个字符，同时计算行数。
	void PrintDetail(WordInfo word);//打印词法分析信息
	WordInfo GetBasicWord();


public:
	LexicalAnalyzer();
	~LexicalAnalyzer();
	bool IsReadyToAnalyze(bool show_detail = true, const string code_filename = "./raw_data/test.cpp");//文件是否读到
};

#endif