#include "scbSchemeOutput.h"
#include "scbAbstractScheme.h"
#include "..\genApplication.h"

scbSchemeOutput::scbSchemeOutput ( scbAbstractScheme* ownerScheme, const wstring& name, int id ) :
	scbAbstractSchemeDevice ( ownerScheme ),
	m_TargetScheme ( nullptr ),
	m_Id ( id )
{
	this->m_TargetSchemeName = new wstring ( name );
}

scbSchemeOutput::~scbSchemeOutput ()
{
	if ( this->m_TargetSchemeName != nullptr )
		delete this->m_TargetSchemeName;
}

void scbSchemeOutput::Init ()
{
	// Пустой вызов
}

void scbSchemeOutput::IdleTimer ( unsigned long long time )
{
	// Пустой вызов
}

void scbSchemeOutput::ChangeStatus ( const scbOutputStream& param )
{
	scbOutputStream mask_on = { 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L };
	scbOutputStream mask_off = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };

	for ( auto& conv : this->m_Convertations )
		if ( ( param.Mask [conv.InputElement] & conv.InputMask ) != 0 )
			mask_on.Mask [conv.OutputElement] |= conv.OutputMask;
		else
			mask_off.Mask [conv.OutputElement] &= ~conv.OutputMask;

	if ( this->m_TargetScheme == nullptr )
	{
		if ( this->m_TargetSchemeName != nullptr )
		{
			// Разрешение имени схемы в ее указатель
			this->m_TargetScheme = genApplication::Instance ()->GetScheme ( *( this->m_TargetSchemeName ));
			delete this->m_TargetSchemeName;
			this->m_TargetSchemeName = nullptr;
			if ( this->m_TargetScheme == nullptr )
				return;
		}
		else
			return;
	}
	this->m_TargetScheme->CorrectInputStatus ( mask_on, mask_off, this->m_Id );
}
