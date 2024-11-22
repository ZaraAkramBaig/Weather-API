#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "alert.h"

#This function triggered an alert if critical condition are met i.e, temperature < 30 and humidity < 80
void triggerifCritical(float temperature, float humidity) {
    if (temperature > 30.0 || humidity > 80.0) {
        raise(SIGUSR1);  // Raise the custom signal to trigger the alert
    }
}
#This function handles alert based on received signal
void triggerAlert(int sig) {
    if (sig == SIGUSR1) {
        printf("Alert: Critical environmental condition detected!\n");
        // Write the critical alert to the log file
        system("/bin/echo 'Critical Alert! Check environment immediately.' >> /home/areebakhan/intergrated_enviromental_monitoring_system/logs/alerts.log");
    }
}

