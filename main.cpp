/*
 * turing_machine simulation program
 *
 * Created by Nicholas Gilbert (nickgilbert2@gmail.com)
 *
 * A program that simulates the running of an infinite tape turing machine
 * based on parsed text files.
 *
 * Input to the tape can be manipulated, and the processing of the input is
 * shown in steps to simulate the position of the tapehead as it processes input
 */
#include "main.h"

const int WIDTH = 100;
const int HEIGHT = 40;

int main()
{
    turing_machine tm;

    vector<string> choices;
    choices.push_back("Load a machine from file");
    choices.push_back("Display states of the machine");
    choices.push_back("Build the infinite tape");
    choices.push_back("Display the current tape");
    choices.push_back("Select the start position of the tapehead");
    choices.push_back("Process the input");
    choices.push_back("Exit");

    WIN menu_win;
    WIN disp_win;

    int highlight = 1;
    int choice = 0;
    int c;

    initscr();
    clear();
    noecho();
    cbreak();

    menu_win.x = 2;
    menu_win.y = 2;
    menu_win.width = COLS / 4;
    menu_win.height = LINES / 4;

    disp_win.x = menu_win.x + menu_win.width;
    disp_win.y = 2;

    disp_win.width = COLS / 3;
    disp_win.height = LINES / 2;

    menu_win.window = newwin(menu_win.height, menu_win.width, menu_win.y, menu_win.x);
    keypad(menu_win.window, TRUE);
    
    disp_win.window = newwin(disp_win.height, disp_win.width, disp_win.y, disp_win.x);

    mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
    refresh();


    while (choice != 7)
    {
        prompt_menu(menu_win, highlight, choices, choice, c, 2);

        switch(choice)
        {
            case 1:
                {
                    load_machine(tm, disp_win);
                    display_states(tm, disp_win);
                    choice = 0;
                    break;
                }
            case 2:
                {
                    display_states(tm, disp_win);
                    choice = 0;
                    break;
                }
            case 3:
                {
                    build_tape(tm, disp_win);
                    display_tape(tm, disp_win);
                    choice = 0;
                    break;
                }
            case 4:
                {
                    display_tape(tm, disp_win);
                    choice = 0;
                    break;
                }
            case 5:
                {
                    select_start(tm, menu_win);
                    //tm.display_tape();
                    display_tape(tm, disp_win);
                    choice = 0;
                    break;
                }
            case 6:
                {
                    process_tape(tm, disp_win);
                    choice = 0;
                    break;
                }
            case 7:
                {
                    cout << "See ya\n";
                    break;
                }
        }

        clrtoeol();
        werase(menu_win.window);
    }
    endwin();
    return 1;
}
