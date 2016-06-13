
/* mdtlc - multiple dielectric transmission line calculator


Copyright (C) 2007 Kirby Goulet

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either package_version 2
of the License, or (at your option) any later package_version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,
USA.



*/
#include <time.h>
//#include "definitions.h"
#include "mdtlc.h"
#include "fltk_if.h"
#include "diff_pair_broad.h"
#include "single_end_trace.h"
#include "coplanar_diff.h"
#include "coplanar_se.h"
#include "input_bmp.h"
#include "output_bmp.h"
#include "atlc.h"

//    Fl_Choice*     structure;
 
    Fl_Value_Input* smt_thickness;
    Fl_Value_Input* smt_er;
    Fl_Value_Input* smt_loss_tangent;
    Fl_Value_Input* smt_open_x_w;
    Fl_Value_Input* smt_open_x_off;
    Fl_Value_Slider* smt_fill;
    
    Fl_Value_Input* smb_thickness;
    Fl_Value_Input* smb_er;
    Fl_Value_Input* smb_loss_tangent;
    Fl_Value_Input* smb_open_x_w;
    Fl_Value_Input* smb_open_x_off;
    
    Fl_Value_Input*     cut_thickness;
    Fl_Value_Input*     cut_open_x_off;
    Fl_Value_Input*     cut_open_x_w;
    Fl_Value_Input*     cut_etchback;
    Fl_Value_Input*     cut_filler_er;    

    Fl_Value_Input*     cub_thickness;
    Fl_Value_Input*     cub_open_x_off;
    Fl_Value_Input*     cub_open_x_w;
    Fl_Value_Input*     cub_etchback;
    Fl_Value_Input*     cub_filler_er;    

    Fl_Value_Input*    lam1_thickness; 
    Fl_Value_Input*    lam1_resin_er;
    Fl_Value_Input*    lam1_glass_er;
    Fl_Value_Input*    lam1_resin_content;
    Fl_Value_Input*    lam1_loss_tangent;

    Fl_Value_Input*    lam2_thickness; 
    Fl_Value_Input*    lam2_resin_er;
    Fl_Value_Input*    lam2_glass_er;
    Fl_Value_Input*    lam2_resin_content;
    Fl_Value_Input*    lam2_loss_tangent;

    Fl_Value_Input*     sig1_thickness;
    Fl_Value_Input*     sig1_trace1_w;
    Fl_Value_Input*     sig1_trace_etchback;
    Fl_Value_Input*     sig1_filler_er;
    Fl_Value_Input*     sig1_loss_tangent;
    Fl_Value_Input*     sig1_trace_separation;
    Fl_Value_Input*     sig1_trace2_width;
    
    Fl_Check_Button*    sig1_cop1_enable;
    Fl_Value_Input*     sig1_cop1_width;
    Fl_Value_Input*     sig1_cop1_separation;
    Fl_Check_Button*    sig1_cop2_enable;
    Fl_Check_Button*    sig1_cop2_symmetry;
    Fl_Value_Input*     sig1_cop2_width;
    Fl_Value_Input*     sig1_cop2_separation;
    
    Fl_RGB_Image* input_bmp_rgb;
    Fl_RGB_Image* output_bmp_rgb;
    Fl_BMP_Image* rgb_image;

    double cu_resistance_20c = 0.6787; 
   
    unsigned char* diagram1;
    Fl_RGB_Image* diagram1_rgb;
    int           bitmap_size;    
    char       p_test_file_name[] = "test_this.txt"; 
    
    int fltk_output_parameters();
    
