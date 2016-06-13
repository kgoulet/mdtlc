#ifndef output_bmp_h
#define output_bmp_h


extern unsigned char* output_odd_bmp;
extern double* Vodd;
extern double* Veven;

int              ob_allocate();
int              ob_draw();
int              ob_draw_even();
#endif
