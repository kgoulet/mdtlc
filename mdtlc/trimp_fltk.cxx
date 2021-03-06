// generated by Fast Light User Interface Designer (fluid) version 1.0105

#include "trimp_fltk.h"
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <FL/Fl_File_Chooser.H>
#include "fltk_if.h"
#include "trimp_private.h"
//#include "button_callbacks.h"
int progress_counter;

Fl_Double_Window *main_panel=(Fl_Double_Window *)0;

static void cb_import_values(Fl_Menu_*, void*) {
  //char *select_file;
//select_file = fl_file_chooser("Import File","bmp (*.bmp)\t",NULL,0);
//fc_callback( select_file );
////      input_target->take_focus();
////      input_target->value("");
//btn_analyze->deactivate();
}

static void cb_Quit(Fl_Menu_*, void*) {
  exit(0);
}

static void cb_Configure(Fl_Menu_*, void*) {
  config_window->show();
}

static void cb_About(Fl_Menu_*, void*) {
  about_window->show();
}

Fl_Menu_Item menu_[] = {
 {"File", 0,  0, 0, 64, 0, 0, 14, 56},
 {"Import", 0,  (Fl_Callback*)cb_import_values, 0, 0, 0, 0, 14, 56},
 {"Quit", 0,  (Fl_Callback*)cb_Quit, 0, 0, 0, 0, 14, 56},
 {0},
 {"Options", 0,  0, 0, 64, 0, 0, 14, 56},
 {"Configure", 0,  (Fl_Callback*)cb_Configure, 0, 0, 0, 0, 14, 56},
 {0},
 {"Help", 0,  0, 0, 64, 0, 0, 14, 56},
 {"About", 0,  (Fl_Callback*)cb_About, 0, 0, 0, 0, 14, 56},
 {0},
 {0}
};

Fl_Tabs *tab_set_1=(Fl_Tabs *)0;

Fl_Box *ref_diagram=(Fl_Box *)0;

Fl_Value_Input *smt_thk_o=(Fl_Value_Input *)0;

static void cb_smt_thk_o(Fl_Value_Input*, void*) {
  fltk_sync_values(0);
}

Fl_Value_Input *top_cu_thk_o=(Fl_Value_Input *)0;

static void cb_top_cu_thk_o(Fl_Value_Input*, void*) {
  fltk_sync_values(0);
}

Fl_Value_Input *lam1_thk_o=(Fl_Value_Input *)0;

static void cb_lam1_thk_o(Fl_Value_Input*, void*) {
  fltk_sync_values(0);
}

Fl_Value_Input *lam1_er=(Fl_Value_Input *)0;

static void cb_lam1_er(Fl_Value_Input*, void*) {
  fltk_sync_values(0);
}

Fl_Value_Input *trace1_width_main_i=(Fl_Value_Input *)0;

static void cb_trace1_width_main_i(Fl_Value_Input*, void*) {
  fltk_sync_values(0);
}

Fl_Value_Input *trace_sep_main_i=(Fl_Value_Input *)0;

static void cb_trace_sep_main_i(Fl_Value_Input*, void*) {
  fltk_sync_values(0);
}

Fl_Value_Input *lam2_er=(Fl_Value_Input *)0;

static void cb_lam2_er(Fl_Value_Input*, void*) {
  fltk_sync_values(0);
}

Fl_Value_Input *lam2_thk_o=(Fl_Value_Input *)0;

static void cb_lam2_thk_o(Fl_Value_Input*, void*) {
  fltk_sync_values(0);
}

Fl_Value_Input *bot_cu_thk_o=(Fl_Value_Input *)0;

static void cb_bot_cu_thk_o(Fl_Value_Input*, void*) {
  fltk_sync_values(0);
}

Fl_Value_Input *smb_thk_o=(Fl_Value_Input *)0;

static void cb_smb_thk_o(Fl_Value_Input*, void*) {
  fltk_sync_values(0);
}

static void cb_Draw(Fl_Button*, void*) {
  button_check_bmp( );
tab_set_1->value(bitmap_drawing);
}

Fl_Check_Button *smt_enable=(Fl_Check_Button *)0;

static void cb_smt_enable(Fl_Check_Button*, void*) {
  // if disabling,  keep old value in pop-up
if (smt_enable->value()== 1) {
smt_thk_o->value(smt_thickness->value());
}


fltk_sync_values(0);
}

Fl_Check_Button *top_plane_enable=(Fl_Check_Button *)0;

static void cb_top_plane_enable(Fl_Check_Button*, void*) {
  if ( top_plane_enable->value() == 1 ) {
top_cu_thk_o->value(cut_thickness->value());
}
fltk_sync_values(0);
}

Fl_Check_Button *lam1_enable=(Fl_Check_Button *)0;

static void cb_lam1_enable(Fl_Check_Button*, void*) {
  if ( lam1_enable->value() == 1 ) {
lam1_thk_o->value(lam1_thickness->value());
}
fltk_sync_values(0);
}

Fl_Check_Button *edge_diff=(Fl_Check_Button *)0;

static void cb_edge_diff(Fl_Check_Button*, void*) {
  fltk_switch_ref_diagram();
}

Fl_Check_Button *coplanar_enable=(Fl_Check_Button *)0;

static void cb_coplanar_enable(Fl_Check_Button* o, void*) {
  fltk_switch_ref_diagram();
if ( o->value() == 1 ) {layer_cop->show();
sig1_cop1_enable->value(1);
sig1_cop2_enable->value(1);
}
else {
sig1_cop1_enable->value(0);
sig1_cop2_enable->value(0);
layer_cop->hide();
};
}

Fl_Choice *sig1_cu_thickness=(Fl_Choice *)0;

