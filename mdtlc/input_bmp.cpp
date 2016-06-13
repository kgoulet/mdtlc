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
#include <stdio.h>
#include "atlc.h"
#include "input_bmp.h"
#include "output_bmp.h"
#include "mdtlc.h"
#include "fltk_if.h"


unsigned char* input_bmp;


int     n_layers;

 
        
int              material[MAX_MATERIALS];
Material_rgb     material_color[MAX_MATERIALS];
Material_rgb     color_value_cu_gnd = COLOR_CU_GND;
Material_rgb     color_value_cu_pos = COLOR_CU_POS;
Material_rgb     color_value_cu_neg = COLOR_CU_NEG;
Material_rgb     color_value_air = COLOR_AIR;
Material_rgb     color_value_smt = COLOR_SMT;
Material_rgb     color_value_smb = COLOR_SMB;
Material_rgb     color_value_fill = COLOR_FILL_RES;
Material_rgb     color_value_res1 = COLOR_RES1;
Material_rgb     color_value_gla1 = COLOR_GLA1;
Material_rgb     color_value_res2 = COLOR_RES2;
Material_rgb     color_value_gla2 = COLOR_GLA2;

//double  material_er[MAX_MATERIALS];

int              material_count=0;
int                dielectric_count=0;

double  thou_per_pix = 0.1;          // conversion factor may be variable in future
double  air_allowance_top = 10;          // 20 thou
double  air_allowance_bot = 10;
double  outer_space;
double  horizontal_center;
int     vertical_pix;
int     horizontal_pix;
int     horizontal_center_pix;

int     air_top_pix;
int     smt_pix;
int     smt_line;
int     smt_open_off_pix;
int     smt_open_width_pix;
int     cu_plane_1_pix;
int     cu_plane_1_open_off_pix;
int     cu_plane_1_open_width_pix;
int     laminate_1_pix;
int     cu_etch_1_pix;
int     sig1_neg_off_pix;
int     sig1_neg_width_pix;
double  sig1_neg_width_bot;
double  sig1_neg_etchback;
int     sig1_pos_off_pix;
int     sig1_pos_width_pix;
double  sig1_pos_width_bot;
double  sig1_pos_etchback;
double  sig1_cop1_rbot;
int     sig1_cop1_width_pix;
int     sig1_cop1_rbot_pix;
double  sig1_cop2_lbot;
int     sig1_cop2_width_pix;
int     sig1_cop2_lbot_pix;
int     laminate_2_pix;
int     cu_plane_2_pix;
int     cu_plane_2_open_off_pix;
int     cu_plane_2_open_width_pix;
int     smb_pix;
int     smb_open_off_pix;
int     smb_open_width_pix;
int     air_bot_pix;

int     set_pix( unsigned char* set_point , Material_rgb* set_color );
int     test_pix( unsigned char* test_point , Material_rgb* test_color );
int     fill_line( unsigned char* starting , Material_rgb* color_value );
int     fill_part_line( unsigned char* starting , int offset , 
                        int width , Material_rgb* color_value );
int     fill_part_line_rev( unsigned char* starting , int offset , 
                        int width , Material_rgb* color_value );
int     fill_part_dotted_line( unsigned char* starting , int offset , 
                        int width , int ratio_1 , int ratio_2 , int ratio_offset,
                        Material_rgb* color_value1 , Material_rgb* color_value2 );
    

int              ib_initialize() {
                 int i;
                 
                 material[MATERIAL_AIR] =       1;
                 material[MATERIAL_SMT] =       2;
                 material[MATERIAL_CU_GND] =    3;
                 material[MATERIAL_CU_POS] =    4;
                 material[MATERIAL_CU_NEG] =    5;
                 material[MATERIAL_LAM1_RES] =  6;
                 material[MATERIAL_LAM1_GLA] =  7;
                 material[MATERIAL_FILL1_RES] = 8;
                 material[MATERIAL_LAM2_RES] =  9;
                 material[MATERIAL_LAM2_GLA] =  10;
                 material[MATERIAL_SMB] =       11;
                 
                 material_count = 11;
                 
                 material_color[MATERIAL_AIR] =     color_value_air;
                 material_color[MATERIAL_SMT] =     color_value_smt  ;
                 material_color[MATERIAL_CU_GND] =  color_value_cu_gnd  ;
                 material_color[MATERIAL_CU_POS] =  color_value_cu_pos  ;
                 material_color[MATERIAL_CU_NEG] =  color_value_cu_neg  ;
                 material_color[MATERIAL_LAM1_RES] = color_value_res1 ;
                 material_color[MATERIAL_LAM1_GLA] =  color_value_gla1;
                 material_color[MATERIAL_FILL1_RES] = color_value_fill;
                 material_color[MATERIAL_LAM2_RES] = color_value_res2 ;
                 material_color[MATERIAL_LAM2_GLA] =  color_value_gla2;
                 material_color[MATERIAL_SMB] =      color_value_smb ;
                 

                 
                 return(0);
                 }
                 
