# pasquino

This repository contains an example of using the `PID_v1` library with Arduino.

## File extension

Arduino sketches use the `.ino` extension. You can create a sketch by opening the Arduino IDE and selecting **File > New**. After writing your code, upload it to the board by choosing the appropriate board and serial port. Then click the upload button.

## Library installation

The `PID_v1.h` library can be installed via the Arduino IDE Library Manager:

1. Go to **Sketch > Include Library > Manage Libraries**.
2. Search for **PID**.
3. Install **PID_v1**.

Once installed, include it in your code:

```cpp
#include <PID_v1.h>
```

Note that `PID_v1` is no longer actively maintained. Libraries such as `PID` or `PID_auto` may offer more features and better performance.

## Example code

The file [`pid.c`](pid.c) demonstrates a basic PID controller with an auto-tune routine. Rename it to `pid.ino` before opening it in the Arduino IDE.
