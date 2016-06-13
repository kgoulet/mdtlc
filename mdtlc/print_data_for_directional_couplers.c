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
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
// direct output to the browser log defined at main level
#include "mdtlc.h"  

#include "definitions.h"

/* The following simple function just prints data into a file, or if
fp-stout, to the screen. Depending on whether the dielectric is mixed or
not, it is or is not possible to quote a value for Er. If Er is passed
as a mumber < 0, this function interprets that as meaning that the
dielectric is mixed, and says 'Er= MIXED' */

void print_data_for_directional_couplers(struct transmission_line_properties data, FILE *where_to_print_fp, char *inputfile_name)
{
     char pWork[512];
  if(data.display==Z_ODD_SINGLE_DIELECTRIC)
  {
  Fl::check();
//    if(data.verbose_level ==1)
//      fprintf(where_to_print_fp,"%s 3 Er_odd= %6.2f Er_even= %s Zodd= %7.3f Zeven= %s Zo= %s Zdiff= %6.2f Zcomm= %s Ohms VERSION=%s\n",inputfile_name,data.Er_odd, "??????", data.Zodd, "??????","??????",data.Zdiff, "??????", PACKAGE_VERSION);
//    else if (data.verbose_level >=2)
//      fprintf(where_to_print_fp,"%s 3 Er_odd= %6.2f Er_even= %s Zodd= %7.3f Zeven= %s Zo= %s Zdiff= %6.2f Zcomm= %s Ohms VERSION=%s\n",inputfile_name,data.Er_odd, "??????", data.Zodd, "??????","??????",data.Zdiff, "??????", PACKAGE_VERSION);
  }
  else if(data.display == Z_EVEN_SINGLE_DIELECTRIC)
  {
    if(data.verbose_level ==1) 
//      fprintf(where_to_print_fp,"%s 3 Er_odd= %7.3f Er_even= %7.3f Zodd= %7.3f Zeven= %7.3f Zo= %7.3f Zdiff= %7.3f Zcomm= %7.3f Ohms VERSION=%s\n",inputfile_name,data.Er_odd, data.Er_even, data.Zodd, data.Zeven, data.Zo,data.Zdiff, data.Zcomm, PACKAGE_VERSION);
//    else if (data.verbose_level >=2)
//      fprintf(where_to_print_fp,"%s 3 Er_odd= %7.3f Er_even= %7.3f Zodd= %7.3f Zeven= %7.3f Zo= %7.3f Zdiff= %7.3f Zcomm= %7.3f Ohms VERSION=%s\n",inputfile_name,data.Er_odd, data.Er_even, data.Zodd, data.Zeven, data.Zo,data.Zdiff, data.Zcomm, PACKAGE_VERSION);
        {
        Fl::check();
        central_log->add_line(" ");
      central_log->add_line(" DC resistance by pixel count:");
      sprintf(pWork, " Rdc_trace_1= %7.3f     Rdc_trace_2 = %7.3f milliohm/in",1000*67.87/data.pixels_positive,1000*67.87/data.pixels_negative);
      central_log->add_line(pWork);        
      sprintf(pWork, " C_odd      = %7.3f pF/in    C_even = %7.3f pF/in",data.Codd*1e12/39.37,data.Ceven*1e12/39.37);
      central_log->add_line(pWork);
      sprintf(pWork, " Er_odd     = %7.3f         Er_even = %7.3f",data.Er_odd,data.Er_even);
      central_log->add_line(pWork);
      sprintf(pWork, " Loss_tan_o = %6.5f     Loss_tan_e  = %6.5f  ",data.loss_tan_o,data.loss_tan_e);
      central_log->add_line(pWork);
      sprintf(pWork, " Delay_odd  = %7.3f      Delay_even = %7.3f  ps/in.",TD_LIGHT_ENGL*sqrt(data.Er_odd),
                     TD_LIGHT_ENGL*sqrt(data.Er_even));
      central_log->add_line(pWork);
      sprintf(pWork, " Z_diff     = %7.3f  ohms   Z_comm  = %7.3f  ohms",data.Zdiff,data.Zcomm);
      central_log->add_line(pWork);

      central_log->add_line(" ");
              Fl::check();
      }
       
  }
//  system("PAUSE");
}
