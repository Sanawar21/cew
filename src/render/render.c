#include "render.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void trim_trailing_whitespace(char *str)
{
  int length = strlen(str);

  // Iterate backwards until a non-whitespace character is found
  while (length > 0 && isspace((unsigned char)str[length - 1]))
  {
    length--;
  }

  str[length] = '\0'; // Null-terminate at the new length
}

void trim_leading_whitespace(char **str)
{
  // Advance the pointer to skip leading whitespace
  while (isspace((unsigned char)**str))
  {
    (*str)++;
  }
}

char *render_html_without_head(char *html)
{
  bool in_tag = false;
  bool in_head = false;
  char buffer[4096]; // Buffer to store filtered content (adjust size if necessary)
  int index = 0;     // Index for buffer

  for (char *ptr = html; *ptr; ++ptr)
  {
    if (strncmp(ptr, "<head>", 6) == 0)
    {
      in_head = true;
      ptr += 5; // Move pointer to the end of "<head>"
    }
    else if (strncmp(ptr, "</head>", 7) == 0)
    {
      in_head = false;
      ptr += 6; // Move pointer to the end of "</head>"
    }
    else if (strncmp(ptr, "&quot;", 6) == 0)
    {
      buffer[index++] = '"'; // Replace &quot; with "
      ptr += 5;              // Move pointer to the end of "&quot;"
    }
    else if (strncmp(ptr, "Follow @igor_chubin", 19) == 0)
    {
      break; // Stop processing if "Follow @igor_chubin" is found
    }
    else if (*ptr == '<')
    {
      in_tag = true;
    }
    else if (*ptr == '>')
    {
      in_tag = false;
    }
    else if (!in_tag && !in_head)
    {
      buffer[index++] = *ptr; // Add content outside tags and <head> to buffer
    }
  }

  buffer[index] = '\0'; // Null-terminate the buffer

  // Remove trailing whitespace and newline
  trim_trailing_whitespace(buffer);

  // Skip leading whitespace
  char *trimmed_buffer = buffer;
  trim_leading_whitespace(&trimmed_buffer);

  // Allocate memory for the final result
  char *result = malloc(strlen(trimmed_buffer) + 1);
  if (!result)
  {
    fprintf(stderr, "Memory allocation failed\n");
    return NULL;
  }
  strcpy(result, trimmed_buffer);
  printf("%s\n", result); // Print the cleaned content
  return result;          // Return the cleaned content
}

void render_processed_html(char *html)
{
  // Allocate memory for the final result
  char *result = malloc(strlen(html) + 1);
  if (!result)
  {
    fprintf(stderr, "Memory allocation failed\n");
    return;
  }
  strcpy(result, html);
  printf("%s\n", result); // Print the processed HTML
}