int fltk_startup( void ) {
    int image_width,image_height;
    

    main_window = make_window();         ///< construct main panel
    about_window = make_about_window();  ///< construct about window
    config_window = make_config_window();///< construct configuration window

//    structure = select_structure;        ///< used to reference which structure user has selected
    
    /// add the image to the image box

    image_width = diff_pair_broad_queryw();
    image_height = diff_pair_broad_queryh();
    diagram1 = (unsigned char*)calloc(3*image_width*image_height+1024,sizeof( unsigned char));
    diff_pair_broad_decode( diagram1 );
    diagram1_rgb= new Fl_RGB_Image( diagram1 , image_width , image_height , 3);
    ref_diagram->image(diagram1_rgb);
    ref_diagram->redraw();
    
    scroll_bmp->position((current_bmp->w()-scroll_bmp->w())/2 , 
                         (current_bmp->h()-scroll_bmp->h())/2);
    field_plot_s->position((field_plot->w())/2 , 
                         (field_plot->h())/2);
   
    sig1_cu_thickness->value(2); // check that this is 1/2oz    

    /// SMT layer    
    layer_smt = make_layer_sm_window();
    layer_smt->label("Solder Mask Top");
    sm_group->label("Solder Mask Top");
    // capture some pointers before they get overwitten
    smt_thickness = sm_thickness;
    smt_er = sm_er;
    smt_loss_tangent= sm_loss_tangent;
    smt_open_x_off = sm_open_x_off;
    smt_open_x_w = sm_open_x_w;
    smt_fill = sm_fill_type;

    /// SMB Layer
    layer_smb = make_layer_sm_window();
    layer_smb->label("Solder Mask Bottom");
    sm_group->label("Solder Mask Bottom");
    
    smb_thickness = sm_thickness;
    smb_er = sm_er;
    smb_loss_tangent= sm_loss_tangent;
    smb_open_x_off = sm_open_x_off;
    smb_open_x_w = sm_open_x_w;    

    /// TOP Copper Plane
    layer_top_plane = make_layer_cu_plane_window();
    layer_top_plane->label("Copper Plane Top");
    cu_group->label("Copper Plane Top");
    
    cut_thickness = cu_thickness;
    cut_open_x_off = cu_open_x_off;
    cut_open_x_w = cu_open_x_w;
//    cut_etchback = cu_etchback;
    cut_filler_er = cu_filler_er;

    /// BOTTOM Copper Plane    
    layer_bot_plane = make_layer_cu_plane_window();
    layer_bot_plane->label("Copper Plane Bottom");
    cu_group->label("Copper Plane Bottom");

    cub_thickness = cu_thickness;
    cub_open_x_off = cu_open_x_off;
    cub_open_x_w = cu_open_x_w;
//    cub_etchback = cu_etchback;
    cub_filler_er = cu_filler_er;

    /// LAMINATE LAYER 1    
    layer_lam1 = make_layer_laminate_window();
    layer_lam1->label("Laminate Layer 1");
    lam_group->label("Laminate Layer 1"); 
    lam1_thickness = lam_thickness; 

    lam1_resin_er = lam_resin_er;
    lam1_glass_er = lam_glass_er;
    lam1_resin_content = lam_resin_content;
    lam1_loss_tangent = lam_loss_tangent;

    /// LAMINATE Layer 2    
    layer_lam2 = make_layer_laminate_window();
    layer_lam2->label("Laminate Layer 2");
    lam_group->label("Laminate Layer 2");

    lam2_thickness = lam_thickness; 
    lam2_resin_er = lam_resin_er;
    lam2_glass_er = lam_glass_er;
    lam2_resin_content = lam_resin_content;
    lam2_loss_tangent = lam_loss_tangent;
    
    /// SIGNAL Layer
    layer_sig1 = make_layer_signal_window();
    layer_sig1->label("Signal Layer 1");
    sig_group->label("Signal Layer 1");
    
    sig1_thickness = sig_thickness;
    sig1_trace1_w = sig_trace1_w;
    sig1_trace_etchback = sig_trace_etchback;
    sig1_filler_er = sig_filler_er;
    sig1_loss_tangent = sig_loss_tangent;
    sig1_trace_separation = sig_trace_separation;
    sig1_trace2_width = sig_trace2_width;
    

    
    // coplanar option
    layer_cop = make_coplanar_input_window();
    sig1_cop1_enable = cop1_enable;
    sig1_cop1_width = cop1_width;
    sig1_cop1_separation = cop1_separation;
    
    sig1_cop2_enable = cop2_enable;
    sig1_cop2_width = cop2_width;
    sig1_cop2_separation = cop2_separation;  
    sig1_cop2_symmetry = cop2_symmetry; 
         
    ib_initialize();    // reset the color map
    
    compute_status->value("Input");
    
    return(0);
}

