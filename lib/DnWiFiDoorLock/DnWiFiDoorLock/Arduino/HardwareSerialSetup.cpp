#include "HardwareSerialSetup.h"

namespace DnWiFiDoorLock::Arduino {

    HardwareSerialSetup::HardwareSerialSetup(
        HardwareSerial &serial,
        const DnWiFiDoorLock::Arduino::Hardware &hardware,
        const long bitsPerSecond
    ):
        serial(serial),
        hardware(hardware),
        bitsPerSecond(bitsPerSecond) {
    }

    void HardwareSerialSetup::onSetup() {
        serial.begin(bitsPerSecond);

        // waiting by uptime is not enough?!
        // without it the first Hello message is not printed :/
        hardware.pause(2000);

        // wait for serial port to open
        // taken from https://github.com/khoih-prog/WiFiWebServer/blob/master/examples/HelloServer/HelloServer.ino#L90
        while (!Serial && hardware.getUptime().getSeconds() < 5);

        // todo: do not hardcode app name
        serial.print(DnApp::Common::Strings::format(
            "\n\n\n\n\n\n\n\n\n"
            "%s"
            "================================"
            "%s"
            "\n\n"
            "%s"
            "  Hello from `DnWiFiDoorLock`!"
            "%s"
            "\n\n"
            "%s"
            "================================"
            "%s"
            "\n\n\n",
            VT100_FORMAT_BOLD_BLUE,
            VT100_FORMAT_RESET,
            VT100_FORMAT_BOLD_GREEN,
            VT100_FORMAT_RESET,
            VT100_FORMAT_BOLD_BLUE,
            VT100_FORMAT_RESET
        ).get());
    }

    void HardwareSerialSetup::onLoop() {
        // do nothing
    }

}
