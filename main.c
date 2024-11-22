#include <stdio.h>            // Standard I/O library for input/output operations
#include <signal.h>           // Library for handling signals
#include <stdlib.h>           // Standard library for general-purpose functions (e.g., memory allocation, process control)
#include "api_interaction.h"  // Header for functions related to API interaction (likely retrieving weather data)
#include "alert.h"            // Header for functions related to triggering alerts
#include "main.h"             // Custom header, likely containing shared declarations (not provided here)
#include <unistd.h>           // Provides access to POSIX operating system API (e.g., sleep function)

void interpret_sensor_data();  // Forward declaration of the function that will interpret sensor data

int main() {
    
    // Set up a signal handler for the SIGUSR1 signal to call the triggerAlert function when this signal is received
    signal(SIGUSR1, triggerAlert);  

    const char *city = "London";  // Set the city for which weather data will be fetched

    // Infinite loop to repeatedly check weather data
    while (1) {
        
        // Retrieve weather data for the specified city (London) from the external API
        retrieve_weather_data(city);

        // Sample temperature and humidity values (hardcoded for demonstration)
        float temperature = 35.0;  // Temperature in Celsius
        float humidity = 85.0;     // Humidity percentage
        
        // Check if the temperature and humidity are critical, and trigger an alert if so
        triggerifCritical(temperature, humidity);

        // Interpret the sensor data (likely to process or display the data in some way)
        interpret_sensor_data();

        // Pause for 120 seconds (2 minutes) before the next iteration
        sleep(120);
    }

    return 0;  // Exit the program (never reached due to infinite loop)
}
