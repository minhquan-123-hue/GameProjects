// Simple terminal Pong in C using ncurses
// Build: gcc pong.c -lncurses -o pong
// Run: ./pong

#include <ncurses.h>
#include <unistd.h>

#define DELAY 30000

int main()
{
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    int ball_x = max_x / 2;
    int ball_y = max_y / 2;
    int dir_x = 1;
    int dir_y = 1;

    int paddle_y = max_y / 2;
    int paddle_x = 2;

    while (1)
    {
        clear();

        // Draw paddle
        mvprintw(paddle_y - 1, paddle_x, "|");
        mvprintw(paddle_y, paddle_x, "|");
        mvprintw(paddle_y + 1, paddle_x, "|");

        // Draw ball
        mvprintw(ball_y, ball_x, "o");

        // Input
        int ch = getch();
        if (ch == 'q')
            break;
        if (ch == KEY_UP && paddle_y > 2)
            paddle_y--;
        if (ch == KEY_DOWN && paddle_y < max_y - 3)
            paddle_y++;

        // Ball movement
        ball_x += dir_x;
        ball_y += dir_y;

        // Collision with walls
        if (ball_y <= 0 || ball_y >= max_y - 1)
            dir_y = -dir_y;

        // Paddle collision
        if (ball_x == paddle_x + 1 && (ball_y >= paddle_y - 1 && ball_y <= paddle_y + 1))
        {
            dir_x = -dir_x;
        }

        // Missed ball
        if (ball_x <= 0)
        {
            ball_x = max_x / 2;
            ball_y = max_y / 2;
        }
        if (ball_x >= max_x - 1)
            dir_x = -dir_x;

        refresh();
        usleep(DELAY);
    }

    endwin();
    return 0;
}
