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

void load_machine(turing_machine & tm);
void build_tape(turing_machine & tm);
void select_start(turing_machine & tm);

void print_menu(WINDOW *menu_win, int highlight, vector<string> & choices);
void print_string_vector(WINDOW *current_win, vector<string> & output);
