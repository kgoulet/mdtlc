
#ifndef fltk_if_h
#define fltk_if_h

#include "trimp_fltk.h"

//extern    Fl_Choice*     structure;

extern    Fl_Value_Input* smt_thickness;
extern    Fl_Value_Input* smt_er;
extern    Fl_Value_Input* smt_loss_tangent;
extern    Fl_Value_Input* smt_open_x_off;
extern    Fl_Value_Input* smt_open_x_w;
extern    Fl_Value_Slider* smt_fill;

extern    Fl_Value_Input* smb_thickness;
extern    Fl_Value_Input* smb_er;
extern    Fl_Value_Input* smb_loss_tangent;
extern    Fl_Value_Input* smb_open_x_off;
extern    Fl_Value_Input* smb_open_x_w;

extern     Fl_Value_Input*     cut_thickness;
extern     Fl_Value_Input*     cut_open_x_off;
extern     Fl_Value_Input*     cut_open_x_w;
extern     Fl_Value_Input*     cut_etchback;
extern     Fl_Value_Input*     cut_filler_er;    

extern     Fl_Value_Input*     cub_thickness;
extern     Fl_Value_Input*     cub_open_x_off;
extern     Fl_Value_Input*     cub_open_x_w;
extern     Fl_Value_Input*     cub_etchback;
extern     Fl_Value_Input*     cub_filler_er;    

extern     Fl_Value_Input*    lam1_thickness; 
extern     Fl_Value_Input*    lam1_resin_er;
extern     Fl_Value_Input*    lam1_glass_er;
extern     Fl_Value_Input*    lam1_resin_content;
extern     Fl_Value_Input*    lam1_loss_tangent;

extern     Fl_Value_Input*    lam2_thickness; 
extern     Fl_Value_Input*    lam2_resin_er;
extern     Fl_Value_Input*    lam2_glass_er;
extern     Fl_Value_Input*    lam2_resin_content;
extern     Fl_Value_Input*    lam2_loss_tangent;

extern    Fl_Value_Input*     sig1_thickness;
extern    Fl_Value_Input*     sig1_trace1_w;
extern    Fl_Value_Input*     sig1_trace_etchback;
extern    Fl_Value_Input*     sig1_filler_er;
extern        Fl_Value_Input*     sig1_loss_tangent;
extern    Fl_Value_Input*     sig1_trace_separation;
extern    Fl_Value_Input*     sig1_trace2_width;

extern        Fl_Check_Button*    sig1_cop1_enable;
extern        Fl_Value_Input*     sig1_cop1_width;
extern        Fl_Value_Input*     sig1_cop1_separation;
extern        Fl_Check_Button*    sig1_cop2_enable;
extern        Fl_Check_Button*    sig1_cop2_symmetry;
extern        Fl_Value_Input*     sig1_cop2_width;
extern        Fl_Value_Input*     sig1_cop2_separation;

extern char       p_test_file_name[];    

extern int align_bitmap_image(int W, int H, unsigned char *unaligned_image, unsigned char *byte_aligned_image);
extern void write_bitmap_out(unsigned char *image_data, FILE *image_data_fp, int image_size, int W, int H);

int       fltk_startup(void);
int       fltk_sync_values( int direction );
int       fltk_switch_ref_diagram();
int       button_check_bmp();
int       button_field_bmp();
int       button_field_even_bmp();
int       button_z0();
int       button_save_log_file( Fl_Widget* pw  );
int       button_write_bmp();
int       button_import_bmp(char* file_name);
int       copy2paste();


#endif
