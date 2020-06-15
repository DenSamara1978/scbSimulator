#pragma once

#include <string>
#include <unordered_map>

using std::wstring;
using std::unordered_map;

class scbMessage
{
public:
	enum class MessageType
	{
		Error = 0,
		Warning,
	};

private:
	MessageType m_MessageType;
	wstring m_Message;
	int m_Row;
	int m_Position;
	wstring m_Param1;
	wstring m_Param2;

	wstring m_StringForConsole;
	wstring m_StringForLog;

	void ConstructStrings ();

public:
	scbMessage ( const wstring& message );
	scbMessage ( const wstring& message, const wstring& param1 );
	scbMessage ( const wstring& message, const wstring& param1, const wstring& param2 );
	scbMessage ( const wstring& message, int row );
	scbMessage ( const wstring& message, int row, const wstring& param1 );
	scbMessage ( const wstring& message, int row, const wstring& param1, const wstring& param2 );
	scbMessage ( const wstring& message, int row, int position );
	scbMessage ( const wstring& message, int row, int position, const wstring& param1 );
	scbMessage ( const wstring& message, int row, int position, const wstring& param1, const wstring& param2 );
	const wstring& GetStringForConsole () const;
	const wstring& GetStringForLog () const;
	bool IsError () const;
	bool IsWarning () const;
};

inline scbMessage::scbMessage ( const wstring& message ) :
	m_MessageType ( MessageType::Error ),
	m_StringForConsole ( message ),
	m_StringForLog ( message )
{
	this->ConstructStrings ();
}

inline scbMessage::scbMessage ( const wstring& message, const wstring& param1 ) :
	m_MessageType ( MessageType::Error ),
	m_StringForConsole ( message ),
	m_StringForLog ( message ),
	m_Param1 ( param1 )
{
	this->ConstructStrings ();
}

inline scbMessage::scbMessage ( const wstring& message, const wstring& param1, const wstring& param2 ) :
	m_MessageType ( MessageType::Error ),
	m_StringForConsole ( message ),
	m_StringForLog ( message ),
	m_Param1 ( param1 ),
	m_Param2 ( param2 )
{
	this->ConstructStrings ();
}

inline scbMessage::scbMessage ( const wstring& message, int row ) :
	m_MessageType ( MessageType::Error ),
	m_StringForConsole ( message ),
	m_StringForLog ( message ),
	m_Row ( row )
{
	this->ConstructStrings ();
}

inline scbMessage::scbMessage ( const wstring& message, int row, const wstring& param1 ) :
	m_MessageType ( MessageType::Error ),
	m_StringForConsole ( message ),
	m_StringForLog ( message ),
	m_Row ( row ),
	m_Param1 ( param1 )
{
	this->ConstructStrings ();
}

inline scbMessage::scbMessage ( const wstring& message, int row, const wstring& param1, const wstring& param2 ) :
	m_MessageType ( MessageType::Error ),
	m_StringForConsole ( message ),
	m_StringForLog ( message ),
	m_Row ( row ),
	m_Param1 ( param1 ),
	m_Param2 ( param2 )
{
	this->ConstructStrings ();
}

inline scbMessage::scbMessage ( const wstring& message, int row, int position ) :
	m_MessageType ( MessageType::Error ),
	m_StringForConsole ( message ),
	m_StringForLog ( message ),
	m_Row ( row ),
	m_Position ( position )
{
	this->ConstructStrings ();
}

inline scbMessage::scbMessage ( const wstring& message, int row, int position, const wstring& param1 ) :
	m_MessageType ( MessageType::Error ),
	m_StringForConsole ( message ),
	m_StringForLog ( message ),
	m_Row ( row ),
	m_Position ( position ),
	m_Param1 ( param1 )
{
	this->ConstructStrings ();
}

inline scbMessage::scbMessage ( const wstring& message, int row, int position, const wstring& param1, const wstring& param2 ) :
	m_MessageType ( MessageType::Error ),
	m_StringForConsole ( message ),
	m_StringForLog ( message ),
	m_Row ( row ),
	m_Position ( position ),
	m_Param1 ( param1 ),
	m_Param2 ( param2 )
{
	this->ConstructStrings ();
}

inline const wstring& scbMessage::GetStringForConsole () const
{
	return this->m_StringForConsole;
}

inline const wstring& scbMessage::GetStringForLog () const
{
	return this->m_StringForLog;
}

inline bool scbMessage::IsError () const
{
	return ( this->m_MessageType == MessageType::Error );
}

inline bool scbMessage::IsWarning () const
{
	return ( this->m_MessageType == MessageType::Warning );
}
