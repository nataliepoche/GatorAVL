//
// Created by Natalie Poche on 6/14/2024.
//

#ifndef PROJECT1_AVL_H
#define PROJECT1_AVL_H

#endif //PROJECT1_AVL_H
#include <iostream>
#include <sstream>
#include <set>
#include <vector>
using namespace std;

void initialize_commands(set<string>& commands){
    commands.emplace("insert");
    commands.emplace("remove");
    commands.emplace("search");
    commands.emplace("removeInorder");
    commands.emplace("printInorder");
    commands.emplace("printPreorder");
    commands.emplace("printPostorder");
    commands.emplace("printLevelCount");
}

void get_input(unordered_map<string, string>& commands_args){
    vector<string> map_keys;
    map_keys.push_back("command");
    map_keys.push_back("arg1");
    map_keys.push_back("arg2");
    int index = 0;

    string line;
    getline(cin >> ws,line);
    istringstream instream(line);

    while(instream >> quoted(line)){
        commands_args.emplace(map_keys[index], line);
        index++;
    }
}

bool validateID(string& ufid){
    stringstream ss;
    ss << ufid;
    ufid = ss.str();

    if(ufid.length() == 8){
        for(int i = 0; i < ufid.length(); i++){
            if(isdigit(ufid[i]) == 0){
                return false;
            }
        }
        return true;
    }
    else{
        return false;
    }
}

bool validateName(string& name){

    for(int i = 0; i < name.length(); i++){
        if((isalpha(name[i] == 0 && !(isspace(name[i])))) || (isdigit(name[i]) != 0)){
            return false;
        }
    }
    return true;
}

bool validateNumber(string& number, int& node_count){
    try{
        int result = stoi(number);

        if((0 <= result) && (result < node_count)){
            return true;
        }
        else{
            return false;
        }
    }

    catch(...){
        return false;
    }
}

class AVLTree{
private:

    struct Node{
        // Node attributes
        string name = "";
        string ufid = "";
        Node* left;
        Node* right;
        int height = 0;

        Node(const string& name, const string& ufid){
            this->name = name;
            this->ufid = ufid;
            this->left = nullptr;
            this->right = nullptr;
            height = 1;
        }
    };

    Node* _root;

    int nodeCount = 0;

    int getHeight(Node* node){
        if(node == nullptr){
            return 0;
        }
        else{
            return node->height;
        }
    }

    // insertion
    Node* _insert(Node* node, const string& name, const string& ufid, string& result){

        if(node == nullptr){
            nodeCount++;
            result = "successful";
            return new Node(name, ufid);
        }
        if(ufid < node->ufid){
            node->left = _insert(node->left, name, ufid, result);
        }
        else if(ufid > node->ufid){
            node->right = _insert(node->right, name, ufid, result);
        }
        else if(ufid == node->ufid){
            result = "unsuccessful";
        }

        return _balanceTree(node);
    }

    // removal
    Node* _removeID(Node* root, string ufid, string& result){
        if(root == nullptr){
            return nullptr;
        }

        if(ufid < root->ufid){
            root->left = _removeID(root->left, ufid, result);
        }

        else if(ufid > root->ufid){
            root->right = _removeID(root->right, ufid, result);
        }

        else{
            if(root->left == nullptr && root->right == nullptr){ // in case of leaf node
                delete root;
                result = "successful";
                nodeCount--;
                return nullptr;
            }
            else if(root->left == nullptr){ // node with only right child
                Node* temp = root->right;
                delete root;
                result = "successful";
                nodeCount--;
                return temp;
            }

            else if(root->right == nullptr){ // node with only left child
                Node* temp = root->left;
                delete root;
                result = "successful";
                nodeCount--;
                return temp;
            }
            else{
                Node* successor = _inorderSuccessor(root->right);
                root->name = successor->name;
                root->ufid = successor->ufid;
                root->right = _removeID(root->right, successor->ufid, result);
            }
        }
        return _balanceTree(root);
    }
    Node* _removeInorder(Node* root, int& target, int& loop_count, string& result){
        if(root == nullptr){
            return nullptr;
        }

        root->left = _removeInorder(root->left, target, loop_count, result);

        if(target == loop_count){
            if(root == _root){
                _root = _removeID(root, root->ufid, result);
            }
            else{
                root = _removeID(root, root->ufid, result);
                loop_count++;
                return root;
            }
        }

        loop_count++;
        root->right = _removeInorder(root->right, target, loop_count, result);

        return root;
    }
    Node* _inorderSuccessor(Node* root){
        if(root == nullptr || root->left == nullptr){
            return root;
        }

        return _inorderSuccessor(root->left);
    }

