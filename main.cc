/* Local Includes */
#include "Game.h"

int main()
{
    /* Hide blinking cursor */
    fprintf(stderr, "\e[?25l");

    /* Clear the screen */
    printf("\e[1;1H\e[2J");

    /*
     * NOTE:
     * - Full screen terminal is 204 across.
     * - Full screen terminal is 60 down.
    */

    /* Seed random number generator */
    srand(time(0));

    /* Allocate memory for the game object and game timer */
    Game* game = new Game();

    /* Initialise the game object and game timer object */
    game->Initialise();

    /* Used to exit the game */
    bool playing = true;

    /* Main game loop */
    while(true == playing)
    {
        /* Update the game */
        game->Update();

        /* Draw the objects that the game contains */
        game->Draw();

        /* Check if the game has ended */
        playing = game->GetIsPlaying();
    }

    /* Clean up everything when we're done playing */
    delete(game);

    return(0);
}