static void cb_1(Fl_Menu_*, void*) {
  sig1_thickness->value(0.17);
fltk_sync_values(0);
}

static void cb_11(Fl_Menu_*, void*) {
  sig1_thickness->value(0.34);
fltk_sync_values(0);
}

static void cb_12(Fl_Menu_*, void*) {
  sig1_thickness->value(0.7);
fltk_sync_values(0);
}

static void cb_1oz(Fl_Menu_*, void*) {
  sig1_thickness->value(1.4);
fltk_sync_values(0);
}

static void cb_2oz(Fl_Menu_*, void*) {
  sig1_thickness->value(2.75);
fltk_sync_values(0);
}

Fl_Menu_Item menu_sig1_cu_thickness[] = {
 {"1/8oz", 0,  (Fl_Callback*)cb_1, 0, 0, 0, 0, 14, 56},
 {"1/4oz", 0,  (Fl_Callback*)cb_11, 0, 0, 0, 0, 14, 56},
 {"1/2oz", 0,  (Fl_Callback*)cb_12, 0, 4, 0, 0, 14, 56},
 {"1oz", 0,  (Fl_Callback*)cb_1oz, 0, 0, 0, 0, 14, 56},
 {"2oz", 0,  (Fl_Callback*)cb_2oz, 0, 0, 0, 0, 14, 56},
 {"Custom", 0,  0, 0, 0, 0, 0, 14, 56},
 {0}
};

Fl_Check_Button *lam2_enable=(Fl_Check_Button *)0;

static void cb_lam2_enable(Fl_Check_Button*, void*) {
  if ( lam2_enable->value() == 1 ) {
lam2_thk_o->value(lam2_thickness->value());
}
fltk_sync_values(0);
}

Fl_Check_Button *fillerer_same=(Fl_Check_Button *)0;

static void cb_fillerer_same(Fl_Check_Button*, void*) {
  fltk_sync_values(0);
}

Fl_Check_Button *lam2_same=(Fl_Check_Button *)0;

static void cb_lam2_same(Fl_Check_Button*, void*) {
  fltk_sync_values(0);
}

Fl_Check_Button *bot_plane_enable=(Fl_Check_Button *)0;

static void cb_bot_plane_enable(Fl_Check_Button*, void*) {
  if ( bot_plane_enable->value() == 1 ) {
bot_cu_thk_o->value(cub_thickness->value());
}
fltk_sync_values(0);
}

Fl_Check_Button *smb_enable=(Fl_Check_Button *)0;

static void cb_smb_enable(Fl_Check_Button*, void*) {
  if (smb_enable->value()== 1) {
smb_thk_o->value(smb_thickness->value());
}

fltk_sync_values(0);
}

static void cb_Edit(Fl_Button*, void*) {
  layer_smt->show();
}

static void cb_Edit1(Fl_Button*, void*) {
  layer_top_plane->show();
}

static void cb_Edit2(Fl_Button*, void*) {
  layer_lam1->show();
}

static void cb_Edit3(Fl_Button*, void*) {
  layer_sig1->show();
}

static void cb_Edit4(Fl_Button*, void*) {
  layer_lam2->show();
}

static void cb_Edit5(Fl_Button*, void*) {
  layer_bot_plane->show();
}

static void cb_Edit6(Fl_Button*, void*) {
  layer_smb->show();
}

Fl_Group *bitmap_drawing=(Fl_Group *)0;

static void cb_bitmap_drawing(Fl_Group*, void*) {
  //int ix;
//int iy;
//ix = current_density_plot_s->xposition();
//iy = current_density_plot_s->yposition();
//scroll_bmp->position(ix,iy);
}

Fl_Scroll *scroll_bmp=(Fl_Scroll *)0;

Fl_Box *current_bmp=(Fl_Box *)0;

static void cb_Calculate(Fl_Button*, void*) {
  tab_set_1->value(log_output);
button_z0();
}

static void cb_Import(Fl_Button*, void*) {
  char *select_file;
select_file = fl_file_chooser("Import File","bmp (*.bmp)\t",NULL,0);
button_import_bmp( select_file );
//      input_target->take_focus();
//      input_target->value("");
//btn_analyze->deactivate();
}

static void cb_Export(Fl_Button*, void*) {
  //char *select_file;
//select_file = fl_file_chooser("Import File","bmp (*.bmp)\t",NULL,0);
//fc_callback( select_file );
//      input_target->take_focus();
//      input_target->value("");
//btn_analyze->deactivate();
button_write_bmp();
}

static void cb_Redraw(Fl_Button*, void*) {
  button_check_bmp( );
tab_set_1->value(bitmap_drawing);
}

Fl_Group *log_output=(Fl_Group *)0;

Fl_Browser *main_log=(Fl_Browser *)0;

static void cb_main_log(Fl_Browser* o, void*) {
  //int i,j,l;
//i=o->size();
//j=1;
//while (i<j ) 
//{
//  l=strlen(o->text(j));
//  Fl::copy(o->text(j),l,1);
//  j++;
//}
copy2paste();   // copy selected lines to paste buffer;
}

Fl_Button *btn_analyze=(Fl_Button *)0;

static void cb_btn_analyze(Fl_Button* o, void*) {
  button_save_log_file( o );
}

Fl_Output *compute_status=(Fl_Output *)0;

static void cb_Output(Fl_Group*, void*) {
  //int ix;
//int iy;
//ix = copper_plane_s->xposition();
//iy = copper_plane_s->yposition();
//current_density_plot_s->position(ix,iy);
}

static void cb_Plot(Fl_Button*, void*) {
  button_field_bmp();
}

static void cb_Plot1(Fl_Button*, void*) {
  button_field_even_bmp();
}

