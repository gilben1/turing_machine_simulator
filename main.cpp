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

    /*WINDOW *menu_win;
    int menux = 0;
    int menuy = 0;
    int menuwidth = 0;
    int menuheight = 0;

    WINDOW *disp_win;
    int dispx = 0;
    int dispy = 0;
    int dispwidth = 0;
    int dispheight = 0;*/
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
        print_menu(menu_win, highlight, choices);
        while (choice != 7)
        {
            c = wgetch(menu_win.window);
            switch(c)
            {
                case KEY_UP:
                    if (highlight == 1)
                        highlight == choices.size();
                    else
                        --highlight;
                    break;
                case KEY_DOWN:
                    if (highlight == choices.size())
                        highlight = 1;
                    else
                        ++highlight;
                    break;
                case 10:
                    choice = highlight;
                    break;
                default:
                    mvprintw(24, 0, "Character pressed is = %3d Hopefully it can be printed as '%c'", c, c);
                    refresh();
                    break;
            }
            print_menu(menu_win, highlight, choices);
            if (choice != 0)
                break;
        }

        //mvprintw(menuy + HEIGHT, 0, "You chose choice %d with choice string %s\n", choice, choices[choice - 1].c_str());

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
                    select_start(tm);
                    tm.display_tape();
                    choice = 0;
                    break;
                }
            case 6:
                {
                    if (tm.process_tape())
                        cout << "Halt and accept\n";
                    else
                        cout << "Halt and reject\n";
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
        refresh();
        c = wgetch(menu_win.window);
        wclear(menu_win.window);
    }
    endwin();
    /*
       cout << "Welcome to the near useless turing machine simulator!\n";
       int resp = 0;
    // Menu loop
    do
    {
    cout << "Please select what you would like to do:\n";
    cout << "\t1 - Load a machine from file\n";
    cout << "\t2 - Display the states of the machine\n";
    cout << "\t3 - Build the infinite tape\n";
    cout << "\t4 - Display the current tape\n";
    cout << "\t5 - Select the start position of the tapehead\n";
    cout << "\t6 - Process the input\n";
    cout << "\tOr, any other input to exit the program\n";
    cin >> resp;
    cin.ignore();
    switch(resp)
    {
    case 1:
    load_machine(tm);
    tm.display_states();
    break;
    case 2:
    tm.display_states();
    break;
    case 3:
    build_tape(tm);
    tm.display_tape();
    break;
    case 4:
    tm.display_tape();
    break;
    case 5:
    select_start(tm);
    tm.display_tape();
    break;
    case 6:
    if (tm.process_tape())
    cout << "Halt and accept\n";
    else
    cout << "Halt and reject\n";
    break;
    default:
    cout << "See ya\n";
    break;
    }
    }
    while (resp > 0 && resp < 7);*/
    return 1;
}
