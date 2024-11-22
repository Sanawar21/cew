// src/http/http_request.h
#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <stdlib.h>
#include <curl/curl.h>

typedef struct {
  char *data;
  size_t length;
} Response;

// Function to initialize the Response struct
void init_response(Response *response);

// Function to perform HTTP GET request
CURLcode http_get(  char *url, Response *response);

#endif // HTTP_REQUEST_H
