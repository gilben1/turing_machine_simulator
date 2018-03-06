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
 * 
 * turing_machine & tm => turing machine to use
 * WIN & current_win => Window to display to
 */
void load_machine(turing_machine & tm, WIN & current_win)
{
    current_win.current_line = 2;

    string input = user_get(current_win, "Enter the name of the file you'd like to load");

    string output = tm.read_from_file(input);
    if (output != "")
    {
        print_string(current_win, output, true);
    }
}

/*
 * Displays the states of the passed turing machine into the current window
 * 
 * turing_machine & tm => turing machine to use
 * WIN & current_win => Window to display to
 */
void display_states(turing_machine & tm, WIN & current_win)
{
    vector<string> output = tm.display_states();
    if (!output.empty())
        print_string_vector(current_win, output);
}

/*
 * Displays the tape of the turing machine in the window
 * 
 * turing_machine & tm => turing machine to use
 * WIN & current_win => Window to display to
 */
void display_tape(turing_machine & tm, WIN & current_win)
{
    vector<string> output = tm.display_tape();
    if (!output.empty())
        print_string_vector(current_win, output);
}

/*
 * Builds the tape in the machine based on user input
 * 
 * turing_machine & tm => turing machine to use
 * WIN & current_win => Window to display to
 */
void build_tape(turing_machine & tm, WIN & current_win)
{
    current_win.current_line = 2;

    string input = user_get(current_win, "Enter the string you'd like to parse");

    tm.build_tape(input);
}

/*
 * Menu for selecting the start position of the tapehead
 * 
 * turing_machine & tm => turing machine to use
 * WIN & current_win => Window to display to
 */
void select_start(turing_machine & tm, WIN & current_win)
{
    int resp = 0;

    current_win.current_line = 2;

    werase(current_win.window);
    box(current_win.window, 0, 0);

    mvwprintw(current_win.window, current_win.current_line++, 2, "%s", "Select the start position of the tapehead");
    wrefresh(current_win.window);

    vector<string> choices;
    choices.push_back( "\t1 - Blank on LHS");
    choices.push_back( "\t2 - First character of LHS");
    choices.push_back( "\t3 - Blank on RHS");
    choices.push_back( "\t4 - First character of RHS");
    choices.push_back( "\t5 - Cancel");

    int highlight = 1;
    int choice = 0;
    int c;

    prompt_menu(current_win, highlight, choices, choice, c, current_win.current_line);

    switch(choice)
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
            break;
    }
    current_win.current_line = 2;
}

/*
 * Processes the tape and outputs as an animation in the display window
 * 
 * turing_machine & tm => turing machine to use
 * WIN & current_win => window to print to
 */
void process_tape(turing_machine & tm, WIN & current_win)
{
    vector<string> output;
    int result = tm.process_tape(output);
    if (result)
    {
        output.push_back("Halt and accept");
    }
    else
    {
        output.push_back("Halt and reject");
    }
    for (int i = 0; i < output.size() - 1; i += 2)
    {
        current_win.current_line = 2;
        print_string(current_win, output[i], true);
        print_string(current_win, output[i+1], false);
        std::this_thread::sleep_for (std::chrono::milliseconds(500));
    }
    print_string(current_win, output[output.size() - 1], false);
}

/*
 * Display a menu in the menu window, taking in a vector of choices
 * 
 * WIN & menu_win => window to print to
 * int highlight => the selected menu item
 * vector<string> & choices => choices to print
 * int & choice => the choice selected
 * int & c => the inputted character
 * int offset => the number of lines to offset the menu by
 */
void prompt_menu(WIN & menu_win, int highlight, vector<string> & choices, int & choice, int & c, int offset)
{
    print_menu(menu_win, highlight, choices, offset);
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
        print_menu(menu_win, highlight, choices, offset);
        if (choice != 0)
            break;
    }
}

/*
 * Prints a menu where the highlighted item is inverted
 * 
 * WIN & menu_win => window to print to
 * int highlight => Highlighted choice
 * vectr<string> & choices => vector of choices to display
 * int offset => offset to print menu you by in lines
 */
void print_menu(WIN & menu_win, int highlight, vector<string> & choices, int offset)
{
    int x, y, i;

    x = 2;
    y = offset;
    box(menu_win.window, 0, 0);
    int size = choices.size();
    for(i = 0; i < size; ++i)
    {   if(highlight == i + 1) /* High light the present choice */
        {   wattron(menu_win.window, A_REVERSE); 
            mvwprintw(menu_win.window, y, x, "%s", choices[i].c_str());
            wattroff(menu_win.window, A_REVERSE);
        }
        else
            mvwprintw(menu_win.window, y, x, "%s", choices[i].c_str());
        ++y;
    }
    wrefresh(menu_win.window);
}

/*
 * Prints a passed in vector to the passed in window
 * 
 * WIN & current_win => window to print to
 * vector<string> & output => output to print
 */
void print_string_vector(WIN & current_win, vector<string> & output)
{
    int x = 2;
    int y = 2;

    werase(current_win.window);
    box(current_win.window, 0, 0);

    int size = output.size();

    for (int i = 0; i < size; ++i)
    {
        mvwprintw(current_win.window, y, x, "%s", output[i].c_str());
        ++y;
    }
    box(current_win.window, 0, 0);
    wrefresh(current_win.window);
}

/*
 * Prints a single string to the current window at the current line
 * 
 * WIN & current_win => window to print to
 * string & output => string to print
 * bool clear => true to erase window, false to retain current window
 */
void print_string(WIN & current_win, string & output, bool clear)
{
    int x = 2;
    if (clear)
    {
        werase(current_win.window);
        box(current_win.window, 0, 0);
    }

    mvwprintw(current_win.window, current_win.current_line++, x, "%s", output.c_str());
    box(current_win.window, 0, 0);
    wrefresh(current_win.window);
}

/*
 * Get input from the user, prompted from the passed in window
 * 
 * WIN & current_win => window to prompt and take imput in
 * const string prompt => prompt to display
 * 
 * return => user input
 */
string user_get(WIN & current_win, const string prompt)
{
    char input[1000];

    werase(current_win.window);
    box(current_win.window, 0, 0);

    mvwprintw(current_win.window, current_win.current_line++, 2, "%s", prompt.c_str());
    wrefresh(current_win.window);

    wmove(current_win.window, current_win.current_line++, 2);
    wrefresh(current_win.window);

    echo();
    wgetstr(current_win.window, input);
    mvwprintw(current_win.window, current_win.current_line++, 2, "%s %s", "You entered: ", input);
    noecho();

    return string(input);
}

WIN::WIN()
{
    x = y = width = height = current_line = 0;
}

