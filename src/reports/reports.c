#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reports.h"
#include "../http/http_request.h"

char *retrieve_processed_html_report(char *city)
{
  char filename[100];
  sprintf(filename, "data/processed/html/%s.dat", city);

  FILE *file = fopen(filename, "r");
  if (file == NULL)
  {
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  long length = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *buffer = malloc(length + 1);
  if (buffer)
  {
    fread(buffer, 1, length, file);
  }

  fclose(file);
  return buffer;
}

void save_report(char *city, char *data, char *type)
{
  char filename[100];
  sprintf(filename, "data/%s/%s.dat", type, city);

  FILE *file = fopen(filename, "w");
  if (file == NULL)
  {
    fprintf(stderr, "Failed to open file\n");
    return;
  }

  fprintf(file, "%s", data);
  fclose(file);

  printf("Report saved to %s\n", filename);
}

char *fetch_report(char *city, char *format)
{
  char url[100];

  if (strcmp(format, "html") == 0)
    sprintf(url, "https://wttr.in/%s?1", city);
  else if (strcmp(format, "json") == 0)
    sprintf(url, "https://wttr.in/%s?format=j1", city);
  else
    sprintf(url, "https://wttr.in/%s", city);

  Response response;
  init_response(&response);

  CURLcode res = http_get(url, &response);

  if (res != CURLE_OK)
  {
    return NULL;
  }

  return response.data;
}

char *fetch_html_report(char *city)
{
  return fetch_report(city, "html");
}

char *fetch_json_report(char *city)
{
  return fetch_report(city, "json");
}
void save_raw_html_report(char *city, char *data)
{
  save_report(city, data, "raw/html");
}

void save_processed_html_report(char *city, char *data)
{
  save_report(city, data, "processed/html");
}

void save_raw_json_report(char *city, char *data)
{
  save_report(city, data, "raw/json");
}

void save_processed_json_report(char *city, char *data)
{
  save_report(city, data, "processed/json");
}