int  fltk_switch_ref_diagram() {
     int image_width;
     int image_height;
     free(diagram1);
     diagram1_rgb->~Fl_RGB_Image();
     if ( edge_diff->value() == 1 && coplanar_enable->value() == 0) {
      image_width = diff_pair_broad_queryw();
      image_height = diff_pair_broad_queryh();
      diagram1 = (unsigned char*)calloc(3*image_width*image_height+1024,sizeof( unsigned char));
      diagram1_rgb= new Fl_RGB_Image( diagram1 , image_width , image_height , 3);
      diff_pair_broad_decode( diagram1 );

      ref_diagram->image(diagram1_rgb);
      ref_diagram->redraw();    
      } 
     else if ( edge_diff->value() == 1 && coplanar_enable->value() == 1) {
      image_width = coplanar_diff_queryw();
      image_height = coplanar_diff_queryh();
      diagram1 = (unsigned char*)calloc(3*image_width*image_height+1024,sizeof( unsigned char));
      diagram1_rgb= new Fl_RGB_Image( diagram1 , image_width , image_height , 3);
      coplanar_diff_decode( diagram1 );

      ref_diagram->image(diagram1_rgb);
      ref_diagram->redraw();    
      } 
     else if ( edge_diff->value() == 0 && coplanar_enable->value() == 1) {
      image_width = coplanar_se_queryw();
      image_height = coplanar_se_queryh();
      diagram1 = (unsigned char*)calloc(3*image_width*image_height+1024,sizeof( unsigned char));
      diagram1_rgb= new Fl_RGB_Image( diagram1 , image_width , image_height , 3);
      coplanar_se_decode( diagram1 );

      ref_diagram->image(diagram1_rgb);
      ref_diagram->redraw();    
      } 
    else {
      image_width = single_end_trace_queryw();
      image_height = single_end_trace_queryh();
      diagram1 = (unsigned char*)calloc(3*image_width*image_height+1024,sizeof( unsigned char));
      diagram1_rgb= new Fl_RGB_Image( diagram1 , image_width , image_height , 3);
      single_end_trace_decode( diagram1 );

      ref_diagram->image(diagram1_rgb);
      ref_diagram->redraw();  
    }
    return(0);
}         
/// When any input value changes, sync all input values just to minimize code upkeep
int fltk_sync_values( int direction ) {
    double ratio1;

if ( direction == 1 ) { /// calling from a pop-up or main
   if ( smt_enable->value() == 0 ) {
        smt_thk_o->value(0) ;
      }
   else {
        smt_thk_o->value(smt_thickness->value()) ;
        }
        
   if ( smb_enable->value() == 0 ) {
        smb_thk_o->value(0) ;
      }
   else {
        smb_thk_o->value(smb_thickness->value()) ;
        }
        
   if ( top_plane_enable->value() == 0 ) {
        top_cu_thk_o->value(0) ;
      }
   else {
        top_cu_thk_o->value(cut_thickness->value()) ;
        }
        
   if ( bot_plane_enable->value() == 0 ) {
        bot_cu_thk_o->value(0) ;
      }
   else {
        bot_cu_thk_o->value(cub_thickness->value()) ;
        }
   ratio1 = lam1_resin_content->value()/100.0;
   lam1_er->value( (ratio1*lam1_resin_er->value()) + ((1-ratio1)*lam1_glass_er->value()));

   ratio1 = lam2_resin_content->value()/100.0;
   if ( lam2_same->value() ) {
        lam2_er->value(lam1_er->value());
        }
   else {
   lam2_er->value( (ratio1*lam2_resin_er->value()) + ((1-ratio1)*lam2_glass_er->value()));
   }
   
   if ( fillerer_same->value() ) {
        sig1_filler_er->value(lam1_er->value());
        }

   if ( lam1_enable->value() == 0 ) {
        lam1_thk_o->value(0) ;
      }
   else {
        lam1_thk_o->value(lam1_thickness->value()) ;
        }
        
   if ( lam2_enable->value() == 0 ) {
        lam2_thk_o->value(0) ;
      }
   else {
          lam2_thk_o->value(lam2_thickness->value()) ;
        }
    trace_sep_main_i->value(sig1_trace_separation->value());
    if ( sig1_thickness->changed() ) {
       sig1_cu_thickness->value(5); // need to chenge this value if list is changed
       }
    trace1_width_main_i->value(sig1_trace1_w->value());
    
    if ( sig1_cop2_symmetry->value() == 1 ) {
         sig1_cop2_separation->value(sig1_cop1_separation->value());
         sig1_cop2_width->value(sig1_cop1_width->value());
         }

        }
else {
     if ( smt_enable->value() == 0 ) {
        smt_thk_o->value(0);
        }
     else {
        smt_thickness->value(smt_thk_o->value());
        }
        
     if ( smb_enable->value() == 0 ) {
        smb_thk_o->value(0);
        }
     else {
        smb_thickness->value(smb_thk_o->value());
        }
        
   if ( top_plane_enable->value() == 0 ) {
        top_cu_thk_o->value(0) ;
      }
   else {
        cut_thickness->value(top_cu_thk_o->value()) ;
        }
        
   if ( bot_plane_enable->value() == 0 ) {
        bot_cu_thk_o->value(0) ;
      }
   else {
        cub_thickness->value(bot_cu_thk_o->value()) ;
        }
        
   if ( lam1_er->value() < lam1_resin_er->value() ) {
        lam1_er->value(lam1_resin_er->value());
        }
   else if ( lam1_er->value() > lam1_glass_er->value() ) {
        lam1_er->value(lam1_glass_er->value());
        }
   lam1_resin_content->value(100.0*((lam1_glass_er->value()-lam1_er->value())/
                                 (lam1_glass_er->value()-lam1_resin_er->value())));

   if ( lam2_same->value() == 0 ) {                                 
       if ( lam2_er->value() < lam2_resin_er->value() ) {
            lam2_er->value(lam2_resin_er->value());
            }
       else if ( lam2_er->value() > lam2_glass_er->value() ) {
            lam2_er->value(lam2_glass_er->value());
            }
       lam2_resin_content->value(100.0*((lam2_glass_er->value()-lam2_er->value())/
                                     (lam2_glass_er->value()-lam2_resin_er->value())));
       }
   else {
        lam2_er->value(lam1_er->value());
               lam2_resin_content->value(100.0*((lam2_glass_er->value()-lam2_er->value())/
                                     (lam2_glass_er->value()-lam2_resin_er->value())));
        }
                                 

   if ( fillerer_same->value() ) {
        sig1_filler_er->value(lam1_er->value());
        }


   if ( lam1_enable->value() == 0 ) {
        lam1_thk_o->value(0) ;
      }
   else {
        lam1_thickness->value(lam1_thk_o->value()) ;
        }

  
   if ( lam2_enable->value() == 0 ) {
        lam2_thk_o->value(0) ;
      }
   else {
        lam2_thickness->value(lam2_thk_o->value());
        }


    sig1_trace1_w->value(trace1_width_main_i->value());
    sig1_trace2_width->value(trace1_width_main_i->value()); /// identical trace width implied
    sig1_trace_separation->value(trace_sep_main_i->value());
    }
return(0);
}
  
  
  
