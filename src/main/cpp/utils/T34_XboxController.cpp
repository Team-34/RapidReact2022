#include "utils/T34_XboxController.h"

// Constructor - Call base class constructor and Setup default values for data
T34_XboxController::T34_XboxController(int32_t port) 
    : XboxController(port)
    , m_left_x_db(0.0)
    , m_left_y_db(0.0)
    , m_right_x_db(0.0)
    , m_right_y_db(0.0)
    , m_left_trigger_db(0.0)
    , m_right_trigger_db(0.0)
{

}

void T34_XboxController::SetAllAxisDeadband(double value)
{
	if (value < 1.0 && value >= 0.0)
	{
		m_left_x_db = value;
		m_left_y_db = value;
		m_right_x_db = value;
		m_right_y_db = value;
		m_left_trigger_db = value;
		m_right_trigger_db = value;
	}
}

// Sets a deadband range for a given axis of the controller
void T34_XboxController::SetAxisDeadband(JoystickHand hand, AxisType axis, double value)
{
    // Clamp value from 0.0 to 1.0 
    if (value > 1.0) value = 1.0;
    if (value < 0.0) value = 0.0;

    switch(axis)
    {
        case AxisType::Trigger:
            if (hand == JoystickHand::Left)
                m_left_trigger_db = value;
            else 
                m_right_trigger_db = value;
            break;
        case AxisType::XAxis:
            if (hand == JoystickHand::Left)
                m_left_x_db = value;
            else
                m_right_x_db = value;
            break;
        case AxisType::YAxis:
            if (hand == JoystickHand::Left)
                m_left_y_db = value;
            else    
                m_right_y_db = value;
        default:
            return;
    }
}

double T34_XboxController::GetXDB(JoystickHand hand) const
{
    double value = (hand == JoystickHand::Left ? GetLeftX() : GetRightX());
    double db = (hand == JoystickHand::Left ? m_left_x_db : m_right_x_db);

    if (value < 0.0)
    {
        if (value > -db)
            value = 0.0;
    }
    else if (value < db)
            value = 0.0;

    return value;
}

double T34_XboxController::GetYDB(JoystickHand hand) const
{
    double value = (hand == JoystickHand::Left ? GetLeftY() : GetRightY());
    double db = (hand == JoystickHand::Left ? m_left_y_db : m_right_y_db);

    if (value < 0.0)
    {
        if (value > -db)
            value = 0.0;
    }
    else if (value < db)
            value = 0.0;

    return value;
}

double T34_XboxController::GetTriggerDB(JoystickHand hand) const
{
    double value = (hand == JoystickHand::Left ? GetLeftTriggerAxis() : GetRightTriggerAxis());
    double db = (hand == JoystickHand::Left ? m_left_trigger_db : m_right_trigger_db);

    if (value < 0.0)
    {
        if (value > -db)
            value = 0.0;
    }
    else if (value < db)
            value = 0.0;

    return value;
}

double T34_XboxController::GetTriggersCoercedDB() const
{
	return GetLeftTriggerDB() + -GetRightTriggerDB();
}

