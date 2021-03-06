// scbCompiler.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <codecvt>
#include <locale>
#include <vector>

#include "Description.h"

#include "SchemeManager.h"
#include "DeviceManager.h"
#include "ApparatManager.h"

#include "MessagePool.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/filereadstream.h"

using std::wcout;
using std::wcin;
using std::endl;
using std::locale;

bool ReadToken(const wstring& source, int& position, int& start_position, wstring& token)
{
	token.clear();

	if (position >= static_cast<int>(source.length()))
		return false;

	while (true)
	{
		auto sym = source[position];
		if ((sym == L' ') || (sym == L'\t'))
			++position;
		else if (sym == L'\0')
			return false;
		else
			break;
	}

	start_position = position + 1;
	bool parsed = false;
	while (true)
	{
		auto sym = source[position];
		if ((sym == L',') || (sym == L';') || (sym == L'(') || (sym == L')') ||
			(sym == L'{') || (sym == L'}') || (sym == L'[') || (sym == L']') ||
			(sym == L'.') || (sym == L'!') || (sym == L':') || (sym == L'+') ||
			(sym == L'<') || (sym == L'>') || (sym == L'"') || (sym == L'%') ||
			(sym == L'#') || (sym == L'@') || (sym == L'=') || (sym == L'\0') ||
			(sym == L' ') || (sym == L'\t') || (sym == L'&'))
		{
			if (!parsed)
			{
				token += sym;
				position++;
			}
			break;
		}
		else
		{
			parsed = true;
			token += sym;
			position++;
		}
	}
	return true;
}

using rapidjson::GenericDocument;
using rapidjson::GenericValue;
using rapidjson::StringBuffer;
using rapidjson::IStreamWrapper;
using rapidjson::UTF16;
using rapidjson::AutoUTF;
using rapidjson::AutoUTFInputStream;
using rapidjson::FileReadStream;

typedef GenericDocument<UTF16<>> WDocument;
typedef GenericValue<UTF16<>> WValue;

void json()
{

	FILE* fp;
	fopen_s(&fp, "G:\\scheme\\mrc13-nm2ap.json", "rb");
	char readBuffer[256];
	FileReadStream bis(fp, readBuffer, sizeof(readBuffer));
	AutoUTFInputStream<unsigned, FileReadStream> eis(bis);

	WDocument doc;
	doc.ParseStream<0, AutoUTF<unsigned>>(eis);
	auto error = doc.GetParseError();
	auto offset = doc.GetErrorOffset();
	auto row = doc.GetErrorRow();

	const WValue locale1(L"СХЕМА");
	const WValue locale2(L"Название");
	auto arr = doc[locale1].GetArray();
	auto item = arr[0].GetObject();
	wstring str = item[locale2].GetString();
	wstring str1 = doc[locale1][0][locale2].GetString();
}

