#include "subsystems/SwerveMath.h"
#include "subsystems/SwerveModule.h"
#include <frc/smartdashboard/SmartDashboard.h>

namespace t34 {

    SwerveModule::SwerveModule(std::string name, const int drive_id, const int steer_id, int invert) {
        m_name = name;
        m_drive = new WPI_TalonFX(drive_id);
        m_steer = new WPI_TalonFX(steer_id);


        m_steer->SetNeutralMode(NeutralMode::Coast);
        m_steer->Set(ControlMode::Position, 0);
        m_steer->ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, 0);
        m_steer->ConfigIntegratedSensorAbsoluteRange(AbsoluteSensorRange::Signed_PlusMinus180);
        m_steer->SetInverted(false);
        m_steer->Config_kD(0, 0.05, 0);

        m_drive->SetNeutralMode(NeutralMode::Brake);
        m_drive_brake_on = true;
        
        m_default_invert = m_invert = invert;
    }

    SwerveModule::~SwerveModule() {
        if (m_drive)
            delete m_drive;
            
        if (m_steer)
            delete m_steer;
    }

    void SwerveModule::setDriveBrake(bool on) {
        if (on)     {
            m_drive->SetNeutralMode(NeutralMode::Brake);    
            m_drive_brake_on = true;
        }
        else     {
            m_drive->SetNeutralMode(NeutralMode::Coast);    
            m_drive_brake_on = false;
        }
    }

    void SwerveModule::toggleDriveBrake() {
        setDriveBrake(!m_drive_brake_on);
    }

    void SwerveModule::setDriveSpeed(const double & speed) {
        frc::SmartDashboard::PutNumber("Drive Speed ", (m_invert * speed));
        
        m_drive->Set(ControlMode::PercentOutput, m_invert * speed);
    }

    void SwerveModule::setSteerPosition(const double & position, double offset) {
        double current_position = m_steer->GetSensorCollection().GetIntegratedSensorPosition();
        double set_point = (((position + offset) + 180) / 360.0) * FULL_UNITS;
        double delta = fmod(set_point - current_position, FULL_UNITS);

        //Calculating Shortest Distance
        if(fabs(delta > 9216.0))     {
            delta -= copysign(18432.0, delta);
            m_invert = -1.0;
        }
        else {
            m_invert = 1.0;
        }
        
        
        m_steer->Set(ControlMode::Position, current_position + delta);
    }

}
