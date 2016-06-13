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

#include "definitions.h"
// direct output to the browser log defined at main level
#include "mdtlc.h"  

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#ifdef SYS_TYPES_H
#include <sys/types.h>
#endif

/* The following simple function just prints data into a file, or if
fp-stout, to the screen. Depending on whether the dielectric is mixed or
not, it is or is not possible to quote a value for Er. If Er is passed
as a mumber < 0, this function interprets that as meaning that the
dielectric is mixed, and says 'Er= MIXED' */

void print_data_for_two_conductor_lines(struct transmission_line_properties data, FILE *where_to_print_fp, char *inputfile_name)
{
     char pWork[100];
//  if(data.verbose_level <2)
//    fprintf(where_to_print_fp,"%s 2 Er= %5.2f Zo= %7.3f Ohms C= %6.1f pF/m L= %6.1f nH/m v= %.4g m/s v_f= %.3f VERSION= %s\n",
//inputfile_name,data.Er, data.Zo,data.C*1e12, data.L_vacuum*1e9, data.velocity,data.velocity_factor,PACKAGE_VERSION);
//  else
//    fprintf(where_to_print_fp,"%s 2 Er= %16.13f Zo= %16.13f Ohms C= %16.13f pF/m L= %16.13f nH/m v= %16.13g m/s v_f= %16.13f VERSION= %s\n",inputfile_name,data.Er, data.Zo,data.C*1e12, data.L_vacuum*1e9, data.velocity,data.velocity_factor,PACKAGE_VERSION);
      central_log->add_line(" DC resistance by pixel count:");
      sprintf(pWork, " Rdc_trace_1= %7.3f milliohm/in.",1000*67.87/data.pixels_positive); 
      central_log->add_line(pWork);
      sprintf(pWork, " C          = %7.3f pF/in        L = %7.3f nH/in.",data.C*1e12/39.37,data.L_vacuum*1e9/39.37);
      central_log->add_line(pWork);
      sprintf(pWork, " Er         = %7.3f       Loss_tan =   %6.5f",data.Er,data.loss_tan_o);
      central_log->add_line(pWork);
      sprintf(pWork, " Zo         = %7.3f Ohms     Delay = %7.3f ps/in.",data.Zo,TD_LIGHT_ENGL/data.velocity_factor);
      central_log->add_line(pWork);
      central_log->add_line(" ");
              Fl::check();
}
