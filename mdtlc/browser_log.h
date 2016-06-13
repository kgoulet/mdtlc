#ifndef browser_log_h
#define browser_log_h

#include "trimp_fltk.h"
#define TERM_WIDTH 82

class browser_log {
      public:
             int initialize( Fl_Browser* pFlBrowser );
             int add_line( char* pString );
             int add_line_t( char* pString );
             int dump_blk( char* blk_start , int blk_size);
             int dump_blk_t( char* blk_start , int blk_size);
             int clear_log( void );
             int paste_selected( void );
             char* write_log( void );
             browser_log( void );
             ~browser_log();
             
      private:
              Fl_Browser* p_browser;
              int         n_lines;
              int         max_lines;
              char        log_name[256];
              char*        paste_buffer;
              int         paste_count;
              int         paste_limit;
      };

#endif
