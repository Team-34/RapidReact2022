#pragma once

#include <AHRS.h>

#include "RobotMap.h"
#include "subsystems/SwerveModule.h"


namespace t34 {

    enum class DriveMode {
        RobotCentric,
        FieldOriented
    };

    class SwerveDrive {
    public:
        static SwerveDrive * getInstance();
        ~SwerveDrive();

        AHRS * getGyro();
        void zeroYaw();
        
        void setDriveMode(DriveMode dm);
        void toggleDriveMode();
        
        void setDriveBrake(bool on = true);
        void toggleDriveBrake();
        
        void drive(double x, double y, double r);
        void sheildWall();
        void toggleSpeed();


    private:
        SwerveDrive();
        void putMode();

        AHRS * m_gyro;
        DriveMode m_mode;
        
        SwerveModule m_lf;
        SwerveModule m_la;
        SwerveModule m_rf;
        SwerveModule m_ra;
        double m_db;
        double m_speed;
    };

}

