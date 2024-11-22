#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to trigger macOS notification
void send_alert(char *title, char *body)
{
  // Construct the AppleScript command to trigger the notification
  char command[512];
  snprintf(command, sizeof(command), "osascript -e 'display notification \"%s\" with title \"%s\"'", title, body);

  // Execute the AppleScript command
  system(command);
}
