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
#include<iostream>
#include<vector>
#include<cstring>
#include<string>
#include<sstream>
#include<thread>
#include<chrono>

using namespace std;

struct node
{
    node();
    node(char set);
    ~node();

    char content;
    node * left;
    node * right;
};

class tape
{
    public:
        tape();
        ~tape();
        void clear();
        void move_left();
        void move_right();
        void write(char set);
        char read();
        vector<string> display_tape();
        void start_pos(bool left, bool blank);
        void start_pos(); // Using class members rather than passed values

    protected:
        node * tapehead;
        bool left;
        bool blank;
};
