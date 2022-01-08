#pragma once

#include <frc/XboxController.h>

// Enumeration for specifying the target axis in a generic function
enum class AxisType
{
    Trigger,
    XAxis,
    YAxis,
    ZAxis
};

enum class JoystickHand {
	Left,
	Right,
};

// Subclass of the frc::XboxController adding extra functionality
class T34_XboxController : public frc::XboxController
{
public: // PUBLIC METHODS
    T34_XboxController(int32_t port);

	void SetAllAxisDeadband(double value);
    void SetAxisDeadband(JoystickHand hand, AxisType axis, double value);

    double GetXDB(JoystickHand hand) const;
    double GetYDB(JoystickHand hand) const;
    double GetTriggerDB(JoystickHand hand) const;
	double GetTriggersCoercedDB() const;
	
	inline double GetLeftStickXDB() const   { return GetXDB(JoystickHand::Left); }
	inline double GetLeftStickYDB() const   { return GetYDB(JoystickHand::Left); }
	inline double GetRightStickXDB() const  { return GetXDB(JoystickHand::Right); }
	inline double GetRightStickYDB() const  { return GetYDB(JoystickHand::Right); }
	inline double GetLeftTriggerDB() const  { return GetTriggerDB(JoystickHand::Left); }
	inline double GetRightTriggerDB() const { return GetTriggerDB(JoystickHand::Right); }
	
	/*
	inline bool GetLeftStickPressed()       { return GetStickButtonPressed(JoystickHand::Left); }
	inline bool GetLeftStickReleased()      { return GetStickButtonReleased(JoystickHand::Left); }
	inline bool GetRightStickPressed()      { return GetStickButtonPressed(JoystickHand::Right); }
	inline bool GetRightStickReleased()     { return GetStickButtonReleased(JoystickHand::Right); }
	inline bool GetLeftBumperPressed()      { return GetBumperPressed(JoystickHand::Left); }
	inline bool GetLeftBumperReleased()     { return GetBumperReleased(JoystickHand::Left); }
	inline bool GetRightBumperPressed()     { return GetBumperPressed(JoystickHand::Right); }
	inline bool GetRightBumperReleased()    { return GetBumperReleased(JoystickHand::Right); }
	*/

private: //PRIVATE DATA
    double m_left_x_db;
    double m_left_y_db;
    double m_right_x_db;
    double m_right_y_db;
    double m_left_trigger_db;
    double m_right_trigger_db;
};
