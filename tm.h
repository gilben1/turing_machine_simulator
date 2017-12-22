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

class turing_machine : public tape
{
    public:
        turing_machine();
        ~turing_machine();
        void add_state(state & src);
        void read_from_file(string filename);
        void display_states();
        void build_tape(const string input);
        int process_tape();
    protected:
        vector<state> states;
        state current_state;
        string desc;
};
