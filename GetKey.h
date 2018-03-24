// https://ubuntuforums.org/showthread.php?t=554845
/*================================================*/
#include <termios.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
/*================================================*/

#include <stdio.h>
#define NB_DISABLE 0
#define NB_ENABLE 1

#include <iostream>

enum KEY
{
    KEY_UP = 65,
    KEY_DOWN = 66,
    KEY_LEFT = 68,
    KEY_RIGHT = 67,
    KEY_ENTER = 10,
    KEY_BACKSPACE = 127,
    KEY_ONE = 49,
    KEY_TWO = 50,
    KEY_INVALID = 0
};

class GetKey
{
    /* Member functions */
public:
    GetKey();
    ~GetKey();

    KEY GetKeyPress();
    int kbhit();

protected:

private:
    int Getch() const;

    /* Member variables*/
public:
protected:
private:
};