int       button_check_bmp() {
          ib_allocate();
          ib_draw();
          current_bmp->image(NULL);
          if ( input_bmp_rgb != NULL ) {
               delete input_bmp_rgb;
               }
          input_bmp_rgb = new Fl_RGB_Image( input_bmp, horizontal_pix, vertical_pix,3);
          current_bmp->image(input_bmp_rgb);
          current_bmp->redraw();
          return(0);
            
}

int       button_import_bmp(char* file_name) {
           

 FILE* fp;
 const char* pS; 
 unsigned char* pD;
 int n,i,j;
 char in_buffer[160];
// char input_filename[1024];
 
  if ( input_bmp != NULL ) {
       free(input_bmp);
      }

//  if ( input_bmp_rgb != NULL ) {
//       delete input_bmp_rgb;
//       } 
//  input_filename = file_name;
  if ( file_name )
     {
       fp = fopen(file_name , "rb");
       if (fp == NULL)
          {
          central_log->add_line("File error.");
          return(-2);
          }
       sprintf( in_buffer , "Reading file %s ...", file_name );
       central_log->add_line( in_buffer );
       if ( rgb_image ) { rgb_image->~Fl_BMP_Image(); }

       rgb_image = new Fl_BMP_Image(file_name);

       current_bmp->image(rgb_image);
       current_bmp->redraw();
       
       vertical_pix = rgb_image->h();
       horizontal_pix  = rgb_image->w();
       
       // copy the bitmap to local bitmap

       input_bmp = (unsigned char*)calloc( vertical_pix*horizontal_pix*3+1024 , sizeof (unsigned char) );
       if ( input_bmp == NULL ) return(-1);
       
       pS = rgb_image->data()[0];
       pD = input_bmp;
       i=0;
       while ( i < vertical_pix ) {
             j=0;
             while ( j < horizontal_pix ) {
                   *pD++ = *pS++;
                   *pD++ = *pS++;
                   *pD++ = *pS++;
                   j++;
                   }
             i++;
             }
       
//       rgb_depth  = rgb_image->d();
       
       sprintf( in_buffer , "Image pixel dimensions: %i high x %i wide", vertical_pix , horizontal_pix );
       central_log->add_line( in_buffer );       
       }
       return(0);
}

