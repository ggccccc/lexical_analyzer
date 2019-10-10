#include"lexical_analyzer.h"

const char* TypeTranslation[] = { "NUM", "KEYWARD", "IDENTIFIER", "TYPE", "BOARDER", "UNKNOWN", "EOF", "OPERATOR" };

bool LexicalAnalyzer::IsLetter(const unsigned char ch) {
	if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z' || '_' == ch)//�����»���
		return true;
	else
		return false;
}

bool LexicalAnalyzer::IsDigital(const unsigned char ch) {
	if (ch >= '0' && ch <= '9')
		return true;
	else
		return false;
}

bool LexicalAnalyzer::IsSingleCharOperator(const unsigned char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
		return true;
	else
		return false;
}

bool LexicalAnalyzer::IsDoubleCharOperatorPre(const unsigned char ch)
{
	if (ch == '=' || ch == '<' || ch == '>' || ch == '!')
		return true;
	else
		return false;
}

bool LexicalAnalyzer::IsBlank(const unsigned char ch) {
	if (' ' == ch || '\n' == ch || '\t' == ch || 255 == ch)
		return true;
	else
		return false;
}

unsigned char LexicalAnalyzer::GetNextChar() {
	unsigned char ch = code_reader_.get();
	if ('\n' == ch)
		line_counter_++;
	return ch;
}

WordInfo LexicalAnalyzer::GetBasicWord() {
	unsigned char ch;
	string str_token;
	WordInfo word;
	while (!code_reader_.eof()) {
		ch = GetNextChar();
		if ('/' == ch) {
			unsigned char next = GetNextChar();
			if ('/' == ch) {
				while (GetNextChar() != '\n' && !code_reader_.eof());//���س�Ϊֹ
			}
			else if ('*' == next)// /**/ע��
			{
				while (!code_reader_.eof())
				{
					while (GetNextChar() != '*' && !code_reader_.eof());//��*Ϊֹ

					//UNKNOWN
					if (code_reader_.eof())//����������ע��
					{
						word.type = LUNKNOWN; //δ֪
						word.value = "commitment error! line: " + std::to_string(line_counter_);
						return word;
					}

					//  /**/ ע�ͽ���
					if (GetNextChar() == '/')
						break;
				}
			}
		}
		else if (IsDigital(ch)) {
			str_token += ch;
			while (!code_reader_.eof()) {
				unsigned char next = GetNextChar();
				if (!IsDigital(next)) {
					code_reader_.seekg(-1, ios::cur);
					word.type = LCINT;
					word.value = str_token;
					return word;
				}
				else {
					str_token += next;
				}
			}
		}
		else if (IsLetter(ch)) {
		}
		else if (BORDERS.find(ch) != BORDERS.end())
		{
			word.type = LBORDER;
			word.value = ch;
			return word;
		}
		else if (IsSingleCharOperator(ch))
		{
			word.type = LOPERATOR;
			word.value = ch;
			return word;
		}
		else if (IsDoubleCharOperatorPre(ch))
		{
			str_token += ch;
			unsigned char next = GetNextChar();
			if ('=' == next)
			{
				str_token += next;
				word.type = LOPERATOR; //������
				word.value = str_token;
				return word;
			}
			else
			{
				code_reader_.seekg(-1, ios::cur);//�����ļ�ָ�����,��Ϊ�����next
				if (ch != '!')//�Ǹ������Ų�����
				{
					word.type = LOPERATOR; //������
					word.value = str_token;
					return word;
				}
				else// ! δ����ķ���
				{
					word.type = LUNKNOWN; //������
					word.value = str_token + ", line: " + std::to_string(line_counter_);
					return word;
				}
			}
		}
		else if (IsBlank(ch))
		{
			continue;
		}
		else
		{
			word.type = LUNKNOWN;
			word.value = ch;
			word.value += ", line: " + std::to_string(line_counter_);
			return word;
		}
	}
	word.type = LEOF;
	word.value = "#";
	return word;
}



void LexicalAnalyzer::PrintDetail(WordInfo word)
{
	if (word.type == LEOF)
		return;
	lexical_analyser_printer_ << "step " << step_counter_ << " , type: " << TypeTranslation[word.type] << " , value: " << word.value;
	if (word.type == LUNKNOWN)
		lexical_analyser_printer_ << "    ****** warning! ******";
	lexical_analyser_printer_ << endl;
	step_counter_++;
	return;
}

LexicalAnalyzer::LexicalAnalyzer()
{
	line_counter_ = 1;
	step_counter_ = 1;
	print_detail_ = false;
}

LexicalAnalyzer::~LexicalAnalyzer()
{
	if (code_reader_.is_open())
		code_reader_.close();

	if (lexical_analyser_printer_.is_open())
		lexical_analyser_printer_.close();
}

bool LexicalAnalyzer::IsReadyToAnalyze(bool show_detail, const string code_filename)
{
	if (show_detail)//�Ƿ���������������ʾ�ʷ������Ĳ���
	{
		print_detail_ = true;
		lexical_analyser_printer_.open("./lexical_analyser_result.txt");
		if (!lexical_analyser_printer_.is_open()) {
			cerr << "�ʷ����������У���ʾ�������ļ���ʧ�ܣ�" << endl;
		}
	}
	else
		print_detail_ = false;

	code_reader_.open(code_filename);
	//ios::binary ���ﲻ����Binary�� ��Ϊtest.cpp����win����ϵͳ�´����ģ����ڴ��л�����\r\n��
	//���ʱ�����ֱ�Ӵ�ʹ�ö����ƶ�����������\r\n

	if (!code_reader_.is_open()) {
		cerr << "�ʷ����������У�Դ�����ļ���ʧ�ܣ�" << endl;
		return false;
	}
	while (!code_reader_.eof())
	{
		WordInfo word = GetBasicWord();
		PrintDetail(word);
	}
	return true;
}