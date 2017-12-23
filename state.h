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

using namespace std;

class inst
{
    public:
        inst();
        inst(const inst & src);
        inst(char co, char se, char di, int de);
        bool compare(char comp);
        string display();
        char get_set();
        char get_dir();
        int get_dest();

    protected:
        /*
         * In turing machine formating:
         * condition -> set, dir
         */
        char condition;
        char set;
        char dir;
        int dest;
};
class state
{
    public:
        state();
        state(int id);
        state(const state & src);
        inst * process(char cur);
        void add_transition(inst & src);
        vector<string> display();

    protected:
        int id;
        vector<inst> commands;
};

