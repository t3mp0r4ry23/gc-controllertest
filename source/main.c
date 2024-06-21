//based off of the grrlib template code, hence the inconsistent formatting for comments
//also borrows code from the examples, i'm still learning, but i've tried to ensure i understand anything i put in here
#include <grrlib.h>
#include <ogcsys.h>
#include <gccore.h>
#include <stdio.h>
#include <stdlib.h>
//font data
#include "font_png.h"

int main(int argc, char **argv) {
    // Initialise the Graphics & Video subsystem
    GRRLIB_Init();

    // Initialise the GameCube controllers
    PAD_Init();


    //load font
    GRRLIB_texImg *tex_font = GRRLIB_LoadTexture(font_png);
    GRRLIB_InitTileSet(tex_font, 8, 8, 32);
    
    // Loop forever
    while(1) {
        PAD_ScanPads(); // Scan the GameCube controllers

        //put our analog and button values into nifty little variables because it makes the code look pretty :3
        int leftStickX = PAD_StickX(0);
        int leftStickY = PAD_StickY(0);
        int cStickX = PAD_SubStickX(0);
        int cStickY = PAD_SubStickY(0);
        int triggerL = PAD_TriggerL(0);
        int triggerR = PAD_TriggerR(0);
        int buttonsDown = PAD_ButtonsDown(0);
        int buttonsHeld = PAD_ButtonsHeld(0);

        //make the bg to catppuccin mocha base
        GRRLIB_SetBackgroundColour(0x1e, 0x1e, 0x2e, 0xFF);

        /* figure out something to do with this later
        //make our text and format it
        char msg[255];
        snprintf(msg, sizeof(msg), "Current Left Stick Coords: %d, %d", leftStickX, leftStickY);
        //draw our message
        GRRLIB_Printf(8, 8, tex_font, 0xcdd6f4ff, 2, msg);
        */

        //draw rectangles for the triggers
        GRRLIB_Rectangle(64, 96, 32, -64 + triggerL / 8, 0xcdd6f4ff, buttonsHeld & PAD_TRIGGER_L);
        GRRLIB_Rectangle(544, 96, 32, -64 + triggerR / 8, 0xcdd6f4ff, buttonsHeld & PAD_TRIGGER_R);

        //draw a visual of the left stick position
        GRRLIB_Line(160, 160, leftStickX / 4 + 160, -leftStickY / 4 + 160, 0xcdd6f4ff);
        GRRLIB_Circle(leftStickX / 4 + 160, -leftStickY / 4 + 160, 16, 0xcdd6f4ff, 1);
        GRRLIB_Rectangle(128, 128, 64, 64, 0xcdd6f4ff, 0);

        //draw a visual of the c-stick position
        GRRLIB_Line(384, 256, cStickX / 4 + 384, -cStickY / 4 + 256, 0xfab387ff);
        GRRLIB_Circle(cStickX / 4 + 384, -cStickY / 4 + 256, 12, 0xf9e2afff, 1);
        GRRLIB_Rectangle(352, 224, 64, 64, 0xf9e2afff, 0);

        GRRLIB_Render(); // Render the frame buffer to the TV
    }
    return 0;
}
