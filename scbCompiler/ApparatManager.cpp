#include "ApparatManager.h"

ApparatManager::ApparatManager() :
	mode(0),
	submode(0)
{

}

ApparatManager::~ApparatManager()
{

}

int ApparatManager::parse(const ParseInfo& info)
{
	const wstring& token = info.token;
	if (this->submode == 0)
	{
		if (token == L"�����")
		{
			this->mode = 1;
			this->submode = 0;
			return 0;
		}
		else if (token == L"������")
		{
			this->mode = 2;
			this->submode = 0;
			return 0;
		}
	}

	int res = 0;
	switch (this->mode)
	{
		case 0:
			res = this->parseApparat(info);
			break;
		default:
			res = this->messagePool->syntaxError(info);
			break;
	}

	// 0 - ����� �������� �����
	// 1 - ��������� ������
	return res;
}

void ApparatManager::compile()
{

}

void ApparatManager::flushBinFile(const ofstream& file)
{

}

void ApparatManager::flushLogFile(const wofstream& file)
{

}

int ApparatManager::parseApparat(const ParseInfo& info)
{
	const wstring& token = info.token;
	int res = 0;
	switch (this->submode)
	{
		case 0:
			if (token == L";")
				break;
			else
			{
				// TODO
				this->submode = 1;
			}
			break;
		case 1:
			if (token == L".")
				this->submode = 2;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 2:
			if (token == L"<")
				this->submode = 3;
			else
			{
				// TODO
				this->submode = 5;
			}
			break;
		case 3:
			// TODO
			this->submode = 4;
			break;
		case 4:
			if (token == L">")
				this->submode = 5;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 5:
			if (token == L".")
				this->submode = 6;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 6:
			// TODO
			this->submode = 7;
			break;
		case 7:
			if (token == L"{")
				this->submode = 8;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 8:
			if (token == L"����������")
				this->submode = 9;
			else if (token == L"��������")
				this->submode = 15;
			else if (token == L"������")
				this->submode = 18;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 9:
			if (token == L":")
				this->submode = 10;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 10:
			// TODO
			this->submode = 11;
			break;
		case 11:
			if (token == L"(")
				this->submode = 12;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 12:
			// TODO
			this->submode = 13;
			break;
		case 13:
			if (token == L")")
				this->submode = 14;
			else
			{
				// TODO
			}
			break;
		case 14:
			if (token == L";")
				this->submode = 21;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 15:
			if (token == L":")
				this->submode = 16;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 16:
			// TODO
			this->submode = 17;
			break;
		case 17:
			if (token == L";")
				this->submode = 21;
			else if (token == L",")
				this->submode = 16;
			else
			{
				// TODO
			}
			break;
		case 18:
			if (token == L":")
				this->submode = 19;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 19:
			// TODO
			this->submode = 20;
			break;
		case 20:
			if (token == L";")
				this->submode = 21;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 21:
			if (token == L"}")
				this->submode = 22;
			else if (token == L"����������")
				this->submode = 9;
			else if (token == L"��������")
				this->submode = 15;
			else if (token == L"������")
				this->submode = 18;
			else
				res = this->messagePool->syntaxError(info);
			break;
		case 22:
			if (token == L";")
				this->submode = 0;
			else
				res = this->messagePool->syntaxError(info);
			break;
		default:
			res = this->messagePool->syntaxError(info);
			break;
	}
	return res;
}

