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
#include "tm.h"
#include <ncurses.h>


struct WIN
{
    WIN();
    WINDOW * window;
    int x;
    int y;
    int width;
    int height;
};
void load_machine(turing_machine & tm, WIN & current_win);
void display_states(turing_machine & tm, WIN & current_win);
void build_tape(turing_machine & tm);
void select_start(turing_machine & tm);

void print_menu(WIN & menu_win, int highlight, vector<string> & choices);
void print_string_vector(WIN & current_win, vector<string> & output);
void print_string(WIN & current_win, string & output);

string user_get(WIN & current_win, int & line, const string prompt);