Fl_Scroll *field_plot_s=(Fl_Scroll *)0;

Fl_Box *field_plot=(Fl_Box *)0;

Fl_Double_Window* make_window() {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = main_panel = new Fl_Double_Window(885, 648, "Transmission Line Analysis");
    w = o;
    o->when(FL_WHEN_NEVER);
    { Fl_Menu_Bar* o = new Fl_Menu_Bar(0, 0, 885, 25);
      o->menu(menu_);
    }
    { Fl_Tabs* o = tab_set_1 = new Fl_Tabs(20, 35, 1940, 1465);
      o->align(FL_ALIGN_CENTER);
      { Fl_Group* o = new Fl_Group(35, 65, 845, 555, "Stackup Definition");
        { Fl_Box* o = ref_diagram = new Fl_Box(50, 90, 515, 465);
          o->box(FL_THIN_DOWN_BOX);
          o->color((Fl_Color)55);
          o->align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
        }
        { Fl_Value_Input* o = smt_thk_o = new Fl_Value_Input(765, 93, 45, 25, "Thickness");
          o->maximum(10);
          o->step(0.1);
          o->callback((Fl_Callback*)cb_smt_thk_o);
          o->align(FL_ALIGN_TOP);
          o->when(3);
        }
        { Fl_Value_Input* o = top_cu_thk_o = new Fl_Value_Input(765, 123, 45, 25);
          o->maximum(10);
          o->step(0.1);
          o->callback((Fl_Callback*)cb_top_cu_thk_o);
          o->align(FL_ALIGN_TOP);
        }
        { Fl_Value_Input* o = lam1_thk_o = new Fl_Value_Input(765, 153, 45, 25);
          o->maximum(100);
          o->step(0.1);
          o->callback((Fl_Callback*)cb_lam1_thk_o);
          o->align(FL_ALIGN_TOP);
        }
        { Fl_Value_Input* o = lam1_er = new Fl_Value_Input(765, 183, 45, 25, "Laminate 1 Er");
          o->minimum(1);
          o->maximum(8);
          o->step(0.05);
          o->value(4);
          o->callback((Fl_Callback*)cb_lam1_er);
        }
        { Fl_Value_Input* o = trace1_width_main_i = new Fl_Value_Input(765, 290, 45, 25, "Trace Width (at bottom)");
          o->minimum(1);
          o->maximum(100);
          o->step(0.1);
          o->value(4);
          o->callback((Fl_Callback*)cb_trace1_width_main_i);
        }
        { Fl_Value_Input* o = trace_sep_main_i = new Fl_Value_Input(765, 320, 45, 25, "Trace Separation (at bottom)");
          o->minimum(1);
          o->maximum(100);
          o->step(0.1);
          o->value(4);
          o->callback((Fl_Callback*)cb_trace_sep_main_i);
        }
        { Fl_Value_Input* o = lam2_er = new Fl_Value_Input(765, 405, 45, 25, "Laminate 2 Er");
          o->minimum(1);
          o->maximum(8);
          o->step(0.05);
          o->value(4);
          o->callback((Fl_Callback*)cb_lam2_er);
        }
        { Fl_Value_Input* o = lam2_thk_o = new Fl_Value_Input(765, 435, 45, 25, "Thickness");
          o->maximum(100);
          o->step(0.1);
          o->callback((Fl_Callback*)cb_lam2_thk_o);
          o->align(FL_ALIGN_CENTER);
        }
        { Fl_Value_Input* o = bot_cu_thk_o = new Fl_Value_Input(765, 465, 45, 25);
          o->maximum(10);
          o->step(0.1);
          o->callback((Fl_Callback*)cb_bot_cu_thk_o);
          o->align(FL_ALIGN_TOP);
        }
        { Fl_Value_Input* o = smb_thk_o = new Fl_Value_Input(765, 495, 45, 25);
          o->maximum(10);
          o->step(0.1);
          o->callback((Fl_Callback*)cb_smb_thk_o);
          o->align(FL_ALIGN_TOP);
        }
        { Fl_Button* o = new Fl_Button(765, 535, 95, 25, "Draw Bitmap");
          o->color(FL_DARK1);
          o->callback((Fl_Callback*)cb_Draw);
        }
        { Fl_Check_Button* o = smt_enable = new Fl_Check_Button(730, 93, 20, 25, "Top Solder Mask");
          o->down_box(FL_DOWN_BOX);
          o->callback((Fl_Callback*)cb_smt_enable);
          o->align(FL_ALIGN_LEFT);
        }
        { Fl_Check_Button* o = top_plane_enable = new Fl_Check_Button(730, 123, 25, 25, "Top Plane");
          o->down_box(FL_DOWN_BOX);
          o->value(1);
          o->callback((Fl_Callback*)cb_top_plane_enable);
          o->align(FL_ALIGN_LEFT);
        }
        { Fl_Check_Button* o = lam1_enable = new Fl_Check_Button(730, 153, 25, 25, "Laminate 1");
          o->down_box(FL_DOWN_BOX);
          o->value(1);
          o->callback((Fl_Callback*)cb_lam1_enable);
          o->align(FL_ALIGN_LEFT);
        }
        { Fl_Check_Button* o = edge_diff = new Fl_Check_Button(705, 255, 25, 25, "Edge Differential");
          o->down_box(FL_DOWN_BOX);
          o->value(1);
          o->callback((Fl_Callback*)cb_edge_diff);
          o->align(FL_ALIGN_LEFT);
        }
        { Fl_Check_Button* o = coplanar_enable = new Fl_Check_Button(705, 225, 25, 25, "Coplanar Enable");
          o->down_box(FL_DOWN_BOX);
          o->callback((Fl_Callback*)cb_coplanar_enable);
          o->align(FL_ALIGN_LEFT);
        }
        { Fl_Choice* o = sig1_cu_thickness = new Fl_Choice(790, 255, 75, 25, "Cu Thick");
          o->down_box(FL_BORDER_BOX);
          o->menu(menu_sig1_cu_thickness);
        }
        { Fl_Check_Button* o = lam2_enable = new Fl_Check_Button(730, 435, 25, 25, "Laminate 2");
          o->down_box(FL_DOWN_BOX);
          o->value(1);
          o->callback((Fl_Callback*)cb_lam2_enable);
          o->align(FL_ALIGN_LEFT);
        }
        { Fl_Check_Button* o = fillerer_same = new Fl_Check_Button(765, 350, 25, 25, "Trace Filler Er = Laminate 1");
          o->down_box(FL_DOWN_BOX);
          o->value(1);
          o->callback((Fl_Callback*)cb_fillerer_same);
          o->align(FL_ALIGN_LEFT);
        }
        { Fl_Check_Button* o = lam2_same = new Fl_Check_Button(765, 375, 25, 25, "Laminate 2 Er = Laminate 1");
          o->down_box(FL_DOWN_BOX);
          o->value(1);
          o->callback((Fl_Callback*)cb_lam2_same);
          o->align(FL_ALIGN_LEFT);
        }
        { Fl_Check_Button* o = bot_plane_enable = new Fl_Check_Button(730, 465, 25, 25, "Bottom Plane");
          o->down_box(FL_DOWN_BOX);
          o->value(1);
          o->callback((Fl_Callback*)cb_bot_plane_enable);
          o->align(FL_ALIGN_LEFT);
        }
        { Fl_Check_Button* o = smb_enable = new Fl_Check_Button(730, 495, 20, 25, "Bot Solder Mask");
          o->down_box(FL_DOWN_BOX);
          o->callback((Fl_Callback*)cb_smb_enable);
          o->align(FL_ALIGN_LEFT);
        }
        { Fl_Button* o = new Fl_Button(830, 93, 35, 25, "Edit");
          o->callback((Fl_Callback*)cb_Edit);
        }
        { Fl_Button* o = new Fl_Button(830, 123, 35, 25, "Edit");
          o->callback((Fl_Callback*)cb_Edit1);
        }
        { Fl_Button* o = new Fl_Button(830, 153, 35, 25, "Edit");
          o->callback((Fl_Callback*)cb_Edit2);
        }
        { Fl_Button* o = new Fl_Button(830, 305, 35, 25, "Edit");
          o->callback((Fl_Callback*)cb_Edit3);
        }
        { Fl_Button* o = new Fl_Button(830, 435, 35, 25, "Edit");
          o->callback((Fl_Callback*)cb_Edit4);
        }
        { Fl_Button* o = new Fl_Button(830, 465, 35, 25, "Edit");
          o->callback((Fl_Callback*)cb_Edit5);
        }
        { Fl_Button* o = new Fl_Button(830, 495, 35, 25, "Edit");
          o->callback((Fl_Callback*)cb_Edit6);
        }
        o->end();
      }
      { Fl_Group* o = bitmap_drawing = new Fl_Group(25, 60, 1172, 575, "Input Bitmap");
        o->callback((Fl_Callback*)cb_bitmap_drawing);
        o->hide();
        { Fl_Scroll* o = scroll_bmp = new Fl_Scroll(34, 78, 625, 484, "Input Bitmap Image");
          o->type(7);
          o->box(FL_THIN_DOWN_BOX);
          current_bmp = new Fl_Box(34, 78, 1200, 800);
          o->end();
        }
        { Fl_Button* o = new Fl_Button(690, 540, 116, 25, "Calculate Zo");
          o->callback((Fl_Callback*)cb_Calculate);
        }
        { Fl_Button* o = new Fl_Button(690, 190, 115, 25, "Import BMP");
          o->callback((Fl_Callback*)cb_Import);
        }
        { Fl_Button* o = new Fl_Button(690, 120, 115, 25, "Export BMP");
          o->callback((Fl_Callback*)cb_Export);
        }
        { Fl_Button* o = new Fl_Button(695, 500, 115, 25, "Redraw Bitmap");
          o->color(FL_DARK1);
          o->callback((Fl_Callback*)cb_Redraw);
        }
        o->end();
      }
      { Fl_Group* o = log_output = new Fl_Group(25, 60, 855, 570, "Log");
        o->hide();
        { Fl_Browser* o = main_log = new Fl_Browser(40, 120, 550, 460, "Computation Log");
          o->type(3);
          o->callback((Fl_Callback*)cb_main_log);
          o->align(FL_ALIGN_TOP_LEFT);
        }
        { Fl_Button* o = btn_analyze = new Fl_Button(670, 140, 115, 25, "Save Report");
          o->color(FL_BACKGROUND2_COLOR);
          o->labelfont(1);
          o->labelcolor((Fl_Color)59);
          o->callback((Fl_Callback*)cb_btn_analyze);
        }
        { Fl_Output* o = compute_status = new Fl_Output(255, 85, 115, 25, "Status");
          o->align(FL_ALIGN_RIGHT);
        }
        o->end();
      }
      { Fl_Group* o = new Fl_Group(25, 60, 1935, 1440, "Output Image");
        o->callback((Fl_Callback*)cb_Output);
        o->hide();
        { Fl_Button* o = new Fl_Button(690, 95, 85, 25, "Plot E Odd");
          o->color((Fl_Color)10);
          o->callback((Fl_Callback*)cb_Plot);
        }
        { Fl_Button* o = new Fl_Button(690, 150, 85, 25, "Plot E Even");
          o->color((Fl_Color)10);
          o->callback((Fl_Callback*)cb_Plot1);
        }
        { Fl_Scroll* o = field_plot_s = new Fl_Scroll(40, 90, 627, 487);
          o->type(7);
          o->box(FL_THIN_DOWN_BOX);
          { Fl_Box* o = field_plot = new Fl_Box(360, 300, 1600, 1200);
            o->align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
          }
          o->end();
        }
        o->end();
      }
      o->end();
    }
    o->end();
  }
  return w;
}