int wmain(int argc, wchar_t* argv[])
{
	json();
	return 0;

	Description DescriptionIstance;
	SchemeManager schemeManager;
	DeviceManager devManager;

	locale current_locale("");
	locale::global(current_locale);

	//	std::locale utf8locale = std::locale ( std::locale (), new codecvt_utf8_utf16<wchar_t> );

	locale utf8locale {"ru_ru.utf-8"};

	wchar_t fileSeparator;
	Manager* pManager;
	MessagePool messagePool;

	wcout << L"Начинаем работу." << endl << endl;

	if (argc == 2)
	{
		wifstream makefile(argv[1]);
		if (makefile.is_open())
		{
			wstring makefileName(argv[1]);
			wstring initDir;
			size_t pos = makefileName.rfind(L"\\");
			if (pos != wstring::npos)
			{
				fileSeparator = L'\\';
				initDir = makefileName.substr(0, pos);
			}
			else
			{
				pos = makefileName.rfind(L"/");
				if (pos != wstring::npos)
				{
					fileSeparator = L'/';
					initDir = makefileName.substr(0, pos);
				}
			}

			wstring generalProtocolFilename(initDir + fileSeparator + L"Protocol" + fileSeparator + L"General_Protocol.html");
			wofstream generalProtocol(generalProtocolFilename, wofstream::out | wofstream::trunc);
			//			generalProtocol.imbue ( utf8locale );
			if (generalProtocol.is_open())
			{
				generalProtocol << L"<HTML><HEAD><TITLE>Протокол компиляции</TITLE>" << endl;
				generalProtocol << L"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=windows-1251\"></HEAD>" << endl;
				generalProtocol << L"<BODY>" << endl;

				wstring filename;
				wstring basefilename;
				wstring txtFilename;
				wstring binFilename;
				wstring logFilename;
				wifstream txtFile;
				wofstream logFile;
				ofstream binFile;

				int position;
				wstring token;
				wstring row;
				bool fatalError;

				ParseInfo info;

				while (!makefile.eof())
				{
					getline(makefile, filename);
					if (filename.empty())
						continue;
					if (filename[0] == L'-')
						continue;
					txtFilename = initDir + fileSeparator + filename;
					txtFile.open(txtFilename);
					txtFile.imbue(utf8locale);
					if (txtFile.is_open())
					{
						wcout << L"Обрабатывается файл " << filename << L"...";
						basefilename = filename.substr(0, filename.rfind(L'.'));
						generalProtocol << L"<A href=""" << basefilename << L".html"">" << basefilename << L"</A>" << endl;

						info.row = 0;
						fatalError = false;

						txtFile >> token;

						messagePool.clear();
						pManager = nullptr;
						if (token == L"СХЕМА")
							pManager = &schemeManager;
						else if (token == L"ШЛЮЗ")
							pManager = &devManager;

						if (pManager)
						{
							pManager->clear();
							pManager->setMessagePool(&messagePool);
							while (!txtFile.eof())
							{
								getline(txtFile, row);
								info.row++;

								position = 0;
								while (ReadToken(row, position, info.pos, info.token) && !fatalError)
								{
									if ((info.token.length() > 1) && (info.token[0] == L'/') && (info.token[1] == L'/'))
										break;
									fatalError = (pManager->parse(info) == 1);
								}
							}
						}
						else
						{
							messagePool.incorrectTypeOfFile();
							fatalError = true;
						}

						txtFile.close();

						bool error = false;
						bool warning = false;

						for (const auto& message : messagePool.getPool())
							if (message.isError())
								error = true;
						if (!error and pManager)
							pManager->compile();

						if (fatalError)
							messagePool.fatalError();

						error = false;
						for (const auto& message : messagePool.getPool())
						{
							if (message.isError())
								error = true;
							if (message.isWarning())
								warning = true;
						}
						if (!error)
						{
							binFilename = initDir + fileSeparator + L"Bin" + fileSeparator + basefilename + L".bin";
							binFile.open(binFilename);
							if (binFile.is_open() and pManager)
							{
								pManager->flushBinFile(binFile);
								binFile.close();
							}
							else
								wcout << L"Невозможно открыть файл " << binFilename << L"! Обработка прервана." << endl << endl;
						}

						logFilename = initDir + fileSeparator + L"Protocol" + fileSeparator + basefilename + L".html";
						logFile.open(logFilename);
						//						logFile.imbue ( utf8locale );						
						if (logFile.is_open())
						{
							logFile << L"<HTML><HEAD><TITLE>Протокол компиляции " << txtFilename << L"</TITLE>" << endl;
							logFile << L"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=windows-1251\"></HEAD>" << endl << L"<BODY>" << endl;
							logFile << L"<H1 style=\"color: red;\">" << txtFilename << L"</H1><BR>" << endl;

							if (error || warning)
							{
								wcout << endl;
								wstring str;
								for (const auto& message : messagePool.getPool())
								{
									wcout << message.getStringForConsole() << endl;
									logFile << message.getStringForLog() << endl;
								}
								logFile << L"<BR><BR>" << endl;
							}
							else
								wcout << L" Успешно!" << endl;

							if (pManager)
								pManager->flushLogFile(logFile);

							logFile << L"</BODY></HTML>" << endl;
							logFile.close();
						}
						else
							wcout << L"Невозможно открыть файл " << logFilename << L"! Обработка прервана." << endl << endl;

						if (error)
							generalProtocol << L" - <B style=\"color: red;\">Ошибки</B><BR>" << endl;
						else if (warning)
							generalProtocol << L" - <B style=\"color: #F0C000;\">Предупреждения</B><BR>" << endl;
						else
							generalProtocol << L" - <SPAN style=\"color: green;\">Успешно</SPAN><BR>" << endl;

						pManager = nullptr;
					}
					else
						wcout << L"Невозможно открыть файл " << txtFilename << L"! Обработка прервана." << endl << endl;
				}

				generalProtocol << L"</BODY></HTML>" << endl;
				generalProtocol.close();

				wcout << endl << L"Обработка файлов завершена! Результаты компиляции в файлах протоколов." << endl << endl;
			}
			else
				wcout << L"Невозможно открыть файл " << generalProtocolFilename << L"! Работа компилятора прервана." << endl << endl;
			makefile.close();
		}
		else
			wcout << L"Невозможно открыть файл " << argv[1] << L"! Работа компилятора прервана." << endl << endl;
	}
	else
	{
		wcout << L"Формат вызова: scbCompiler.exe имя_файла_задания" << endl << endl;
	}

	wcout << L"Для завершения нажмите любую клавишу." << endl;
	wcin.ignore();
	return 0;
}

