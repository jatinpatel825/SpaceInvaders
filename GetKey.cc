#include "GetKey.h"

void nonblock(int state)
{
    struct termios ttystate;

    //get the terminal state
    tcgetattr(STDIN_FILENO, &ttystate);

    if (state==NB_ENABLE)
    {
        //turn off canonical mode
        ttystate.c_lflag &= ~ICANON;
        //minimum of number input read.
        ttystate.c_cc[VMIN] = 1;
    }
    else if (state==NB_DISABLE)
    {
        //turn on canonical mode
        ttystate.c_lflag |= ICANON;
    }
    //set the terminal attributes.
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}

/* Default Constructor */
GetKey::GetKey()
{
    nonblock(NB_ENABLE);
}

/* Default Destructor */
GetKey::~GetKey()
{
    nonblock(NB_DISABLE);
}

int GetKey::kbhit()
{
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds); //STDIN_FILENO is 0
    select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}

KEY GetKey::GetKeyPress()
{
    int input = 0;
    int res = this->kbhit();

    if(res != 0)
    {
        input = fgetc(stdin);
    }

    switch(input)
    {
        case 10:
            return KEY::KEY_ENTER;

        case 127:
            return KEY::KEY_BACKSPACE;

        case 49:
            return KEY::KEY_ONE;

        case 50:
            return KEY::KEY_TWO;

        case 119:
        case 65:
            return KEY::KEY_UP;

        case 115:
        case 66:
            return KEY::KEY_DOWN;

        case 100:
        case 67:
            return KEY::KEY_RIGHT;

        case 97:
        case 68:
            return KEY::KEY_LEFT;

        default:
        {
            // Do nothing
        }
    }

    return KEY::KEY_INVALID;
}

int GetKey::Getch() const
{
    // https://ubuntuforums.org/showthread.php?t=554845
    int c=0;
    struct termios org_opts, new_opts;
    int res=0;
    //-----  store old settings -----------
    res=tcgetattr(STDIN_FILENO, &org_opts);
    assert(res==0);

    //---- set new terminal parms --------
    memcpy(&new_opts, &org_opts, sizeof(new_opts));
    new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
    c=getchar();

    //------  restore old settings ---------
    res=tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);
    assert(res==0);
    return(c);
}