Fl_Button *about_close=(Fl_Button *)0;

static void cb_about_close(Fl_Button* o, void*) {
  ((Fl_Window*)(o->parent()))->hide();
}

Fl_Double_Window* make_about_window() {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = new Fl_Double_Window(254, 300, "Transmission Line");
    w = o;
    new Fl_Box(25, 10, 190, 25, "Transmission Line Analysis");
    new Fl_Box(25, 35, 190, 25, "Copyright 2007");
    new Fl_Box(25, 60, 190, 25, "Kirby Goulet");
    { Fl_Box* o = new Fl_Box(25, 85, 190, 25, "VER_STRING");
      o->label(VER_STRING);
    }
    { Fl_Button* o = about_close = new Fl_Button(25, 235, 190, 25, "CLOSE");
      o->color((Fl_Color)46);
      o->labelcolor(FL_GRAY0);
      o->callback((Fl_Callback*)cb_about_close);
    }
    { Fl_Box* o = new Fl_Box(30, 265, 185, 25, "kgoulet@@ieee.org");
      o->labelsize(12);
    }
    new Fl_Box(25, 150, 190, 25, "Uses:");
    new Fl_Box(25, 170, 190, 25, "fltk - fltk.org");
    { Fl_Box* o = new Fl_Box(30, 120, 180, 25, "All Rights Reserved");
      o->color((Fl_Color)55);
    }
    new Fl_Box(25, 190, 190, 25, "atlc - atlc.sf.net");
    o->end();
  }
  return w;
}

