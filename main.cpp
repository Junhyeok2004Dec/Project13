#include <gtk/gtk.h>
#include <locale.h>

#include "TextEnumrate.h"


GtkBuilder* builder;
GObject* window , * car_connection_button , * car_register_button, *exit_button;
GError* error;
GObject* title_label , * label_1;

constexpr unsigned int HashCode ( const char* str )
{
	return str[ 0 ] ? static_cast<unsigned int>(str[ 0 ]) + 0xEDB8832Full * HashCode ( str + 1 ) : 8603;
}

static void ButtonClick ( GtkButton* button , gpointer user_data ) {
	gtk_label_set_label ( GTK_LABEL ( label_1 ) , "차량접속" );


	const char* name = gtk_buildable_get_buildable_id( GTK_BUILDABLE ( button ) );

	printf ( "%d", g_utf8_validate ( "차량접속" , -1 , NULL ) );
	printf ( "\t%s" , name );
	switch (HashCode(name))
	{
	case HashCode("car_connection_button"):
		gtk_label_set_label ( GTK_LABEL ( label_1 ) , "차량접속" );
		break;
	case HashCode("car_register_button") :
		gtk_label_set_label ( GTK_LABEL ( label_1 ) , "차량등록" );
		break;
	default:
		gtk_label_set_label ( GTK_LABEL ( label_1 ) , "test" );
		break;
	}


}





static gboolean on_window_close ( GtkButton* button, gpointer user_data ) {


	g_application_quit ( G_APPLICATION ( user_data ) );
	return GDK_EVENT_STOP;  
}

void localeChange ( ) {
	setlocale ( LC_ALL , "ko_KR.UTF-8" );
	printf ( "Current Locale: %s\n" , setlocale ( LC_ALL , NULL ) );
}

static void init_components ( GtkApplication* app , gpointer user_data ) {
	// Initialize components here

	builder = gtk_builder_new ( );
	if (!gtk_builder_add_from_file ( builder , "interface.ui" , &error )) {
		g_printerr ( "Error loading UI file: %s\n" , error->message );
		g_clear_error ( &error );
		return;
	}
	window = gtk_builder_get_object ( builder , "main_window" );
	car_connection_button = gtk_builder_get_object ( builder , "car_connection_button" );
	car_register_button = gtk_builder_get_object ( builder , "car_register_button" );
	title_label = gtk_builder_get_object ( builder , "title_label" );
	label_1 = gtk_builder_get_object ( builder , "text_display_1_label" );


}


static void on_window_destroy ( GtkWidget* widget , gpointer user_data ) {
	g_application_quit ( G_APPLICATION ( user_data ) );
}


static void on_activate ( GtkApplication* app , gpointer user_data ) {

	error = NULL;
	init_components ( app , user_data );
	gtk_window_set_application ( GTK_WINDOW ( window ) , app );


	g_signal_connect ( car_connection_button , "clicked" , G_CALLBACK ( ButtonClick ) , NULL );
	g_signal_connect ( car_register_button , "clicked" , G_CALLBACK ( ButtonClick ) , NULL );
	g_signal_connect ( exit_button , "clicked" , G_CALLBACK ( on_window_close ) , NULL );

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
