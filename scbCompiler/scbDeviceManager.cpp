#include "scbDeviceManager.h"

scbDeviceManager::scbDeviceManager () :
	m_Mode ( 0 ),
	m_Submode ( 0 )
{

}

scbDeviceManager::~scbDeviceManager ()
{

}

void scbDeviceManager::Clear ()
{
	this->m_Mode = 0;
	this->m_Submode = 0;
}

int scbDeviceManager::Parse ( const scbParseInfo& info )
{
	const wstring& token = info.Token;
	if ( this->m_Submode == 0 )
	{
		if ( token == L"ВХОДЫ" )
		{
			this->m_Mode = 1;
			this->m_Submode = 0;
			return 0;
		}
		else if ( token == L"ВЫХОДЫ" )
		{
			this->m_Mode = 2;
			this->m_Submode = 0;
			return 0;
		}
	}

	int res = 0;
	switch ( this->m_Mode )
	{
	case 0:
		res = this->ParseDevice ( info );
		break;
	case 1:
		res = this->ParseInput ( info );
		break;
	case 2:
		res = this->ParseOutput ( info );
		break;
	default:
		res = this->m_MessagePool->SyntaxError ( info );
		break;
	}

	// 0 - можно работать далее
	// 1 - фатальная ошибка
	return res;
}

void scbDeviceManager::Compile ()
{

}

void scbDeviceManager::FlushBinFile ( const ofstream& file )
{

}

void scbDeviceManager::FlushLogFile ( const wofstream& file )
{

}

int scbDeviceManager::ParseDevice ( const scbParseInfo& info )
{
	const wstring& token = info.Token;
	int res = 0;
	switch ( this->m_Submode )
	{
	case 0:
		if ( token == L";" )
			break;
		else
		{
			// TODO
			this->m_Submode = 1;
		}
		break;
	case 1:
		if ( token == L"." )
			this->m_Submode = 2;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 2:
		if ( token == L"<" )
			this->m_Submode = 3;
		else
		{
			// TODO
			this->m_Submode = 5;
		}
		break;
	case 3:
		// TODO
		this->m_Submode = 4;
		break;
	case 4:
		if ( token == L">" )
			this->m_Submode = 5;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 5:
		if ( token == L"." )
			this->m_Submode = 6;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 6:
		// TODO
		this->m_Submode = 7;
		break;
	case 7:
		if ( token == L"{" )
			this->m_Submode = 8;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 8:
		if ( token == L"Размещение" )
			this->m_Submode = 9;
		else if ( token == L"Описание" )
			this->m_Submode = 15;
		else if ( token == L"Объект" )
			this->m_Submode = 18;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 9:
		if ( token == L":" )
			this->m_Submode = 10;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 10:
		// TODO
		this->m_Submode = 11;
		break;
	case 11:
		if ( token == L"(" )
			this->m_Submode = 12;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 12:
		// TODO
		this->m_Submode = 13;
		break;
	case 13:
		if ( token == L")" )
			this->m_Submode = 14;
		else
		{
			// TODO
		}
		break;
	case 14:
		if ( token == L";" )
			this->m_Submode = 21;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 15:
		if ( token == L":" )
			this->m_Submode = 16;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 16:
		// TODO
		this->m_Submode = 17;
		break;
	case 17:
		if ( token == L";" )
			this->m_Submode = 21;
		else if ( token == L"," )
			this->m_Submode = 16;
		else
		{
			// TODO
		}
		break;
	case 18:
		if ( token == L":" )
			this->m_Submode = 19;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 19:
		// TODO
		this->m_Submode = 20;
		break;
	case 20:
		if ( token == L";" )
			this->m_Submode = 21;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 21:
		if ( token == L"}" )
			this->m_Submode = 22;
		else if ( token == L"Размещение" )
			this->m_Submode = 9;
		else if ( token == L"Описание" )
			this->m_Submode = 15;
		else if ( token == L"Объект" )
			this->m_Submode = 18;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 22:
		if ( token == L";" )
			this->m_Submode = 0;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	default:
		res = this->m_MessagePool->SyntaxError ( info );
		break;
	}
	return res;
}

int scbDeviceManager::ParseInput ( const scbParseInfo& info )
{
	const wstring& token = info.Token;
	int res = 0;
	switch ( this->m_Submode )
	{
	case 0:
		if ( token == L";" )
			break;
		else
		{
			// TODO
			this->m_Submode = 1;
		}
		break;
	case 1:
		if ( token == L":" )
			this->m_Submode = 2;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 2:
		// TODO
		this->m_Submode = 3;
		break;
	case 3:
		if ( token == L";" )
			this->m_Submode = 0;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	default:
		res = this->m_MessagePool->SyntaxError ( info );
		break;
	}
	return res;
}

int scbDeviceManager::ParseOutput ( const scbParseInfo& info )
{
	const wstring& token = info.Token;
	int res = 0;
	switch ( this->m_Submode )
	{
	case 0:
		if ( token == L";" )
			break;
		else
		{
			// TODO
			this->m_Submode = 1;
		}
		break;
	case 1:
		if ( token == L":" )
			this->m_Submode = 2;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	case 2:
		// TODO
		this->m_Submode = 3;
		break;
	case 3:
		if ( token == L";" )
			this->m_Submode = 0;
		else
			res = this->m_MessagePool->SyntaxError ( info );
		break;
	default:
		res = this->m_MessagePool->SyntaxError ( info );
		break;
	}
	return res;
}
