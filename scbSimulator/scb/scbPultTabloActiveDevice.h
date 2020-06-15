#pragma once

#include "scbAbstractSchemeDevice.h"
#include "scbPultTablo.h"

class scbPultTabloActiveDevice : public scbAbstractSchemeDevice
{
public:
	scbPultTabloActiveDevice ( scbAbstractScheme* ownerScheme );
	virtual ~scbPultTabloActiveDevice () override;

	// Методы, реализация которых зависит от конкретных аппаратов управления
	virtual void Press (); // Нажатие
	virtual void Release (); // Отпускание
	virtual void TurnCW (); // Поворот по часовой стрелке
	virtual void TurnCCW (); // поворот против часовой стрелки
	virtual void Unseal (); // Снятие пломбы и отведение пломировочной скобы
	virtual void Seal (); // Установка пломировочной скобы и установка пломбы
	virtual void Remove (); // Извлечение ключа-жезла
	virtual void Insert (); // Вставка ключа-жезла

	virtual void ChangeStatus ( const scbOutputStream& param ) override; // Вызывается схемой-хозяином после расчета
};

