// RS41.h
#ifndef RS41_H
#define RS41_H

#include "Arduino.h"



class RS41 {

#define RS41_SERIAL_BUFFER_SIZE 1024
#define RS41_GPIO_PWR_PIN 32
  public:
    /// @brief Data fields from the RS41 sensor data string
    /// These are in the order that the tokens appear in the data string.
    struct RS41SensorData {
      /// @brief If this record is valid
      /// If the data read is unsuccesful, or the data decoding
      /// fails, valid will be false
      bool valid = false;
      /// @brief 0. Count of each frame sent since unit power up
      unsigned int frame_count = 0;
      /// @brief 1. RSS421 Air Temperature
      double air_temp_degC = 0.0;
      /// @brief 2. RSS421 Humidity at sensor temperature
      double humdity_percent = 0.0;
      /// @brief 3. RSS421 Humidity sensor temperature
      double hsensor_temp_degC = 0.0;
      /// @brief 4. RSS421 Pressure
      double pres_mb = 0.0;
      /// @brief 5. RSS421 Internal Module Temperature
      double internal_temp_degC = 0.0;
      /// @brief 6. RSS421 module status code
      unsigned int module_status = 0;
      /// @brief 7. RSS421 module error code
      unsigned int module_error = 0;
      /// @brief 8. Measured power supply voltage
      double pcb_supply_V= 0.0;
      /// @brief 9. Measured PCB temperature from LSM303 IC. Note: this sensor data is used to control the PCB heater.
      double lsm303_temp_degC = 0.0;
      /// @brief 10. Status of the PCB heater: disabled =0, enabled=1
      unsigned int pcb_heater_on = 0;
      /// @brief 11. Magnetic heading from the LSM303 X-Y measurements. Range 0-360°
      double mag_hdgXY_deg = 0.0;
      /// @brief 12. Magnetic heading from the LSM303 X-Z measurements. Range 0-360°
      double mag_hdgXZ_deg = 0.0;
      /// @brief 13. Magnetic heading from the LSM303 Y-Z measurements. Range 0-360°
      double mag_hdgYZ_deg = 0.0;
      /// @brief 14. X-axis gauss acceleration from the LSM303
      double accelX_mG = 0.0;
      /// @brief 15. Y-axis gauss acceleration from the LSM303
      double accelY_mG = 0.0;
      /// @brief 16. Z-axis gauss acceleration from the LSM303
      double accelZ_mG = 0.0;
    };

    /// A string that can be used as a column header for sensor data CSV files.
    /// The variable names match the order of the variables in the sensor
    /// data string, and the order of the members in RS41SensorData
    String sensor_data_var_names =  
      "frame_count,air_temp_degC,humdity_percent,hsensor_temp_degC,pres_mb,internal_temp_degC,module_status,module_error,pcb_supply_V,lsm303_temp_degC,pcb_heater_on,mag_hdgXY_deg,mag_hdgXZ_deg,mag_hdgYZ_deg,accelX_mG,accelY_mG,accelZ_mG";

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
    /// @brief Firmware banner
    /// @return The RS41 firmware banner which is sent
    /// at initial power on. If it was not detected,
    /// the return value will be an empty string.
    String banner();
    /// @brief Decoded sensor data
    RS41SensorData decoded_sensor_data();
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
    bool tokenize_string(String& source, String (&tokens)[], int nTokens);

  protected:
    HardwareSerial& _serial;
    uint8_t _rs41_rx_buffer[RS41_SERIAL_BUFFER_SIZE];
    uint8_t _rs41_tx_buffer[RS41_SERIAL_BUFFER_SIZE];
    String _banner;
};

#endif
