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

int main()
{
    turing_machine tm;
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
    while (resp > 0 && resp < 7);

    return 1;
}
