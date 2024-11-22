#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include "api_interaction.h"
#include "alert.h"
#include "main.h"
#include <unistd.h>


void interpret_sensor_data();  

int main() {
    
    signal(SIGUSR1, triggerAlert);  

    
    const char *city = "London";  

    
    while (1) {
        
        retrieve_weather_data(city);

        
        float temperature = 35.0;  
        float humidity = 85.0;     
        triggerifCritical(temperature, humidity);

       
        interpret_sensor_data();

        
        sleep(120);
    }

    return 0;
}