//
// Allocate the memory 
int              ib_allocate() {
                 double etch_feature_width;
                 char tmpStr[80];
                 
                 // estimate thickness
                 vertical_pix = 0;
                 air_top_pix=0;
                 smt_pix=0;
                 cu_plane_1_pix=0;
                 laminate_1_pix=0;
                 cu_etch_1_pix=0;
                 laminate_2_pix=0;
                 cu_plane_2_pix=0;
                 smb_pix=0;
                 air_bot_pix=0;   

                // estimate width
                 // --- need to develop a good algorithm here ---
                 // --- just a quck method right here         ---
                 
                 etch_feature_width = 0;
                 etch_feature_width += sig1_trace1_w->value();
                 etch_feature_width += sig1_trace2_width->value();
                 etch_feature_width += sig1_trace_separation->value();
                 
                 if ( sig1_trace1_w->value() == 0 || sig1_trace2_width == 0 ) {
                      // allow more space if signle ended
                      outer_space = 5 * etch_feature_width;
                      }
                 else {
                      outer_space = 2 * etch_feature_width;
                      }
                 if ( outer_space < 20 ) outer_space = 20;
                 
                 horizontal_pix = 0.5+((outer_space+outer_space+etch_feature_width)/thou_per_pix);
                 horizontal_center_pix = horizontal_pix/2;
                 horizontal_center = thou_per_pix * horizontal_center_pix;
              
                 // code maintenance: verify order of menu choices
//                 if ( structure->value() == 0 ) {  // edge diff pair 1 etch 2 plane
                    // add top air if top copper plane not present or has opening
                    if ( top_cu_thk_o->value() == 0 || cut_open_x_w->value() > 0 ) {
                       air_allowance_top = 2*(5 + smt_thk_o->value()+ lam2_thk_o->value());
                       air_top_pix = (0.5+(air_allowance_top /thou_per_pix));
                       vertical_pix += air_top_pix;
                       }
                    // add top solder mask
                    if ( smt_thk_o->value() > 0 ) {
                         smt_pix=(0.5+(smt_thk_o->value()/thou_per_pix));
                         vertical_pix += smt_pix;
                         smt_open_off_pix = (smt_open_x_off->value()/thou_per_pix)+0.5;
                         smt_open_off_pix += horizontal_center_pix;
                         if ( smt_open_off_pix < 0 ) smt_open_off_pix = 0;
                         smt_open_width_pix = (smt_open_x_w->value()/thou_per_pix)+0.5;
                         }
                    
                    // add top copper plane
                       cu_plane_1_pix=(0.5+(top_cu_thk_o->value()/thou_per_pix));
                       vertical_pix += cu_plane_1_pix;
                      // find hole offset if spec'd
                      if ( cut_open_x_w->value() != 0 ) {
                           cu_plane_1_open_off_pix = (0.5 + (cut_open_x_off->value()/thou_per_pix));
                           cu_plane_1_open_off_pix += horizontal_center_pix;
                           if ( cu_plane_1_open_off_pix < 0 ) cu_plane_1_open_off_pix = 0;
                           cu_plane_1_open_width_pix = (0.5 + (cut_open_x_w->value()/thou_per_pix));
                           }
                      else {
                           cu_plane_1_open_width_pix = 0;
                           }
                    
                    // add laminate 1                  
                       laminate_1_pix=(0.5+(lam1_thk_o->value()/thou_per_pix));
                       vertical_pix += laminate_1_pix;
                    // add etch layer
               if ( edge_diff->value() == 1) {
                       cu_etch_1_pix=(0.5+(sig1_thickness->value()/thou_per_pix));
                       vertical_pix += cu_etch_1_pix;
                       sig1_neg_width_bot = sig1_trace1_w->value();
                       sig1_neg_width_pix = 0.5 + (sig1_neg_width_bot/thou_per_pix);
                       sig1_neg_off_pix = horizontal_center_pix - 
                        (0.5+((sig1_trace1_w->value()+(sig1_trace_separation->value()/2)))/thou_per_pix);
                       sig1_neg_etchback = sig1_trace_etchback->value();
                       sig1_pos_width_bot = sig1_trace2_width->value();
                       sig1_pos_width_pix = 0.5 + (sig1_pos_width_bot/thou_per_pix);
                       sig1_pos_off_pix = horizontal_center_pix + 
                          (0.5+(((sig1_trace_separation->value()/2)))/thou_per_pix);
                       sig1_pos_etchback = sig1_trace_etchback->value();
                       
                     // add coplanar
                     if ( sig1_cop1_enable->value()==1 ) {
                          // draw this from right to left to allow for inf plane
                          sig1_cop1_rbot = (sig1_cop1_separation->value()) +
                                           (sig1_trace_separation->value()/2.0) +
                                           sig1_trace1_w->value() ;
                          sig1_cop1_rbot_pix = 0.5 + ((horizontal_center - sig1_cop1_rbot)/thou_per_pix);
                          sig1_cop1_width_pix = 0.5 + (sig1_cop1_width->value()/thou_per_pix);
                          printf("left cop %i %i \n",sig1_cop1_rbot_pix , sig1_cop1_width_pix);
                          //system("PAUSE");
                          }
                     if ( sig1_cop2_enable->value()==1 ) {
                          // draw this from right to left to allow for inf plane
                          sig1_cop2_lbot = (sig1_cop2_separation->value()) +
                                           (sig1_trace_separation->value()/2.0) +
                                           (sig1_trace2_width->value()) ;
                          sig1_cop2_lbot_pix = 0.5 + ((horizontal_center + sig1_cop2_lbot)/thou_per_pix);
                          sig1_cop2_width_pix = 0.5 + (sig1_cop2_width->value()/thou_per_pix);
                          printf("right cop %i %i \n",sig1_cop2_lbot_pix , sig1_cop2_width_pix);
                          //system("PAUSE");
                          }                                                  
                       }
               else {
                       cu_etch_1_pix=(0.5+(sig1_thickness->value()/thou_per_pix));
                       vertical_pix += cu_etch_1_pix;
                       sig1_neg_width_bot = 0;
                       sig1_pos_width_bot = sig1_trace1_w->value();
                       sig1_pos_width_pix = 0.5 + (sig1_pos_width_bot/thou_per_pix);
                       sig1_pos_off_pix = horizontal_center_pix - 
                        (0.5+((sig1_trace1_w->value()/2)/thou_per_pix));
                       sig1_pos_etchback = sig1_trace_etchback->value();     
                       
                      // add coplanar
                     if ( sig1_cop1_enable->value()==1 ) {
                          // draw this from right to left to allow for inf plane
                          sig1_cop1_rbot = sig1_cop1_separation->value() +
                                           (sig1_trace1_w->value()/2) ;
                          sig1_cop1_rbot_pix = 0.5 + ((horizontal_center - sig1_cop1_rbot)/thou_per_pix);
                          sig1_cop1_width_pix = 0.5 + (sig1_cop1_width->value()/thou_per_pix);
                          printf("left cop %i %i \n",sig1_cop1_rbot_pix , sig1_cop1_width_pix);
                          //system("PAUSE");
                          }
                     if ( sig1_cop2_enable->value()==1 ) {
                          // draw this from right to left to allow for inf plane
                          sig1_cop2_lbot = sig1_cop2_separation->value() +
                                           (sig1_trace1_w->value()/2) ;
                          sig1_cop2_lbot_pix = 0.5 + ((horizontal_center + sig1_cop2_lbot)/thou_per_pix);
                          sig1_cop2_width_pix = 0.5 + (sig1_cop2_width->value()/thou_per_pix);
                          printf("right cop %i %i \n",sig1_cop2_lbot_pix , sig1_cop2_width_pix);
                          //system("PAUSE");
                          }                                                           
                     }
                        
                    // add laminate 2
                       laminate_2_pix=(0.5+(lam2_thk_o->value()/thou_per_pix));
                       vertical_pix += laminate_2_pix;
                    // add bottom copper plane
                       cu_plane_2_pix=(0.5+(bot_cu_thk_o->value()/thou_per_pix));
                       vertical_pix += cu_plane_2_pix;
                      // find hole offset if spec'd
                      if ( cub_open_x_w->value() != 0 ) {
                           cu_plane_2_open_off_pix = (0.5 + (cub_open_x_off->value()/thou_per_pix));
                           cu_plane_2_open_off_pix += horizontal_center_pix;
                           if ( cu_plane_2_open_off_pix < 0 ) cu_plane_2_open_off_pix = 0;
                           cu_plane_2_open_width_pix = (0.5 + (cub_open_x_w->value()/thou_per_pix));
                           }
                      else {
                           cu_plane_2_open_width_pix = 0;
                           }
                    // add bottom solder mask
                    if ( smb_thk_o->value() > 0 ) {
                         smb_pix=(0.5+(smb_thk_o->value()/thou_per_pix));
                         vertical_pix += smb_pix;
                         smb_open_off_pix = (smb_open_x_off->value()/thou_per_pix)+0.5;
                         smb_open_off_pix += horizontal_center_pix;
                         if ( smb_open_off_pix < 0 ) smb_open_off_pix = 0;
                         smb_open_width_pix = (smb_open_x_w->value()/thou_per_pix)+0.5;
                         }  
                    // add bottom air if bottom copper plane not present or has opening                                      
                    if ( bot_cu_thk_o->value() == 0 || cub_open_x_w->value() > 0 ) {
                         air_allowance_bot = 2*(5 + smb_thk_o->value()+ lam1_thk_o->value());
                         air_bot_pix= (0.5+(air_allowance_bot /thou_per_pix));
                       vertical_pix += air_bot_pix;
                       }

                 sprintf( tmpStr, "Simulation pix map %i pixels high by %i pixels wide.", 
                          vertical_pix,horizontal_pix);
                 central_log->add_line(tmpStr);                 

                 if ( input_bmp != 0 ) {
                      free(input_bmp);
//                      delete input_bmp_rgb;
                      }
                 input_bmp = (unsigned char*)calloc( 3*vertical_pix*horizontal_pix+1024,sizeof( unsigned char)); 
//                 input_bmp_rgb = new Fl_RGB_Image( input_bmp , vertical_pix , horizontal_pix , 3);   

                 sprintf( tmpStr, "%i bytes allocated for bmp.", 3*vertical_pix*horizontal_pix+1024 );
                 central_log->add_line(tmpStr);            
       
                 return(0);
                 
}
                 
