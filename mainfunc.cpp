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

/*
 * Loads machine from file based on user input
 */
void load_machine(turing_machine & tm)
{
    cout << "Enter the name of the file you'd like to load:\n";
    char input[1000];
    cin.get(input, 1000, '\n');
    cin.ignore(1000, '\n');

    tm.read_from_file(input);
}

/*
 * Builds the tape in the machine based on user input
 */
void build_tape(turing_machine & tm)
{
    cout << "Enter the string you'd like to process:\n";
    char input[1000];
    cin.get(input, 1000, '\n');
    cin.ignore(1000, '\n');

    tm.build_tape(input);
}

/*
 * Menu for selecting the start position of the tapehead
 */
void select_start(turing_machine & tm)
{
    int resp = 0;
    cout << "Select the start position for the tapehead:\n";
    cout << "\t1 - Blank on LHS\n";
    cout << "\t2 - First character of LHS\n";
    cout << "\t3 - Blank on RHS\n";
    cout << "\t4 - First character on RHS\n";

    cin >> resp;
    cin.ignore();
    switch(resp)
    {
        case 1:
            tm.start_pos(true, true);
            break;
        case 2:
            tm.start_pos(true, false);
            break;
        case 3:
            tm.start_pos(false, true);
            break;
        case 4:
            tm.start_pos(false, false);
            break;
        default:
            cout << "No start position selected\n";
            break;
    }
}
void print_menu(WINDOW *menu_win, int highlight, char *choices[], int n_choices)
{
    int x, y, i;

    x = 2;
    y = 2;
    box(menu_win, 0, 0);
    for(i = 0; i < n_choices; ++i)
    {   if(highlight == i + 1) /* High light the present choice */
        {   wattron(menu_win, A_REVERSE); 
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        }
        else
            mvwprintw(menu_win, y, x, "%s", choices[i]);
        ++y;
    }
    wrefresh(menu_win);
}
