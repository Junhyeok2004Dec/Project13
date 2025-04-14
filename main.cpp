#include <gtk/gtk.h>
#include <locale.h>
#include <pango/pango.h>
#include <glib.h>


static void ComponentHandler ( GtkWidget* gtk_window_ , GtkWidget* gtk_component ) {
	GError* error = NULL;
	
	
	gtk_window_set_child ( GTK_WINDOW ( gtk_window_ ) , GTK_WIDGET ( gtk_component ) );


}





	
static void ButtonShow(GtkWidget* gtk_window_, GtkWidget* gtk_button) {  
   gtk_window_set_child(GTK_WINDOW(gtk_window_), GTK_WIDGET(gtk_button));  
}


static void ButtonClick ( GtkButton* button , gpointer user_data ) {
	gtk_button_set_label ( button , "Clicked" );
}



static void LabelShow (GtkWidget* gtk_window_, const char* string_) {

	GtkWidget* label = gtk_label_new (string_);

	gtk_window_set_child ( GTK_WINDOW ( gtk_window_ ) , label );

}




static void on_activate(GtkApplication* app, gpointer user_data) {
    GtkWidget* window = gtk_application_window_new(app);

	GError* error = NULL;

	const char* local_string = "Jejunu";

	gchar* utf8_string = g_locale_to_utf8 ( local_string , -1 , NULL , NULL , &error );

	if (!utf8_string) {
		g_print ( "변환 실패: %s\n" , error->message );
		g_error_free ( error );
		return;
	}
    gtk_window_set_title(GTK_WINDOW(window), utf8_string );
    gtk_window_set_default_size(GTK_WINDOW(window), 1280, 720);


	
	GtkWidget* label = gtk_label_new( utf8_string );
	gtk_window_set_child ( GTK_WINDOW ( window ) , label );

	LabelShow (window, "helo");

	GtkWidget* button = gtk_button_new_with_label ( "Activate" );
	ButtonShow ( window , button );
	g_signal_connect( button , "clicked" , G_CALLBACK ( ButtonClick ) , NULL );

    GtkCssProvider* provider = gtk_css_provider_new();
    gtk_css_provider_load_from_string(provider,
        "* { font-family: 'Malgun Gothic'; font-size: 14pt; }");

    GdkDisplay* display = gdk_display_get_default();
    gtk_style_context_add_provider_for_display(display,
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER);


    gtk_window_present(GTK_WINDOW(window));
}



// Encoding Setting
void localeChange() {

	setlocale ( LC_ALL , "ko_KR.UTF-8" );
	printf ( "Current Locale: %s\n" , setlocale ( LC_ALL , NULL ) );

}
int main(int argc, char** argv)
{

	localeChange ( );
	GtkApplication* app;
	int status;

	PangoFontDescription* font_desc = pango_font_description_from_string("Malgun Gothic 12");
	pango_font_description_free(font_desc);

	app = gtk_application_new("com.gtk.GtkApp", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);

	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	return status;
}