int ib_draw() {
                 
                 unsigned char* current_row;
                 unsigned char* temp_ptr;
                 unsigned char* last_row;
                 unsigned char* smt_row;
                 unsigned char* smb_row;
                 unsigned char* lam2_row;
                 unsigned char* cuplane2_row;
                 unsigned char* air_bot_row;

                 double offset;
                 double weave_pitch;
                 int counter_mod4;
                 int    weave_pix_thread, row_count , row_offset , base_offset;
                 int i,j,k,pix_row;
                 int increment_offset, increment_width;
                 int no,nw,we,sw;
                 int so,se,ea,ne; 
                 
                 current_row = input_bmp;                
                 // leave space for air
                 last_row = current_row + air_top_pix*horizontal_pix*3;
                 while ( current_row < last_row ) {
                       fill_line(  current_row ,   &material_color[MATERIAL_AIR] ); 
                       current_row+= 3*horizontal_pix;
                       }                           
                 // leave space for solder mask
                 smt_row = current_row;
                 // fill with air for now
                 last_row = current_row + smt_pix*horizontal_pix*3;
                 while ( current_row < last_row ) {
                       fill_line(  current_row ,   &material_color[MATERIAL_AIR] ); 
                       current_row+= 3*horizontal_pix;
                       } 

                 // start with top copper layer 
                 temp_ptr = current_row;
                 last_row = current_row + (3*horizontal_pix*cu_plane_1_pix);
                 while ( current_row < last_row ) {
                       // flood with copper
                       fill_line(  current_row ,   &material_color[MATERIAL_CU_GND] ); 
                       current_row+= 3*horizontal_pix;
                       }
//printf(" %i  %i  \n",cu_plane_1_pix,cu_plane_1_open_width_pix);
//system("PAUSE");
                 // open hole to air
                 if ( cu_plane_1_open_width_pix > 0 ) {
                          current_row = temp_ptr;
                          while ( current_row < last_row ) {
                                fill_part_line( current_row , cu_plane_1_open_off_pix , 
                                                cu_plane_1_open_width_pix , 
                                                &material_color[MATERIAL_AIR]);
                                current_row+= 3*horizontal_pix;
                                }
                          }

                 // laminate 1
                   temp_ptr = current_row;
                   last_row = current_row + (3*horizontal_pix*laminate_1_pix);
                   while ( current_row < last_row ) {
                       fill_line(  current_row ,   &material_color[MATERIAL_LAM1_RES] ); 
                       current_row+= 3*horizontal_pix;
                       }  
//                   // draw in the glass weave (approx)
//                   weave_pitch = 1000*1/60/thou_per_pix;
//                   // expand to allow for porosity
//                   weave_pix_thread = ((100.0-lam1_resin_content->value())/100.0)/(1-GLA_POROSITY)*weave_pitch;
//                   row_count=0;
//                   row_offset=0;
//                   base_offset =0;
//                   counter_mod4=0;
//                   current_row = temp_ptr;
//                   while ( current_row < last_row ) {
//                        fill_part_dotted_line( current_row  , row_offset , 
//                                weave_pix_thread, 3 , 1 , counter_mod4,
//                                &material_color[MATERIAL_LAM1_GLA], &material_color[MATERIAL_LAM1_RES] );
//                         if ( row_offset >= horizontal_pix ) {
//
//                              current_row += 3*horizontal_pix;
//                              row_count++;
//                              if ( row_count > GLA_LAYER_SWITCH ) {
//                                   row_count = 0;
//                                   if ( base_offset == 0 ) {
//                                        base_offset = weave_pitch/2;
//                                        }
//                                   else {
//                                        base_offset = 0;
//                                        }
//                                   }
//                              row_offset = base_offset;
//                              } // end check if end of current row
//                         else {
//                              row_offset += weave_pitch;
//                              }
//                         if (counter_mod4 == 0 )      counter_mod4 = 2;
//                         else if (counter_mod4 == 2 ) counter_mod4 = 1;
//                         else if (counter_mod4 == 1 ) counter_mod4 = 3;
//                         else if (counter_mod4 == 3 ) counter_mod4 = 0;
//                         }
//                                        
                       //system("PAUSE");
              if ( edge_diff->value() == 1 ) {                       
                                      
                 // signal layer 1
                    // fill in filler (resin) if between laminates
                    temp_ptr = current_row;
                    last_row = current_row + (3*horizontal_pix*cu_etch_1_pix);
                    if ( !(laminate_1_pix == 0 || laminate_2_pix == 0 )) {
                      while ( current_row < last_row ) {
                       fill_line(  current_row ,   &material_color[MATERIAL_FILL1_RES] ); 
                       current_row+= 3*horizontal_pix;
                       }
                    }
                    else {
                      while ( current_row < last_row ) {
                       fill_line(  current_row ,   &material_color[MATERIAL_AIR] ); 
                       current_row+= 3*horizontal_pix;
                       }                                      
                    }
                         
                    // add left diff signal
                    current_row = temp_ptr;
                    pix_row = 0;
                    while ( current_row < last_row ) {
                          offset =  ((double)(cu_etch_1_pix-pix_row)) / cu_etch_1_pix * sig1_neg_etchback;
                          increment_offset = 0.5 + ( offset / thou_per_pix);
//                          increment_width = 0.5 + ( (sig1_neg_width_bot - (2*offset))/thou_per_pix);
                            increment_width = sig1_neg_width_pix - 2*increment_offset;
                          fill_part_line( current_row , sig1_neg_off_pix + increment_offset , 
                                          increment_width ,
                                          &material_color[MATERIAL_CU_POS]);
                          pix_row++;
                          current_row+= 3*horizontal_pix;
                          }
                    // add right (pos) diff signal
                    current_row = temp_ptr;
                    pix_row = 0;
                    while ( current_row < last_row ) {
                          offset =  ((double)(cu_etch_1_pix-pix_row)) / cu_etch_1_pix * sig1_pos_etchback;
                          increment_offset = 0.5 + ( offset / thou_per_pix);
//                          increment_width = 0.5 + ( (sig1_neg_width_bot - (2*offset))/thou_per_pix);
                            increment_width = sig1_pos_width_pix - 2*increment_offset;
                          fill_part_line( current_row , sig1_pos_off_pix + increment_offset , 
                                          increment_width ,
                                          &material_color[MATERIAL_CU_NEG]);
                          pix_row++;
                          current_row+= 3*horizontal_pix;
                          }
                if ( sig1_cop1_enable->value()==1 ) {
                // add left coplanar
                    current_row = temp_ptr;
                    pix_row = 0;
                    while ( current_row < last_row ) {
                          offset =  ((double)(cu_etch_1_pix-pix_row)) / cu_etch_1_pix * sig1_neg_etchback;
                          increment_offset = 0.5 + ( offset / thou_per_pix);
//                          increment_width = 0.5 + ( (sig1_neg_width_bot - (2*offset))/thou_per_pix);
                            increment_width = sig1_cop1_width_pix - 2*increment_offset;
                          fill_part_line_rev( current_row , sig1_cop1_rbot_pix - increment_offset , 
                                          increment_width ,
                                          &material_color[MATERIAL_CU_GND]);
                          pix_row++;
                          current_row+= 3*horizontal_pix;
                          }
                          } 
                if ( sig1_cop2_enable->value()==1 ) {
                // add right coplanar
                    current_row = temp_ptr;
                    pix_row = 0;
                    while ( current_row < last_row ) {
                          offset =  ((double)(cu_etch_1_pix-pix_row)) / cu_etch_1_pix * sig1_pos_etchback;
                          increment_offset = 0.5 + ( offset / thou_per_pix);
//                          increment_width = 0.5 + ( (sig1_neg_width_bot - (2*offset))/thou_per_pix);
                            increment_width = sig1_cop2_width_pix - 2*increment_offset;
                          fill_part_line( current_row , sig1_cop2_lbot_pix + increment_offset , 
                                          increment_width ,
                                          &material_color[MATERIAL_CU_GND]);
                          pix_row++;
                          current_row+= 3*horizontal_pix;
                          }
                          } 
                          

                   }
              else {
                 // signal layer 1
                    // fill in filler (resin) if between laminates
                    temp_ptr = current_row;
                    last_row = current_row + (3*horizontal_pix*cu_etch_1_pix);
                    if ( !(laminate_1_pix == 0 || laminate_2_pix == 0 )) {
                      while ( current_row < last_row ) {
                       fill_line(  current_row ,   &material_color[MATERIAL_FILL1_RES] ); 
                       current_row+= 3*horizontal_pix;
                       }
                    }
                    else {
                      while ( current_row < last_row ) {
                       fill_line(  current_row ,   &material_color[MATERIAL_AIR] ); 
                       current_row+= 3*horizontal_pix;
                       }                                      
                    }
                         
                    // add left diff signal
                    current_row = temp_ptr;
                    pix_row = 0;
                    while ( current_row < last_row ) {
                          offset =  ((double)(cu_etch_1_pix-pix_row)) / cu_etch_1_pix * sig1_pos_etchback;
                          increment_offset = 0.5 + ( offset / thou_per_pix);
//                          increment_width = 0.5 + ( (sig1_neg_width_bot - (2*offset))/thou_per_pix);
                            increment_width = sig1_pos_width_pix - 2*increment_offset;
                          fill_part_line( current_row , sig1_pos_off_pix + increment_offset , 
                                          increment_width ,
                                          &material_color[MATERIAL_CU_POS]);
                          pix_row++;
                          current_row+= 3*horizontal_pix;
                          }
                          
                if ( sig1_cop1_enable->value()==1 ) {
                // add left coplanar
                    current_row = temp_ptr;
                    pix_row = 0;
                    while ( current_row < last_row ) {
                          offset =  ((double)(cu_etch_1_pix-pix_row)) / cu_etch_1_pix * sig1_pos_etchback;
                          increment_offset = 0.5 + ( offset / thou_per_pix);
//                          increment_width = 0.5 + ( (sig1_neg_width_bot - (2*offset))/thou_per_pix);
                            increment_width = sig1_cop1_width_pix - 2*increment_offset;
                          fill_part_line_rev( current_row , sig1_cop1_rbot_pix - increment_offset , 
                                          increment_width ,
                                          &material_color[MATERIAL_CU_GND]);
                          pix_row++;
                          current_row+= 3*horizontal_pix;
                          }
                          } 
                if ( sig1_cop2_enable->value()==1 ) {
                // add right coplanar
                    current_row = temp_ptr;
                    pix_row = 0;
                    while ( current_row < last_row ) {
                          offset =  ((double)(cu_etch_1_pix-pix_row)) / cu_etch_1_pix * sig1_pos_etchback;
                          increment_offset = 0.5 + ( offset / thou_per_pix);
//                          increment_width = 0.5 + ( (sig1_neg_width_bot - (2*offset))/thou_per_pix);
                            increment_width = sig1_cop2_width_pix - 2*increment_offset;
                          fill_part_line( current_row , sig1_cop2_lbot_pix + increment_offset , 
                                          increment_width ,
                                          &material_color[MATERIAL_CU_GND]);
                          pix_row++;
                          current_row+= 3*horizontal_pix;
                          }
                          } 
                            


                 }                    
                        
                 // laminate 2 
                 temp_ptr = current_row;
                 last_row = current_row + (3*horizontal_pix*laminate_2_pix);
                 while ( current_row < last_row ) {
                       fill_line(  current_row ,   &material_color[MATERIAL_LAM2_RES] ); 
                       current_row+= 3*horizontal_pix;
                       } 
                 cuplane2_row = current_row;   

                 // bottom copper layer 
                 temp_ptr = current_row;
                 last_row = current_row + (3*horizontal_pix*cu_plane_2_pix);
                 while ( current_row < last_row ) {
                       fill_line(  current_row ,   &material_color[MATERIAL_CU_GND] ); 
                       current_row+= 3*horizontal_pix;
                       }
                 // open hole to air
                     if ( cu_plane_2_open_width_pix > 0 ) {
                          current_row = temp_ptr;
                          while ( current_row < last_row ) {
                                fill_part_line( current_row , cu_plane_2_open_off_pix , 
                                                cu_plane_2_open_width_pix , 
                                                &material_color[MATERIAL_AIR]);
                                current_row+= 3*horizontal_pix;
                                }
                          }
                 // leave space for solder mask
                 smb_row = current_row;
                 last_row = current_row + smb_pix*horizontal_pix*3;
                 // temporarily fill with air
                 while ( current_row < last_row ) {
                       fill_line(  current_row ,   &material_color[MATERIAL_AIR] ); 
                       current_row+= 3*horizontal_pix;
                       }  
                 air_bot_row = current_row;
                 // add air if opening in copper plane
                 last_row = current_row + air_bot_pix*horizontal_pix*3;
                 while ( current_row < last_row ) {
                       fill_line(  current_row ,   &material_color[MATERIAL_AIR] ); 
                       current_row+= 3*horizontal_pix;
                       } 
//                        printf("smt %i topcu %i botbu %i smb %i \n",smt_pix,cu_plane_1_pix,cu_plane_2_pix,smb_pix);
//                       system("PAUSE");
                                     
             
                 // now "coat" the board
                 
                 // nov 9 2007
                 // change the coating algorithm to partly drop down coat
                 // partly contour coating

                 // smt_pix = number of pixels thick for coating
                 // smt_conform = fraction that is conformal coating
                 // smt_vert = fraction that is drop down
                 // conform_frac = fraction that is conformal 0 to 1
                 
//                 smt_conform = conform_frac*(double)smt_pix;
                                  
              // straight line fill if no top plane
              if ( top_cu_thk_o->value() != 0 ) {
                   smt_line = 0;
                   }
              else {
                   smt_line = (100-smt_fill->value())*smt_pix/100;
                   }
              // conformal coat                 
              k=0;
              while ( k < smt_line ) {
              // go 'down' in search for solid surface
                temp_ptr = smt_row;
                j = 0;
                while ( j < vertical_pix - smt_pix ) {
                      //printf("material color %i %i\n",j,test_pix( temp_ptr , &material_color[MATERIAL_AIR] ));
                      if ( test_pix( temp_ptr , &material_color[MATERIAL_AIR] )==0 ) {
                           // found surface
                           break;
                           }
                      else {
                          j++;
                          temp_ptr+=3*horizontal_pix;  // down one more line
                          }
                      }

                 // set a point
                 temp_ptr -= 3*horizontal_pix;  // move up one line
                 set_pix( temp_ptr , &material_color[MATERIAL_SMT] );      
                 //travel straight across, but change only air points
                 j=0;
                 while ( j < horizontal_pix ) {
                       temp_ptr += 3;
                       if ( smt_open_width_pix == 0 ||
                                   (i < smt_open_off_pix || i > smt_open_off_pix + smt_open_width_pix ) ) {
                       if   ( test_pix( temp_ptr , &material_color[MATERIAL_AIR] )==1 ) {
                            set_pix( temp_ptr , &material_color[MATERIAL_SMT] );
                            }
                            }
                       j++;
                       }
                 k++;
                 }
                                             

              k=0;
              while ( k < smt_pix - smt_line ) {                
                // go 'down' in search for solid surface
                temp_ptr = smt_row;
                j = 0;
                while ( j < vertical_pix - smt_pix ) {
                      //printf("material color %i %i\n",j,test_pix( temp_ptr , &material_color[MATERIAL_AIR] ));
                      if ( test_pix( temp_ptr , &material_color[MATERIAL_AIR] )==0 ) {
                           // found surface
                           break;
                           }
                      else {
                          j++;
                          temp_ptr+=3*horizontal_pix;  // down one more line
                          }
                      }

                 // set a point
                 temp_ptr -= 3*horizontal_pix;  // move up one line
                 set_pix( temp_ptr , &material_color[MATERIAL_SMT] );      
                 //crawl along surface  
                 i = 0;           
                 //printf("Test debug\n");             
                 while ( i < horizontal_pix ) {
                       if ( smt_open_width_pix == 0 ||
                                   (i < smt_open_off_pix || i > smt_open_off_pix + smt_open_width_pix ) ) {
                                   // check if W
//                                   if ( i>0 &&(test_pix( temp_ptr-3, &material_color[MATERIAL_AIR] )==1) ) {
//                                        // move temp pointer and set point
//                                        temp_ptr+= -3;
//                                        set_pix( temp_ptr , &material_color[MATERIAL_SMT] );
//                                        i--;
//                                        }   
                                   no=1;nw=1;we=1;sw=1;
                                   so=1;se=1;ea=1;ne=1;    
                                   // check SW
                                   if ( i>0 &&(test_pix( temp_ptr+(3*horizontal_pix)-3, &material_color[MATERIAL_AIR] )==1) ) {
                                        sw=0;
                                        }
                                   // check S
                                  if ( test_pix( temp_ptr+(3*horizontal_pix), &material_color[MATERIAL_AIR] )==1 ) {
                                        so=0;
                                        }                                   
                                   // check  SE
                                   if ( (i)<horizontal_pix&&(test_pix( temp_ptr+(3*horizontal_pix)+3, &material_color[MATERIAL_AIR] )==1) ) {
                                        se=0;
                                        }         
                                   // check  E
                                   if ( (i)<horizontal_pix&&(test_pix( temp_ptr+3, &material_color[MATERIAL_AIR] )==1) ) {
                                        ea=0;
                                        } 
                                   // check  NE
                                   if ( (i)<horizontal_pix&&(test_pix( temp_ptr-(3*horizontal_pix)+3, &material_color[MATERIAL_AIR] )==1) ) {
                                        ne=0;
                                        } 
                                   // check  N
                                   if ( test_pix( temp_ptr-(3*horizontal_pix), &material_color[MATERIAL_AIR] )==1 ) {
                                        no=0;
                                        } 
                                   // check NW
                                   if ( i>0 && (test_pix( temp_ptr-(3*horizontal_pix)-3, &material_color[MATERIAL_AIR] )==1) ) {
                                        nw=0;
                                        } 
                                   // check  W
                                   if ( i>0 && (test_pix( temp_ptr-3, &material_color[MATERIAL_AIR] )==1) ) {
                                        we=0;
                                        } 
                                        
                                   // move east if east open and south and south-east solid
                                   if ( ea==0 && so==1 && se==1 ) {
                                        // move temp pointer and set point
                                        temp_ptr+=3;
                                        set_pix( temp_ptr , &material_color[MATERIAL_SMT] );
                                        i++;
                                        //printf("E\n");
                                        }
                                   // move up if east and south blocked and north east blocked
                                   else if  ( ea==1 && ne==1 && no==0 ) {   
                                        // move temp pointer and set point
                                        temp_ptr+= -(3*horizontal_pix);
                                        set_pix( temp_ptr , &material_color[MATERIAL_SMT] );
                                        //printf("N\n");
                                        }
                                   // move up and east if north east open
                                   else if  ( ea==1  && se==1 && ne==0 ) {   
                                        temp_ptr+= -(3*horizontal_pix)+3;
                                        set_pix( temp_ptr , &material_color[MATERIAL_SMT] );
                                        i++;
                                        //printf("NE\n");
                                        }
                                   // move up and west if north west only option
                                   else if  ( ea==1  && ne==1 && no==1 && nw==0 ) { 
                                        // move temp pointer and set point
                                        temp_ptr+= -(3*horizontal_pix)-3;
                                        set_pix( temp_ptr , &material_color[MATERIAL_SMT] );
                                        i--;
                                        //printf("NW\n");
                                        }
                                   // go west if west open 
                                   else if  ( we==0 ) {  
                                        // move temp pointer and set point
                                        temp_ptr+= -3;
                                        set_pix( temp_ptr , &material_color[MATERIAL_SMT] );
                                        i--;
                                        //printf("WE\n");
                                        //printf("n %i ne %i e %i se %i \n",no,ne,ea,se);
                                       // printf("s %i sw %i w %i nw %i \n",so,sw,we,nw);
                                        //system("PAUSE");
                                        }
                                   // move down and west if south west open
                                   else if  ( sw==0 ) {                                       
                                        // move temp pointer and set point
                                        temp_ptr+= (3*horizontal_pix)-3;
                                        set_pix( temp_ptr , &material_color[MATERIAL_SMT] );
                                        i--;
                                        //printf("SW\n");
                                        }
                                   // move down if south open
                                   else if  ( so==0  ) {                                       
                                        // move temp pointer and set point
                                        temp_ptr+=3*horizontal_pix;
                                        set_pix( temp_ptr , &material_color[MATERIAL_SMT] );
                                        //printf("SOUTH\n"); 
                                        }
                                   // move down and right if south closed
                                   else if  ( se==0 ) {                                       
                                        // move temp pointer and set point
                                        temp_ptr+=3*horizontal_pix+3;
                                        set_pix( temp_ptr , &material_color[MATERIAL_SMT] );
                                        i++;
                                        //printf("SE\n");
                                        }
                                   else
                                       {
                                       // nowhere to go - stop
                                       if ( i>0 ) i = horizontal_pix;
                                       else i=horizontal_pix;
                                       }
                                  }
                                  //system("PAUSE");
                                  else {
                                    i++; temp_ptr+= 3;
                                     }
                            } 


                       k++;
                       }
//  printf("smbpix %i cu2 %i\n",smb_pix,cu_plane_2_pix);
//  printf("smbrow %x base %x last %x size %x vert %i\n",smb_row,input_bmp,last_row,last_row-input_bmp,vertical_pix);
//  system("PAUSE");
                                     
                
//                 temp_ptr = smb_row;
                 i = 0;
                 while ( i < horizontal_pix ) {
                       if ( smb_open_width_pix == 0 ||
                                   (i < smb_open_off_pix || i > smb_open_off_pix + smb_open_width_pix ) ) {
                            j = 0;
                            temp_ptr = smb_row + (3*i);
                            temp_ptr -= 3*horizontal_pix;
                            // go 'up' in search for solid surface
                            while ( j < (cu_plane_2_pix + smb_pix + 1 ) ) {

                                  if ( test_pix( temp_ptr , &material_color[MATERIAL_AIR] )==0 ) {
                                       // found surface
                                  //printf("material color %i %i %i\n",i,j,test_pix( temp_ptr , &material_color[MATERIAL_AIR] ));
                                       //system("PAUSE");
                                       break;
                                       }
                                  else {
                                      j++;
                                      temp_ptr -= 3*horizontal_pix;
                                      }
                                  }    
                            // start coating in down direction
                            j = 0;
                            while ( j < smb_pix ) {
                                     temp_ptr += 3*horizontal_pix;
                                     if ( temp_ptr < last_row ) set_pix( temp_ptr , &material_color[MATERIAL_SMB] );
                                  j++;
                                  }
                      //      // also do sidewall coatings

                            }
                        //printf("loop %i %i \n",i,j );
                        //system("PAUSE");
                       i++;
                       }
        
                 // draw a conductive box around structure
                 temp_ptr = input_bmp;
                 fill_line( temp_ptr , &material_color[MATERIAL_CU_GND] );
                 temp_ptr += 3*(horizontal_pix)*(vertical_pix-1);
                 fill_line( temp_ptr , &material_color[MATERIAL_CU_GND] );
                 temp_ptr = input_bmp;
                 i = 0;
                 while ( i<vertical_pix)  {
                       fill_part_line( temp_ptr , 0 , 1 , &material_color[MATERIAL_CU_GND] );
                       fill_part_line( temp_ptr , horizontal_pix-1 , 1 , &material_color[MATERIAL_CU_GND] );
                       temp_ptr += horizontal_pix*3;
                       i++;
                       }
                            
                 return(0);
}

