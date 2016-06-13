// mdtlc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <windows.h>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <stdlib.h>

//#include "../../trimp_private.h"
#include "mdtlc.h"


#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_File_Icon.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_PNM_Image.H>
#include "filename_functions.cxx"
#include "trimp_fltk.h"
#include "fltk_if.h"
#include "atlc.h"
//#include "button_callbacks.h"

/**
 *      
 *      
 *      
 */

using namespace std;


int             log_header( browser_log* pl );
int             log_date( browser_log* pl );
void	        fc_callback(char* filename);
int             stop_tests;
int             msg_lvl;

browser_log*    central_log;
Filename_work*  file;
const char*     input_filename = "";
const char      *read_files_label = "Start Function";
extern          Fl_File_Chooser		*fc;
void main_panel_close( Fl_Widget* widget , void* nothing);

int main( int argc , char** argv )
//int main(HINSTANCE hInstance , HINSTANCE hPrevInstance , PSTR szCmdLine , 
//             int iCMdShow)

{
    char  tString[80];
    msg_lvl = 1;   
    Fl_File_Icon	*icon;	// New file icon   

/** setup the gui */
    fltk_startup();
    fltk_sync_values(1); /// pop-ups have the correct default values
    // except signal thickness
    sig1_cu_thickness->value(3); // check that this is 1oz 
    fltk_sync_values(0);
// filename containers

  file = new Filename_work();
// Make the file chooser...
  Fl::scheme(NULL);
//  Fl_File_Icon::load_system_icons();

//  fc = new Fl_File_Chooser(".", "*", Fl_File_Chooser::MULTI, "Input File Select");
//  fc->filter("text (*.txt)\t" "all (*)\t");
//  fc->callback(fc_callback);
    main_panel->callback(main_panel_close);

/** initiatize the main buffer for the text log window */    
    main_log->has_scrollbar(Fl_Browser::VERTICAL_ALWAYS);
    central_log = new browser_log;
    central_log->initialize( main_log );  
    log_header( central_log );   
    
    main_window->show();  ///< make the main panel visible

    Fl::lock();           ///< to initialize threading
    Fl::run();
    return EXIT_SUCCESS;

}
 
int log_header( browser_log* pl ) {
    char tString[80];
    pl->add_line( "-------------------------------" );
    pl->add_line( "2D Impedance Calculator Program" );
    sprintf( tString , "Version %s" , "to be versioned" );
    pl->add_line( tString );
    log_date( pl ); 
    pl->add_line( "GPL Version 2.0" );
    pl->add_line( "-------------------------------" );
//    log_time( pl );
	return 0;
}

int log_date( browser_log* pl ) {
    char tString[80];
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime ); 
    // using precision to truncate \n off asctime - watch implementations of asctime!!!
    sprintf( tString , "Time: %.24s" , asctime(timeinfo) );
    
    pl->add_line( tString );
	return 0;
}

//
// 'fc_callback()' - Handle choices in the file chooser...
//

void
fc_callback(char* file_name)	// I - Data
{
 FILE* fp;
 int n;
 char in_buffer[84];
 char in_string[16];
 char conversion_str[32];
 float in_number;
 int   in_number_i;
 
 // return if file chooser window still open - user is choosing between files

  input_filename = file_name;
    if ( input_filename)
  {
       fp = fopen(input_filename , "rb");
       if (fp == NULL)
      {
      central_log->add_line("File error.");
      return;
      }
      while ( !feof(fp) ) {
            *in_buffer=NULL;
            fgets(in_buffer, 82 , fp); 
            // scan for first number 
            in_string[0]=NULL; in_number=0;
//            sscanf( in_buffer , "%f %10s" , &in_number , in_string );
//            in_string[15]=NULL;
//            if ( in_number > 0 && in_number < 1.1e7 ) {
//                 in_number_i = in_number;
//                 sprintf( conversion_str , "%i %s" , in_number_i , in_string);
//                 input_target->value(conversion_str);
//                 button_go( (Fl_Widget*)go_button );
//                 }
            }

      }

}

void main_panel_close( Fl_Widget* widget , void* nothing)
     {
                       exit(0);// hiding the main window should cause normal exit by ending Fl::run()
                       }
    
