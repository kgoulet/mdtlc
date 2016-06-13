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
#include "atlc.h"
#include "output_bmp.h"
#include "mdtlc.h"
#include "fltk_if.h"


unsigned char* output_odd_bmp;
//unsigned char* output_even_bmp;
double* Vodd;
double* Veven;


//#include "o_image.h"
#include <math.h>

//Fl_RGB_Image*    o_image_p;
//const unsigned char* image_data;
unsigned char* o_image;

int          linesize;
int          lines;

double       i_max;
double       i_min;
double       i_p75 , i_p50, i_p25;
unsigned char      i_r;
unsigned char      i_g;
unsigned char      i_b;
double*      ptr;

//
// Allocate the memory 
int              ob_allocate() {

          static int out_bmp_size = 0;
           
          if ( out_bmp_size != (3*height*width+1024) ) {        
              if ( output_odd_bmp != 0 ) {
                  free(output_odd_bmp);
                   }
              output_odd_bmp= (unsigned char*)calloc( 3*height*width+1024,
                             sizeof( unsigned char)); 
//              output_even_bmp= (unsigned char*)calloc( 3*height*width+1024,
//                             sizeof( unsigned char)); 
              if ( output_odd_bmp != NULL ) {
                 out_bmp_size = 3*height*width+1024;
                 linesize = width;
                 lines = height;
                 }
              }
              
          return(out_bmp_size);           
}
                 
int ob_draw() {

    double Ex = 0;
    double Ey = 0;
    double E,U;
    double* field_val;
    int h,w;
    static max_values ob_max_values;

     int i,j,k;
     double i_point;
     double i_p75,i_p50,i_p25;
     
     // converts double value into a pix intensity
     i_p75 = 0.75;
     i_p50 = 0.50;
     i_p25 = 0.25;

     o_image = (unsigned char*)output_odd_bmp;             
     

    // find the maximum values
    field_val = Vodd;

    i_max = 0;
    i_min = 0;
    for ( h = 0; h < height ; h++) {
        for ( w = 0 ; w < width ; w++ ) {
            if ( *field_val++ > i_max ) i_max = *field_val;
        }
    }
  
    
    field_val = Vodd;
    for(h=height-1;h>=0;h--)
    {
      for(w=0;w<width;w++)
      {
     i_point = *field_val++;
     i_point = (i_point - i_min)/(i_max-i_min); 
        
     if ( i_point > i_p75 ) {
          i_r = 255;
          i_g = 255;
          i_b = int((i_point - 0.75)/0.25 * 255);
          }
     else if ( i_point > i_p50 ) {
          i_r = 255;
          i_g = int((i_point - 0.50)/0.25 * 255);
          i_b = 0;
          }
     else if ( i_point > i_p25 ) {
          i_r = int(sqrt((i_point-0.25)/0.25)*255);
          i_g = 0;
          i_b = int(0.75*255*(1 - (i_point-0.25)/0.25));
          }
     else {
          i_r = 0;
          i_g = 0;
          i_b = int(i_point*0.75/0.25*255);
          }
          *o_image++ = i_r;
          *o_image++ = i_g;
          *o_image++ = i_b;
      }
    } 
    return(0);
}

int ob_draw_even() {

    double Ex = 0;
    double Ey = 0;
    double E,U;
    double* field_val;
    int h,w;
    static max_values ob_max_values;

     int i,j,k;
     double i_point;
     double i_p75,i_p50,i_p25;
     
     // converts double value into a pix intensity
     i_p75 = 0.75;
     i_p50 = 0.50;
     i_p25 = 0.25;

     o_image = (unsigned char*)output_odd_bmp;             
     

    // find the maximum values
    field_val = Veven;

    i_max = 0;
    i_min = 0;
    for ( h = 0; h < height ; h++) {
        for ( w = 0 ; w < width ; w++ ) {
            if ( *field_val++ > i_max ) i_max = *field_val;
        }
    }
  
    
    field_val = Veven;
    for(h=height-1;h>=0;h--)
    {
      for(w=0;w<width;w++)
      {
     i_point = *field_val++;
     i_point = (i_point - i_min)/(i_max-i_min); 
        
     if ( i_point > i_p75 ) {
          i_r = 255;
          i_g = 255;
          i_b = int((i_point - 0.75)/0.25 * 255);
          }
     else if ( i_point > i_p50 ) {
          i_r = 255;
          i_g = int((i_point - 0.50)/0.25 * 255);
          i_b = 0;
          }
     else if ( i_point > i_p25 ) {
          i_r = int(sqrt((i_point-0.25)/0.25)*255);
          i_g = 0;
          i_b = int(0.75*255*(1 - (i_point-0.25)/0.25));
          }
     else {
          i_r = 0;
          i_g = 0;
          i_b = int(i_point*0.75/0.25*255);
          }
          *o_image++ = i_r;
          *o_image++ = i_g;
          *o_image++ = i_b;
      }
    } 
    return(0);
}