int       button_field_bmp() {

          // reallocating from start
          field_plot->image(NULL);
          bitmap_size = ob_allocate(); 
  
     
        
          if ( output_bmp_rgb != NULL ) {
             delete output_bmp_rgb;
             }          
          ob_draw();
          output_bmp_rgb = new Fl_RGB_Image( output_odd_bmp, width, height,3);
          field_plot->image(output_bmp_rgb);
          field_plot->redraw();
          return(0);         
          }

int       button_field_even_bmp() {
          // reallocating from start
              
          field_plot->image(NULL);
          bitmap_size = ob_allocate(); 
  
          if ( output_bmp_rgb != NULL ) {
             delete output_bmp_rgb;
             }

          ob_draw_even();
          output_bmp_rgb = new Fl_RGB_Image( output_odd_bmp, width, height,3);
          field_plot->image(output_bmp_rgb);
          field_plot->redraw();
          return(0);
          }

int button_z0() {
    int i,j;
    // set the dielectric values
    i =0;
//    while ( i < material_count ) {
//          // is it copper
//          if ( material_color[i] == material_color[MATERIAL_CU_GND] ||
//               material_color[i] == material_color[MATERIAL_CU_POS] ||
//               material_color[i] == material_color[MATERIAL_CU_NEG] ) {
//                                 i++;
//                                 }
//          else {
//               Er_in_bitmap[i].red = material_color[i].red;
//               Er_in_bitmap[i].green = material_color[i].green;
//               Er_in_bitmap[i].blue = material_color[i].blue;
//               Er_in_bitmap[i].epsilon = material_color[i].red;
    // go through settins one by one
//    data.dielectrics_on_command_line = 0;
//    i = 0;

      Fl::check();  // allow FLTK to update screen to log output
      
    data.dielectrics_on_command_line = 0;

    // AIR
    Er_on_command_line[i].red = material_color[MATERIAL_AIR].red;
    Er_on_command_line[i].green = material_color[MATERIAL_AIR].green;
    Er_on_command_line[i].blue = material_color[MATERIAL_AIR].blue;

    Er_on_command_line[i].epsilon = 1.0006;
    Er_on_command_line[i].loss_tangent = 0.00;
    data.dielectrics_on_command_line++; i++;

    
    // SMT
    Er_on_command_line[i].red = material_color[MATERIAL_SMT].red;
    Er_on_command_line[i].green = material_color[MATERIAL_SMT].green;
    Er_on_command_line[i].blue = material_color[MATERIAL_SMT].blue;

    Er_on_command_line[i].epsilon = smt_er->value();
    Er_on_command_line[i].loss_tangent = smt_loss_tangent->value();
    data.dielectrics_on_command_line++; i++;
    
    // laminate 1 glass
    Er_on_command_line[i].red = material_color[MATERIAL_LAM1_GLA].red;
    Er_on_command_line[i].green = material_color[MATERIAL_LAM1_GLA].green;
    Er_on_command_line[i].blue = material_color[MATERIAL_LAM1_GLA].blue;

    Er_on_command_line[i].epsilon = lam1_glass_er->value();
    Er_on_command_line[i].loss_tangent = lam1_loss_tangent->value();
    data.dielectrics_on_command_line++; i++;

    
    // laminate 1 resin
    Er_on_command_line[i].red = material_color[MATERIAL_LAM1_RES].red;
    Er_on_command_line[i].green = material_color[MATERIAL_LAM1_RES].green;
    Er_on_command_line[i].blue = material_color[MATERIAL_LAM1_RES].blue;
// not mixing glass and resin at bitmap so use average value for resin colour
//    Er_on_command_line[i].epsilon = lam1_resin_er->value();
//    Er_on_command_line[i].epsilon = (lam1_resin_content->value()*0.01*lam1_resin_er->value())+
//                           ((1-(lam1_resin_content->value()*0.01))*lam1_glass_er->value());
    Er_on_command_line[i].epsilon = lam1_er->value();
    Er_on_command_line[i].loss_tangent = lam1_loss_tangent->value();
    data.dielectrics_on_command_line++; i++;

    // filler
    Er_on_command_line[i].red = material_color[MATERIAL_FILL1_RES].red;
    Er_on_command_line[i].green = material_color[MATERIAL_FILL1_RES].green;
    Er_on_command_line[i].blue = material_color[MATERIAL_FILL1_RES].blue;

    Er_on_command_line[i].epsilon = sig1_filler_er->value();
    Er_on_command_line[i].loss_tangent = sig1_loss_tangent->value();
    data.dielectrics_on_command_line++; i++;

    // laminate 2 glass
    Er_on_command_line[i].red = material_color[MATERIAL_LAM2_GLA].red;
    Er_on_command_line[i].green = material_color[MATERIAL_LAM2_GLA].green;
    Er_on_command_line[i].blue = material_color[MATERIAL_LAM2_GLA].blue;
    Er_on_command_line[i].epsilon = lam2_glass_er->value();
    Er_on_command_line[i].loss_tangent = lam2_loss_tangent->value();
    data.dielectrics_on_command_line++; i++;

    // laminate 2 resin
    Er_on_command_line[i].red = material_color[MATERIAL_LAM2_RES].red;
    Er_on_command_line[i].green = material_color[MATERIAL_LAM2_RES].green;
    Er_on_command_line[i].blue = material_color[MATERIAL_LAM2_RES].blue;
// not mixing glass and resin at bitmap so use average value for resin colour
//    Er_on_command_line[i].epsilon = (lam2_resin_content->value()*0.01*lam2_resin_er->value())+
//                           ((1-(lam2_resin_content->value()*0.01))*lam2_glass_er->value());
    Er_on_command_line[i].epsilon = lam2_er->value();
    Er_on_command_line[i].loss_tangent = lam2_loss_tangent->value();
    data.dielectrics_on_command_line++; i++;

    // SMB
    Er_on_command_line[i].red = material_color[MATERIAL_SMB].red;
    Er_on_command_line[i].green = material_color[MATERIAL_SMB].green;
    Er_on_command_line[i].blue = material_color[MATERIAL_SMB].blue;

    Er_on_command_line[i].epsilon = smb_er->value();
    Er_on_command_line[i].loss_tangent = smb_loss_tangent->value();
    data.dielectrics_on_command_line++; i++;
    
    j=0;
    while ( j < i ) {
              Er_on_command_line[j].other_colour = (Er_on_command_line[j].red<<16) + 
                                       (Er_on_command_line[j].green<<8) + 
                                       Er_on_command_line[j].blue;
                                       j++;
                                       }

    fltk_output_parameters();

    Fl::check();  // allow FLTK to update screen to log output

    
    // transfer to atlc
    free(Vodd);
    free(Veven);
    Vodd = (double*)calloc( horizontal_pix*vertical_pix , sizeof( double ) );
    Veven = (double*)calloc( horizontal_pix*vertical_pix , sizeof( double ) );
//    system("PAUSE");
    main2( p_test_file_name , input_bmp  , horizontal_pix , vertical_pix ,
           Vodd , Veven );

    
	return 0; }

