#include <gb/gb.h>
#include <stdio.h>
#include <stdint.h>
#include <gbdk/font.h>
#include "arrow.c"
#include "arrowmap.c"
#include "citymaptiles.c"
#include "windowmap.c"

uint8_t playerLocation[2];
int8_t backgroundLocation[2];
int8_t gravity = -1;
int8_t fallSpeed = 0;

void efficientDelay(uint8_t loops){
    uint8_t i;
    for (i=0; i<loops;i++){
        wait_vbl_done();
    }
}

int CheckSpriteBoundaryX(uint8_t x) {
    if (x > 160) {
        return 160;
    } else if (x < 10) {
        return 10;
    } else {
        return x;
    }
        
}
int CheckSpriteBoundaryY(uint8_t y) {
    if (y > 125){
        return 125;
    } else if (y < 20) {
        return 20;
    } else {
        return y;
    }
}

int CheckBackgroundBoundaryX(uint8_t x) {
    if (x > 100) {
        return 100;
    } else if (x < 20) {
        return 20;
    } else {
        return x;
    }
        
}
int CheckBackgroundBoundaryY(int8_t y) {
    if (y > 80){
        return 80;
    } else if (y < 1) {
        return 1;
    } else {
        return y;
    }
}

void main(void)
{
    //init font
    font_t min_font;
    font_init();
    min_font = font_load(font_min);
    font_set(min_font);
    
    //background
    set_bkg_data(37,10,citymaptextures);
    backgroundLocation[0] = 0;
    backgroundLocation[1] = 0;
    set_bkg_tiles(backgroundLocation[0],backgroundLocation[1],40,36,citymap);
    SHOW_BKG;
    DISPLAY_ON;

    //window
    set_win_tiles(0,0,16,1,windowmap);
    SHOW_WIN;
    move_win(7,135);

    //sprites
    uint8_t currentspriteindex = 26;
    int counter = 0;
    set_sprite_data(26,8,Arrow);
    set_sprite_tile(0,0);
    playerLocation[0] = 88;
    playerLocation[1] = 78;
    move_sprite(0,playerLocation[0],playerLocation[1]);
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
            efficientDelay(10);
            //sets and moves left
            currentspriteindex = 28;
            set_sprite_tile(0, currentspriteindex);
            scroll_sprite(0,-10,0);
            efficientDelay(10);
            //sets and moves up
            currentspriteindex = 26;
            set_sprite_tile(0, currentspriteindex);
            scroll_sprite(0,0,-10);
            efficientDelay(10);
            //sets and moves right
            currentspriteindex = 29;
            set_sprite_tile(0, currentspriteindex);
            scroll_sprite(0,10,0);
            efficientDelay(10);
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
            efficientDelay(10);
            counter++;
        }
        currentspriteindex = 6;
        switch(joypad()){
            case J_LEFT:
                currentspriteindex = 32;
                set_sprite_tile(0, currentspriteindex);
                playerLocation[0] -= 5;
                playerLocation[0] = CheckSpriteBoundaryX(playerLocation[0]);
                move_sprite(0,playerLocation[0],playerLocation[1]);
                backgroundLocation[0] -= 8;
                move_bkg(backgroundLocation[0],backgroundLocation[1]);
                break;
            case J_RIGHT:
                currentspriteindex = 33;
                set_sprite_tile(0, currentspriteindex);
                playerLocation[0] += 5;
                playerLocation[0] = CheckSpriteBoundaryX(playerLocation[0]);
                move_sprite(0,playerLocation[0],playerLocation[1]);
                backgroundLocation[0] += 8;
                move_bkg(backgroundLocation[0],backgroundLocation[1]);
                break;
            case J_DOWN:
                currentspriteindex = 31;
                set_sprite_tile(0, currentspriteindex);
                playerLocation[1] += 5;
                playerLocation[1] = CheckSpriteBoundaryY(playerLocation[1]);
                move_sprite(0,playerLocation[0],playerLocation[1]);
                backgroundLocation[1] += 8;
                backgroundLocation[1] = CheckBackgroundBoundaryY(backgroundLocation[1]);
                move_bkg(backgroundLocation[0],backgroundLocation[1]);
                break;
            case J_UP:
                currentspriteindex = 30;
                set_sprite_tile(0, currentspriteindex);
                playerLocation[1] -= 5;
                playerLocation[1] = CheckSpriteBoundaryY(playerLocation[1]);
                move_sprite(0,playerLocation[0],playerLocation[1]);
                backgroundLocation[1] -= 8;
                backgroundLocation[1] = CheckBackgroundBoundaryY(backgroundLocation[1]);
                move_bkg(backgroundLocation[0],backgroundLocation[1]);
                fallSpeed = 0;
                break;
            default: 
                currentspriteindex = 33;
                set_sprite_tile(0, currentspriteindex);
                if (fallSpeed < -5) {
                    fallSpeed = -5;
                }
                fallSpeed += gravity;
                playerLocation[1] -= fallSpeed;
                playerLocation[1] = CheckSpriteBoundaryY(playerLocation[1]);
                move_sprite(0,playerLocation[0],playerLocation[1]);
                backgroundLocation[1] += 8;
                backgroundLocation[1] = CheckBackgroundBoundaryY(backgroundLocation[1]);
                backgroundLocation[0] += 4;
                move_bkg(backgroundLocation[0],backgroundLocation[1]);
        } 
    
        scroll_bkg(10,0);
        efficientDelay(10); 
    }
    
}

