// Uses POSIX functions to send and receive data from a Maestro.
// NOTE: The Maestro's serial mode must be set to "USB Dual Port".
// NOTE: You must change the 'const char * device' line below.
 
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <math.h>
 
// Gets the position of a Maestro channel.
// See the "Serial Servo Commands" section of the user's guide.
int maestroGetPosition(int fd, unsigned char channel)
{
  unsigned char command[] = {0x90, channel};
  if(write(fd, command, sizeof(command)) == -1)
  {
    perror("error writing");
    return -1;
  }
   
  unsigned char response[2];
  if(read(fd,response,2) != 2)
  {
    perror("error reading");
    return -1;
  }

  int result = response[0] + 256*response[1];
  return (int) round((((double) (result - 4000)) / 44.4444));
}
 
// Sets the target of a Maestro channel.
// See the "Serial Servo Commands" section of the user's guide.
// The units of 'target' are quarter-microseconds.
int maestroSetTarget(int fd, unsigned char channel, unsigned short target)
{
  // Convert the target to quarter-of-microseconds
  target = (unsigned short) round(4000 + ((double) target) * 44.4444);

  // Send the command
  unsigned char command[] = {0x84, channel, target & 0x7F, target >> 7 & 0x7F};
  if (write(fd, command, sizeof(command)) == -1)
  {
    perror("error writing");
    return -1;
  }
  return 0;
}
 
int main(int argc, char* argv[])
{
  if (argc != 4) {
    printf("Invalid number of arguments (3 needed)\n");
    exit(2);
  }

  char *device = argv[1];
  int channel = atoi(argv[2]);
  int position = atoi(argv[3]);

  printf("device = %s, channel = %d, position = %d\n", device, channel, position);

  // Open the Maestro's virtual COM port.
  //const char * device = "\\\\.\\USBSER000";  // Windows, "\\\\.\\COM6" also works
  //const char * device = "/dev/ttyACM0";  // Linux
  //const char * device = "/dev/cu.usbmodem00068971"; // Mac OS X
  int fd = open(device, O_RDWR | O_NOCTTY);
  if (fd == -1)
  {
    perror(device);
    return 1;
  }
   
  int currentPosition = maestroGetPosition(fd, channel);
  printf("Current position is %d.\n", currentPosition); 
 
  //int target = (position < 6000) ? 7000 : 5000;
  //printf("Setting target to %d (%d us).\n", target, target/4);
  //maestroSetTarget(fd, 11, target);

  maestroSetTarget(fd, channel, position);
   
  close(fd);
  return 0;
}