int fltk_output_parameters() {
    char   work[1024];
    double trace1_area;
    double trace2_area;
    
    central_log->add_line(" ");
    central_log->add_line("INPUT PARAMETERS:");
    central_log->add_line(" ");

    central_log->add_line("      Layer             Thick   Specifications ");

//   if ( air_top_pix > 0 ) {
//
//      sprintf(work, "  %20s %6.2f  %4.2f  ",
//                     "Air top",
//                     air_top_pix*thou_per_pix,
//                     1.0);
//      central_log->add_line(work);
//      }

   if ( smt_thk_o->value() > 0 ) {
      sprintf(work, "  %20s %6.2f    Opening w=%.1f  offset=%.1f",
                     layer_smt->label(),
                     smt_thk_o->value(),
                     
                     smt_open_x_w->value(),
                     smt_open_x_off->value());
      central_log->add_line(work);                    
    } 

   if ( top_cu_thk_o->value() > 0 ) {
      sprintf(work, "  %20s %6.2f    Opening w=%.1f  offset=%.1f",
                     layer_top_plane->label(),
                     top_cu_thk_o->value(),
                     
                     cut_open_x_w->value(),
                     cut_open_x_off->value());
      central_log->add_line(work); 
    }  
    
   if ( lam1_thk_o->value() > 0 ) {
      sprintf(work, "  %20s %6.2f    Resin Content  %.1f%% %.1f-%.1f ",
                     layer_lam1->label(),
                     lam1_thk_o->value(),
                     
                     lam1_resin_content->value(),
                     lam1_resin_er->value(),
                     lam1_glass_er->value() );
      central_log->add_line(work);    
    }  

if (edge_diff->value() == 1 ) {    
      sprintf(work, "  %20s %6.2f  %.1f-%.1f-%.1f  Etchback=%.2f",
                     layer_sig1->label(),
                     sig1_thickness->value(),
                     
                     sig1_trace1_w->value(),
                     sig1_trace_separation->value(),
                     sig1_trace2_width->value(),
                     sig1_trace_etchback->value() );
      central_log->add_line(work);      
      }
else {
      sprintf(work, "  %20s %6.2f  Width=%.1f  Etchback=%.2f",
                     layer_sig1->label(),
                     sig1_thickness->value(),
                     
                     sig1_trace1_w->value(),
                     sig1_trace_etchback->value() );
      central_log->add_line(work);          
     
     }
    
   if ( lam2_thk_o->value() > 0 ) {
      sprintf(work, "  %20s %6.2f    Resin Content  %.1f%% %.1f-%.1f ",
                     layer_lam2->label(),
                     lam2_thk_o->value(),
                     
                     lam2_resin_content->value(),
                     lam2_resin_er->value(),
                     lam2_glass_er->value() );
      central_log->add_line(work);        
    }  

   if ( bot_cu_thk_o->value() > 0 ) {
      sprintf(work, "  %20s %6.2f    Opening w=%.1f  offset=%.1f",
                     layer_bot_plane->label(),
                     cub_thickness->value(),
                     
                     cub_open_x_w->value(),
                     cub_open_x_off->value());
      central_log->add_line(work); 
    }

   if ( smb_thk_o->value() > 0 ) {
      sprintf(work, "  %20s %6.2f    Opening w=%.1f  offset=%.1f",
                     layer_smb->label(),
                     smb_thk_o->value(),
                     
                     smb_open_x_w->value(),
                     smb_open_x_off->value());
      central_log->add_line(work);

      
    }
//   if ( air_bot_pix > 0 ) {
//      sprintf(work, "  %20s %6.2f  %4.2f ",
//                     "Air bottom",
//                     air_bot_pix*thou_per_pix,
//                     1.0);
//      central_log->add_line(work);
//}
    central_log->add_line(" ");
 
    central_log->add_line("      Layer             Thick   Er    Loss Tangent");
// add mention of air allowance later
//   sprintf( work ,"Air Er = %f",Er_on_command_line[0].epsilon );
//   central_log->add_line(work);

   if ( air_top_pix > 0 ) {

      sprintf(work, "  %20s %6.2f  %4.2f    %7.5f",
                     "Air top",
                     air_top_pix*thou_per_pix,
                     1.0,Er_on_command_line[0].loss_tangent);
      central_log->add_line(work);
      }

   if ( smt_thk_o->value() > 0 ) {
      sprintf(work, "  %20s %6.2f  %4.2f    %7.5f",
                     layer_smt->label(),
                     smt_thk_o->value(),
                     smt_er->value(),
                     smt_loss_tangent->value());
      central_log->add_line(work);
                     
    } 

   if ( top_cu_thk_o->value() > 0 ) {
      sprintf(work, "  %20s %6.2f  %4.2f   ",
                     layer_top_plane->label(),
                     top_cu_thk_o->value(),
                     cut_filler_er->value()
                     );
      central_log->add_line(work); 
    }  
    

   if ( lam1_thk_o->value() > 0 ) {
      sprintf(work, "  %20s %6.2f  %4.2f    %7.5f ",
                     layer_lam1->label(),
                     lam1_thk_o->value(),
                     lam1_er->value(),
                     lam1_loss_tangent->value() );
      central_log->add_line(work);    
    }  

if (edge_diff->value() == 1 ) {    
      sprintf(work, "  %20s %6.2f  %4.2f    %7.5f",
                     layer_sig1->label(),
                     sig1_thickness->value(),
                     sig1_filler_er->value(),
                     sig1_loss_tangent->value() );
      central_log->add_line(work);      
      }
else {
      sprintf(work, "  %20s %6.2f  %4.2f    %7.5f",
                     layer_sig1->label(),
                     sig1_thickness->value(),
                     sig1_filler_er->value(),
                     sig1_loss_tangent->value() );
      central_log->add_line(work);          
     
     }
    
   if ( lam2_thk_o->value() > 0 ) {
      sprintf(work, "  %20s %6.2f  %4.2f    %7.5f",
                     layer_lam2->label(),
                     lam2_thk_o->value(),
                     lam2_er->value(),
                     lam2_loss_tangent->value() );
      central_log->add_line(work);        
    }  

   if ( bot_cu_thk_o->value() > 0 ) {
      sprintf(work, "  %20s %6.2f  %4.2f",
                     layer_bot_plane->label(),
                     cub_thickness->value(),
                     cub_filler_er->value()
                     );
      central_log->add_line(work); 
    }

   if ( smb_thk_o->value() > 0 ) {
      sprintf(work, "  %20s %6.2f  %4.2f    %7.5f",
                     layer_smb->label(),
                     smb_thk_o->value(),
                     smb_er->value(),
                     smb_loss_tangent->value() );
      central_log->add_line(work);

      
    }
   if ( air_bot_pix > 0 ) {
      sprintf(work, "  %20s %6.2f  %4.2f    %7.5f",
                     "Air bottom",
                     air_bot_pix*thou_per_pix,
                     1.0,
                     Er_on_command_line[0].loss_tangent);
      central_log->add_line(work);

}
    central_log->add_line(" ");
     
    if ( edge_diff->value() == 1 ) {
    central_log->add_line(" DC resistance by dimensions:");

         trace1_area = (sig1_trace1_w->value()-sig1_trace_etchback->value())*sig1_thickness->value();
         trace2_area = (sig1_trace2_width->value()-sig1_trace_etchback->value())*sig1_thickness->value();
         sprintf(work, " Rdc_trace_1= %.2f      Rdc_trace_2 = %.2f  milliohms/in 20C",
                       cu_resistance_20c/trace1_area*1000,cu_resistance_20c/trace2_area*1000);
         central_log->add_line(work);
         }
    else {

         trace1_area = (sig1_trace1_w->value()-sig1_trace_etchback->value())*sig1_thickness->value();
         trace2_area = (sig1_trace2_width->value()-sig1_trace_etchback->value())*sig1_thickness->value();
         sprintf(work, " Rdc_trace_1= %.2f  milliohms/in 20C",
                       cu_resistance_20c/trace1_area*1000);
         central_log->add_line(work);
         }

    
//    if ( sig1_trace2_width->value()>0 && edge_diff->value()==1 ) {
//         trace2_area = (sig1_trace2_width->value()-sig1_trace_etchback->value())*sig1_thickness->value();
//         sprintf(work, "  Trace 2 DC resistance %.2f milliohms/in 20C",
//                       cu_resistance_20c/trace2_area*1000);
//         central_log->add_line(work);
//                       }
//    central_log->add_line(" ");                  

    return(0);
}
     
