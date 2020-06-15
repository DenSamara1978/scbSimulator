#include "scbSchemeCross.h"

scbSchemeCross::scbSchemeCross ( const wstring& name ) :
    scbSchemeObject ( name ),
    m_Order ( 0 ),
    m_Count ( 1 )
{
    this->m_Contacts.fill ( 0 );
}

scbSchemeCross::~scbSchemeCross ()
{
}

int scbSchemeCross::SetLocation ( const wstring& location )
{
    // Проверка возможности установки этого типа реле в указываемое место ( например BigBlock на 16 ряд СРКМ не установить )
    this->m_Location = location;
    return 0;
}

int scbSchemeCross::SetPlacement ( int id, scbDescription::PlacementType pl_type )
{
    this->m_Placement = id;
    return ( scbDescription::CheckCaseInPlacement ( scbDescription::DeviceCase::Cross, pl_type ) ) ? 0 : -1;
}

int scbSchemeCross::SetOrder ( int order )
{
    this->m_Order = order;
    return 0;
}

int scbSchemeCross::SetCable ( const wstring& cable )
{
    this->m_Cable = cable;
    return 0;
}

int scbSchemeCross::SetContact ( const wstring& contact )
{
    int cont = -1;
    if ( ( contact == L"1-2" ) or ( contact == L"2-1" ) )
        cont = 0;
    else if ( ( contact == L"3-4" ) or ( contact == L"4-3" ) )
        cont = 1;
    else if ( ( contact == L"5-6" ) or ( contact == L"6-5" ) )
        cont = 2;
    else if ( ( contact == L"7-8" ) or ( contact == L"8-7" ) )
        cont = 3;
    else if ( ( contact == L"9-10" ) or ( contact == L"10-9" ) )
        cont = 4;
    else if ( ( contact == L"11-12" ) or ( contact == L"12-11" ) )
        cont = 5;
    else if ( ( contact == L"13-14" ) or ( contact == L"14-13" ) )
        cont = 6;
    else if ( ( contact == L"15-16" ) or ( contact == L"16-15" ) )
        cont = 7;

    if ( cont == -1 )
        return -1;
    else if ( this->m_Contacts [cont] == 1 )
        return 1;
    else
    {
        this->m_Contacts [cont] = 1;
        return 0;
    }
}

int scbSchemeCross::SetCount ( int count )
{
    this->m_Count = count;
    return 0;
}

int scbSchemeCross::FixDescription ()
{
    return 0;
}

const scbSchemeObject::ObjectType scbSchemeCross::GetObjectType () const
{
    return scbSchemeObject::ObjectType::Cross;
}

