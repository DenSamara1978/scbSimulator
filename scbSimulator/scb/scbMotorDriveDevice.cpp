#include "scbAbstractScheme.h"
#include "scbMotorDriveDevice.h"
#include "..\track\trackSwitch.h"

scbMotorDriveDevice::scbMotorDriveDevice ( scbAbstractScheme* ownerScheme ) :
	scbAbstractSchemeDevice ( ownerScheme ),
	m_Temperature ( 20.0f ),
	m_FrostAmount1 ( 0.0f ),
	m_FrostAmount2 ( 0.0f ),
	m_FrostAmount3 ( 0.0f ),
	m_FrostAmount4 ( 0.0f ),
	m_FlapPosition ( 0.0f ),
	m_GatePosition ( 1.0f ),
	m_ControlLinePosition ( 1.0f ),
	m_AutoSwitch12Position ( -1.0f ),
	m_AutoSwitch34Position ( 1.0f ),
	m_ReductorPhase ( this->m_cWorkingSector / 2.0f ),
	m_AutoSwitchGap ( 0.0f ),
	m_MotorPhase ( 0.0f ),
	m_LeftSwivelCamPosition ( 1.0f ),
	m_RightSwivelCamPosition ( 0.0f ),
	m_FlapStatus ( 0 ),
	m_MotorStatus ( 0 ),
	m_Friction ( false ),
	m_LeftSwivelCamFalling ( false ),
	m_RightSwivelCamFalling ( false ),
	m_TimeStamp ( 0 ),
	m_TrackSwitch ( nullptr ),
	m_ControlLinePresence ( true ),
	m_IsGateClose ( true )
{
}

scbMotorDriveDevice::~scbMotorDriveDevice ()
{

}

inline void scbMotorDriveDevice::RecalculateAutoSwitch ()
{
	// Находим положение левого автопереключателя ( 1-2 )
	float old = this->m_AutoSwitch12Position;
	if (( this->m_ControlLinePosition > 0.0f ) && this->m_ControlLinePresence )
		this->m_AutoSwitch12Position = -this->m_LeftSwivelCamPosition;
	else
		this->m_AutoSwitch12Position = 1.0f - 2.0f * this->m_LeftSwivelCamPosition;

	if ( ( old < -this->m_cAutoSwitchLevel ) && ( this->m_AutoSwitch12Position > -this->m_cAutoSwitchLevel ) )
		this->m_OwnerScheme->ResetStatusBit ( this->m_cAutoSwitch12PowerBit );
	if ( ( old > -this->m_cAutoSwitchLevel ) && ( this->m_AutoSwitch12Position < -this->m_cAutoSwitchLevel ) )
		this->m_OwnerScheme->SetStatusBit ( this->m_cAutoSwitch12PowerBit );
	if ( ( old < this->m_cAutoSwitchLevel ) && ( this->m_AutoSwitch12Position > this->m_cAutoSwitchLevel ) )
		this->m_OwnerScheme->SetStatusBit ( this->m_cAutoSwitch12ControlBit );
	if ( ( old > this->m_cAutoSwitchLevel ) && ( this->m_AutoSwitch12Position < this->m_cAutoSwitchLevel ) )
		this->m_OwnerScheme->ResetStatusBit ( this->m_cAutoSwitch12ControlBit );

	// Находим положение правого автопереключателя ( 3-4 )
	old = this->m_AutoSwitch34Position;
	if (( this->m_ControlLinePosition < 1.0f ) && this->m_ControlLinePresence )
		this->m_AutoSwitch34Position = -this->m_RightSwivelCamPosition;
	else
		this->m_AutoSwitch34Position = 1.0f - 2.0f * this->m_RightSwivelCamPosition;

	if ( ( old < -this->m_cAutoSwitchLevel ) && ( this->m_AutoSwitch34Position > -this->m_cAutoSwitchLevel ) )
		this->m_OwnerScheme->ResetStatusBit ( this->m_cAutoSwitch34PowerBit );
	if ( ( old > -this->m_cAutoSwitchLevel ) && ( this->m_AutoSwitch34Position < -this->m_cAutoSwitchLevel ) )
		this->m_OwnerScheme->SetStatusBit ( this->m_cAutoSwitch34PowerBit );
	if ( ( old < this->m_cAutoSwitchLevel ) && ( this->m_AutoSwitch34Position > this->m_cAutoSwitchLevel ) )
		this->m_OwnerScheme->SetStatusBit ( this->m_cAutoSwitch34ControlBit );
	if ( ( old > this->m_cAutoSwitchLevel ) && ( this->m_AutoSwitch34Position < this->m_cAutoSwitchLevel ) )
		this->m_OwnerScheme->ResetStatusBit ( this->m_cAutoSwitch34ControlBit );
}

