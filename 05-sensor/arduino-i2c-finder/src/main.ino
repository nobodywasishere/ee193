// /*I2C_scanner
//   This sketch tests standard 7-bit addresses.
//   Devices with higher bit address might not be seen properly.*/

// #include <Arduino.h>
// #include <Wire.h>

// void setup()
// {
//     Wire.begin();

//     Serial.begin(9600);
//     while (!Serial)
//         ;
//     Serial.println("\nI2C Scanner");
// }

// void loop()
// {
//     byte error, address;
//     int nDevices;

//     Serial.println("Scanning...");

//     nDevices = 0;
//     for (address = 1; address < 255; address++)
//     {
        // Wire.beginTransmission(address);
//         error = Wire.endTransmission();

//         if (error == 0)
//         {
//             Serial.print("I2C device found at address 0x");
//             if (address < 16)
//                 Serial.print("0");
//             Serial.print(address, HEX);
//             Serial.println("  !");

//             nDevices++;
//         }
//         else if (error == 4)
//         {
//             Serial.print("Unknown error at address 0x");
//             if (address < 16)
//                 Serial.print("0");
//             Serial.println(address, HEX);
//         }
//     }
//     if (nDevices == 0)
//         Serial.println("No I2C devices found\n");
//     else
//         Serial.println("done\n");

//     delay(5000);
// }


#include <Arduino.h>
#include <Wire.h>


void setup()
{

    Wire.begin(); // join i2c bus (address optional for master)

    Serial.begin(9600); // start serial for output
    Serial.println("Serial enabled...");
}

void loop()
{
    // Serial.println("Requesting 6 bytes");
    Wire.requestFrom(0x48, 1); // request 6 bytes from peripheral device #8

    if (! Wire.available()) {
        Serial.println("Device not available!");
    }
    while (Wire.available())
    { // peripheral may send less than requested

        int c = Wire.read(); // receive a byte as character
        Serial.print(c); // print the character
        // Serial.print(d >> 7); // print the character
        Serial.println("*C");
    }

    delay(1000);
}
