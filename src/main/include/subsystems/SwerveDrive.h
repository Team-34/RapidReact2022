#pragma once

#include <AHRS.h>

#include "RobotMap.h"
#include "subsystems/SwerveModule.h"


enum class DriveMode {
    RobotCentric,
    FieldOriented
};

class SwerveDrive {
public:
    static SwerveDrive * GetInstance();
    ~SwerveDrive();

    AHRS * GetGyro();
    void ZeroYaw();
    
    void SetDriveMode(DriveMode dm);
    void ToggleDriveMode();
    
    void SetDriveBrake(bool on = true);
    void ToggleDriveBrake();
    
    void Drive(double x, double y, double r);
    void Sheild_Wall();
    void ToggleSpeed();


private:
    SwerveDrive();
    void PutMode();

    AHRS * m_gyro;
    DriveMode m_mode;
    
    SwerveModule m_lf;
    SwerveModule m_la;
    SwerveModule m_rf;
    SwerveModule m_ra;
    double m_db;
    double m_speed;

};
