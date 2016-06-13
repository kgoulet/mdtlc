// the link between the non-gui atlc and the gui
//
#include "definitions_glo.h"

extern double **Vij;
extern double **Er;
extern unsigned char **oddity; 
extern unsigned char **cell_type; 
extern unsigned char **cell_dielectric;  // mdtlc addition
extern unsigned char *image_data;
extern int width;
extern int height;
extern double* pVodd;
extern double* pVeven;



extern struct pixels Er_in_bitmap[MAX_DIFFERENT_PERMITTIVITIES];
extern struct pixels Er_on_command_line[MAX_DIFFERENT_PERMITTIVITIES];

extern struct transmission_line_properties data;

int main2(char* p_test_file_name , unsigned char* bitmap , int w , int h,
     double* Vodd , double* Veven);
void find_maximum_values(struct max_values *maximum_values, int zero_elementsQ);
double find_Ex(int w, int h) ;
double find_Ey(int w, int h);
double find_E(int w, int h);
double voltage_ij(int i, int j);
double find_energy_per_metre(int i, int j);
