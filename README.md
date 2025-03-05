DnApp
===

---
Home automation project(s) with ESP8266 microcontroller
---

Project ideas that are currently work in progress:

* a door lock
* a furnace (central heating) controller

---
Big thanks!
---

Thank you for all the help that I received on 
[`Better C++` Discord server](https://discord.gg/pJwsdep3Hn)!

- `00001H#8295`
- `alex88#9252`
- `Alvin121#2883`
- `Arno#7285`
- `Doctor Bazooka#2461`
- `Droid33#7264`
- `DXPower#0133`
- `Felix#6325`
- `Fluffles#6709`
- `Jérôme#1807`
- `Kev#3440`
- `Pickleas Cage#4209`
- `SlyBach#4412`
- `The Dreams Wind#1949`

Thank you for all the help that I received on 
[`PlatformIO Community` forum](https://community.platformio.org/)!

- [`ivankravets`](https://community.platformio.org/u/ivankravets)
- [`jcw`](https://community.platformio.org/u/jcw)
- [`maxgerhardt`](https://community.platformio.org/u/maxgerhardt)

---
A few notes
---

* Building environments:
  * `nodemcu` to upload to `NodeMCU DevKit 1.0`,
  * `nodemcu_ota` for WiFi uploads
  * `native` to run unit tests for pure C++,
  * `native_arduino` to run unit tests with Arduino framework mocked.
* In general, `pio run` builds `src` dir, while `pio test` builds `test` dir.
* `rm -rf .pio` – a quick way to get rid of the `PIO`'s generated files.
* `pio init --ide clion`

---
Building, uploading, running, monitoring
---

* `pio run -e nodemcu` and `pio run -e native` both build `src` directory,
   but with a given environment config.
* `pio run -t upload` builds and uploads to the board.
* `pio run -t monitor` – serial monitor (over USB cable)
* `pio run -t upload -t monitor` – upload and monitor combined

  **When serial monitor is active, the code cannot be uploaded!**

  That is why we need to combine this into one command,
  instead of having the monitor always in the background.

* `pio run -e native` builds native (desktop / command line) env.
* `pio run -e native -t exec` builds and runs the native "app".

---
Unit Tests
---

* `pio test -e native` builds and runs tests in `test/native/` directory.

* `pio test -e nodemcu` basically does nothing,
   as it would build tests do deploy on the embedded device.

* TDD workflow: watches for file changes and runs test(s) immediately, in a continuous loop.
  * Install `fswatch` tool first: `brew install fswatch`.
  * `./scripts/tdd.sh test/native/Foo/test_Foo` – pass path to the test as the first argument.
  * `./scripts/tdd.sh native/Foo/test_Foo` – you can also skip te `test` part of the path.
  * For `CLion` IDE it is best to configure `External Tools` and `Keymap` to run `tdd.sh`:
    * `Program`: `ABSOLUTE_PATH_TO_THE_PROJECT/scripts/tdd.sh`
    * `Arguments`: `$FileDirRelativeToProjectRoot$`
    * `Working directory`: `ABSOLUTE_PATH_TO_THE_PROJECT`
  * See more info inside the file.

---
Code quality
---

`pio check`

---
To Do
---

* [x] door lock open/close by website
* [x] automatically reconnects to Wi-Fi after lost connection
* [x] indicates lost Wi-Fi connection by blinking led
* [ ] physical buttons to open/close
* [ ] servo cutoff power circuit for energy saving
  > Use one pin with the servo library to control the position
     and use another the other pin with a MOSFET (/(npn switching) transistor (like 2N4401) / relay)
     (or other higher current driver) to turn the power to each servo on and off as you need to.
* [ ] door lock should work without Wi-Fi (i.e. being closed by default)
* [ ] configure `pio check` so it does not analyse external libraries
      https://docs.platformio.org/en/latest/core/userguide/cmd_check.html
* [ ] serial monitor output colors
  * [ ] [possible issue](https://community.platformio.org/t/monitor-configure-colors-for-line-with-tags/8625/10)
* [ ] To be used eventually? `std::unordered_map<key type, value type>`
* [ ] [Configure GH Workflows CI](https://piolabs.com/blog/insights/unit-testing-part-3.html)
* [ ] configure [simulator(s)](https://docs.platformio.org/en/latest/advanced/unit-testing/simulators/index.html)
  * [ ] [QEMU](https://docs.platformio.org/en/latest/advanced/unit-testing/simulators/qemu.html)
  * [ ] [Renode](https://docs.platformio.org/en/latest/advanced/unit-testing/simulators/renode.html)
  * [ ] [SimAVR](https://docs.platformio.org/en/latest/advanced/unit-testing/simulators/simavr.html)
* [ ] [update](https://github.com/esp8266/Arduino/issues/8779) and test fix

---
Ideas
---

* NodeMCU has 2 built–in LEDs -> I'm only using one for now, maybe I could use both.
  * https://lowvoltage.github.io/2017/07/09/Onboard-LEDs-NodeMCU-Got-Two
  * https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/
  * https://rabbithole.wwwdotorg.org/2017/03/28/esp8266-gpio.html
  * `D0` / `GPIO16`
    * on board
    * `high` at boot, falls to `low` after ~110ms
    * `USER`: whatever that means
    * `WAKE`: used to wake up from deep sleep
    * input: no interrupt
    * output: no PWM or I2C support
    * low output level isn’t the expected `0V`, but rather about `1V`
    * it is "inverted" – LED is bright on `low`, not on `high`
  * `D4` / `GPIO2`
    * on chip
    * `high` at boot, according to [1](https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/);
       varies at boot and stabilizes at `high` ~70ms after boot,
       while can be set to `low` ~110ms after boot,
       according to [2](https://rabbithole.wwwdotorg.org/2017/03/28/esp8266-gpio.html)
    * `TXD1`: whatever that means
    * `U1TXD`: it is probably the reason it flashes during chip programming
    * boot fails if pulled LOW
    * input: pulled up
    * output: OK
    * it is "inverted" – LED is bright on `low`, not on `high`
    * it is the `LED_BUILTIN` in the source code
    * I'm using this one currently to indicate app's status.
* LED brightness can be regulated with `analogWrite`, instead of just turning it on with `digitalWrite`
  * PWM must be supported on the PIN
  * For the loop indicator, I could use a soft heartbeat blinking,
    while using hard–bright blinking for error indication.
  * Must remember: `digitalRead` and `analogRead` give "wrong" results after `analogWrite`
    – if I want to track the state, I have to do it with a code var. 

---
Will NOT do (non–goals)
---

Most of the stuff, that _could_ be done, takes precious resources: time and hardware.

This project's focus is on learning and experimenting.
It is more important to me that I learn stuff doing it,
than that I achieve some incredible, polished result.

Another thing is that microcontroller hardware is very limited.
There is always a tradeoff between memory and speed. AND code quality.

* Super pretty web design
  * It is not a commercial project, that I'd want to advertise as having a shiny interface.
  * It has to work and be easy to use, not necessarily be pretty.
  * To spend more time on the looks, means to spend less time on the workings.
* Support for old web browsers
  * I don't use old web browsers, you shouldn't either (security reasons for starters).
* Support for disabled Javascript
  * It would be nice to have, but it would de facto mean doing and testing yet another UI,
    that I would not actually use, after all.
* Support for microcontroller boards I don't have or plan to use.
* [i18n](https://en.wikipedia.org/wiki/Internationalization_and_localization)
  – English only (and _maybe_ Polish)

---
Code style, conventions, decisions
---

* 4 spaces for indents
* Better have more lines, but keep them short
* What can be tested (and I know how), shall be tested (I mean automated testing ofc)
* `OOP`, `SOLID`
* `explicit` constructors (almost?) everywhere
* Always using `{}` for initialization, not `()`
* Marking classes as `final`, unless I actually need to extend over them
* One class definition per file
  * With the exception for internal, NOT reusable classes: so class in a class is allowed.
* Header files only, where possible
  * `.h` are enough most of the time to what I do.
  * Potential slower compilation does not bother me (it is still quick enough).
  * It sucks to maintain two files (`.h` and `.cpp`) for each class I make.
  * Readability is not a problem when you keep your classes short, 
    and doing one thing only, as required by `SRP`.
* Using `PROGMEM` everywhere I can (keeping strings in Flash, instead of RAM)
  * _Everywhere I can_, meaning the Arduino–related code, skipping for generic C++ code
  * `F` macro is not needed, `PSTR()` macro is enough.
    * Even for the code that is not Flash storage aware. 
      * At least on ESP-8266 it works.
        * It is [Von Neumann architecture](https://en.wikipedia.org/wiki/Von_Neumann_architecture)
          - there is one address space for both instructions and data.
      * If I'd ever want to make it compatible with the "real" Arduinos,
        therefore having [Harvard architecture](https://en.wikipedia.org/wiki/Harvard_architecture),
        where instructions and data are separate,
        the code would have to be strongly redesigned anyway.
      * There are a few places that `PSTR()` does not work, hence using `F()` or nothing.
        * They have a todo to find out why it does not work.
        * `ArduinoJson` lib crashes on `PSTR()`, but works with `F()`.
* A space between closure's context and body:
  ```cpp
  auto closure = [] () {};
  ```
* A comment, explaining why the header is being included, when it isn't obvious from the header's name:
  ```cpp
  #include <memory> // std::make_unique
  ```
* [`ArduinoJson`](https://arduinojson.org/)
  * `StaticJsonDocument` when recommended (<1KB and "predictable")
    -> with version `6` I'm forced to hardcode/calculate the size anyway,
       so `DynamicJsonDocument` does _not_ really ease the usage
  * It crashes on `PSTR()`, so using the "proper" `F()` instead
    -> todo: maybe I should get rid of it anyway? just use CStrings?
  * Serialization error handling policy: checking for overflow (`jsonDocument.overflowed()`)
* `const` methods vs `mutable`
  * https://isocpp.org/wiki/faq/const-correctness#logical-vs-physical-const
  * `DnApp::Logger::Logger`
    * `Logger` implementations obviously can have (some of them do have) internal state to manage 
      * -> to stay truthful with their nature, their methods are _not_ marked `const`.
      * -> to allow that, I don't specify `const` for the abstract base class methods as well.
    * On the other hand, the userland objects (services) might log or not
      -> whether they do or not, it does not **logically** change the service's state,
      -> therefore the internal `Logger logger` field might be marked as `mutable`.
    * https://discord.com/channels/583251190591258624/1088209923302768691/1089911377151397918
* [AAA: Almost Always Auto](https://herbsutter.com/2013/08/12/gotw-94-solution-aaa-style-almost-always-auto/)
* Integer types
  * Prefer the (size) explicit options (like `uint8_t`), over the unspecified (like `int`).
  * Use Arduino specific types (like `byte`) only for
    code directly dealing with such requirements from the Arduino framework.
  * Watch out for sizes on different platforms!
    * Can be tested in this way:
      ```cpp
      // compiles in the `nodemcu` env, does not on _(my)_ `native` env
      static_assert(sizeof(unsigned long) == sizeof(uint32_t));
      ```
    * `byte` / `unsigned byte`:
      * `nodemcu`: `int8_t` / `uint8_t` (`-128`–`127` / `0`–`255`)
      * `native`:  ~
    * `short` / `unsigned short`:
      * `nodemcu`: `int16_t` / `uint16_t` (`-32,768`–`32,767` / `0`–`65,535`)
      * `native`:  `int16_t` / `uint16_t` (`-32,768`–`32,767` / `0`–`65,535`)
    * `int` / `unsigned int`:
      * `nodemcu`: `int32_t` / `uint32_t` (`-2,147,483,648`–`2,147,483,647` / `0`–`4,294,967,295`)
      * `native`:  `int32_t` / `uint32_t` (`-2,147,483,648`–`2,147,483,647` / `0`–`4,294,967,295`)
    * `long` / `unsigned long`:
      * `nodemcu`: `int32_t` / `uint32_t` (`-2,147,483,648`–`2,147,483,647` / `0`–`4,294,967,295`)
      * `native`:  `int64_t` / `uint64_t` (large^^)
* `// todo:[2137] Description of what is to be done`
  – the number is for easier grep,
    when the same kind of issue appears in multiple places.
* `static_cast` to `void` when function arguments are not being used.
  I know of 3 possible solutions:
    * A.) `static_cast<void>(unusedParameter);`
          – the preferred C++ way, that we're doing,
    * B.) `(void) unusedParameter;`
          – the "old" C–style casting, but `A.)` is more precise,
    * C.) remove `unusedParameter` var from the function arguments
          – but keeping the name better explains what it represents.

---