void scbMotorDriveDevice::SetSwitch ( trackSwitch* point )
{
	this->m_TrackSwitch = point;
	if ( point != nullptr )
		point->SetDrive ( this );
}

void scbMotorDriveDevice::Init ()
{
	this->m_OwnerScheme->SetStatusBit ( this->m_cAutoSwitch12PowerBit );
	this->m_OwnerScheme->SetStatusBit ( this->m_cAutoSwitch34ControlBit );
	this->m_OwnerScheme->SetStatusBit ( this->m_cLockSwitchBit );
	this->m_OwnerScheme->SetStatusBit ( this->m_cAutoSwitch1FrostBit );
	this->m_OwnerScheme->SetStatusBit ( this->m_cAutoSwitch2FrostBit );
	this->m_OwnerScheme->SetStatusBit ( this->m_cAutoSwitch3FrostBit );
	this->m_OwnerScheme->SetStatusBit ( this->m_cAutoSwitch4FrostBit );
}

void scbMotorDriveDevice::FlapDown ()
{
	switch ( this->m_FlapStatus )
	{
	case 0:
		// инициировать опускание
		if ( this->m_TimeStamp == 0 )
			this->m_TimeStamp = scbTimer::Instance ()->GetWorkingTime ();
		this->m_FlapStatus = 1;
		this->AddIdleTimer ();
		break;
	case 4:
		// прекратить поднятие и с этого места начать опускание
		this->m_FlapStatus = 2;
		break;
	case 5:
		// прекратить поднятие и с этого места начать опускание
		this->m_FlapStatus = 1;
		break;
	}
}

void scbMotorDriveDevice::FlapUp ()
{
	switch ( this->m_FlapStatus )
	{
	case 3:
		// инициировать поднятие
		if ( this->m_TimeStamp == 0 )
			this->m_TimeStamp = scbTimer::Instance ()->GetWorkingTime ();
		this->m_FlapStatus = 4;
		this->AddIdleTimer ();
		break;
	case 1:
		// прекратить опускание и с этого места начать поднятие
		this->m_FlapStatus = 5;
		break;
	case 2:
		// прекратить опускание и с этого места начать поднятие
		this->m_FlapStatus = 4;
		break;
	}

}

void scbMotorDriveDevice::LeftWedgeInsert ()
{
	this->m_TrackSwitch->IncreaseLeftObstacle ();
}

void scbMotorDriveDevice::LeftWedgeRemove ()
{
	this->m_TrackSwitch->DecreaseLeftObstacle ();
}

void scbMotorDriveDevice::RightWedgeInsert ()
{
	this->m_TrackSwitch->IncreaseRightObstacle ();
}

void scbMotorDriveDevice::RightWedgeRemove ()
{
	this->m_TrackSwitch->DecreaseRightObstacle ();
}

float scbMotorDriveDevice::GetLeftWedgePosition () const
{
	return this->m_TrackSwitch->GetLeftObstacle ();
}

float scbMotorDriveDevice::GetRightWedgePosition () const
{
	return this->m_TrackSwitch->GetRightObstacle ();
}

