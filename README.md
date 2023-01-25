# pasquino

The extension for an Arduino file is .ino. This file type is specific to Arduino and it contains the code that will be uploaded to the board.

You can create an .ino file by opening the Arduino IDE and selecting "File" > "New" from the menu. Once you've written your code, you can upload it to the board by connecting the board to your computer via a USB cable and selecting the appropriate board and serial port in the Arduino IDE. Then you can click on the upload button to send the code to the board.

Regarding the PID_v1.h library, it can be easily installed via the Arduino IDE library manager. To do this, you can open the Arduino IDE and go to "Sketch" > "Include Library" > "Manage Libraries". Then, in the search bar, type "PID", select the PID_v1 library, and click on the "Install" button. Once the library is installed, you can include it in your code by adding the following line at the top of your code:

Copy code
#include <PID_v1.h>
It's worth noting that this library is a version of the PID library that is no longer actively maintained, and there are other libraries such as "PID" and "PID_auto" that offer more features, better performance and are actively maintained.
