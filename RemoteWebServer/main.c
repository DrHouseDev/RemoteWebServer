#include <stdio.h>
#include <string.h>
#include "mongoose.h"

static void *callback(enum mg_event event,
                      struct mg_connection *conn) {
  const struct mg_request_info *request_info = mg_get_request_info(conn);

  if (event == MG_NEW_REQUEST) {

	  if (!strcmp(mg_get_request_info(conn)->uri, "/play")) {

		  char content[1024];
		  int content_length = _snprintf(content, sizeof(content),
			  "PlayBoy",
			  request_info->remote_port);
		  mg_printf(conn,
			  "HTTP/1.1 200 OK\r\n"
			  "Content-Type: text/plain\r\n"
              "Content-Length: %d\r\n"        // Always set Content-Length
              "\r\n"
              "%s",
              content_length, content);
	  }
	  else
	  {
		  
		  char content[1024];
		  int content_length = _snprintf(content, sizeof(content),
			  "Hello from mongoose! Remote port: %d",
			  request_info->remote_port);
		  mg_printf(conn,
			  "HTTP/1.1 200 OK\r\n"
			  "Content-Type: text/plain\r\n"
              "Content-Length: %d\r\n"        // Always set Content-Length
              "\r\n"
              "%s",
              content_length, content);
	  }
    // Mark as processed
    return "";
  } else {
    return NULL;
  }
}

int main(void) {
  struct mg_context *ctx;
  const char *options[] = {"listening_ports", "8080,80,7777", NULL};

  ctx = mg_start(&callback, NULL, options);
  getchar();  // Wait until user hits "enter"
  mg_stop(ctx);

  return 0;
}
