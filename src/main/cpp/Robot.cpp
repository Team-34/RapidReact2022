// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <fmt/core.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include <iostream>

void Robot::RobotInit() {
    m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
    m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
    frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

    m_ramp_limiter_on = false;

    m_x_limiter = RAMP_LIMIT_X;
    m_y_limiter = RAMP_LIMIT_Y;
    m_r_limiter = RAMP_LIMIT_R;

    m_sheild_wall_on = false;

    m_driver_ctrl = new t34::XboxController(ID_DRIVE_CONTROLLER);
    m_driver_ctrl->setAllAxisDeadband(0.07);

    m_mech_ctrl = new t34::XboxController(ID_MECH_CONTROLLER);
    m_mech_ctrl->setAllAxisDeadband(0.08);

    m_swerve_drive = t34::SwerveDrive::getInstance();
    m_swerve_drive->setDriveMode(t34::DriveMode::RobotCentric);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {

}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
    m_autoSelected = m_chooser.GetSelected();
    // m_autoSelected = SmartDashboard::GetString("Auto Selector",
    //     kAutoNameDefault);
    fmt::print("Auto selected: {}\n", m_autoSelected);

    if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
    } else {
    // Default Auto goes here
    }
}

void Robot::AutonomousPeriodic() {
    if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
    } else {
    // Default Auto goes here
    }
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
    if (m_driver_ctrl->GetAButtonReleased())
        m_swerve_drive->toggleDriveMode();
        
    if (m_driver_ctrl->GetYButtonReleased())
        m_swerve_drive->toggleSpeed();
        //m_swerve_drive->ToggleDriveBrake();

    if (m_driver_ctrl->GetBButtonReleased()) {
        m_sheild_wall_on = !m_sheild_wall_on;

        if (m_sheild_wall_on)
           m_swerve_drive->sheildWall();
    }


    if (m_driver_ctrl->GetXButtonReleased()) {
        m_ramp_limiter_on = !m_ramp_limiter_on;
        if (m_ramp_limiter_on) {
            m_x_limiter.reset();
            m_y_limiter.reset();
            m_r_limiter.reset(); 
        }
    }
        
    if (m_driver_ctrl->GetBackButtonReleased())
        m_swerve_drive->zeroYaw();

    if (!m_sheild_wall_on) {
        if (m_ramp_limiter_on)
            m_swerve_drive->drive(m_x_limiter.calculate(m_driver_ctrl->getLeftStickXDB()), 
                                  m_y_limiter.calculate(m_driver_ctrl->getLeftStickYDB()), 
                                  m_r_limiter.calculate(m_driver_ctrl->getTriggersCoercedDB()));
        else
            m_swerve_drive->drive(m_driver_ctrl->getLeftStickXDB(), 
                                  m_driver_ctrl->getLeftStickYDB(), 
                                  m_driver_ctrl->getTriggersCoercedDB());
    } 
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