int button_save_log_file( Fl_Widget* pw  ) {
    char* output_file_name;
    
    central_log->add_line("Log file save name:"); 
    output_file_name = central_log->write_log();
    if ( output_file_name ) {
         central_log->add_line( output_file_name );
         central_log->add_line( "" );
         } 
    else {
         central_log->add_line("!File write failed.");
         }
    return(0);
}

int copy2paste() {
    central_log->paste_selected();
	return 0;
}

int button_write_bmp() {

    int i , j;
    int vector_aligned;
    int   ret_val;
    char  bmp_name[40];
    FILE*    bmp_file;
    unsigned char* image_data;

    time_t rawtime;
    struct tm * timeinfo;

    ret_val = 0;  ///< return value 0=success -1=fail
    
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    /// 
    sprintf( bmp_name , "mdtlc_%02i%02i%02i%05i.bmp" ,
             timeinfo->tm_year - 100 ,
             timeinfo->tm_mon ,
             timeinfo->tm_mday ,
             timeinfo->tm_hour * 3600 + timeinfo->tm_min * 60 + timeinfo->tm_sec );
    bmp_file = fopen( bmp_name , "w+" );
    if ( bmp_file )  {

         /* put into the vector, in reverse order - i.e. from bottom to top and 
            align each row on 4-byte boundaries */
         // temporarily grab some memory
         image_data = (unsigned char*)calloc( 3*vertical_pix*(horizontal_pix+3),sizeof( unsigned char)); // allow for worst case 3 byte padding per row
         vector_aligned=align_bitmap_image(horizontal_pix , vertical_pix, input_bmp,image_data);
         write_bitmap_out( image_data , bmp_file , vector_aligned ,
                    horizontal_pix , vertical_pix );
         free(image_data);  // do not forget to release the memory

         ret_val = 1;
         }
    else {
         ret_val = (char)0;
         }
         central_log->add_line("Writing BMP file:"); 
    if ( bmp_file ) {
       central_log->add_line( bmp_name );
       central_log->add_line( "" );
       } 
    else {
       central_log->add_line("!BMP file write failed.");
       }
    return( ret_val );
}


