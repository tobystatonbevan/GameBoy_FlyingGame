#include <gb/gb.h>
#include <stdio.h>
#include <gbdk/font.h>
#include "arrow.c"
#include "arrowmap.c"
#include "citymaptiles.c"
#include "windowmap.c"

void main(void)
{
    //init font
    font_t min_font;
    font_init();
    min_font = font_load(font_min);
    font_set(min_font);
    
    //background
    set_bkg_data(37,10,citymaptextures);
    set_bkg_tiles(0,0,40,36,citymap);
    SHOW_BKG;
    DISPLAY_ON;

    //window
    set_win_tiles(0,0,16,1,windowmap);
    SHOW_WIN;
    move_win(7,135);

    //sprites
    UINT8 currentspriteindex = 26;
    int counter = 0;
    set_sprite_data(26,8,Arrow);
    set_sprite_tile(0,0);
    move_sprite(0,88,78);
    SHOW_SPRITES;

    while (1)
    {
        while (counter <= 4){
            //sets to up on first run and as is on subsequent runs
            set_sprite_tile(0, currentspriteindex);
            //sets and moves down
            currentspriteindex = 27;
            set_sprite_tile(0, currentspriteindex);
            scroll_sprite(0,0,10);
            delay(100);
            //sets and moves left
            currentspriteindex = 28;
            set_sprite_tile(0, currentspriteindex);
            scroll_sprite(0,-10,0);
            delay(100);
            //sets and moves up
            currentspriteindex = 26;
            set_sprite_tile(0, currentspriteindex);
            scroll_sprite(0,0,-10);
            delay(100);
            //sets and moves right
            currentspriteindex = 29;
            set_sprite_tile(0, currentspriteindex);
            scroll_sprite(0,10,0);
            delay(100);
            counter++;
        }
        //game start sound. Hex values can also be binary values (eg 0b10000000 instead of 0x80)
        NR52_REG = 0x80; //turns the sound on
        NR50_REG = 0x77; //sets volume for both to max
        NR51_REG = 0xFF; //enables all audio channels for both L and R
        if (counter == 5){
            //sound design in registers
            NR10_REG = 0x16;
            NR11_REG = 0x4F;
            NR12_REG = 0x73;
            NR13_REG = 0x00;
            NR14_REG = 0xC3;
            delay(100);
            counter++;
        }
        currentspriteindex = 6;
        switch(joypad()){
            case J_LEFT:
                currentspriteindex = 32;
                set_sprite_tile(0, currentspriteindex);
                //scroll_sprite(0,-10,0);
                scroll_bkg(-8,0);
                break;
            case J_RIGHT:
                currentspriteindex = 33;
                set_sprite_tile(0, currentspriteindex);
                //scroll_sprite(0,10,0);
                scroll_bkg(8,0);
                break;
            case J_DOWN:
                currentspriteindex = 31;
                set_sprite_tile(0, currentspriteindex);
                //scroll_sprite(0,0,10);
                scroll_bkg(0,8);
                break;
            case J_UP:
                currentspriteindex = 30;
                set_sprite_tile(0, currentspriteindex);
                //scroll_sprite(0,0,-10);
                scroll_bkg(0,-8);
                break;
        } 
        delay(100);  
    }
    
}

