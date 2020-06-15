#pragma once

#include "scbAbstractSchemeDevice.h"

class trackSwitch;

class scbMotorDriveDevice : public scbAbstractSchemeDevice
{
	float m_FrostAmount1; // Количество инея на первой группе автопереключателя ( 0.0f - нет совсем, 1.0f - полностью покрыто )
	float m_FrostAmount2; // Количество инея на второй группе автопереключателя ( 0.0f - нет совсем, 1.0f - полностью покрыто )
	float m_FrostAmount3; // Количество инея на третьей группе автопереключателя ( 0.0f - нет совсем, 1.0f - полностью покрыто )
	float m_FrostAmount4; // Количество инея на четвертой группе автопереключателя ( 0.0f - нет совсем, 1.0f - полностью покрыто )

	float m_Temperature; // Текущая температура

	static constexpr float m_cFrostSlewRate = 1.0f; // Постоянная скорости нарастания инея, ед. в мин.-град.цельсия 
	static constexpr float m_cFrostMeltingRate = 1.0f; // Постянная скорости таяния инея, ед. в мин.-град.цельсия
	static constexpr float m_cFrostContactLevel = 0.6f; // Уровень инея, выше которого автопереключатель не соединяет свою цепь

	static constexpr float m_cLockSwitchLevel = 0.2f; // Уровень срабатывания БК
	static constexpr float m_cAutoSwitchLevel = 0.5f; // Уровень срабатывания автопереключателей

	static constexpr float m_cSwivelCamFallingTime = 10.0f; // Время вынужденного падения поворотного кулачка в паз муфты, мс
	static constexpr float m_cFlapTime = 500.0f; // Время поднятия/опускания курбельной заслонки, мс
	static constexpr float m_cMotorRatePerSecondWork = 10.0f; // Скорость вращения якоря двигателя в рабочем режиме, об/с
	static constexpr float m_cMotorRatePerSecondFriction = 5.0f; // Скорость вращения якоря двигателя при фрикции, об/с
	static constexpr float m_cGearRatio = 10.0f; // Передаточное число редуктора
	static constexpr float m_cGapSector = 16.0f; // Сектор зазора мужду шестерней редуктора и муфтой, градусов
	static constexpr float m_cWorkingSector = 280.0f; // Сектор вращения шестерни редуктора, градусов

	bool m_Friction; // наличие фрикции
	float m_LeftSwivelCamPosition; // Положение левого поворотного кулачка, 0 - ролик в пазе муфты, 1 - ролик на поверхности муфты
	float m_RightSwivelCamPosition; // Положение правого поворотного кулачка, 0 - ролик в пазе муфты, 1 - ролик на поверхности муфты
	float m_AutoSwitchGap; // Зазор между шестерней редуктора и муфтой автопереключателя 0 - зазор в левой части, +16 - зазор в правой части
	float m_MotorPhase; // Фаза положения якоря мотора, градус
	float m_ReductorPhase; // Фаза положения входной шестерни автопереключателя, градус ( от 140 шибер справа до -140 шибер слева )
	float m_FlapPosition; // Положение курбельной заслонки ( 0.0f - замкнут, 1.0f - разомкнут )
	float m_GatePosition; // Положение шибера ( 0.0f - крайнее левое, 1.0f - крайнее правое )
	float m_ControlLinePosition; // Положение контрольных линеек ( 0.0f - крайнее левое, 1.0f - крайнее правое )
	float m_AutoSwitch12Position; // Положение левого автопереключателя ( -1.0f - крайнее левое ( рабочее ), 0.0f - среднее , 1.0f - крайнее правое ( контрольное ))
	float m_AutoSwitch34Position; // Положение правого автопереключателя ( -1.0f - крайнее правое ( рабочее ), 0.0f - среднее , 1.0f - крайнее левое ( контрольное ))