    // balance and rotation
    void _updateHeight(Node* node){
        node->height = 1 + max((node->left ? node->left->height:0), (node->right ? node->right->height:0));
    }
    Node* _balanceTree(Node* node){
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);

        int balanceFactor = leftHeight - rightHeight;

        if(balanceFactor < -1){ // tree is right heavy
            if(getHeight(node->right->right) > getHeight(node->right->left)){
                node = _rotateLeft(node);
            }
            else{
                node = _rotateRightLeft(node);
            }
        }
        else if(balanceFactor > 1){
            if(getHeight(node->left->left) >= getHeight(node->left->right)){
                node = _rotateRight(node);
            }
            else{
                node = _rotateLeftRight(node);
            }
        }

        _updateHeight(node);
        return node;
    }
    Node* _rotateLeft(Node* node){
        Node* grandchild = node->right->left;
        Node* newParent = node->right;
        newParent->left = node;
        node->right = grandchild;
        _updateHeight(node);
        _updateHeight(newParent);
        return newParent;
    }
    Node* _rotateRight(Node* node){
        Node* grandchild = node->left->right;
        Node* newParent = node->left;
        newParent->right = node;
        node->left = grandchild;
        _updateHeight(node);
        _updateHeight(newParent);
        return newParent;
    }
    Node* _rotateLeftRight(Node* node){
        node->left = _rotateRight(node->left);
        node= _rotateRight(node);
        return node;
    }
    Node* _rotateRightLeft(Node* node){
        node->right = _rotateRight(node->right);
        node = _rotateLeft(node);
        return node;
    }


    // searching
    Node* _searchID(Node* root, string ufid){

        if(root == nullptr){
            return nullptr;
        }

        if(ufid < root->ufid){
            return _searchID(root->left, ufid);
        }
        else if(ufid > root->ufid){
            return _searchID(root->right, ufid);
        }
        else if(ufid == root->ufid){
            return root;
        }

        return root;
    }
    Node* _searchName(Node* root, string& name, string& final){

        if(root == nullptr){
            return nullptr;
        }

        if(root->name == name){
            final += root->ufid + "\n";
        }

        _searchName(root->left, name, final);
        _searchName(root->right, name, final);

        return root;
    }

    // printing
    void _printInorder(Node* root, vector<string>& names){
        if(root == nullptr){
            return;
        }

        _printInorder(root->left, names);

        names.push_back(root->name);

        _printInorder(root->right, names);
    }
    void _printPreorder(Node* root, vector<string>& names){
        if(root == nullptr){
            return;
        }

        names.push_back(root->name);
        _printPreorder(root->left, names);
        _printPreorder(root->right, names);
    }
    void _printPostorder(Node* root, vector<string>& names){
        if(root == nullptr){
            return;
        }

        _printPostorder(root->left, names);
        _printPostorder(root->right, names);

        names.push_back(root->name);
    }

public:

    // constructor
    AVLTree(){
        _root = nullptr;
        nodeCount = 0;
    }

    // getter
    int getNodeCount(){return nodeCount;}

    // AVL Tree functionality
    string insert(const string& name, const string& ufid){
        string result;
        _root = _insert(_root, name, ufid, result);
        return(result);
    }
    string removeID(string ufid){
        string result = "unsuccessful";

        _root = _removeID(_root, ufid, result);

        return result;
    }
    string removeInorder(int target){

        string result;
        int loop_count = 0;
        _removeInorder(_root, target, loop_count, result);

        if(result == "successful"){
            return result;
        }
        else{
            return "unsuccessful";
        }
    }
    string searchID(string ufid){
        Node* result = _searchID(_root, ufid);
        if(result != nullptr){
            return(result->name);
        }
        else{
            return "unsuccessful";
        }
    }
    string searchName(string& name){

        string final;
        _searchName(_root, name, final);

        if(!final.empty()){
            return final;
        }
        else{
            return "unsuccessful";
        }
    }
    string printInorder(){
        vector<string> names;
        _printInorder(_root, names);

        string namelist = names[0];
        for(int i = 1; i < names.size(); i++){
            namelist += ", " + names[i];
        }

        return namelist;
    }
    string printPreorder(){
        vector<string> names;

        _printPreorder(_root, names);

        string namelist = names[0];
        for(int i = 1; i < names.size(); i++){
            namelist += ", " + names[i];
        }

        return namelist;
    }
    string printPostorder(){
        vector<string> names;
        _printPostorder(_root, names);

        string namelist = names[0];
        for(int i = 1; i < names.size(); i++){
            namelist += ", " + names[i];
        }

        return namelist;
    }
    string printLevelCount(){
        if(_root != nullptr){
            return to_string(_root->height);
        }
        else{
            return to_string(0);
        }
    }

};