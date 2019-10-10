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
		"auto", "break", "case","const", "continue",
		"default", "do", "else", "enum", "extern", "for", "goto", "if",
		"register", "return","signed", "sizeof", "static",
		"struct", "switch", "typedef", "union", "unsigned",
		"volatile", "while" 
	};
	set<string> TYPES = { "int","void","char","short","float","double","long"};
	set<string> PRE_OPERATORS = { "+","-" };
	set<char> BORDERS = { '(',')','{','}',',',';' };
	ifstream code_reader_;
	ofstream lexical_analyser_printer_;
	ofstream lexical_analyser_print_info_;
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
	void PrintInfo(WordInfo word);
	int Index(string word_value);
	WordInfo GetBasicWord();


public:
	LexicalAnalyzer();
	~LexicalAnalyzer();
	bool IsReadyToAnalyze(bool show_detail = true, const string code_filename = "./raw_data/test.cpp");//文件是否读到
};

#endif