	/* Состояние курбельной заслонки и блокировочного контакта
	0 - заслонка поднята, контакт замкнут
	1 - заслонка опускается, контакт замкнут
	2 - заслонка опускается, контакт разомкнут
	3 - заслонка опущена, контакт разомкнут
	4 - заслонка поднимается, контакт разомкнут
	5 - заслонка поднимается, контакт замкнут
	*/
	int m_FlapStatus;

	/* Состояние работы двигателя
	0 - покой
	1 - работа вправо
	2 - фрикция фправо
	3 - работа влево
	4 - фрикция влево
	*/
	int m_MotorStatus;
	bool m_ControlLinePresence;
	bool m_IsGateClose;

	bool m_LeftSwivelCamFalling; // Вынужденное западание левого поворотного кулачка в открытый паз муфты
	bool m_RightSwivelCamFalling; // Вынужденное западание правого поворотного кулачка в открытый паз муфты
								 
	static constexpr int m_cAutoSwitch12ControlBit = 0;
	static constexpr int m_cAutoSwitch12PowerBit = 1;
	static constexpr int m_cAutoSwitch34ControlBit = 2;
	static constexpr int m_cAutoSwitch34PowerBit = 3;
	static constexpr int m_cWorkingAmperageBit = 4;
	static constexpr int m_cFrictionAmperageBit = 5;
	static constexpr int m_cAutoSwitch1FrostBit = 6;
	static constexpr int m_cAutoSwitch2FrostBit = 7;
	static constexpr int m_cAutoSwitch3FrostBit = 8;
	static constexpr int m_cAutoSwitch4FrostBit = 9;
	static constexpr int m_cLockSwitchBit = 10;

	unsigned long long m_TimeStamp;

	trackSwitch* m_TrackSwitch;

	void RecalculateAutoSwitch ();

public:
	scbMotorDriveDevice ( scbAbstractScheme* ownerShema );
	virtual ~scbMotorDriveDevice ();

	void SetSwitch ( trackSwitch* point );

	virtual void Init () override;
	virtual void IdleTimer ( unsigned long long time ) override;
	virtual void ChangeStatus ( const scbOutputStream& param ) override; // Вызывается светофором-хозяином

	bool ShiftGate ( float position );
	void ShiftControlRod ( float position );

	void FlapDown ();
	void FlapUp ();
	void LeftWedgeInsert ();
	void LeftWedgeRemove ();
	void RightWedgeInsert ();
	void RightWedgeRemove ();

	float GetMotorPhase () const;
	float GetReductorPhase () const;
	float GetFlapPosition () const;
	float GetGatePosition () const;
	float GetControlLinePosition () const;
	float GetLeftSwivelCamPosition () const;
	float GetRightSwivelCamPosition () const;
	float GetAutoSwitch12Position () const;
	float GetAutoSwitch34Position () const;
	float GetLeftWedgePosition () const;
	float GetRightWedgePosition () const;
};

inline float scbMotorDriveDevice::GetMotorPhase () const
{
	return this->m_MotorPhase;
}

inline float scbMotorDriveDevice::GetReductorPhase () const
{
	return this->m_ReductorPhase;
}

inline float scbMotorDriveDevice::GetFlapPosition () const
{
	return this->m_FlapPosition;
}

inline float scbMotorDriveDevice::GetGatePosition () const
{
	return this->m_GatePosition;
}

inline float scbMotorDriveDevice::GetControlLinePosition () const
{
	return this->m_ControlLinePosition;
}

inline float scbMotorDriveDevice::GetAutoSwitch12Position () const
{
	return this->m_AutoSwitch12Position;
}

inline float scbMotorDriveDevice::GetAutoSwitch34Position () const
{
	return this->m_AutoSwitch34Position;

}

inline float scbMotorDriveDevice::GetLeftSwivelCamPosition () const
{
	return this->m_LeftSwivelCamPosition;
}

inline float scbMotorDriveDevice::GetRightSwivelCamPosition () const
{
	return this->m_RightSwivelCamPosition;
}
