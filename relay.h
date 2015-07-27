#ifndef __RELAY__
#define __RELAY__
#pragma SPARK_NO_PREPROCESSOR

class Relay {
    public:
    Relay(int id, int pin, bool normalOpen, int status):
    id(id),pin(pin),status(status),normalOpen(normalOpen){
        pinMode(pin, OUTPUT);
    };
    
    void on() {
        digitalWrite(pin, HIGH);
    }
    
    void off() {
        digitalWrite(pin, LOW);
    }
    
    void toggle() {
        status = status ? 0 : 1;
        status ? digitalWrite(pin, HIGH) :
                 digitalWrite(pin, LOW);
    }
    int getStatus() {
        return status;
    }
    
    private:
    int id, pin, status;
    bool normalOpen;
};

#endif
