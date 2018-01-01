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
#include <fstream>
/*
 * TURING MACHINE
 */

turing_machine::turing_machine(){}

turing_machine::~turing_machine(){}

/*
 * Adds the passed in state to the vector of states
 */
void turing_machine::add_state(state & src)
{
    states.push_back(src);
}

/*
 * Parses a file with the passed in filename
 * Lines beginning with # are interpreted as parts of the machine description
 * Lines beginning with #; (0;, 1;, n;) are interpreted as states
 * Lines beginning with L or R are interpreted as the start position for the tapehead
 */
string turing_machine::read_from_file(string filename)
{
    string ret = "";
    states.clear();
    desc.clear();
    ifstream fin;
    fin.open(filename.c_str());
    if (fin)
    {
        string handle;
        getline(fin, handle);
        while (!fin.eof())
        {
            int st = 0;
            char con, set, dir = 0;
            int dest = 0;
            if (handle[0] == '#') // Processing description
            {
                handle.erase(0, 1);
                desc.push_back(handle);
                getline(fin, handle);
            }
            else if (handle[1] != ';') // If we're processing the start pos
            {
                left = handle[0] == 'L';
                blank = handle[1] == 'B';
                getline(fin, handle);
            }
            else // Processing state
            {
                st = handle[0] - '0';
                handle.erase(0, 2);

                state to_add(st);

                while (handle.size() != 0)
                {
                    con = handle[0];
                    set = handle[1];
                    dir = handle[2];
                    dest = handle[3] - '0';
                    handle.erase(0, 5);
                    inst i(con, set, dir, dest);
                    to_add.add_transition(i);
                }
                getline(fin, handle);
                states.push_back(to_add);
            }
        }
        current_state = states[0];
    }
    else
    {
        //cout << "Invalid file!\n";
        ret = "Invalid file!";
    }
    fin.close();
    return ret;
}

/*
 * Display the states of the machine
 */
vector<string> turing_machine::display_states()
{
    vector<string> ret;
    for (int i = 0; i < desc.size(); ++i)
        ret.push_back(desc[i]);

    for (int i = 0; i < states.size(); ++i)
    {
        vector<string> state_out = states[i].display();
        for (int j = 0; j < state_out.size(); ++j)
        {
            ret.push_back(state_out[j]);
        }
    }
    return ret;
}

/*
 * Builds the tape from passed in input
 */
void turing_machine::build_tape(const string input)
{
    clear();
    write('_');
    move_right();
    for (int i = 0; i < input.size(); ++i)
    {
        write(input[i]);
        move_right();
    }
    write('_');
    start_pos();
}

/*
 * Processes the tape bassed on the states in the states vector
 * Handles like an actual turing machine, making moves based on the contents of
 * the tapehead
 * Returns 0 if it rejects
 * Returns 1 if it accepts
 */
int turing_machine::process_tape()
{
    while (true)
    {
        inst * i = current_state.process(read());
        //display_tape();
        if (!i)
            return 0;
        else
        {
            write(i->get_set());
            if (i->get_dir() == 'R')
            {
                move_right();
                //cout << "R ";
            }
            else if (i->get_dir() == 'L')
            {
                move_left();
                //cout << "L ";
            }
            else
                return 0;

            if (i->get_dest() == states.size())
            {
                current_state = states[0];
                return 1;
            }

            current_state = states[i->get_dest()];
        }
    }
}
