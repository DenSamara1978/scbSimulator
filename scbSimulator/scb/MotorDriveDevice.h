#pragma once

#include "AbstractSchemeDevice.h"

namespace track
{
	class Switch;
}

namespace scb
{

	class MotorDriveDevice : public AbstractSchemeDevice
	{
	public:
		MotorDriveDevice(AbstractScheme* ownerShema);
		virtual ~MotorDriveDevice();

		void setSwitch(track::Switch* point);

		virtual void initialize() override;
		virtual void idleTimer(unsigned long long time) override;
		virtual void changeStatus(const OutputStream& param) override; // Вызывается светофором-хозяином

		bool shiftGate(float position);
		void shiftControlRod(float position);

		void flapDown();
		void flapUp();
		void leftWedgeInsert();
		void leftWedgeRemove();
		void rightWedgeInsert();
		void rightWedgeRemove();

		float getMotorPhase() const;
		float getReductorPhase() const;
		float getFlapPosition() const;
		float getGatePosition() const;
		float getControlLinePosition() const;
		float getLeftSwivelCamPosition() const;
		float getRightSwivelCamPosition() const;
		float getAutoSwitch12Position() const;
		float getAutoSwitch34Position() const;
		float getLeftWedgePosition() const;
		float getRightWedgePosition() const;

	private:
		void recalculateAutoSwitch();

		float frostAmount1; // Количество инея на первой группе автопереключателя ( 0.0f - нет совсем, 1.0f - полностью покрыто )
		float frostAmount2; // Количество инея на второй группе автопереключателя ( 0.0f - нет совсем, 1.0f - полностью покрыто )
		float frostAmount3; // Количество инея на третьей группе автопереключателя ( 0.0f - нет совсем, 1.0f - полностью покрыто )
		float frostAmount4; // Количество инея на четвертой группе автопереключателя ( 0.0f - нет совсем, 1.0f - полностью покрыто )

		float temperature; // Текущая температура

		static constexpr float frostSlewRate = 1.0f; // Постоянная скорости нарастания инея, ед. в мин.-град.цельсия 
		static constexpr float frostMeltingRate = 1.0f; // Постянная скорости таяния инея, ед. в мин.-град.цельсия
		static constexpr float frostContactLevel = 0.6f; // Уровень инея, выше которого автопереключатель не соединяет свою цепь

		static constexpr float lockSwitchLevel = 0.2f; // Уровень срабатывания БК
		static constexpr float autoSwitchLevel = 0.5f; // Уровень срабатывания автопереключателей

		static constexpr float swivelCamFallingTime = 10.0f; // Время вынужденного падения поворотного кулачка в паз муфты, мс
		static constexpr float flapTime = 500.0f; // Время поднятия/опускания курбельной заслонки, мс
		static constexpr float motorRatePerSecondWork = 10.0f; // Скорость вращения якоря двигателя в рабочем режиме, об/с
		static constexpr float motorRatePerSecondFriction = 5.0f; // Скорость вращения якоря двигателя при фрикции, об/с
		static constexpr float gearRatio = 10.0f; // Передаточное число редуктора
		static constexpr float gapSector = 16.0f; // Сектор зазора мужду шестерней редуктора и муфтой, градусов
		static constexpr float workingSector = 280.0f; // Сектор вращения шестерни редуктора, градусов

		bool friction; // наличие фрикции
		float leftSwivelCamPosition; // Положение левого поворотного кулачка, 0 - ролик в пазе муфты, 1 - ролик на поверхности муфты
		float rightSwivelCamPosition; // Положение правого поворотного кулачка, 0 - ролик в пазе муфты, 1 - ролик на поверхности муфты
		float autoSwitchGap; // Зазор между шестерней редуктора и муфтой автопереключателя 0 - зазор в левой части, +16 - зазор в правой части
		float motorPhase; // Фаза положения якоря мотора, градус
		float reductorPhase; // Фаза положения входной шестерни автопереключателя, градус ( от 140 шибер справа до -140 шибер слева )
		float flapPosition; // Положение курбельной заслонки ( 0.0f - замкнут, 1.0f - разомкнут )
		float gatePosition; // Положение шибера ( 0.0f - крайнее левое, 1.0f - крайнее правое )
		float controlLinePosition; // Положение контрольных линеек ( 0.0f - крайнее левое, 1.0f - крайнее правое )
		float autoSwitch12Position; // Положение левого автопереключателя ( -1.0f - крайнее левое ( рабочее ), 0.0f - среднее , 1.0f - крайнее правое ( контрольное ))
		float autoSwitch34Position; // Положение правого автопереключателя ( -1.0f - крайнее правое ( рабочее ), 0.0f - среднее , 1.0f - крайнее левое ( контрольное ))

		/* Состояние курбельной заслонки и блокировочного контакта
		0 - заслонка поднята, контакт замкнут
		1 - заслонка опускается, контакт замкнут
		2 - заслонка опускается, контакт разомкнут
		3 - заслонка опущена, контакт разомкнут
		4 - заслонка поднимается, контакт разомкнут
		5 - заслонка поднимается, контакт замкнут
		*/
		int flapStatus;

		/* Состояние работы двигателя
		0 - покой
		1 - работа вправо
		2 - фрикция фправо
		3 - работа влево
		4 - фрикция влево
		*/
		int motorStatus;
		bool controlLinePresence;
		bool isGateClose;

		bool leftSwivelCamFalling; // Вынужденное западание левого поворотного кулачка в открытый паз муфты
		bool rightSwivelCamFalling; // Вынужденное западание правого поворотного кулачка в открытый паз муфты

		static constexpr int autoSwitch12ControlBit = 0;
		static constexpr int autoSwitch12PowerBit = 1;
		static constexpr int autoSwitch34ControlBit = 2;
		static constexpr int autoSwitch34PowerBit = 3;
		static constexpr int workingAmperageBit = 4;
		static constexpr int frictionAmperageBit = 5;
		static constexpr int autoSwitch1FrostBit = 6;
		static constexpr int autoSwitch2FrostBit = 7;
		static constexpr int autoSwitch3FrostBit = 8;
		static constexpr int autoSwitch4FrostBit = 9;
		static constexpr int lockSwitchBit = 10;

		unsigned long long timeStamp;

		track::Switch* trackSwitch;
	};

	inline float MotorDriveDevice::getMotorPhase() const
	{
		return this->motorPhase;
	}

	inline float MotorDriveDevice::getReductorPhase() const
	{
		return this->reductorPhase;
	}

	inline float MotorDriveDevice::getFlapPosition() const
	{
		return this->flapPosition;
	}

	inline float MotorDriveDevice::getGatePosition() const
	{
		return this->gatePosition;
	}

	inline float MotorDriveDevice::getControlLinePosition() const
	{
		return this->controlLinePosition;
	}

	inline float MotorDriveDevice::getAutoSwitch12Position() const
	{
		return this->autoSwitch12Position;
	}

	inline float MotorDriveDevice::getAutoSwitch34Position() const
	{
		return this->autoSwitch34Position;

	}

	inline float MotorDriveDevice::getLeftSwivelCamPosition() const
	{
		return this->leftSwivelCamPosition;
	}

	inline float MotorDriveDevice::getRightSwivelCamPosition() const
	{
		return this->rightSwivelCamPosition;
	}
}