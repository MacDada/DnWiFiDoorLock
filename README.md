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
  * `./tdd.sh native/Foo/test_Foo` – pass path to the test as the first argument.
  * It is best to configure `External Tools` and `Keymap` in `Clion` to run `tdd.sh`.
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
