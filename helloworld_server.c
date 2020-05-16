#include<stdio.h>
#include<stdlib.h>
#include<glib.h>
#include"generated-code.h"
#include <time.h>

static GDBusConnection *session_bus = NULL;
static gboolean
emit_notification_cb(gpointer interface) {
	
	gdbus_emit_notification(interface, 123, "prashant");
	gdbus_set_status (interface, (guint)rand());
	return TRUE;
	
}

static gboolean
hello_world(GDBUS *interface,
                GDBusMethodInvocation *invocation,
                const gchar *greeting, gpointer user_data) {

        gchar *response;
  		g_print("Client Resp: %s \n", greeting);     
        response=g_strdup_printf("hello world %s!!", greeting);
        gdbus_complete_hello_world(interface, invocation, response);
        g_free(response);
        return TRUE;
}

static void
on_name_acquired(GDBusConnection *connection,
                        const gchar *name, gpointer user_data) {

        GDBUS *interface;
        GError *error=NULL;
		session_bus = connection;
        interface=gdbus_skeleton_new();
		g_signal_connect(interface, "handle-hello-world", G_CALLBACK(hello_world), NULL);
        g_dbus_interface_skeleton_export(G_DBUS_INTERFACE_SKELETON(interface), session_bus, "/com/dream/GDBUS", &error);
		g_timeout_add_seconds(5, emit_notification_cb, interface);
}

int main()
{
	GMainLoop *loop;
	loop=g_main_loop_new(NULL, FALSE);
	srand(time(NULL));
	g_bus_own_name(G_BUS_TYPE_SESSION,"com.pgaur",G_BUS_NAME_OWNER_FLAGS_NONE, NULL, on_name_acquired, NULL, NULL, NULL);
	g_main_loop_run(loop);
	return 0;
}

