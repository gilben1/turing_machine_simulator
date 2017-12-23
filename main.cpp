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
    int startx = 0;
    int starty = 0;

    /*char * choices[] = {
        "Choice 1",
        "Choice 2",
        "Choice 3",
        "Choice 4",
        "Exit",
    };*/
    vector<string> choices;
    choices.push_back("Load a machine from file");
    choices.push_back("Display states of the machine");
    choices.push_back("Build the infinite tape");
    choices.push_back("Display the current tape");
    choices.push_back("Select the start position of the tapehead");
    choices.push_back("Process the input");
    choices.push_back("Exit");
    //int n_choices = sizeof(choices) / sizeof(char *);

    WINDOW *menu_win;
    int highlight = 1;
    int choice = 0;
    int c;

    initscr();
    clear();
    noecho();
    cbreak();
    startx = (COLS - WIDTH) / 2;
    starty = (LINES - HEIGHT) / 2;

    menu_win = newwin(HEIGHT, WIDTH, starty, startx);
    keypad(menu_win, TRUE);
    mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
    refresh();
/*
    vector<string> output;

    output.push_back("Hi,");
    output.push_back("My");
    output.push_back("Name");
    output.push_back("Is");
    output.push_back("...");
    output.push_back("...");
    output.push_back("...");
    output.push_back("...what?");

    print_string_vector(menu_win, output);
    clrtoeol();
    refresh();
*/


    print_menu(menu_win, highlight, choices);
    while (1)
    {
        c = wgetch(menu_win);
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

        mvprintw(starty + HEIGHT, 0, "You chose choice %d with choice string %s\n", choice, choices[choice - 1].c_str());

        switch(choice)
        {
            case 1:
                load_machine(tm, menu_win);
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

    clrtoeol();
    refresh();
    c = wgetch(menu_win);
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
