# ESP32 Practice

Getting confortable with _esp_ _idf_ and _freetos_ through implementations ranging from _IO and IO DEVICES_.

## What's in here

- **FreeRTOS basics**  tasks, queues, mutexes, semaphores, timers, and task notifications
- **RGB LED**  cycles through primary and secondary colors by toggling the R/G/B pins
- **7-segment display**  single display counting 0–9, plus a 4-digit multiplexed version driven through a shift register
- **Wokwi**  the `.json` files and `wokwi.toml` are for simulating the boards in Wokwi

Each demo lives in its own file under `main/` (e.g. `queues.c`, `timers.c`, `seven_segment.c`). The entry point is `main/practice.c`, where you can swap in whichever example you want to run.

## Building & running

It's a standard ESP-IDF project, so:

```bash
. $HOME/esp/esp-idf/export.sh   # or wherever your IDF lives
idf.py build
idf.py -p /dev/ttyUSB0 flash monitor
```

Or open it in Wokwi to simulate instead of flashing hardware.

## Notes

- Some files are half-finished , so don't take any of this as a reference.
- If something's missing or wrong, I probably just left it incomplete.
