#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "reports/reports.h"
#include "render/render.h"

char *get_city()
{

  while (1)
  {
    printf("1. Karachi\n");
    printf("2. London\n");
    printf("3. Sydney\n");
    printf("4. Berlin\n");
    printf("5. Miami\n");
    printf("6. Exit\n");

    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
      return "karachi";
    case 2:
      return "london";
    case 3:
      return "sydney";
    case 4:
      return "berlin";
    case 5:
      return "miami";
    case 6:
      return "exit";
    default:
      printf("Invalid choice\n");
    }
  }
}

int main()
{

  printf("Weather App!\n");
  printf("------------\n\n");

  while (1)
  {
    // choose old report retrieval or new report fetching
    printf("1. Get current weather\n");
    printf("2. Get previous report\n");
    printf("3. Exit\n");

    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
    {
      // fetch new report
      char *city = get_city();
      char *report = fetch_html_report(city);
      if (report == NULL)
      {
        printf("API limit reached.\n");
        return 0;
      }
      else
      {
        save_raw_html_report(city, report);
        char *processed = render_html_without_head(report);
        char choice;
        printf("Do you wish to save the report? (y/n): ");
        scanf(" %c", &choice);

        if (choice == 'y')
        {
          save_processed_html_report(city, processed);
          printf("Report saved successfully\n");
        }
        else
        {
          printf("Report not saved\n");
        }

        // free report
        free(report);
        free(processed);
      }

      break;
    }
    case 2:
    {
      // retrieve old report
      char *city = get_city();
      char *report = retrieve_processed_html_report(city);
      if (report == NULL)
      {
        printf("Report not found\n");
        return 0;
      }
      else
      {
        render_processed_html(report);
      }
      break;
    }
    case 3:
      return 0;
    default:
      printf("Invalid choice\n");
    }
    printf("\n");
  }
  return 0;
}
