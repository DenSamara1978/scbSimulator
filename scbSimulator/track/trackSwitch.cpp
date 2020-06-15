#include "trackSwitch.h"
#include "..\scb\scbMotorDriveDevice.h"

trackSwitch::trackSwitch () :
	m_Drive ( nullptr ),
	m_WorkingRod ( true ),
	m_PointPosition ( 1.0f ),
	m_LeftObstacle ( 0.0f ),
	m_RightObstacle ( 0.0f )
{

}

trackSwitch::~trackSwitch ()
{

}

void trackSwitch::ShiftWorkingRodLeft ( float& position, bool& friction )
{
	/* Сравнимается с позицией барьера и крайним положением
	и если дошли до барьера или крайнего положения - скорректировать положение шибера и установить фрикцию
	*/
	if ( this->m_WorkingRod )
	{
		if ( position <= 0.0f )
		{
			// Крайнее положение
			position = 0.0f;
			friction = true;
		}
		else if ( position <= this->m_LeftObstacle )
		{
			// Временная преграда
			position = this->m_LeftObstacle;
			friction = true;
		}
		else
		{
			position = fmin ( 1.0f, position );
			friction = false;
		}
		this->m_Drive->ShiftControlRod ( position );
		this->m_PointPosition = position;
	}
}

void trackSwitch::ShiftWorkingRodRight ( float& position, bool& friction )
{
	/* Сравнимается с позицией барьера и крайним положением
	и если дошли до барьера или крайнего положения - скорректировать положение шибера и установить фрикцию
	*/
	if ( this->m_WorkingRod )
	{
		if ( position >= 1.0f )
		{
			// Крайнее положение
			position = 1.0f;
			friction = true;
		}
		else if ( position >= 1.0f - this->m_RightObstacle )
		{
			// Временная преграда
			position = 1.0f - this->m_RightObstacle;
			friction = true;
		}
		else
		{
			position = fmax ( 0.0f, position );
			friction = false;
		}
		this->m_Drive->ShiftControlRod ( position );
		this->m_PointPosition = position;
	}
}

void trackSwitch::IncreaseLeftObstacle ()
{
	if ( ( this->m_LeftObstacle += 0.1f ) >= 1.0f )
		this->m_LeftObstacle = 1.0f;
	if ( this->m_RightObstacle + this->m_LeftObstacle >= 1.0f )
		this->m_RightObstacle = 1.0f - this->m_LeftObstacle;

	if ( this->m_PointPosition < this->m_LeftObstacle )
	{
		// Остряки должны быть сдвинуты
		this->m_PointPosition = this->m_LeftObstacle;
		if ( this->m_WorkingRod )
			this->m_WorkingRod = this->m_Drive->ShiftGate ( this->m_PointPosition );
		this->m_Drive->ShiftControlRod ( this->m_PointPosition );
	}
}

void trackSwitch::DecreaseLeftObstacle ()
{
	if ( ( this->m_LeftObstacle -= 0.1f ) <= 0.0f )
		this->m_LeftObstacle = 0.0f;
}

void trackSwitch::IncreaseRightObstacle ()
{
	if ( ( this->m_RightObstacle += 0.1f ) >= 1.0f )
		this->m_RightObstacle = 1.0f;
	if ( this->m_LeftObstacle + this->m_RightObstacle >= 1.0f )
		this->m_LeftObstacle = 1.0f - this->m_RightObstacle;

	if ( 1.0f - this->m_PointPosition < this->m_RightObstacle )
	{
		// Остряки должны быть сдвинуты
		this->m_PointPosition = 1.0f - this->m_RightObstacle;
		if ( this->m_WorkingRod )
			this->m_WorkingRod = this->m_Drive->ShiftGate ( this->m_PointPosition );
		this->m_Drive->ShiftControlRod ( this->m_PointPosition );
	}
}

void trackSwitch::DecreaseRightObstacle ()
{
	if ( ( this->m_RightObstacle -= 0.1f ) <= 0.0f )
		this->m_RightObstacle = 0.0f;
}
