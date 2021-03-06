#include <pokeagb/pokeagb.h>
#include "../portraits.h"


// portait positions for portrait player (pp) and portait opponent (po)
#define pp_x 20
#define po_x 220
#define p_y 20 // player and opponent portaits are on same Y position

// player portrait 64x64 square OAM, high priority, normal
const struct OamData portrait_player =  {
                                        .y = 0,
                                        .affine_mode = 0,
                                        .obj_mode = 0,
                                        .mosaic = 0,
                                        .bpp = 0,
                                        .shape = 0,
                                        .x = 0,
                                        .matrix_num = 0,
                                        .h_flip = 1,
                                        .v_flip = 0,
                                        .size = 3,
                                        .tile_num = 0,
                                        .priority = 0,
                                        .palette_num = 0,
                                        .affine_param = 0
};

// same as player's portait, except it's flipped
const struct OamData portrait_opponent =  {
                                        .y = 0,
                                        .affine_mode = 0,
                                        .obj_mode = 0,
                                        .mosaic = 0,
                                        .bpp = 0,
                                        .shape = 0,
                                        .x = 0,
                                        .matrix_num = 0,
                                        .h_flip = 0,
                                        .v_flip = 0,
                                        .size = 3,
                                        .tile_num = 0,
                                        .priority = 0,
                                        .palette_num = 0,
                                        .affine_param = 0
};

static const struct Frame (**nullframe)[] = (const struct Frame (**)[])0x8231CF0;
static const struct RotscaleFrame (**nullrsf)[] = (const struct RotscaleFrame (**)[])0x8231CFC;

void draw_portraits(u16 species_p, u16 species_o) {
        u16 player_species = species_p;
        u16 opp_species = species_o;
        
        // tile data
        struct SpriteTiles face_tiles_player = {NULL, 0x800, player_species};
        struct SpriteTiles face_tiles_opponent = {NULL, 0x800, opp_species}; 
        face_tiles_player.data = portraits_tiles[player_species];
        face_tiles_opponent.data = portraits_tiles[opp_species];
        
        // pal data
        struct SpritePalette face_pal_player = {portraits_pals[player_species], player_species};
        struct SpritePalette face_pal_opponent = {portraits_pals[opp_species], opp_species};
         
        // obj templates make
        struct Template face_temp_player = {
                                        player_species, player_species, &portrait_player, 
                                        nullframe, 0x0, nullrsf, (ObjectCallback)0x800760D
        };
        struct Template face_temp_opponent = {
                                        opp_species, opp_species, &portrait_opponent, 
                                        nullframe, 0x0, nullrsf, (ObjectCallback)0x800760D
        };
        
        // commit structs to memory
        gpu_tile_obj_decompress_alloc_tag_and_upload(&face_tiles_player);
        gpu_tile_obj_decompress_alloc_tag_and_upload(&face_tiles_opponent);
        gpu_pal_obj_alloc_tag_and_apply(&face_pal_player);
        gpu_pal_obj_alloc_tag_and_apply(&face_pal_opponent);
        
        // init objects
        template_instanciate_forward_search(&face_temp_opponent, po_x, p_y, 0x0);
        template_instanciate_forward_search(&face_temp_player, pp_x, p_y, 0x0);
}



