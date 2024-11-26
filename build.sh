gcc src/main.c src/alerts/alerts.c src/reports/reports.c src/http/http_request.c src/render/render.c \
    -lcurl -o build/main

gcc src/notifier.c src/alerts/alerts.c src/reports/reports.c src/http/http_request.c src/render/render.c \
    -lcurl -o build/notifier
