#include "http_request.h"
#include <stdio.h>
#include <string.h>

// Initialize response struct
void init_response(Response *response)
{
  response->data = malloc(1);
  response->length = 0;
  response->data[0] = '\0';
}

// Callback function to write data to response
size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata)
{
  size_t total_size = size * nmemb;
  Response *response = (Response *)userdata;

  char *temp = realloc(response->data, response->length + total_size + 1);
  if (temp == NULL)
  {
    fprintf(stderr, "Failed to allocate memory\n");
    return 0;
  }

  response->data = temp;
  memcpy(response->data + response->length, ptr, total_size);
  response->length += total_size;
  response->data[response->length] = '\0';

  return total_size;
}

// Function to perform HTTP GET request
CURLcode http_get(char *url, Response *response)
{
  CURL *curl = curl_easy_init();
  CURLcode res = CURLE_OK;

  if (curl)
  {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
  }

  return res;
}
