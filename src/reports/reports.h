#ifndef REPORTS_H
#define REPORTS_H

char *fetch_html_report(char *city);
char *fetch_json_report(char *city);
void save_raw_html_report(char *city, char *data);
void save_processed_html_report(char *city, char *data);
void save_raw_json_report(char *city, char *data);
void save_processed_json_report(char *city, char *data);
char *retrieve_processed_html_report(char *city);

#endif
