/**
 * VectraSwarm OS — Hardware Abstraction Layer (HAL)
 * 
 * VSO HAL decouples the OS from any specific drone hardware.
 * OEM manufacturers implement this interface for their hardware.
 * ~200 lines C++ total — intentionally minimal.
 * 
 * Status: Interface definition — PoC implementation in progress
 */

#pragma once
#include <cstdint>

namespace vso {

/// Sensor data structure — common across all hardware
struct SensorData {
    float accel_x, accel_y, accel_z;   // m/s²
    float gyro_x,  gyro_y,  gyro_z;    // rad/s
    float baro_alt;                      // meters
    float battery_voltage;               // V
    uint64_t timestamp_us;               // microseconds
};

/// HAL base interface — OEMs implement this for their hardware
class HALBase {
public:
    virtual ~HALBase() = default;

    /// Initialize hardware — called once at boot
    virtual bool init() = 0;

    /// Read sensor data — must complete in < 1ms (real-time constraint)
    virtual SensorData read() = 0;

    /// Optional: hardware-specific calibration
    virtual bool calibrate() { return true; }

    /// Send MAVLink command to flight controller
    virtual bool send_mavlink(const uint8_t* payload, size_t len) = 0;

    /// Check if hardware is healthy
    virtual bool is_healthy() = 0;
};

/// Reference implementation for Jetson Orin NX + Pixhawk 6X
/// Used in VSO PoC — replace with OEM implementation for other hardware
class JetsonPixhawkHAL : public HALBase {
public:
    bool init() override;
    SensorData read() override;
    bool send_mavlink(const uint8_t* payload, size_t len) override;
    bool is_healthy() override;
};

} // namespace vso
