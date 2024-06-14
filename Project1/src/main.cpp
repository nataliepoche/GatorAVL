#include <iostream>
#include <sstream>
#include <unordered_map>
#include <iomanip>
#include <vector>
#include "AVL.h"
using namespace std;

/* Note:
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope.
*/

int main(){

    AVLTree tree;
    set<string> commands;
    initialize_commands(commands);

    int user_commands = 0;
    cin >> user_commands;

    unordered_map<string, string> command_args;

    for(int i = 0; i < user_commands; i++){
        command_args.clear();
        get_input(command_args);

        if(command_args["command"] == "insert"){
            stringstream ss;
            ss << command_args["arg2"];
            command_args["arg2"] = ss.str();
            if(validateName(command_args["arg1"]) && validateID(command_args["arg2"])){
                string result = tree.insert(command_args["arg1"],command_args["arg2"]);
                cout << result << endl;
            }
            else{
                cout << "unsuccessful" << endl;
            }
        }

        else if(command_args["command"] == "remove"){
            stringstream ss;
            ss << command_args["arg1"];
            command_args["arg1"] = ss.str();

            if(validateID(command_args["arg1"])){
                string result = tree.removeID(command_args["arg1"]);
                cout << result << endl;
            }
            else{
                cout << "unsuccessful" << endl;
            }
        }

        else if(command_args["command"] == "search"){

            if(validateName(command_args["arg1"])){

                string result = tree.searchName(command_args["arg1"]);
                cout << result << endl;
            }

            else if(validateID(command_args["arg1"])){
                stringstream ss;
                ss << command_args["arg1"];
                command_args["arg1"] = ss.str();

                string result = tree.searchID(command_args["arg1"]);
                cout << result << endl;
            }
            else{
                cout << "unsuccessful" << endl;
            }
        }

        else if(command_args["command"] == "removeInorder"){
            int current_node_count = tree.getNodeCount();

            if(validateNumber(command_args["arg1"], current_node_count)){
                string remove = tree.removeInorder(stoi(command_args["arg1"]));
                cout << remove << endl;
            }

            else{
                cout << "unsuccessful" << endl;
            }
        }

        else if(command_args["command"] == "printInorder"){
            string inorder = tree.printInorder();
            cout << inorder << endl;
        }

        else if(command_args["command"] == "printPreorder"){
            string preorder = tree.printPreorder();
            cout << preorder << endl;
        }

        else if(command_args["command"] == "printPostorder"){
            string postorder = tree.printPostorder();
            cout << postorder << endl;
        }

        else if(command_args["command"] == "printLevelCount"){
            string levelCount = tree.printLevelCount();
            cout << levelCount << endl;
        }

        else{
            cout << "unsuccessful" << endl;
        }
    }
	return 0;
}

