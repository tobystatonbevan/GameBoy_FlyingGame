#include <gb/gb.h>
#include <stdio.h>
#include "arrow.c"
#include "arrowmap.c"
#include "citymaptiles.c"

void main(void)
{
    //background
    set_bkg_data(0,10,citymaptextures);
    set_bkg_tiles(0,0,40,36,citymap);
    SHOW_BKG;
    DISPLAY_ON;
    
    //sprites
    UINT8 currentspriteindex = 0;
    int counter = 0;
    set_sprite_data(0,4,Arrow);
    set_sprite_tile(0,0);
    move_sprite(0,88,78);
    SHOW_SPRITES;

    while (1)
    {
        while (counter <= 5){
            //sets to up on first run and as is on subsequent runs
            set_sprite_tile(0, currentspriteindex);
            //sets and moves down
            currentspriteindex = 1;
            set_sprite_tile(0, currentspriteindex);
            scroll_sprite(0,0,10);
            delay(100);
            //sets and moves left
            currentspriteindex = 2;
            set_sprite_tile(0, currentspriteindex);
            scroll_sprite(0,-10,0);
            delay(100);
            //sets and moves up
            currentspriteindex = 0;
            set_sprite_tile(0, currentspriteindex);
            scroll_sprite(0,0,-10);
            delay(100);
            //sets and moves right
            currentspriteindex = 3;
            set_sprite_tile(0, currentspriteindex);
            scroll_sprite(0,10,0);
            delay(100);
            counter = counter + 1;
        }
        switch(joypad()){
            case J_LEFT:
                currentspriteindex = 2;
                set_sprite_tile(0, currentspriteindex);
                //scroll_sprite(0,-10,0);
                scroll_bkg(-8,0);
                break;
            case J_RIGHT:
                currentspriteindex = 3;
                set_sprite_tile(0, currentspriteindex);
                //scroll_sprite(0,10,0);
                scroll_bkg(8,0);
                break;
            case J_DOWN:
                currentspriteindex = 1;
                set_sprite_tile(0, currentspriteindex);
                //scroll_sprite(0,0,10);
                scroll_bkg(0,8);
                break;
            case J_UP:
                currentspriteindex = 0;
                set_sprite_tile(0, currentspriteindex);
                //scroll_sprite(0,0,-10);
                scroll_bkg(0,-8);
                break;
        } 
        delay(100);  
    }
    
}

