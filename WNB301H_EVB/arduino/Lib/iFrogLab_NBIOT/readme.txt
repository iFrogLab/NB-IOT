This is an iFrogLab NB-IoT C++ library for Arduino 0004+, based on one created by 
Nicholas Zambetti for Wiring 0006+

Installation
--------------------------------------------------------------------------------

To install this library, just place this entire folder as a subfolder in your
Arduino/lib/targets/libraries folder.

When installed, this library should look like:

Arduino/lib/targets/libraries/iFrogLab_NBIOT              (this library's folder)
Arduino/lib/targets/libraries/iFrogLab_NBIOT/iFrogLab_NBIOT.cpp     (the library implementation file)
Arduino/lib/targets/libraries/iFrogLab_NBIOT/iFrogLab_NBIOT.h       (the library description file)
Arduino/lib/targets/libraries/iFrogLab_NBIOT/keywords.txt (the syntax coloring file)
Arduino/lib/targets/libraries/iFrogLab_NBIOT/examples     (the examples in the "open" menu)
Arduino/lib/targets/libraries/iFrogLab_NBIOT/readme.txt   (this file)

Building
--------------------------------------------------------------------------------

After this library is installed, you just have to start the Arduino application.
You may see a few warning messages as it's built.

To use this library in a sketch, go to the Sketch | Import Library menu and
select iFrogLab_NBIOT.  This will add a corresponding line to the top of your sketch:
#include <iFrogLab_NBIOT.h>

To stop using this library, delete that line from your sketch.

Geeky information:
After a successful build of this library, a new file named "iFrogLab_NBIOT.o" will appear
in "Arduino/lib/targets/libraries/iFrogLab_NBIOT". This file is the built/compiled library
code.

If you choose to modify the code for this library (i.e. "iFrogLab_NBIOT.cpp" or "iFrogLab_NBIOT.h"),
then you must first 'unbuild' this library by deleting the "iFrogLab_NBIOT.o" file. The
new "iFrogLab_NBIOT.o" with your code will appear after the next press of "verify"

