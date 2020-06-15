// scbCompiler.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <codecvt>
#include <locale>
#include <vector>

#include "scbDescription.h"

#include "scbSchemeManager.h"
#include "scbDeviceManager.h"
#include "scbApparatManager.h"

#include "scbMessagePool.h"

using std::wcout;
using std::wcin;
using std::endl;
using std::locale;

bool ReadToken ( const wstring& source, int& position, int& start_position, wstring& token )
{
	token.clear ();

	if ( position >= static_cast<int>( source.length () ))
		return false;

	while ( true )
	{
		auto sym = source [position];
		if ( ( sym == L' ' ) || ( sym == L'\t' ) )
			++position;
		else if ( sym == L'\0' )
			return false;
		else
			break;
	}

	start_position = position + 1;
	bool parsed = false;
	while ( true )
	{
		auto sym = source [position];
		if (( sym == L',' ) || ( sym == L';' ) || ( sym == L'(' ) || ( sym == L')' ) ||
			( sym == L'{' ) || ( sym == L'}' ) || ( sym == L'[' ) || ( sym == L']' ) ||
			( sym == L'.' ) || ( sym == L'!' ) || ( sym == L':' ) || ( sym == L'+' ) ||
			( sym == L'<' ) || ( sym == L'>' ) || ( sym == L'"' ) || ( sym == L'%' ) ||
			( sym == L'#' ) || ( sym == L'@' ) || ( sym == L'=' ) || ( sym == L'\0' ) ||
			( sym == L' ' ) || ( sym == L'\t' ) || ( sym == L'&' ))
		{
			if ( !parsed )
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

int wmain ( int argc, wchar_t* argv [] )
{
	scbDescription DescriptionIstance;
	scbSchemeManager schemeManager;
	scbDeviceManager devManager;

	locale current_locale ( "" );
	locale::global ( current_locale );

//	std::locale utf8locale = std::locale ( std::locale (), new codecvt_utf8_utf16<wchar_t> );

	locale utf8locale { "ru_ru.utf-8" };

	wchar_t fileSeparator;
	scbManager* pManager;
	scbMessagePool messagePool;

	wcout << L"Начинаем работу." << endl << endl;

	if ( argc == 2 )
	{
		wifstream makefile ( argv [1] );
		if ( makefile.is_open () )
		{
			wstring makefileName ( argv [1] );
			wstring initDir;
			size_t pos = makefileName.rfind ( L"\\" );
			if ( pos != wstring::npos )
			{
				fileSeparator = L'\\';
				initDir = makefileName.substr ( 0, pos );
			}
			else
			{
				pos = makefileName.rfind ( L"/" );
				if ( pos != wstring::npos )
				{
					fileSeparator = L'/';
					initDir = makefileName.substr ( 0, pos );
				}
			}

			wstring generalProtocolFilename ( initDir + fileSeparator + L"Protocol" + fileSeparator + L"General_Protocol.html" );
			wofstream generalProtocol ( generalProtocolFilename, wofstream::out | wofstream::trunc );
//			generalProtocol.imbue ( utf8locale );
			if ( generalProtocol.is_open () )
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

				scbParseInfo info;

				while ( !makefile.eof () )
				{
					getline ( makefile, filename );
					if ( filename.empty () )
						continue;
					if ( filename [0] == L'-' )
						continue;
					txtFilename = initDir + fileSeparator + filename;
					txtFile.open ( txtFilename );
					txtFile.imbue ( utf8locale );
					if ( txtFile.is_open () )
					{
						wcout << L"Обрабатывается файл " << filename << L"...";
						basefilename = filename.substr ( 0, filename.rfind ( L'.' ));
						generalProtocol << L"<A href=""" << basefilename << L".html"">" << basefilename << L"</A>" << endl;

						info.Row = 0;
						fatalError = false;

						txtFile >> token;

						messagePool.Clear ();
						pManager = nullptr;
						if ( token == L"СХЕМА" )
							pManager = &schemeManager;
						else if ( token == L"ШЛЮЗ" )
							pManager = &devManager;

						if ( pManager )
						{
							pManager->Clear ();
							pManager->SetMessagePool ( &messagePool );
							while ( !txtFile.eof ())
							{
								getline ( txtFile, row );
								info.Row++;

								position = 0;
								while ( ReadToken ( row, position, info.Pos, info.Token ) && !fatalError )
								{
									if ( ( info.Token.length () > 1 ) && ( info.Token [0] == L'/' ) && ( info.Token [1] == L'/' ) )
										break;
									fatalError = ( pManager->Parse ( info ) == 1 );
								}
							}
						}
						else
						{
							messagePool.IncorrectTypeOfFile ();
							fatalError = true;
						}

						txtFile.close ();

						bool error = false;
						bool warning = false;

						for ( const auto& message : messagePool.GetPool () )
							if ( message.IsError () )
								error = true;
						if ( !error and pManager )
							pManager->Compile ();

						if ( fatalError )
							messagePool.FatalError ();

						error = false;
						for ( const auto& message : messagePool.GetPool () )
						{
							if ( message.IsError () )
								error = true;
							if ( message.IsWarning () )
								warning = true;
						}
						if ( !error )
						{
							binFilename = initDir + fileSeparator + L"Bin" + fileSeparator + basefilename + L".bin";
							binFile.open ( binFilename );
							if ( binFile.is_open () and pManager )
							{
								pManager->FlushBinFile ( binFile );
								binFile.close ();
							}
							else
								wcout << L"Невозможно открыть файл " << binFilename << L"! Обработка прервана." << endl << endl;
						}

						logFilename = initDir + fileSeparator + L"Protocol" + fileSeparator + basefilename + L".html";
						logFile.open ( logFilename );
//						logFile.imbue ( utf8locale );						
						if ( logFile.is_open () )
						{
							logFile << L"<HTML><HEAD><TITLE>Протокол компиляции " << txtFilename << L"</TITLE>" << endl;
							logFile << L"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=windows-1251\"></HEAD>" << endl << L"<BODY>" << endl;
							logFile << L"<H1 style=\"color: red;\">" << txtFilename << L"</H1><BR>" << endl;

							if ( error || warning )
							{
								wcout << endl;
								wstring str;
								for ( const auto& message : messagePool.GetPool () )
								{
									wcout << message.GetStringForConsole () << endl;
									logFile << message.GetStringForLog () << endl;
								}
								logFile << L"<BR><BR>" << endl;
							}
							else
								wcout << L" Успешно!" << endl;

							if ( pManager )
								pManager->FlushLogFile ( logFile );

							logFile << L"</BODY></HTML>" << endl;
							logFile.close ();
						}
						else
							wcout << L"Невозможно открыть файл " << logFilename << L"! Обработка прервана." << endl << endl;

						if ( error )
							generalProtocol << L" - <B style=\"color: red;\">Ошибки</B><BR>" << endl;
						else if ( warning )
							generalProtocol << L" - <B style=\"color: #F0C000;\">Предупреждения</B><BR>" << endl;
						else
							generalProtocol << L" - <SPAN style=\"color: green;\">Успешно</SPAN><BR>" << endl;

						pManager = nullptr;
					}
					else
						wcout << L"Невозможно открыть файл " << txtFilename << L"! Обработка прервана." << endl << endl;
				}

				generalProtocol << L"</BODY></HTML>" << endl;
				generalProtocol.close ();

				wcout << endl << L"Обработка файлов завершена! Результаты компиляции в файлах протоколов." << endl << endl;
			}
			else
				wcout << L"Невозможно открыть файл " << generalProtocolFilename << L"! Работа компилятора прервана." << endl << endl;
			makefile.close ();
		}
		else
			wcout << L"Невозможно открыть файл " << argv [1] << L"! Работа компилятора прервана." << endl << endl;
	}
	else
	{
		wcout << L"Формат вызова: scbCompiler.exe имя_файла_задания" << endl << endl;
	}

	wcout << L"Для завершения нажмите любую клавишу." << endl;
	wcin.ignore ();
    return 0;
}

