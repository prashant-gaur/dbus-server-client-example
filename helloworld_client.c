#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "test.h"


static void
on_status_changed (GObject    *object,
                     GParamSpec *pspec,
                      gpointer    user_data)
{
  g_print("Server Resp status property changed: %s \n", pspec->name);
  switch(pspec->name)
	{
		case 
}

static gboolean 
hellow_notification(TestPrgGDBUS *interface,
                gint roll_number,
    		const gchar *name)
{
	g_print("signal received from server \n");
	g_print("Server Resp Name --> %s \n", name);
	g_print("Server resp Roll Number--> %d \n", roll_number);	
}


static void async_hellow_proxy(GObject *source_object, GAsyncResult *res, gpointer user_data)
{
	TestPrgGDBUS *proxy;
	GError *error=NULL;
	gchar *buf=NULL;
	proxy=test_prg_gdbus_proxy_new_for_bus_finish(res, &error);
	g_print("Server Resp: proxy created \n");
	#if 0
	test_prg_gdbus_call_hello_world_sync(proxy, "peehu", &buf, NULL, &error);
	if(error != NULL)
	{
		g_print("Error....");
	}
	g_print("Server Resp: %s \n", buf);	
	#endif
	g_signal_connect(proxy,"notification", G_CALLBACK(hellow_notification), NULL);
    g_signal_connect (proxy,"notify", G_CALLBACK (on_status_changed), NULL);
	//g_object_unref(proxy);
}

int main()
{
	#if 0
	TestPrgGDBUS *proxy;
	GError *error=NULL;
	gchar *buf=NULL;
	synchronouse call
	proxy=test_prg_gdbus_proxy_new_for_bus_sync(G_BUS_TYPE_SESSION, G_DBUS_PROXY_FLAGS_NONE, \
						"com.pgaur", "/com/pgaur/GDBUS", NULL, &error);
	#endif
	//asynchronous call
	GMainLoop *loop;
	loop=g_main_loop_new(NULL, FALSE);
	test_prg_gdbus_proxy_new_for_bus(G_BUS_TYPE_SESSION, G_DBUS_PROXY_FLAGS_NONE, \
				"com.pgaur","/com/pgaur/GDBUS", NULL, async_hellow_proxy, NULL);	
	g_main_loop_run(loop);
	#if 0
	test_prg_gdbus_call_hello_world_sync(proxy, "peehu", &buf, NULL, &error);
	if(error != NULL)
	{
		return FALSE;
	}
	
	g_print("Server Resp: %s \n", buf);	
	g_object_unref(proxy);
	#endif
	return 0;
}
