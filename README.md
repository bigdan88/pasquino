# pasquino

The extension for an Arduino file is .ino. This file type is specific to Arduino and it contains the code that will be uploaded to the board.

You can create an .ino file by opening the Arduino IDE and selecting "File" > "New" from the menu. Once you've written your code, you can upload it to the board by connecting the board to your computer via a USB cable and selecting the appropriate board and serial port in the Arduino IDE. Then you can click on the upload button to send the code to the board.

This project now uses the actively maintained **PID** library. It can be installed via the Arduino IDE library manager by searching for `PID` and clicking "Install". Include it in your code with:

```cpp
#include <PID.h>
```

The previous README referenced `PID_v1.h`, which is no longer maintained. The switch to `PID.h` ensures compatibility with the latest fixes and improvements.

## Safety features

The code includes several protections for safer operation:

- Sanity checks on sensor input to detect readings outside the expected 0–1023 range.
- A guard against divide-by-zero during auto-tuning.
- A 30–second timeout in the tuning routine that forces the output to zero if exceeded.
- PID output is clamped before sending the value to the hardware pin.