static void cb_Close(Fl_Button* o, void*) {
  ((Fl_Window*)(o->parent()))->hide();
}

Fl_Double_Window* make_config_window() {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = new Fl_Double_Window(542, 410, "Configuration Settings");
    w = o;
    { Fl_Tabs* o = new Fl_Tabs(25, 25, 495, 315);
      o->align(FL_ALIGN_BOTTOM);
      { Fl_Group* o = new Fl_Group(40, 55, 460, 270, "Panel 1");
        { Fl_Box* o = new Fl_Box(135, 120, 20, 25, "Future Expansion");
          o->labelfont(1);
        }
        o->end();
      }
      o->end();
    }
    { Fl_Button* o = new Fl_Button(390, 360, 125, 25, "Close Panel");
      o->callback((Fl_Callback*)cb_Close);
    }
    o->set_modal();
    o->end();
  }
  return w;
}
Fl_Double_Window* main_window;
Fl_Double_Window* about_window;
Fl_Double_Window* config_window;
Fl_File_Chooser* fc;

static void cb_CLOSE(Fl_Button* o, void*) {
  fltk_sync_values(1);
((Fl_Window*)(o->parent()))->hide();
}

Fl_Group *sm_group=(Fl_Group *)0;

Fl_Value_Input *sm_thickness=(Fl_Value_Input *)0;

static void cb_sm_thickness(Fl_Value_Input*, void*) {
  fltk_sync_values(1);
}

Fl_Value_Input *sm_er=(Fl_Value_Input *)0;

static void cb_sm_er(Fl_Value_Input*, void*) {
  fltk_sync_values(1);
}

Fl_Value_Input *sm_loss_tangent=(Fl_Value_Input *)0;

static void cb_sm_loss_tangent(Fl_Value_Input*, void*) {
  fltk_sync_values(1);
}

Fl_Value_Input *sm_open_x_off=(Fl_Value_Input *)0;

static void cb_sm_open_x_off(Fl_Value_Input*, void*) {
  fltk_sync_values(1);
}

Fl_Value_Input *sm_open_x_w=(Fl_Value_Input *)0;

static void cb_sm_open_x_w(Fl_Value_Input*, void*) {
  fltk_sync_values(1);
}

Fl_Value_Slider *sm_fill_type=(Fl_Value_Slider *)0;

Fl_Double_Window* make_layer_sm_window() {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = new Fl_Double_Window(271, 293, "Solder Mask");
    w = o;
    { Fl_Button* o = new Fl_Button(180, 255, 70, 25, "CLOSE");
      o->callback((Fl_Callback*)cb_CLOSE);
    }
    { Fl_Group* o = sm_group = new Fl_Group(20, 20, 230, 225, "Solder Mask");
      o->box(FL_THIN_UP_BOX);
      o->align(FL_ALIGN_TOP_LEFT);
      { Fl_Value_Input* o = sm_thickness = new Fl_Value_Input(55, 44, 60, 25, "Thickness");
        o->maximum(4);
        o->step(0.1);
        o->value(1);
        o->callback((Fl_Callback*)cb_sm_thickness);
        o->align(FL_ALIGN_TOP_LEFT);
      }
      { Fl_Value_Input* o = sm_er = new Fl_Value_Input(170, 44, 55, 25, "Er");
        o->minimum(1);
        o->maximum(8);
        o->step(0.01);
        o->value(3.5);
        o->callback((Fl_Callback*)cb_sm_er);
        o->align(FL_ALIGN_TOP);
      }
      { Fl_Value_Input* o = sm_loss_tangent = new Fl_Value_Input(170, 75, 55, 25, "Loss tangent");
        o->maximum(0.2);
        o->step(0.0001);
        o->value(0.002);
        o->callback((Fl_Callback*)cb_sm_loss_tangent);
      }
      { Fl_Value_Input* o = sm_open_x_off = new Fl_Value_Input(170, 105, 55, 25, "Opening X Offset");
        o->minimum(-100);
        o->maximum(100);
        o->step(0.1);
        o->callback((Fl_Callback*)cb_sm_open_x_off);
      }
      { Fl_Value_Input* o = sm_open_x_w = new Fl_Value_Input(170, 135, 55, 25, "Opening Width");
        o->maximum(100);
        o->step(0.1);
        o->callback((Fl_Callback*)cb_sm_open_x_w);
      }
      { Fl_Value_Slider* o = sm_fill_type = new Fl_Value_Slider(40, 185, 185, 30, "Percent coating over trace");
        o->type(1);
        o->maximum(100);
        o->step(1);
        o->value(75);
        o->align(FL_ALIGN_TOP_LEFT);
      }
      { Fl_Box* o = new Fl_Box(55, 215, 75, 30, "Not Over");
        o->align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
      }
      { Fl_Box* o = new Fl_Box(185, 215, 40, 30, "Over");
        o->align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
      }
      o->end();
    }
    o->set_non_modal();
    o->end();
  }
  return w;
}

