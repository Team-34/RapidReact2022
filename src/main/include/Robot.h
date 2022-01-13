// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>

#include "subsystems/SwerveDrive.h"
#include "utils/XboxController.h"
#include "utils/RampLimiter.h"


class Robot : public frc::TimedRobot {
public:
    void RobotInit() override;
    void RobotPeriodic() override;
    void AutonomousInit() override;
    void AutonomousPeriodic() override;
    void TeleopInit() override;
    void TeleopPeriodic() override;
    void DisabledInit() override;
    void DisabledPeriodic() override;
    void TestInit() override;
    void TestPeriodic() override;

private:
    frc::SendableChooser<std::string> m_chooser;
    const std::string kAutoNameDefault = "Default";
    const std::string kAutoNameCustom = "My Auto";
    std::string m_autoSelected;

    t34::SwerveDrive * m_swerve_drive;
    t34::XboxController * m_driver_ctrl;
    t34::XboxController * m_mech_ctrl;

    t34::RampLimiter m_x_limiter;
    t34::RampLimiter m_y_limiter;
    t34::RampLimiter m_r_limiter; 

    bool m_sheild_wall_on;
    bool m_ramp_limiter_on;
};