void scbMotorDriveDevice::ChangeStatus ( const scbOutputStream& param )
{
	switch ( param.Mask [0] & 3 )
	{
	case 0:
		if ( this->m_MotorStatus > 0 )
		{
			this->m_OwnerScheme->ResetStatusBit ( this->m_cWorkingAmperageBit );
			this->m_OwnerScheme->ResetStatusBit ( this->m_cFrictionAmperageBit );
			this->m_MotorStatus = 0;
			this->m_Friction = false;
		}
		break;
	case 1:
		// Питание двигателя для движения шибера вправо
		switch ( this->m_MotorStatus )
		{
		case 0:
			this->m_OwnerScheme->SetStatusBit ( this->m_cWorkingAmperageBit );
			this->m_Friction = false;
			this->m_IsGateClose = false;
			this->AddIdleTimer ();
			if ( this->m_TimeStamp == 0 )
				this->m_TimeStamp = scbTimer::Instance ()->GetWorkingTime ();
		case 3:
		case 4:
			this->m_OwnerScheme->ResetStatusBit ( this->m_cFrictionAmperageBit );
			this->m_Friction = false;
			this->m_IsGateClose = false;
			this->m_MotorStatus = 1;
			break;
		}
		break;
	case 2:
		// Питание двигателя для движения шибера влево
		switch ( this->m_MotorStatus )
		{
		case 0:
			this->m_OwnerScheme->SetStatusBit ( this->m_cWorkingAmperageBit );
			this->m_Friction = false;
			this->m_IsGateClose = false;
			this->AddIdleTimer ();
			if ( this->m_TimeStamp == 0 )
				this->m_TimeStamp = scbTimer::Instance ()->GetWorkingTime ();
		case 1:
		case 2:
			this->m_OwnerScheme->ResetStatusBit ( this->m_cFrictionAmperageBit );
			this->m_Friction = false;
			this->m_IsGateClose = false;
			this->m_MotorStatus = 3;
			break;
		}
		break;
	}
}

