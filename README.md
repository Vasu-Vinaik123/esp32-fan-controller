# ESP32 Temperature-Aware Multi-Mode Motor Controller

🎥 Demo Video: 
https://youtube.com/shorts/NNXiFTvhVC4

This is a multi-mode DC motor controller built on the ESP32, using ESP-IDF v6.0 and FreeRTOS. The motor reacts to environmental temperature through a DHT11 sensor or operates in user-selected modes. It shows the basics of real-time embedded firmware.

## Features

Four operating modes cycled via a push button:

| Mode | Behavior |
|---|---|
| **MANUAL** | Motor runs at a fixed speed of 50% |
| **AUTO** | Motor speed changes with ambient temperature (0–50°C translates to 0–100%) |
| **BURST** | Motor pulses at full speed for 300ms on and 300ms off |
| **STOP** | Motor is halted |

Additional features:
- PWM speed control using the ESP32 LEDC peripheral
- A 3-LED speed bar indicates the current motor output level
- DHT11 temperature sensor for closed-loop AUTO mode
- Polling-based button reader with software debouncing set to 500ms
- Modular C structure with separate files for each subsystem
- FreeRTOS task-based design with queue-based event communication

## Hardware

- ESP32 development board
- L298N H-bridge motor driver
- 12V DC motor with a 8.4 V power supply(battery pack)
- DHT11 temperature and humidity sensor
- 3 LEDs with 220Ω resistors
- Push button
- 1kΩ resistors (×3) for GPIO isolation

### Pinout

| Function | GPIO |
|---|---|
| Motor ENA (PWM) | 25 |
| Motor IN1 | 27 |
| Motor IN2 | 26 |
| LED 1 (low) | 32 |
| LED 2 (mid) | 33 |
| LED 3 (high) | 14 |
| Button | 12 |
| DHT11 DATA | 4 |

### Wiring Notes

- Use 1kΩ series resistors between the ESP32 GPIOs (ENA, IN1, IN2) and L298N inputs to prevent GPIO backfeeding through the ESP32 protection diodes when the motor power is connected before USB.
- Ensure a common ground between the ESP32, L298N, and battery negative.
- The recommended power-on order is to connect the ESP32 USB first, followed by the 12V adapter.

## Architecture

The project features three FreeRTOS tasks that communicate through a queue.

## Skills Demonstrated

- ESP-IDF v6.0 framework, FreeRTOS multitasking  
- LEDC PWM peripheral setup for motor control  
- DHT11 sensor integration with a proprietary one-wire protocol  
- Inter-task communication using FreeRTOS queues  
- Mutex-protected shared state between sensor and consumer tasks  
- State machine design for mode management  
- Software button debouncing with timing-based suppression  
- Modular C: header files, `extern` declarations, separation of concerns  

## Build & Flash

Requires ESP-IDF v5.0 or later. Tested on v6.0.

Replace `COM_PORT` with your ESP32 serial port (e.g., `COM3` on Windows).

## File Structure

├── CMakeLists.txt          # Top-level build file
├── main/
│   ├── CMakeLists.txt      # Component build config
│   ├── main.c              # app_main, task creation
│   ├── motor.c / motor.h   # Motor control via LEDC PWM
│   ├── led.c   / led.h     # LED speed bar
│   ├── sensor.c / sensor.h # DHT11 temperature reading
│   ├── input.c / input.h   # Button queue + event_task
│   └── mode.c   / mode.h   # State machine + mode_task
├── sdkconfig               # Build configuration
└── README.md



## Future Improvements

- Add OTA firmware updates
- Web dashboard via Wi-Fi for remote monitoring and mode control
