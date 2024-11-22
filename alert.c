#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "alert.h"

void triggerifCritical(float temperature, float humidity) {
    if (temperature > 30.0 || humidity > 80.0) {
        raise(SIGUSR1);  // Raise the custom signal to trigger the alert
    }
}

void triggerAlert(int sig) {
    if (sig == SIGUSR1) {
        printf("Alert: Critical environmental condition detected!\n");
        // Write the critical alert to the log file
        system("/bin/echo 'Critical Alert! Check environment immediately.' >> /home/areebakhan/intergrated_enviromental_monitoring_system/logs/alerts.log");
    }
}