void scbMotorDriveDevice::IdleTimer ( unsigned long long time )
{
	int deleteMark = 0xFF;

	// Обработка курбельной заслонки
	float delta = static_cast<float> ( time - this->m_TimeStamp );
	switch ( this->m_FlapStatus )
	{
	case 1:
		if (( this->m_FlapPosition += delta / this->m_cFlapTime ) > this->m_cLockSwitchLevel )
		{
			this->m_OwnerScheme->ResetStatusBit ( this->m_cLockSwitchBit );
			this->m_FlapStatus = 2;
		}
		deleteMark &= 0xFE;
		this->m_TimeStamp = time;
		break;
	case 2:
		if ( ( this->m_FlapPosition += delta / this->m_cFlapTime ) > 1.0f )
		{
			this->m_FlapPosition = 1.0f;
			this->m_FlapStatus = 3;
		}
		else
		{
			deleteMark &= 0xFE;
			this->m_TimeStamp = time;
		}
		break;
	case 4:
		if ( ( this->m_FlapPosition -= delta / this->m_cFlapTime ) < this->m_cLockSwitchLevel )
		{
			this->m_OwnerScheme->SetStatusBit ( this->m_cLockSwitchBit );
			this->m_FlapStatus = 5;
		}
		deleteMark &= 0xFE;
		this->m_TimeStamp = time;
		break;
	case 5:
		if ( ( this->m_FlapPosition -= delta / this->m_cFlapTime ) < 0.0f )
		{
			this->m_FlapPosition = 0.0f;
			this->m_FlapStatus = 0;
		}
		else
		{
			deleteMark &= 0xFE;
			this->m_TimeStamp = time;
		}
		break;
	}

	// Обработка работы якоря двигателя
	float deltaPhase = 0.0f;
	switch ( this->m_MotorStatus )
	{
	case 1:
		deltaPhase = delta * this->m_cMotorRatePerSecondWork * 360.0f / 1000.0f;
		deleteMark &= 0xFD;
		break;
	case 2:
		deltaPhase = delta * this->m_cMotorRatePerSecondFriction * 360.0f / 1000.0f;
		deleteMark &= 0xFD;
		break;
	case 3:
		deltaPhase = - delta * this->m_cMotorRatePerSecondWork * 360.0f / 1000.0f;
		deleteMark &= 0xFD;
		break;
	case 4:
		deltaPhase = - delta * this->m_cMotorRatePerSecondFriction * 360.0f / 1000.0f;
		deleteMark &= 0xFD;
		break;
	}
	this->m_MotorPhase += deltaPhase;

	deltaPhase /= this->m_cGearRatio;
	if (( deleteMark & 2 ) == 0 )
	{
		// Если вращался якорь двигателя, надо повернуть редуктор, а следом и шибер
		if ( deltaPhase < 0.0f )
		{
			// Поворот муфты по часовой
			if ( this->m_AutoSwitchGap < this->m_cGapSector )
			{
				// Еще есть зазор
				if ( ( this->m_AutoSwitchGap += -deltaPhase ) > this->m_cGapSector )
				{
					// Уменьшаем зазор
					deltaPhase = this->m_AutoSwitchGap - this->m_cGapSector;
					this->m_AutoSwitchGap = this->m_cGapSector;
				}
				else
					deltaPhase = 0.0f;

				// При необходимости поднимаем правый поворотный кулачок
				this->m_RightSwivelCamFalling = false;
				if ( this->m_RightSwivelCamPosition < 1.0f )
					this->m_RightSwivelCamPosition = this->m_AutoSwitchGap / this->m_cGapSector;
			}
			else
				this->m_RightSwivelCamPosition = 1.0f;

			if ( deltaPhase == 0.0f )
				this->m_ReductorPhase = this->m_GatePosition  * ( this->m_cWorkingSector - this->m_cGapSector ) - this->m_cWorkingSector / 2.0f + ( this->m_cGapSector - this->m_AutoSwitchGap );
			else
			{
				// Двигаем шибер влево
				this->m_GatePosition += deltaPhase / ( this->m_cWorkingSector - this->m_cGapSector );
				this->m_TrackSwitch->ShiftWorkingRodLeft ( this->m_GatePosition, this->m_Friction );
				this->m_ReductorPhase = this->m_GatePosition  * ( this->m_cWorkingSector - this->m_cGapSector ) - this->m_cWorkingSector / 2.0f;

				if (this->m_GatePosition <= 0.0f)
				{
					this->m_GatePosition = 0.0f;
					this->m_Friction = true;
					this->m_IsGateClose = true;
					// шибер достиг крайнего левого положения
					if (this->m_LeftSwivelCamPosition > 0.0f)
					{
						// открылся паз муфты для левого поворотного кулачка
						this->m_LeftSwivelCamFalling = true;
						deleteMark &= 0xFB;
					}
				}

				if ( this->m_Friction )
				{
					// При движении шибера встречено препятствие
					if ((this->m_MotorStatus == 1) || (this->m_MotorStatus == 3))
						this->m_MotorStatus++;
					this->m_OwnerScheme->SetStatusBit ( this->m_cFrictionAmperageBit );
				}
				else
				{
					// При движении шибера препятствие не обнаружено
					if ((this->m_MotorStatus == 2) || (this->m_MotorStatus == 4))
						this->m_MotorStatus--;
					this->m_OwnerScheme->ResetStatusBit (this->m_cFrictionAmperageBit);
				}
			}
		}
		else if ( deltaPhase > 0.0f )
		{
			// Поворот муфты против часовой
			if ( this->m_AutoSwitchGap > 0.0f )
			{
				// Еще есть зазор
				if ( ( this->m_AutoSwitchGap -= deltaPhase ) < 0.0f )
				{
					// Уменьшаем зазор
					deltaPhase = this->m_AutoSwitchGap;
					this->m_AutoSwitchGap = 0.0f;
				}
				else
					deltaPhase = 0.0f;

				// При необходимости поднимаем левый поворотный кулачок
				this->m_LeftSwivelCamFalling = false;
				if ( this->m_LeftSwivelCamPosition < 1.0f )
					this->m_LeftSwivelCamPosition = 1.0f - this->m_AutoSwitchGap / this->m_cGapSector;
			}
			else
				this->m_LeftSwivelCamPosition = 1.0f;

			if ( deltaPhase == 0.0f )
				this->m_ReductorPhase = this->m_GatePosition  * ( this->m_cWorkingSector - this->m_cGapSector ) - this->m_cWorkingSector / 2.0f + this->m_cGapSector - this->m_AutoSwitchGap;
			else
			{
				// Двигаем шибер вправо
				this->m_GatePosition += deltaPhase / ( this->m_cWorkingSector - this->m_cGapSector );
				this->m_TrackSwitch->ShiftWorkingRodRight ( this->m_GatePosition, this->m_Friction );
				this->m_ReductorPhase = this->m_GatePosition  * ( this->m_cWorkingSector - this->m_cGapSector ) - this->m_cWorkingSector / 2.0f + this->m_cGapSector;

				if (this->m_GatePosition >= 1.0f)
				{
					this->m_GatePosition = 1.0f;
					this->m_IsGateClose = true;
					this->m_Friction = true;
					// шибер достиг крайнего правого положения
					if (this->m_RightSwivelCamPosition > 0.0f)
					{
						// открылся паз муфты для правого поворотного кулачка
						this->m_RightSwivelCamFalling = true;
						deleteMark &= 0xF7;
					}
				}

				if ( this->m_Friction )
				{
					// При движении шибера встречено препятствие
					if ( ( this->m_MotorStatus == 1 ) || ( this->m_MotorStatus == 3 ))
						this->m_MotorStatus++;
					this->m_OwnerScheme->SetStatusBit ( this->m_cFrictionAmperageBit );
				}
				else
				{
					// При движении шибера препятствие не обнаружено
					if ((this->m_MotorStatus == 2) || (this->m_MotorStatus == 4))
						this->m_MotorStatus--;
					this->m_OwnerScheme->ResetStatusBit (this->m_cFrictionAmperageBit);
				}
			}
		}
	}

	// Разбираем вынужденное падение левого поворотного кулачка в паз муфты
	if ( this->m_LeftSwivelCamFalling )
	{
		if ( ( this->m_LeftSwivelCamPosition -= delta / this->m_cSwivelCamFallingTime ) < 0.0f )
		{
			this->m_LeftSwivelCamPosition = 0.0f;
			this->m_LeftSwivelCamFalling = false;
			deleteMark |= 4;
		}
		else
			deleteMark &= 0xFB;
	}

	// Разбираем вынужденное падение правого поворотного кулачка в паз муфты
	if ( this->m_RightSwivelCamFalling )
	{
		if ( ( this->m_RightSwivelCamPosition -= delta / this->m_cSwivelCamFallingTime ) < 0.0f )
		{
			this->m_RightSwivelCamPosition = 0.0f;
			this->m_RightSwivelCamFalling = false;
			deleteMark |= 8;
		}
		else
			deleteMark &= 0xF7;
	}

	this->RecalculateAutoSwitch ();

	if ( deleteMark == 0xFF )
	{
		// удалить себя из списка пассивных таймеров
		this->DeleteIdleTimer ();
		this->m_TimeStamp = 0;
	}
	else
		this->m_TimeStamp = time;
}

