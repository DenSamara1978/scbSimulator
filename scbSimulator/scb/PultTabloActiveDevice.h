#pragma once

#include "AbstractSchemeDevice.h"

namespace scb
{

	class PultTabloActiveDevice : public AbstractSchemeDevice
	{
	public:
		PultTabloActiveDevice(AbstractScheme* ownerScheme);
		virtual ~PultTabloActiveDevice() override;

		// Методы, реализация которых зависит от конкретных аппаратов управления
		virtual void press(); // Нажатие
		virtual void release(); // Отпускание
		virtual void turnCw(); // Поворот по часовой стрелке
		virtual void turnCcw(); // поворот против часовой стрелки
		virtual void unseal(); // Снятие пломбы и отведение пломировочной скобы
		virtual void seal(); // Установка пломировочной скобы и установка пломбы
		virtual void remove(); // Извлечение ключа-жезла
		virtual void insert(); // Вставка ключа-жезла

		virtual void changeStatus(const OutputStream& param) override; // Вызывается схемой-хозяином после расчета
	};
}
