#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "reports/reports.h"
#include "alerts/alerts.h"

int extract_temp_C(const char *json)
{
  const char *key = "\"temp_C\":";
  char *key_position = strstr(json, key);
  if (key_position == NULL)
  {
    fprintf(stderr, "Key 'temp_C' not found.\n");
    return -1; // Return -1 to indicate an error
  }
  key_position += strlen(key);

  // Skip whitespace and quotes
  while (*key_position == ' ' || *key_position == '"')
  {
    key_position++;
  }

  // Extract the integer value
  char temp_str[16]; // Temporary buffer for the number
  size_t i = 0;
  while (*key_position >= '0' && *key_position <= '9' && i < sizeof(temp_str) - 1)
  {
    temp_str[i++] = *key_position++;
  }
  temp_str[i] = '\0'; // Null-terminate the string

  // Convert to integer
  return atoi(temp_str);
}

int main()
{
  char *city = "karachi";
  int threshold = 20;
  char *report = fetch_json_report(city);
  if (report == NULL)
  {
    printf("API limit reached.\n");
    return 0;
  }
  else
  {
    save_raw_json_report(city, report);
    int temp = extract_temp_C(report);
    if (temp == -1)
    {
      printf("Failed to extract temperature.\n");
      return 1;
    }
    else
    {
      char temp_str[16];                                // Buffer to hold the string representation of `temp`
      snprintf(temp_str, sizeof(temp_str), "%d", temp); // Convert `temp` to a string
      save_processed_json_report(city, temp_str);
      char body[256];
      if (temp > threshold)
      {
        printf("Temperature is above threshold.\n");
        snprintf(body, sizeof(body), "Temperature has exceeded 20C. It is %dC.", temp);
        send_alert("Temperature Alert", body);
      }
      else
      {
        printf("Temperature is below threshold.\n");
        snprintf(body, sizeof(body), "Temperature is %dC.", temp);
        send_alert("Weather Update", body);
      }
      return 0;
    }
  }
}