Fl_Double_Window *cu_plane=(Fl_Double_Window *)0;

static void cb_CLOSE1(Fl_Button* o, void*) {
  fltk_sync_values(1);
((Fl_Window*)(o->parent()))->hide();
}

Fl_Group *cu_group=(Fl_Group *)0;

Fl_Value_Input *cu_thickness=(Fl_Value_Input *)0;

static void cb_cu_thickness(Fl_Value_Input*, void*) {
  fltk_sync_values(1);
}

Fl_Value_Input *cu_open_x_off=(Fl_Value_Input *)0;

static void cb_cu_open_x_off(Fl_Value_Input*, void*) {
  fltk_sync_values(1);
}

Fl_Value_Input *cu_open_x_w=(Fl_Value_Input *)0;

static void cb_cu_open_x_w(Fl_Value_Input*, void*) {
  fltk_sync_values(1);
}

Fl_Value_Input *cu_loss_tangent=(Fl_Value_Input *)0;

static void cb_cu_loss_tangent(Fl_Value_Input*, void*) {
  fltk_sync_values(1);
}

Fl_Value_Input *cu_filler_er=(Fl_Value_Input *)0;

static void cb_cu_filler_er(Fl_Value_Input*, void*) {
  fltk_sync_values(1);
}

Fl_Double_Window* make_layer_cu_plane_window() {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = cu_plane = new Fl_Double_Window(313, 252, "Copper Plane");
    w = o;
    { Fl_Button* o = new Fl_Button(225, 210, 70, 25, "CLOSE");
      o->callback((Fl_Callback*)cb_CLOSE1);
    }
    { Fl_Group* o = cu_group = new Fl_Group(25, 30, 270, 165, "Copper Plane");
      o->box(FL_THIN_UP_BOX);
      o->align(FL_ALIGN_TOP_LEFT);
      { Fl_Value_Input* o = cu_thickness = new Fl_Value_Input(220, 40, 60, 25, "Thickness");
        o->maximum(4);
        o->step(0.1);
        o->value(1.3);
        o->callback((Fl_Callback*)cb_cu_thickness);
      }
      { Fl_Value_Input* o = cu_open_x_off = new Fl_Value_Input(220, 70, 60, 25, "Opening X Offset");
        o->minimum(-100);
        o->maximum(100);
        o->step(0.1);
        o->callback((Fl_Callback*)cb_cu_open_x_off);
      }
      { Fl_Value_Input* o = cu_open_x_w = new Fl_Value_Input(220, 100, 60, 25, "Opening Width (at bottom)");
        o->maximum(100);
        o->step(0.1);
        o->callback((Fl_Callback*)cb_cu_open_x_w);
      }
      { Fl_Value_Input* o = cu_loss_tangent = new Fl_Value_Input(220, 160, 60, 25, "Er Loss Tangent");
        o->maximum(0.2);
        o->step(0.0001);
        o->value(0.0002);
        o->callback((Fl_Callback*)cb_cu_loss_tangent);
      }
      { Fl_Value_Input* o = cu_filler_er = new Fl_Value_Input(220, 130, 60, 25, "Er Filler");
        o->minimum(1);
        o->maximum(10);
        o->step(0.01);
        o->value(3.2);
        o->callback((Fl_Callback*)cb_cu_filler_er);
      }
      o->end();
    }
    o->set_non_modal();
    o->end();
  }
  return w;
}

Fl_Double_Window *laminate=(Fl_Double_Window *)0;

static void cb_CLOSE2(Fl_Button* o, void*) {
  fltk_sync_values(1);
((Fl_Window*)(o->parent()))->hide();
}

Fl_Group *lam_group=(Fl_Group *)0;

Fl_Value_Input *lam_thickness=(Fl_Value_Input *)0;

static void cb_lam_thickness(Fl_Value_Input*, void*) {
  fltk_sync_values(1);
}

Fl_Value_Input *lam_resin_er=(Fl_Value_Input *)0;

static void cb_lam_resin_er(Fl_Value_Input*, void*) {
  fltk_sync_values(1);
}

Fl_Value_Input *lam_glass_er=(Fl_Value_Input *)0;

static void cb_lam_glass_er(Fl_Value_Input*, void*) {
  fltk_sync_values(1);
}

Fl_Value_Input *lam_resin_content=(Fl_Value_Input *)0;

static void cb_lam_resin_content(Fl_Value_Input*, void*) {
  fltk_sync_values(1);
}

