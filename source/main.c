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

    //initalize some nifty variables to make our lives easier
    int playerNum = 0;
    int leftStickX;
    int leftStickY;
    int cStickX;
    int cStickY;
    int triggerL;
    int triggerR;
    int buttonsHeld;

    // Loop forever
    while(1) {
        PAD_ScanPads(); // Scan the Gamecube controllers

        //check for a reason to switch which controller we're reading inputs from
        for (int i = 0; i < 4; i++) {
            if (PAD_ButtonsDown(i)) {
                playerNum = i;
                break;
            } else {
                continue;
            }
        }

        //put our analog and button values into our vars
        leftStickX = PAD_StickX(playerNum);
        leftStickY = PAD_StickY(playerNum);
        cStickX = PAD_SubStickX(playerNum);
        cStickY = PAD_SubStickY(playerNum);
        triggerL = PAD_TriggerL(playerNum);
        triggerR = PAD_TriggerR(playerNum);
        buttonsHeld = PAD_ButtonsHeld(playerNum);

        //make the bg to catppuccin mocha base
        GRRLIB_SetBackgroundColour(0x1e, 0x1e, 0x2e, 0xFF);

        //make our text and format it
        char msg[32];
        snprintf(msg, sizeof(msg), "Current Controller: %d", playerNum + 1);
        //draw our message
        GRRLIB_Printf(64, 384, tex_font, 0xcdd6f4ff, 2, msg);

        //draw rectangles for the triggers
        GRRLIB_Rectangle(64, 96, 32, -64 + triggerL / 8, 0xcdd6f4ff, (buttonsHeld & PAD_TRIGGER_L) != 0);
        GRRLIB_Rectangle(544, 96, 32, -64 + triggerR / 8, 0xcdd6f4ff, (buttonsHeld & PAD_TRIGGER_R) != 0);
        GRRLIB_Rectangle(448, 96, 64, -16, 0xb4befeff, (buttonsHeld & PAD_TRIGGER_Z) != 0);

        //draw a visual of the left stick position
        GRRLIB_Line(160, 160, leftStickX / 4 + 160, -leftStickY / 4 + 160, 0xcdd6f4ff);
        GRRLIB_Circle(leftStickX / 4 + 160, -leftStickY / 4 + 160, 16, 0xcdd6f4ff, 1);
        GRRLIB_Rectangle(128, 128, 64, 64, 0xcdd6f4ff, 0);

        //draw a visual of the c-stick position
        GRRLIB_Line(416, 256, cStickX / 4 + 416, -cStickY / 4 + 256, 0xfab387ff);
        GRRLIB_Circle(cStickX / 4 + 416, -cStickY / 4 + 256, 12, 0xf9e2afff, 1);
        GRRLIB_Rectangle(384, 224, 64, 64, 0xf9e2afff, 0);

        //draw a visual of the primary face buttons
        GRRLIB_Circle(320, 176, 4, 0xcdd6f4ff, (buttonsHeld & PAD_BUTTON_START) != 0);
        GRRLIB_Circle(480, 160, 16, 0xa6e3a1ff, (buttonsHeld & PAD_BUTTON_A) != 0);
        GRRLIB_Circle(456, 184, 8, 0xf38ba8ff, (buttonsHeld & PAD_BUTTON_B) != 0);
        GRRLIB_Rectangle(504, 144, 8, 32, 0xcdd6f4ff, (buttonsHeld & PAD_BUTTON_X) != 0);
        GRRLIB_Rectangle(464, 128, 32, 8, 0xcdd6f4ff, (buttonsHeld & PAD_BUTTON_Y) != 0);

        //draw a visual of the d-pad
        GRRLIB_Rectangle(192, 248, 40, 16, 0xcdd6f4ff, (buttonsHeld & PAD_BUTTON_LEFT) != 0);
        GRRLIB_Rectangle(216, 248, 40, 16, 0xcdd6f4ff, (buttonsHeld & PAD_BUTTON_RIGHT) != 0);
        GRRLIB_Rectangle(216, 224, 16, 40, 0xcdd6f4ff, (buttonsHeld & PAD_BUTTON_UP) != 0);
        GRRLIB_Rectangle(216, 248, 16, 40, 0xcdd6f4ff, (buttonsHeld & PAD_BUTTON_DOWN) != 0);

        GRRLIB_Render(); // Render the frame buffer to the TV
    }
    return 0;
}
