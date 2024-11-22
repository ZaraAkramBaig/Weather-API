# Weather-API

Integrated Environmental Monitoring System
Description
This project implements an integrated environmental monitoring system in C. It interacts with a free API to retrieve real-time environmental data, processes it, and stores both raw and processed data in files. The system is designed to automate data retrieval and processing tasks using shell scripts, while also implementing real-time alerts for critical environmental conditions (e.g., high temperature and humidity).The project leverages contemporary computer engineering technologies, including dynamic memory allocation, modular programming, and Linux system calls, to optimize the system's efficiency and functionality.

Problem Definition
The goal is to create a system that:
1)Retrieves real-time environmental data such as temperature and humidity from a weather API.
2)Processes and stores raw and processed data in files.
3)Automates tasks such as data retrieval and processing using shell scripts.
4)Implements dynamic memory management to optimize data manipulation.
5)Sends real-time alerts using Linux system calls if critical environmental conditions are detected (e.g., temperature above 30°C or humidity above 80%).
Features
6)Real-time data retrieval: Interact with a free weather API (WeatherAPI) to get current environmental data.
7)Data storage: Store raw and processed data in weather_data.txt and sensor_data.txt files.
8)Data processing: Parse the API response to extract temperature and humidity values.
9)Real-time alerts: Trigger alerts when critical environmental conditions (e.g., high temperature or humidity) are detected.
10)Shell scripts: Automate data retrieval and processing tasks.
11)Modular code: Use header files and dynamic memory allocation to enhance code readability and efficiency.

Technologies Used:
1)Programming Language: C
2)Libraries:
3)libcurl: For retrieving data from the weather API.
4)cJSON: For parsing the API response in JSON format.

Tools:
1)Ubuntu (Linux) system
2)Shell scripting for automation
3)GCC for compiling C code

Installation Instructions

1)Clone the repository:
git clone https://github.com/ZaraAkramBaig/Weather-API

Install dependencies:
2)Install libcurl and cJSON:
sudo apt-get update
sudo apt-get install libcurl4-openssl-dev libjson-c-dev

3)Compile the project:
gcc main.c api_interaction.c alert.c -o weather_update -lcurl -lcjson

4)Run the program:
./weather_update
There are subdirectories in the code file intergrated_enviromental_monitoring_system named as data "data" in which processed_sensor_data.txt and weather_data.txt files are present .The program will retrieve data from api, then and save raw data in "weather_data.txt" file and process it which is save on "processed_sensor_data.txt" . There is another subdirectory  named as "logs" and all the alerts are being saved in "alerts.log" file inside it.

Usage Instructions
1)After compiling the code, run the executable. 
2)It will retrieve the current weather data from the WeatherAPI, process the data (temperature and humidity), and store it in a file called processed_sensor_data.txt.
3)If critical conditions are detected (e.g., temperature > 30°C or humidity > 80%), an alert will be triggered and displayed.
Example
Weather data saved to weather_data.txt.
Processed data saved to processed_sensor_data.txt.
Alert: Critical environmental condition detected! (Temperature: 32.5, Humidity: 85.0)

Shell Scripts:
1)The run_system.sh script automates the process of retrieving weather data and running the C program periodically.
2)To use it, simply modify the script with the desired city and schedule it in your system’s cron job.
 
File Structure:
/integrated_environmental_monitoring_system
 |data (subdirectory)
├── api_interaction.c                             # Handles API interaction and data processing
├── alert.c                                       # Defines critical condition alerts
├── main.c                                        # Main program to start data retrieval and processing
├── alert.h                                       # Header file for alert-related functions
├── api_interaction.h                             # Header file for API interaction functions
├── main.h                                        # Main header file including all project headers
├── weather_data.txt                              # Stores raw weather data
├── processed_sensor_data.txt                     # Stores processed sensor data
└── run_system.sh                                 # Shell script to automate data retrieval

Contributing:
Feel free to fork this repository, make improvements, and submit pull requests. Please ensure that your code adheres to the coding standards outlined in the project.

License:
This project is a semester project for the Computer and Information Systems Engineering department at NED University. It is for educational purposes only and is not intended for commercial use. All rights are reserved.
If you wish to use or modify this project for any purpose, please contact the authors or obtain permission from the relevant academic authorities.

Authors/Contributors:
1)Zara Akram Baig
2)Areeba Khan
3)Javeria Rizwan

Acknowledgments:
Thanks to WeatherAPI for providing the weather data API.
Special thanks to all contributors who helped develop this project.

Known Issues or Limitations:
The current implementation only handles temperature and humidity data. Additional environmental factors could be added in the future.

Contact Information:
For any questions or suggestions, please contact javeriar893@gmail.com.


