/* atlc - arbitrary transmission line calculator, for the analysis of
transmission lines are directional couplers. 

Copyright (C) 2002. Dr. David Kirkby, PhD (G8WRB).

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

Dr. David Kirkby, e-mail drkirkby at ntlworld.com 

*/

#include "config.h"
#include <stdio.h>
#define MAXIMUM_PROCESSING_DEVICES              1024
#define MAX_DIFFERENT_PERMITTIVITIES   10000
#define MAX_ER 12.0

/* The value of EPSILON_0 is taken from the UK National Physical
Laboratory's list of physical constants found on the web. */

#define EPSILON_0 8.854187817e-12
#define MU_0 M_PI*4e-7
#define MAX_THREADS  4
#define BORDER   5 /* The border to put around images. 1 is minimum, but 5 looks better */

#define TINY 1e-12
#define VERY_LARGE 1e15

// time delay of light in vacuum in ps/inch
#define TD_LIGHT_ENGL 84.72528

#define DONT_ZERO_ELEMENTS  0       
#define ZERO_ELEMENTS_FIRST 1       


struct pixels
{
   int red;          /* +1 V */
   int green;        /* 0 V */
   int blue;         /* -1 V */
   int white;        /* Vacuum */
   int other_colour;  /* mix of red, green and blue  */
   double epsilon;
   double loss_tangent;
};

struct max_values
{
double Ex_or_Ey_max, E_max, V_max, U_max, permittivity_max;
};

struct transmission_line_properties{
       
    double WW, HH, ww, ss, gg, hh, tt, Er1, Er2;
    int  W, H, w, s, g, h, t, bmp_size;
    int verbose_level; /* 0, 1 or 2 */
    double Codd, Ceven, C;
    double velocity_odd, velocity_factor_odd, relative_permittivity_odd;
    double velocity_even, velocity_factor_even, relative_permittivity_even;
    double Lodd_vacuum, Leven_vacuum, L_vacuum;
    double Codd_vacuum, Ceven_vacuum, C_vacuum, C_non_vacuum;
    double Zo, Zo_vacuum, Zo_non_vacuum, Zodd, Zodd_vacuum, Zeven;
    double Zeven_vacuum, Zdiff, Zdiff_vacuum, Zcomm, Zcomm_vacuum;
    double Er, the_single_Er, Er_odd, Er_even;
    double velocity, velocity_factor, relative_permittivity;
    double r; /* rate multiplier */
    double image_fiddle_factor;
    double cutoff; /* How small the error in subsequent itterations must be */
    int compute, display; /* none, ZO, ZODD, ZEVEN. ZEVEN_VAC, ZODD_VAC; */
    int should_binary_data_be_written_tooQ;
    int dielectrics_to_consider_just_now;
    int non_vacuum_dielectric_found;
    double found_this_dielectric;
    int dielectrics_on_command_line;
    int dielectrics_in_bitmap;
    int avoid_use_of_fast_convergence_methodQ;
    int couplerQ;
    int write_binary_field_imagesQ;
    int write_bitmap_field_imagesQ;
    double float_values[10];
    int int_values[10];
    int importance[10];
    int odd_or_even[10];
    int best[10];
    int non_metallic_pixels;
    int tenth_of_estimated_iterations_needed;
    int pixels_positive;                     // added for mdtlc for DC resistance calc
    int pixels_negative;                     // atlc found pixel count but discarded data. Put here to keep.
    double loss_tan_o;                       // mdtlc addition
    double loss_tan_e;                       // mdtlc addition
};

/* Despite the fact the Bitmap_File_Head_Struct and Bitmap_Head_Struct
all have int's for the types of data, in practice these must be 2 and 4
byte varialbes. As such, they are written a character at a time, so the
data size is unimportant. This was neeed on the Cray, due to the fact
sizeof(short)=8 */

struct Bitmap_File_Head_Struct
{
  unsigned char   zzMagic[2];	/* 00 "BM" */
  int     bfSize;      /* 02 */
  int    zzHotX;	/* 06 */
  int    zzHotY;	/* 08 */
  int     bfOffs;      /* 0A */
  int     biSize;      /* 0E */
};

struct Bitmap_Head_Struct
{
  int     biWidth;     /* 12 */
  int     biHeight;    /* 16 */
  int    biPlanes;    /* 1A */
  int    biBitCnt;    /* 1C */
  int     biCompr;     /* 1E */
  int     biSizeIm;    /* 22 */
  int     biXPels;     /* 26 */
  int     biYPels;     /* 2A */
  int     biClrUsed;   /* 2E */
  int     biClrImp;    /* 32 */
                        /* 36 */
};
//int align_bitmap_image(int W,int H,unsigned char *unaligned_image,unsigned char *byte_aligned_image);
//void write_bitmap_out(unsigned char *image_data, FILE *image_data_fp,int image_size, int W, int H);
#ifndef M_PI
#define M_PI 3.141592653589793238462643383279502884197169399375105820975
#endif

#define NUMBER_OF_DIELECTRICS_DEFINED 13


