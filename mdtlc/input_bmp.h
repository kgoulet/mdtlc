#ifndef input_bmp_h
#define input_bmp_h

//
//
// Functions to create the bitmap from the input dimensions provided.
//
//

#define COLOR_CU_GND {0x00,0xff,0x00}
#define COLOR_CU_POS {0xFF,0x00,0x00}
#define COLOR_CU_NEG {0x00,0x00,0Xff}
#define COLOR_AIR    {0xff,0xff,0xfe}
#define COLOR_SMT     {0x00,0xaf,0x1f}
#define COLOR_SMB     {0x00,0xaf,0x1e}
#define COLOR_FILL_RES {0xd3,0xd3,0x69}
#define COLOR_RES1    {0xc8,0xc8,0x64}
#define COLOR_GLA1    {0xff,0xef,0x7f}
#define COLOR_RES2    {0xc8,0xc8,0x65}
#define COLOR_GLA2    {0xff,0xef,0x80}

#define MAX_LAYERS 10

// UPDATE MAX_MATERIALS AS MATERIALS ARE ADDED
#define MAX_MATERIALS 11
#define MATERIAL_AIR       1
#define MATERIAL_SMT       2
#define MATERIAL_CU_GND    3
#define MATERIAL_CU_POS    4
#define MATERIAL_CU_NEG    5
#define MATERIAL_LAM1_RES  6
#define MATERIAL_LAM1_GLA  7
#define MATERIAL_FILL1_RES 8
#define MATERIAL_LAM2_RES  9
#define MATERIAL_LAM2_GLA  10
#define MATERIAL_SMB       11

// to simulate the layers if glass cloth, the weave is offset every other layer
#define GLA_LAYER_SWITCH 20
#define GLA_POROSITY 0.25
//extern  double material_er[MAX_MATERIALS];  // not really part of bitmap definition but
                                     // but put here for now

typedef struct  Material_rgb {
        unsigned char         red;
        unsigned char         green;
        unsigned char         blue;
        } Material_rgb;
        
extern    Material_rgb     material_color[MAX_MATERIALS];
extern int                material_count;
extern int                dielectric_count;
//extern    Material_rgb     color_value_cu_gnd ;
//extern    Material_rgb     color_value_cu_pos ;
//extern    Material_rgb     color_value_cu_neg ;
//extern    Material_rgb     color_value_air ;
//extern    Material_rgb     color_value_sm ;
//extern    Material_rgb     color_value_fill ;
//extern    Material_rgb     color_value_res ;
//extern    Material_rgb     color_value_gla ;

extern int air_top_pix;
extern int air_bot_pix;

extern int   vertical_pix;
extern int horizontal_pix;
extern unsigned char* input_bmp;
extern double  thou_per_pix;          // conversion factor may be variable in future

int              ib_initialize();
int              ib_allocate();
int              ib_draw();

#endif
