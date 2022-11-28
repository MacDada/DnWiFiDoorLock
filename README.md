DnWiFiDoorLock
===

---

Thank you for all the help I received on [`Better C++` Discord server](https://discord.gg/pJwsdep3Hn)!
 
- `alex88#9252`
- `Arno#7285`
- `Doctor Bazooka#2461`
- `DXPower#0133`
- `Felix#6325`
- `Fluffles#6709`
- `Pickleas Cage#4209`
- `SlyBach#4412`

--- 

Compile and upload to the device:

`pio run -t upload`

Serial monitor:

`pio run -t monitor`

**When serial monitor is active, the code cannot be uploaded**,
BUT we can combine both commands to run one after another:

`pio run -t upload -t monitor`

todo: why doesn't `pio run -t upload, monitor` work?
[in the docs they say `, ` should work](https://docs.platformio.org/en/latest/projectconf/section_env_build.html#projectconf-targets).

Code quality
===

`pio check`

---

To be used eventually?
`std::unordered_map<key type, value type>`

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
