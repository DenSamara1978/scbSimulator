#include "Switch.h"
#include "..\scb\MotorDriveDevice.h"

using namespace track;
using scb::MotorDriveDevice;

Switch::Switch() :
	drive(nullptr),
	workingRod(true),
	pointPosition(1.0f),
	leftObstacle(0.0f),
	rightObstacle(0.0f)
{

}

Switch::~Switch()
{

}

void Switch::shiftWorkingRodLeft(float& position, bool& friction)
{
	/* Сравнимается с позицией барьера и крайним положением
	и если дошли до барьера или крайнего положения - скорректировать положение шибера и установить фрикцию
	*/
	if (this->workingRod)
	{
		if (position <= 0.0f)
		{
			// Крайнее положение
			position = 0.0f;
			friction = true;
		}
		else if (position <= this->leftObstacle)
		{
			// Временная преграда
			position = this->leftObstacle;
			friction = true;
		}
		else
		{
			position = fminf(1.0f, position);
			friction = false;
		}
		this->drive->shiftControlRod(position);
		this->pointPosition = position;
	}
}

void Switch::shiftWorkingRodRight(float& position, bool& friction)
{
	/* Сравнимается с позицией барьера и крайним положением
	и если дошли до барьера или крайнего положения - скорректировать положение шибера и установить фрикцию
	*/
	if (this->workingRod)
	{
		if (position >= 1.0f)
		{
			// Крайнее положение
			position = 1.0f;
			friction = true;
		}
		else if (position >= 1.0f - this->rightObstacle)
		{
			// Временная преграда
			position = 1.0f - this->rightObstacle;
			friction = true;
		}
		else
		{
			position = fmaxf(0.0f, position);
			friction = false;
		}
		this->drive->shiftControlRod(position);
		this->pointPosition = position;
	}
}

void Switch::increaseLeftObstacle()
{
	if ((this->leftObstacle += 0.1f) >= 1.0f)
		this->leftObstacle = 1.0f;
	if (this->rightObstacle + this->leftObstacle >= 1.0f)
		this->rightObstacle = 1.0f - this->leftObstacle;

	if (this->pointPosition < this->leftObstacle)
	{
		// Остряки должны быть сдвинуты
		this->pointPosition = this->leftObstacle;
		if (this->workingRod)
			this->workingRod = this->drive->shiftGate(this->pointPosition);
		this->drive->shiftControlRod(this->pointPosition);
	}
}

void Switch::decreaseLeftObstacle()
{
	if ((this->leftObstacle -= 0.1f) <= 0.0f)
		this->leftObstacle = 0.0f;
}

void Switch::increaseRightObstacle()
{
	if ((this->rightObstacle += 0.1f) >= 1.0f)
		this->rightObstacle = 1.0f;
	if (this->leftObstacle + this->rightObstacle >= 1.0f)
		this->leftObstacle = 1.0f - this->rightObstacle;

	if (1.0f - this->pointPosition < this->rightObstacle)
	{
		// Остряки должны быть сдвинуты
		this->pointPosition = 1.0f - this->rightObstacle;
		if (this->workingRod)
			this->workingRod = this->drive->shiftGate(this->pointPosition);
		this->drive->shiftControlRod(this->pointPosition);
	}
}

void Switch::decreaseRightObstacle()
{
	if ((this->rightObstacle -= 0.1f) <= 0.0f)
		this->rightObstacle = 0.0f;
}