void scbMotorDriveDevice::ShiftControlRod ( float position )
{
	// Сдвиг контрольных линеек контрольными тягами
	if ( this->m_ControlLinePresence )
	{
		this->m_ControlLinePosition = position;
		this->RecalculateAutoSwitch ();
	}
}

bool scbMotorDriveDevice::ShiftGate ( float position )
{
	// Сдвиг шибера рабочей тягой
	// Возврат false, если тяга переламывается
	if (( ( ( position < 1.0f ) && ( this->m_GatePosition >= 1.0f ) ) ||
		( ( position > 0.0f ) && ( this->m_GatePosition <= 0.0f ) ) ) && this->m_IsGateClose )
		return false;

	float delta = position - this->m_GatePosition;
	float old = this->m_AutoSwitchGap;
	float old1 = this->m_ReductorPhase;

	this->m_GatePosition = position;
	if (( this->m_MotorStatus == 0 ) && ( delta != 0.0f ))
	{
		// Если двигатель выключен, но перевод не замкнут и есть движение шибера, надо расчитать новые положения механических частей без вызова таймера покоя
		// Поворотные кулачки при этом не могут мешать, поскольку незамкнутый привод имеет оба поднятых кулачка
		if ( delta < 0.0f )
		{
			// Шибер сдвинули влево
			if ((this->m_AutoSwitchGap -= delta) > this->m_cGapSector)
			{
				this->m_AutoSwitchGap = this->m_cGapSector;
				delta += this->m_AutoSwitchGap - old;
			}
		}
		else
		{
			// Шибер сдвинули вправо
			if ((this->m_AutoSwitchGap -= delta) < 0.0f)
			{
				this->m_AutoSwitchGap = 0.0f;
				delta -= old - this->m_AutoSwitchGap;
			}
		}
		this->m_ReductorPhase += delta * (this->m_cWorkingSector - this->m_cGapSector);
		this->m_MotorPhase += delta * (this->m_cWorkingSector - this->m_cGapSector) * this->m_cGearRatio;
	}
	return true;
}
