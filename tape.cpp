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
#include "tape.h"
/*
 * NODE
 */
node::node()
{
    content = '_'; // "Blank" in tape
    left = right = NULL;
}

node::node(char set)
{
    content = set;
    left = right = NULL;
}

node::~node()
{
    if (left)
        delete left;
}

/*
 * TAPE
 */

tape::tape():left(true),blank(false)
{
    tapehead = NULL;
}

tape::~tape()
{
    clear();
}

/*
 * Clears the tape to NULL
 */
void tape::clear()
{
    while (tapehead && tapehead->right)
        tapehead = tapehead->right;
    if (tapehead)
        delete tapehead;
    tapehead = NULL;

}

/*
 * Moves the tapehead left
 * If the left is null, create a new node that is "blank" (_)
 */
void tape::move_left()
{
    if (!tapehead) // if nothing to begin with
    {
        tapehead = new node;
        return;
    }
    if (!tapehead->left)
    {
        tapehead->left = new node;
        tapehead->left->right = tapehead;
    }
    tapehead = tapehead->left;
}

/*
 * Move the tapehead right
 * If the right is null, create a new node that is "blank" (_)
 */
void tape::move_right()
{
    if (!tapehead) // if nothing to begin with
    {
        tapehead = new node;
        return;
    }
    if (!tapehead->right)
    {
        tapehead->right = new node;
        tapehead->right->left = tapehead;
    }
    tapehead = tapehead->right;
}

/*
 * Writes the passed in character to the tapehead
 */
void tape::write(char set)
{
    if (!tapehead)
        tapehead = new node;
    tapehead->content = set;
}

/*
 * Returns the contents of the current tapehead
 */
char tape::read()
{
    return tapehead->content;
}

/*
 * Display the entire tape, including the position of the tapehead
 * Example output: _ 0 1 0 1 _
 *                   ^
 */
void tape::display_tape()
{
    if (!tapehead)
    {
        cout << "Tape is empty!\n";
        return;
    }
    node * current = tapehead;
    while (current->left)
        current = current->left;

    string shift = "";
    bool stop = false;

    while (current)
    {
        cout << current->content << " ";
        if (!stop && current == tapehead)
            stop = true;
        if (!stop)
            shift += "  ";

        current = current->right;
    }
    cout << "\n" <<  shift << "^\n";
}

/*
 * Sets the start position of the tapehead
 * Left indicates whether or not to start on the lefthand side of the tape
 * Blank indicates whether or not to start on the blank left of the first character
 */
void tape::start_pos(bool left, bool blank)
{
    if (!tapehead)
        return;

    if (left)
    {
        while(tapehead->left)
            tapehead = tapehead->left;
        if (!blank)
            tapehead = tapehead->right;
    }
    else
    {
        while(tapehead->right)
            tapehead = tapehead->right;
        if (!blank)
            tapehead = tapehead->left;
    }
}

/*
 * Sets the start position to the values read from file
 */
void tape::start_pos()
{
    start_pos(left, blank);
}


