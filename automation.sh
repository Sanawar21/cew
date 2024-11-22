#!/bin/bash

# Define the cron job command
CRON_JOB="* * * * * build/notifier >> logs/output.log 2>&1"

# Check if the cron job is already present
crontab -l | grep -q "build/notifier"
if [ $? -eq 0 ]; then
    echo "Cron job already exists. No changes made."
else
    # Add the cron job
    (crontab -l; echo "$CRON_JOB") | crontab -
    echo "Cron job added."
fi