Fl_Value_Input *lam_loss_tangent=(Fl_Value_Input *)0;

static void cb_lam_loss_tangent(Fl_Value_Input*, void*) {
  fltk_sync_values(1);
}

Fl_Double_Window* make_layer_laminate_window() {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = laminate = new Fl_Double_Window(247, 300, "Laminate");
    w = o;
    { Fl_Button* o = new Fl_Button(160, 255, 70, 25, "CLOSE");
      o->callback((Fl_Callback*)cb_CLOSE2);
    }
    { Fl_Group* o = lam_group = new Fl_Group(15, 20, 215, 215, "Laminate Layer");
      o->box(FL_THIN_UP_BOX);
      o->align(FL_ALIGN_TOP_LEFT);
      { Fl_Value_Input* o = lam_thickness = new Fl_Value_Input(155, 30, 60, 25, "Thickness");
        o->maximum(65);
        o->step(0.1);
        o->value(5);
        o->callback((Fl_Callback*)cb_lam_thickness);
      }
      { Fl_Value_Input* o = lam_resin_er = new Fl_Value_Input(155, 65, 60, 25, "Er Resin");
        o->minimum(1);
        o->maximum(5);
        o->step(0.05);
        o->value(3.2);
        o->callback((Fl_Callback*)cb_lam_resin_er);
      }
      { Fl_Value_Input* o = lam_glass_er = new Fl_Value_Input(155, 95, 60, 25, "Er Glass");
        o->minimum(1);
        o->maximum(7);
        o->step(0.05);
        o->value(6);
        o->callback((Fl_Callback*)cb_lam_glass_er);
      }
      { Fl_Value_Input* o = lam_resin_content = new Fl_Value_Input(155, 125, 60, 25, "Resin Content (%)");
        o->maximum(100);
        o->step(0.1);
        o->value(64.3);
        o->callback((Fl_Callback*)cb_lam_resin_content);
      }
      { Fl_Value_Input* o = lam_loss_tangent = new Fl_Value_Input(155, 160, 60, 25, "Loss Tangent");
        o->step(0.0001);
        o->value(0.0012);
        o->callback((Fl_Callback*)cb_lam_loss_tangent);
      }
      o->end();
    }
    o->set_non_modal();
    o->end();
  }
  return w;
}

Fl_Double_Window *signal=(Fl_Double_Window *)0;

static void cb_CLOSE3(Fl_Button* o, void*) {
  fltk_sync_values(1);
((Fl_Window*)(o->parent()))->hide();
}

Fl_Group *sig_group=(Fl_Group *)0;

Fl_Value_Input *sig_thickness=(Fl_Value_Input *)0;

static void cb_sig_thickness(Fl_Value_Input* o, void*) {
  o->set_changed();
fltk_sync_values(1);
}

Fl_Value_Input *sig_trace_etchback=(Fl_Value_Input *)0;

static void cb_sig_trace_etchback(Fl_Value_Input*, void*) {
  fltk_sync_values(1);
}

Fl_Value_Input *sig_filler_er=(Fl_Value_Input *)0;

static void cb_sig_filler_er(Fl_Value_Input*, void*) {
  fltk_sync_values(1);
}

Fl_Value_Input *sig_loss_tangent=(Fl_Value_Input *)0;

static void cb_sig_loss_tangent(Fl_Value_Input*, void*) {
  fltk_sync_values(1);
}

Fl_Value_Input *sig_trace1_w=(Fl_Value_Input *)0;

static void cb_sig_trace1_w(Fl_Value_Input*, void*) {
  fltk_sync_values(1);
}

Fl_Value_Input *sig_trace_separation=(Fl_Value_Input *)0;

static void cb_sig_trace_separation(Fl_Value_Input*, void*) {
  fltk_sync_values(1);
}

Fl_Value_Input *sig_trace2_width=(Fl_Value_Input *)0;

static void cb_sig_trace2_width(Fl_Value_Input*, void*) {
  fltk_sync_values(1);
}

Fl_Double_Window* make_layer_signal_window() {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = signal = new Fl_Double_Window(277, 323, "Signal Layer");
    w = o;
    { Fl_Button* o = new Fl_Button(191, 285, 70, 25, "CLOSE");
      o->callback((Fl_Callback*)cb_CLOSE3);
    }
    { Fl_Group* o = sig_group = new Fl_Group(16, 20, 245, 250, "Signal Layer");
      o->box(FL_THIN_UP_BOX);
      o->align(FL_ALIGN_TOP_LEFT);
      { Fl_Value_Input* o = sig_thickness = new Fl_Value_Input(181, 30, 60, 25, "Thickness");
        o->maximum(5);
        o->step(0.05);
        o->value(1.35);
        o->callback((Fl_Callback*)cb_sig_thickness);
      }
      { Fl_Value_Input* o = sig_trace_etchback = new Fl_Value_Input(181, 60, 60, 25, "Trace Etchback");
        o->minimum(-1);
        o->step(0.01);
        o->callback((Fl_Callback*)cb_sig_trace_etchback);
      }
      { Fl_Value_Input* o = sig_filler_er = new Fl_Value_Input(181, 96, 60, 25, "Er Filler");
        o->minimum(1);
        o->maximum(10);
        o->step(0.05);
        o->value(4.2);
        o->callback((Fl_Callback*)cb_sig_filler_er);
      }
      { Fl_Value_Input* o = sig_loss_tangent = new Fl_Value_Input(180, 126, 60, 25, "Loss Tangent Filler");
        o->step(0.0001);
        o->value(0.0012);
        o->callback((Fl_Callback*)cb_sig_loss_tangent);
      }
      { Fl_Value_Input* o = sig_trace1_w = new Fl_Value_Input(181, 164, 60, 25, "Trace 1 Width (bottom)");
        o->minimum(1);
        o->maximum(100);
        o->step(0.1);
        o->value(4);
        o->callback((Fl_Callback*)cb_sig_trace1_w);
      }
      { Fl_Value_Input* o = sig_trace_separation = new Fl_Value_Input(181, 194, 60, 25, "Trace Separation");
        o->minimum(0.1);
        o->maximum(100);
        o->step(0.1);
        o->value(6);
        o->callback((Fl_Callback*)cb_sig_trace_separation);
      }
      { Fl_Value_Input* o = sig_trace2_width = new Fl_Value_Input(181, 224, 60, 25, "Trace 2 Width (bottom)");
        o->minimum(1);
        o->maximum(100);
        o->step(0.1);
        o->value(4);
        o->callback((Fl_Callback*)cb_sig_trace2_width);
      }
      o->end();
    }
    o->set_non_modal();
    o->end();
  }
  return w;
}

