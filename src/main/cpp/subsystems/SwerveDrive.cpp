#include <memory>
#include "subsystems/SwerveMath.h"
#include "subsystems/SwerveDrive.h"
#include <frc/smartdashboard/SmartDashboard.h>

std::unique_ptr<SwerveDrive> g_swerve_drive{ nullptr };

SwerveDrive::SwerveDrive() 
    : m_lf(SwerveModule("Left_Front", ID_LEFT_FWD_DRIVE, ID_LEFT_FWD_STEER, -1.0))
    , m_la(SwerveModule("Left Back", ID_LEFT_AFT_DRIVE, ID_LEFT_AFT_STEER, -1.0))
    , m_rf(SwerveModule("Right_Front", ID_RIGHT_FWD_DRIVE, ID_RIGHT_FWD_STEER))
    , m_ra(SwerveModule("Right_Back", ID_RIGHT_AFT_DRIVE, ID_RIGHT_AFT_STEER))
    , m_db(0.1)
    , m_speed(1.0)
{
    m_gyro = new AHRS(frc::SPI::Port::kMXP);
    PutMode();
    frc::SmartDashboard::PutBoolean("High Speed", true);
}

SwerveDrive * SwerveDrive::GetInstance() {
    if (g_swerve_drive == nullptr)
        g_swerve_drive.reset(new SwerveDrive());

    return g_swerve_drive.get();
}

SwerveDrive::~SwerveDrive() {

}

AHRS * SwerveDrive::GetGyro() {
    return m_gyro;
}

void SwerveDrive::ZeroYaw() {
    if (m_gyro != nullptr)
        m_gyro->ZeroYaw();
}

void SwerveDrive::SetDriveMode(DriveMode dm) {
    m_mode = dm;
    PutMode();
}

void SwerveDrive::ToggleDriveMode() {
    if (m_mode == DriveMode::RobotCentric)
        m_mode = DriveMode::FieldOriented;
    else
        m_mode = DriveMode::RobotCentric;
        
    PutMode();
}

void SwerveDrive::SetDriveBrake(bool on) {
    m_lf.SetDriveBrake(on);
    m_la.SetDriveBrake(on);
    m_rf.SetDriveBrake(on);
    m_ra.SetDriveBrake(on);
}

void SwerveDrive::ToggleDriveBrake() {
    m_lf.ToggleDriveBrake();
    m_la.ToggleDriveBrake();
    m_rf.ToggleDriveBrake();
    m_ra.ToggleDriveBrake();
}

void SwerveDrive::Drive(double x, double y, double r) {
    //Deadband
    
    if (fabs(x) < m_db && fabs(y) < m_db && fabs(r) < m_db) {
        m_lf.SetDriveSpeed(0.0);
        m_la.SetDriveSpeed(0.0);
        m_rf.SetDriveSpeed(0.0);
        m_ra.SetDriveSpeed(0.0);        
        return;
    }

    x *= -1;
    y *= -1;

    
    if (m_mode == DriveMode::FieldOriented && m_gyro != nullptr) {   
        double gyro_radians = deg_to_rad(m_gyro->GetYaw());
        double temp_y = y * cos(gyro_radians) + x * sin(gyro_radians);
        x = -y * sin(gyro_radians) + x * cos(gyro_radians);
        y = temp_y;       
    }
    
    double a = (x - r) * FRAME_LENGTH_DIV_RATIO();
    double b = (x + r) * FRAME_LENGTH_DIV_RATIO();
    double c = (y - r) * FRAME_WIDTH_DIV_RATIO();
    double d = (y + r) * FRAME_WIDTH_DIV_RATIO();

    m_lf.SetSteerPosition(rad_to_deg(atan2(b, c)));
    m_la.SetSteerPosition(rad_to_deg(atan2(a, c)));
    m_rf.SetSteerPosition(rad_to_deg(atan2(b, d)));
    m_ra.SetSteerPosition(rad_to_deg(atan2(a, d)));


    double lf_drive_output = sqrt(sqr(b) + sqr(c)); 
    double la_drive_output = sqrt(sqr(a) + sqr(c)); 
    double rf_drive_output = sqrt(sqr(b) + sqr(d)); 
    double ra_drive_output = sqrt(sqr(a) + sqr(d)); 

    double do_max = std::max(std::initializer_list<double>(
        { lf_drive_output, la_drive_output, rf_drive_output, ra_drive_output } ));

    if (do_max > 1.0) {
        lf_drive_output /= do_max;
        la_drive_output /= do_max;
        rf_drive_output /= do_max;
        ra_drive_output /= do_max;
    }

    m_lf.SetDriveSpeed(lf_drive_output * m_speed);
    m_la.SetDriveSpeed(la_drive_output * m_speed);
    m_rf.SetDriveSpeed(rf_drive_output * m_speed);
    m_ra.SetDriveSpeed(ra_drive_output * m_speed);

}

void SwerveDrive::Sheild_Wall() {
    m_lf.SetDriveSpeed(0.0);
    m_la.SetDriveSpeed(0.0);
    m_rf.SetDriveSpeed(0.0);
    m_ra.SetDriveSpeed(0.0);

    m_lf.SetSteerPosition(_315_DEG);
    m_la.SetSteerPosition(_135_DEG);
    m_rf.SetSteerPosition(_135_DEG);
    m_ra.SetSteerPosition(_315_DEG);

}

void SwerveDrive::PutMode() {
    frc::SmartDashboard::PutString("Drive Mode ",
        m_mode == DriveMode::RobotCentric ? "Robot Centric" : "Field Oriented");
}

void SwerveDrive::ToggleSpeed() {
    
    if (m_speed == 0.5) {
        m_speed = 1.0;
        frc::SmartDashboard::PutBoolean("High Speed", true);
    }
    else {
        m_speed = 0.5;
        frc::SmartDashboard::PutBoolean("High Speed", false);
    }
    /*
    if (m_speed = 1.0)
        m_speed = 0.5;
    else
        m_speed = 1.0;
    */
}