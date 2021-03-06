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
#include "state.h"

/*
 * STATE
 */
state::state(){}

state::state(int in_id):id(in_id){}

state::state(const state & src)
{
    id = src.id;
    commands = src.commands;
}

/*
 * Processes the passed in character
 * 
 * char cur => character to process
 * 
 * Returns the instruction based on the commands within the state
 * Returns NULL if no valid command found based on input
 */
inst * state::process(char cur)
{
    for (int i = 0; i < commands.size(); ++i)
    {
        if(commands[i].compare(cur)) // If what we read is matches the current instruction
        {
            return &commands[i];
        }
    }
    return NULL;
}

/*
 * Adds passed inst to the commands vector
 * 
 * inst & src => inst to add to the commands vector
 */
void state::add_transition(inst & src)
{
    commands.push_back(src);
}

/*
 * Displays the commands for the state
 * 
 * return => vector of strings to be outputted
 */
vector<string> state::display()
{
    vector<string> ret;

    stringstream sstm; // Acts sorta like an ostream (cout), and can be converted to string
    sstm << "State " << id << "\n";

    ret.push_back(sstm.str());

    sstm.str(""); // Resets sstm to ""
    for (int i = 0; i < commands.size(); ++i)
    {
        sstm << "Insruction " << i << ": ";
        ret.push_back(sstm.str());
        sstm.str("");
        ret.back() += commands[i].display();
    }
    return ret;
}

/*
 * INSTRUCTION (inst)
 */

inst::inst():condition(0), set(0), dir(0), dest(0){}

inst::inst(const inst & src)
{
    condition = src.condition;
    set = src.set;
    dir = src.dir;
    dest = src.dest;
}

inst::inst(char co, char se, char di, int de):condition(co), set(se), dir(di), dest(de){}

/*
 * Compares to passed in character
 * 
 * char comp => character to compare to
 * 
 * Return if the condition matches the passed in char
 */
bool inst::compare(char comp)
{
    return comp == condition;
}

/*
 * Output current instruction
 * 
 * return => the string to be outputted
 */
string inst::display()
{
    stringstream sstm;
    sstm << condition << " -> " << set << ", " << dir << ": " << dest << "\n";
    return sstm.str();
}

/*
 * Getter for set
 */
char inst::get_set()
{
    return set;
}

/*
 * Getter for direction
 */
char inst::get_dir()
{
    return dir;
}

/*
 * Getter for destination
 */
int inst::get_dest()
{
    return dest;
}

