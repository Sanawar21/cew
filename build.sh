gcc -I/usr/include/libnotify -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include \
    -I/usr/include/gdk-pixbuf-2.0 -I/usr/lib/x86_64-linux-gnu/gdk-pixbuf-2.0/include \
    src/main.c src/alerts/alerts.c src/reports/reports.c src/http/http_request.c src/render/render.c \
    -lcurl -lnotify -lgobject-2.0 -lglib-2.0 -o build/main

gcc -I/usr/include/libnotify -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include \
    -I/usr/include/gdk-pixbuf-2.0 -I/usr/lib/x86_64-linux-gnu/gdk-pixbuf-2.0/include \
    src/notifier.c src/alerts/alerts.c src/reports/reports.c src/http/http_request.c src/render/render.c \
    -lcurl -lnotify -lgobject-2.0 -lglib-2.0 -o build/notifier
