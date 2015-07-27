#pragma SPARK_NO_PREPROCESSOR

#include "application.h"
#include "Relay.h"

Relay Relay1 (0, 0, false, 1);
Relay Relay2 (1, 1, false, 1);
Relay Relay3 (2, 2, false, 1);
Relay Relay4 (3, 3, false, 1);

char *role = "relay";
int numRelays = 4;
Relay relays[4] = {Relay1, Relay2, Relay2, Relay4};

bool silent;

int toggleSilent() {
    silent = silent ? false : true;
    EEPROM.write(1, silent);
    return (int) silent;
}

int setConfig(String args) {
    RGB.control(true);
    RGB.color(255,000,000);
    String command = args.substring(0,2);
    String cmdargs = args.substring(2);
    
    if(command == "to") {
        unsigned int i = cmdargs.substring(0,1).toInt();
        if(i >= 0 and i <= 9 and i <= (sizeof(relays)/sizeof(relays[0]))) {
            relays[i].toggle();
        }
    } else if(command == "on") {
        unsigned int i = cmdargs.substring(0,1).toInt();
        if(i >= 0 and i <= 9 and i <= (sizeof(relays)/sizeof(relays[0]))) {
            relays[i].on();
        }
    } else if(command == "of") {
        unsigned int i = cmdargs.substring(0,1).toInt();
        if(i >= 0 and i <= 9 and i <= (sizeof(relays)/sizeof(relays[0]))) {
            relays[i].off();
        }
    } else if(command == "ao") {
        for(int i = 0; i < numRelays; i++) {
            relays[i].on();
        }
    } else if(command == "af") {
        for(int i = 0; i < numRelays; i++) {
            relays[i].off();
        }
    } else if(command == "ts") {
        toggleSilent();
    } else if(command == "st") {
        unsigned int i = cmdargs.substring(0,1).toInt();
        if(i >= 0 and i <= 9 and i <= (sizeof(relays)/sizeof(relays[0]))) {
            return relays[i].getStatus();
        }
    }
    RGB.control(false);
    return 1;
}

int getStatus(String args) {
    String relay = args.substring(0,1).toInt();
    if(i >= 0 and i <= 9 and i <= (sizeof(relays)/sizeof(relays[0]))) {
        return relays[i].getStatus();
    }
    return -1;
}

void setup() {
    Spark.function("setConfig",setConfig);
    Spark.function("getStatus",getStatus);
    Spark.variable("role", role, STRING);
    silent = (int) EEPROM.read(1);
}

void loop() {
    if(silent && WiFi.ready()) {
        RGB.control(true);
        RGB.color(0,0,0);
    } else if(!silent || !WiFi.ready()) {
        RGB.control(false);
    }
}