int     test_pix( unsigned char* test_point , Material_rgb* test_color  ) {    
                   int i;
                   unsigned char* r;
                   unsigned char* g;
                   unsigned char* b;
                   r = test_point;
                   g = r+1;
                   b = r+2;  
                   //printf("%x%x%x %x%x%x\n",*r,*g,*b,test_color->red,test_color->green,test_color->blue);
                   //system("PAUSE");
                   if ( *r == test_color->red &&
                   *g == test_color->green &&
                   *b == test_color->blue ) {
                         return(1);
                         }
                   return(0);   
                   }

int     set_pix( unsigned char* set_point , Material_rgb* set_color ) {    
                   int i;
                   unsigned char* r;
                   unsigned char* g;
                   unsigned char* b;
                   r = set_point;
                   g = r+1;
                   b = r+2;  
                   *r = set_color->red;
                   *g = set_color->green;
                   *b = set_color->blue;
                   return(0);   
                   }
            
                 
int     fill_line( unsigned char* starting , Material_rgb* color_value ) {
                   int i;
                   unsigned char* r;
                   unsigned char* g;
                   unsigned char* b;
                   r = starting;
                   g = r+1;
                   b = r+2;
                   i = 0;
                   while ( i < horizontal_pix ) {
                         *r = color_value->red;
                         *g = color_value->green;
                         *b = color_value->blue;


                         r+=3;
                         g+=3;
                         b+=3;

                         i++;
                         }
                   return(0);
}
int     fill_part_line( unsigned char* starting , int offset , 
                        int width , Material_rgb* color_value ) {
                   int i;
                   int limit;
                   unsigned char* r;
                   unsigned char* g;
                   unsigned char* b;
                   r = starting + (3*offset);
                   g = r+1;
                   b = r+2;
                   i = 0;
                   limit = width ;
                   if ( (limit + offset) > horizontal_pix ) limit = horizontal_pix - offset;
                   while ( i < limit ) {
                         *r = color_value->red;
                         *g = color_value->green;
                         *b = color_value->blue;


                         r+=3;
                         g+=3;
                         b+=3;

                         i++;
                         }
                   return(0);
}

