# E-Nose Project

This is my submission for the DiamondHacks 2021 hackathon.

## Demo

[Here](https://youtu.be/ebkcwQ11CI8) is a link to the demo on YouTube.

## Code

All code is provided and commented in the e-nose.ino file.

## Hardware
* [Pro Mini 3.3v ATMega 328p](https://www.aliexpress.com/item/32821902128.html)
* [3.3v Voltage regulator](https://www.aliexpress.com/item/32732025305.html)
* [0.96" I2C Yellow-Blue SSD1306 OLED](https://www.aliexpress.com/item/32828425736.html?)
* [SGP40 Gas Sensor](https://www.adafruit.com/product/4829)
* [DHT11 Temperature and Humidity Sensor](https://www.aliexpress.com/item/1005003149739904.html)
* Toggle Switch
* Generic LiPo Battery

## Wiring
![Wiring Diagram](https://github.com/Watt3r/e-nose/raw/master/images/Wiring.fzz.png "Wiring.fzz")

### Pinouts
| DHT 11 Pins   | Arduino Pins  |
| ------------- | ------------- |
| 0 (Left)      | 2             |
| 1 (Middle)    | 3.3v          |
| 2 (Right)     | GND           |

| SGP40 Pins    | Arduino Pins  |
| ------------- | ------------- |
| VIN           | RAW           |
| 3.3v          | Empty         |
| GND           | GND           |
| SCL           | A5            |
| SDA           | A4            |

| 128x64 OLED Pins | Arduino Pins  |
| -------------    | ------------- |
| GND              | GND           |
| VCC              | RAW           |
| SCL              | A5            |
| SDA              | A4            |

## Libraries used

For this project I used many helpful libraries, listed below.

[SSD1306Ascii](https://github.com/greiman/SSD1306Ascii)

[Adafruit SGP40 Library](https://github.com/adafruit/Adafruit_SGP40)

[Adafruit DHT Sensor Library](https://github.com/adafruit/DHT-sensor-library)

## Next Steps
V2 of the e-nose will be a custom PCB on raspberry pi zero with Machine Learning to detect smells. 
