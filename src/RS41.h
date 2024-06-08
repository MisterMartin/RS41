// RS41.h
#ifndef RS41_H
#define RS41_H

#include "Arduino.h"


struct RS41SensorData {
};

class RS41 {

#define RS41_SERIAL_BUFFER_SIZE 1024
#define RS41_GPIO_PWR_PIN 32

  public:
    /// @brief Constructor
    /// @param serial The RS421 serial port
    RS41(HardwareSerial& serial);
    /// @brief Destructor
    ///   Power off RS41
    ~RS41();
    /// @brief Initialize RS41
    /// - Initialize the RS41 serial port
    /// - Power cycle the RS41
    /// - Read the banner message
    /// - Get the RS41 meta data
    void init();
    /// @brief Query the RS41 for the RS41 sensor data
    /// @return A string containing the sensor data. The 
    /// string will be zero length if the query timed out.
    String read_sensor_data();
    /// @brief Query the RS41 for the RS41 meta data
    /// @return A string containing the sensor data. The 
    /// string will be zero length if the query timed out.
    String read_meta_data();
    /// @brief Start the recondition process
    /// @return ">RH Reconditioning". A zero length string
    /// will be returned if the query timed out.
    String recondition();
    /// @brief Send the command to the RS41
    /// @param cmd A RS41 command (.e.g. RMD, RSD, RHS)
    /// @return The commnd result
    /// The command is written to RS41_SERIAL, followed by
    /// a flush(). The flush() will hold until all of
    /// the characters have been transmitted. This is followed
    /// by a readStringUntil('\r'). Thus this function will take
    /// a relatively long time to execute, because it includes the
    /// time to send the cmd characters, the time for the RS41 to 
    /// make the measurements, and the time for all of the result 
    /// characters to be read by the UART. At 56700 baud, and for
    /// a total of (say) 100 characters to be sent and received,
    /// this would be ~18ms.
    String rs41_cmd(const String& cmd);

  private:
    HardwareSerial& _serial;
    uint8_t _rs41_rx_buffer[RS41_SERIAL_BUFFER_SIZE];
    uint8_t _rs41_tx_buffer[RS41_SERIAL_BUFFER_SIZE];
    RS41SensorData _sensor_data;

};

#endif