int     fill_part_line_rev( unsigned char* starting , int offset , 
                        int width , Material_rgb* color_value ) {
                   int i;
                   int limit;
                   unsigned char* r;
                   unsigned char* g;
                   unsigned char* b;
                   r = starting + (3*offset);
                   g = r+1;
                   b = r+2;
                   i = 0;
                   limit = width ;
                   if ( (offset - limit) < 0 ) limit = offset;
                   while ( i < limit ) {
                         *r = color_value->red;
                         *g = color_value->green;
                         *b = color_value->blue;


                         r-=3;
                         g-=3;
                         b-=3;

                         i++;
                         }
                   return(0);
}

int     fill_part_dotted_line( unsigned char* starting , int offset , 
                        int width , int ratio_1 , int ratio_2 , int ratio_offset,
                        Material_rgb* color_value1 , Material_rgb* color_value2 ) {
                        
                   int i;
                   int limit;
                   
                   unsigned char* r;
                   unsigned char* g;
                   unsigned char* b;
                   // no check is made for consistency between ratio and ratio_offset
                   int color_count;
                   
                   color_count = ratio_offset;
                   
                   r = starting + (3*offset);
                   g = r+1;
                   b = r+2;
                   i = 0;
                   limit = width ;
                   if ( (limit + offset) > horizontal_pix ) limit = horizontal_pix - offset;
                   while ( i < limit ) {
                         if ( color_count < ratio_1 ) {
                            *r = color_value1->red;
                            *g = color_value1->green;
                            *b = color_value1->blue;
                            color_count++;}
                         else {
                            *r = color_value2->red;
                            *g = color_value2->green;
                            *b = color_value2->blue;
                            if ( color_count < ratio_2+ratio_1 ) {
                                 color_count++; }
                            else {
                                 color_count = 0;}
                            }                              
                         r+=3;
                         g+=3;
                         b+=3;

                         i++;
                         }
                   return(0);
}                         
