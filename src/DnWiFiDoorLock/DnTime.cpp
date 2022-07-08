#include "DnTime.h"

using namespace DnWiFiDoorLock;

DnTime DnTime::uptime() {
    return DnTime(millis());
}

// If I count correctly, `unsigned long` gives us max 49 days without restart xD
// 4294967295/1000/60/60/24 ~= 49
// 
// btw, i used to have `int` here:
// how is that the compiler did not warn me
// that the potencial value coming here could me `unsigned long`,
// which is given by `millis()`?
// what will happen after 49 days?
// a crash? or `millis()` will just give a wrong result?
//
// another question: does static `const` for arg make any difference?
DnTime::DnTime(const unsigned long milliseconds) {
    // potencial RAM saving:
    //   calculate on demand,
    //   instead of storing precalculated values,
    //   4 bytes each ;-)
    this->milliseconds = milliseconds;
    seconds = milliseconds / 1000;
    minutes = seconds / 60;
    hours = minutes / 60;
    days = hours / 24;
}

unsigned long DnTime::getMilliseconds() {
    return milliseconds;
}

long DnTime::getSeconds() {
    return seconds;
}

long DnTime::getMinutes() {
    return minutes;
}

int DnTime::getHours() {
    return hours;
}

// `byte` is enough, we won't be going longer than 49 days xD
byte DnTime::getDays() {
    return days;
}

int DnTime::getRemainingMilliseconds() {
    return milliseconds % 1000;
}

byte DnTime::getRemainingSeconds() {
    return seconds % 60;
}

byte DnTime::getRemainingMinutes() {
    return minutes % 60;
}

byte DnTime::getRemainingHours() {
    return hours % 24;
}