Fl_Check_Button *cop1_enable=(Fl_Check_Button *)0;

Fl_Value_Input *cop1_width=(Fl_Value_Input *)0;

static void cb_cop1_width(Fl_Value_Input*, void*) {
  fltk_sync_values(1);
}

Fl_Value_Input *cop1_separation=(Fl_Value_Input *)0;

static void cb_cop1_separation(Fl_Value_Input*, void*) {
  fltk_sync_values(1);
}

Fl_Check_Button *cop2_enable=(Fl_Check_Button *)0;

Fl_Check_Button *cop2_symmetry=(Fl_Check_Button *)0;

static void cb_cop2_symmetry(Fl_Check_Button*, void*) {
  fltk_sync_values(1);
}

Fl_Value_Input *cop2_width=(Fl_Value_Input *)0;

static void cb_cop2_width(Fl_Value_Input*, void*) {
  fltk_sync_values(1);
}

Fl_Value_Input *cop2_separation=(Fl_Value_Input *)0;

static void cb_cop2_separation(Fl_Value_Input*, void*) {
  fltk_sync_values(1);
}

Fl_Double_Window* make_coplanar_input_window() {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = new Fl_Double_Window(202, 447, "Coplanar Input");
    w = o;
    { Fl_Box* o = new Fl_Box(17, 23, 170, 110, "Coplanar Strip 1");
      o->box(FL_THIN_DOWN_FRAME);
      o->labelfont(1);
      o->align(FL_ALIGN_TOP_LEFT);
    }
    { Fl_Check_Button* o = cop1_enable = new Fl_Check_Button(162, 28, 25, 25, "Coplanar 1 Enable");
      o->down_box(FL_DOWN_BOX);
      o->align(FL_ALIGN_LEFT);
    }
    { Fl_Value_Input* o = cop1_width = new Fl_Value_Input(132, 63, 45, 25, "CPWidth 1");
      o->maximum(999);
      o->step(0.1);
      o->value(999);
      o->callback((Fl_Callback*)cb_cop1_width);
    }
    { Fl_Value_Input* o = cop1_separation = new Fl_Value_Input(132, 98, 45, 25, "CP Separation 1");
      o->maximum(100);
      o->step(0.1);
      o->value(10);
      o->callback((Fl_Callback*)cb_cop1_separation);
    }
    { Fl_Box* o = new Fl_Box(16, 163, 170, 137, "Coplanar Strip 2");
      o->box(FL_THIN_DOWN_FRAME);
      o->labelfont(1);
      o->align(FL_ALIGN_TOP_LEFT);
    }
    { Fl_Check_Button* o = cop2_enable = new Fl_Check_Button(161, 167, 25, 25, "Coplanar 2 Enable");
      o->down_box(FL_DOWN_BOX);
      o->align(FL_ALIGN_LEFT);
    }
    { Fl_Check_Button* o = cop2_symmetry = new Fl_Check_Button(160, 190, 25, 25, "Symmetrical Coplanar");
      o->down_box(FL_DOWN_BOX);
      o->value(1);
      o->callback((Fl_Callback*)cb_cop2_symmetry);
      o->align(FL_ALIGN_LEFT);
    }
    { Fl_Value_Input* o = cop2_width = new Fl_Value_Input(130, 225, 45, 25, "CPWidth 2");
      o->maximum(999);
      o->step(0.1);
      o->value(999);
      o->callback((Fl_Callback*)cb_cop2_width);
    }
    { Fl_Value_Input* o = cop2_separation = new Fl_Value_Input(130, 260, 45, 25, "CP Separation 2");
      o->maximum(100);
      o->step(0.1);
      o->value(10);
      o->callback((Fl_Callback*)cb_cop2_separation);
    }
    { Fl_Box* o = new Fl_Box(15, 341, 170, 84, "Coplanar Strip 3 (Center)");
      o->box(FL_THIN_DOWN_FRAME);
      o->labelfont(1);
      o->align(FL_ALIGN_TOP_LEFT);
    }
    { Fl_Check_Button* o = new Fl_Check_Button(159, 349, 25, 25, "Coplanar 3 Enable (center)");
      o->down_box(FL_DOWN_BOX);
      o->align(132);
    }
    { Fl_Value_Input* o = new Fl_Value_Input(124, 389, 45, 25, "CPWidth 3");
      o->maximum(50);
      o->step(0.1);
    }
    o->end();
  }
  return w;
}
Fl_Double_Window* layer_smt;
Fl_Double_Window* layer_smb;
Fl_Double_Window* layer_top_plane;
Fl_Double_Window* layer_bot_plane;
Fl_Double_Window* layer_lam1;
Fl_Double_Window* layer_lam2;
Fl_Double_Window* layer_sig1;
Fl_Double_Window* layer_cop;
