#include <gtk/gtk.h>
#include <locale.h>

static void ButtonClick ( GtkButton* button , gpointer user_data ) {
	gtk_button_set_label ( button , "Clicked" );
}


static gboolean on_window_close ( GtkButton* button, gpointer user_data ) {


	g_application_quit ( G_APPLICATION ( user_data ) );
	return GDK_EVENT_STOP;  
}

void localeChange ( ) {
	setlocale ( LC_ALL , "ko_KR.UTF-8" );
	printf ( "Current Locale: %s\n" , setlocale ( LC_ALL , NULL ) );
}

static void on_activate ( GtkApplication* app , gpointer user_data ) {
	GtkBuilder* builder;
	GObject* window , * button, *button2;
	GError* error = NULL;

	builder = gtk_builder_new ( );
	if (!gtk_builder_add_from_file ( builder , "interface.ui" , &error )) {
		g_printerr ( "Error loading UI file: %s\n" , error->message );
		g_clear_error ( &error );
		return;
	}

	window = gtk_builder_get_object ( builder , "main_window" );
	button = gtk_builder_get_object ( builder , "main_button" );
	button2 = gtk_builder_get_object ( builder , "exit_button" );


	gtk_window_set_application ( GTK_WINDOW ( window ) , app );


	g_signal_connect ( button , "clicked" , G_CALLBACK ( ButtonClick ) , NULL );
	g_signal_connect ( button2 , "clicked" , G_CALLBACK ( on_window_close ) , NULL,  window );

	// CSS 설정
	GtkCssProvider* provider = gtk_css_provider_new ( );
	gtk_css_provider_load_from_string ( provider ,
		"* { font-family: 'Malgun Gothic'; font-size: 14pt; }" );

	GdkDisplay* display = gdk_display_get_default ( );
	gtk_style_context_add_provider_for_display ( display ,
		GTK_STYLE_PROVIDER ( provider ) ,
		GTK_STYLE_PROVIDER_PRIORITY_USER );

	gtk_window_present ( GTK_WINDOW ( window ) );
	g_object_unref ( builder );
}

int main ( int argc , char** argv ) {
	localeChange ( );

	GtkApplication* app;
	int status;

	// std::thread ros_thread ( ros2_thread_func ); // 



	app = gtk_application_new ( "com.gtk.GtkApp" , G_APPLICATION_FLAGS_NONE );
	g_signal_connect ( app , "activate" , G_CALLBACK ( on_activate ) , NULL );

	status = g_application_run ( G_APPLICATION ( app ) , argc , argv );
	g_object_unref ( app );
	return status;
}
