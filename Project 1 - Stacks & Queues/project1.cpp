//Mark Koszykowski ECE264 Project 1
//The intent of this program is to recieve an input file that contains a list of commands to create stacks and queues, push values to these stacks and queues, and pop values from these stacks and queues and produce an output file containing a summary of the operations

#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

template <typename Object>
class SimpleList {
        private:
                //Function used to initialize SimpleList
                void init() {
                        set_size(0);
                        this->head = NULL;
                        this->tail = NULL;
                }

                //Nested class Node that contains the value and a pointer to the next Node in the list
                class Node {
                        public:
                                //Node Constructor
                                Node(Object d, Node *ptr) {
                                        this->data = d;
                                        this->next = ptr;
                                }
                                Object data;
                                Node *next;
                };

                //Declaration of pointer to the first and last non-sentinel nodes
                Node *head;
                Node *tail;

                //Declaration of SimpleList data
                string name;
                int size;
        protected:
                //Non-virtual function that acts as the "push" for derived Stack class 
                void insert_head(const Object &d) {
                        if(get_size() == 0) {
                                Node *node = new Node(d, NULL);
                                this->tail = node;
                                this->head = node;
                        }
                        else {
                                Node *node = new Node(d, this->head);
                                this->head = node;
                        }
                }

                //Non-virtual function that acts as the "push" for derived Queue class
                void insert_tail(Object d) {
                        Node *node = new Node(d, NULL);
                        if(get_size() == 0) {
                                this->tail = node;
                                this->head = node;
                        }
                        else {
                              this->tail->next = node;
                              this->tail = node;  
                        }
                }

                //Non-virtual function that acts as "pop" for both derived classes
                Object delete_head() {
                        Node *node = this->head;
                        this->head = node->next;
                        Object data = node->data;
                        delete node;
                        return data;
                }
        public:
                //SimpleList Constructor which calls the initialization function
                SimpleList(const string &n) {this->name = n; init();}
                
                //Pure virtual functions for the derived classes
                virtual void push(Object d) = 0;
                virtual Object pop() = 0;
                
                //Public functions to edit or access private data
                string get_name() {
                        return name;
                }
                int get_size() {
                        return size;
                }
                void set_size(int s) {
                        size = s;
                }
};

//Derived Stack class
template <typename Object>
class Stack : public SimpleList<Object> {
        public:
                //Stack Constructor which uses SimpleList Constructor
                Stack(const string &n) : SimpleList<Object>(n) {}
                
                //Pure virtual "push" and "pop" functions
                void push(Object d) {
                        this->insert_head(d);
                        int n = this->get_size();
                        this->set_size(n+1);
                }
                Object pop(){
                        int n = this->get_size();
                        this->set_size(n-1);
                        return this->delete_head();
                }
};

//Derived Queue class
template <typename Object>
class Queue : public SimpleList<Object> {
        public:
                //Queue Constructor which uses SimpleList Constructor
                Queue(const string &n) : SimpleList<Object>(n) {}
                
                //Pure virtual "push" and "pop" functions
                void push(Object d) {
                        this->insert_tail(d);
                        int n = this->get_size();
                        this->set_size(n+1);
                }
                Object pop() {
                        int n = this->get_size();
                        this->set_size(n-1);
                        return this->delete_head();
                }
};

//Search function used to return either a pointer to the desired Stack or Queue or a NULL pointer
template <typename Object>
SimpleList<Object> * search_list(list<SimpleList<Object> *> *l, const string &name) {
        //Create an iterator to iterate through the list of pointers to SimpleLists in the for loop until desired Stack or Queue has been found
        for (typename list<SimpleList<Object> *>::const_iterator itr = l->begin(); itr != l->end(); ++itr) {
                //If the desired SimpleList is found, return a pointer to it
                if((*itr)->get_name() == name) {
                        return *itr;
                }
        }

        //Otherwise return the NULL pointer
        return NULL;
}

//Create function used to add a SimpleList to the list of pointers to SimpleLists
template <typename Object>
void create_list(list<SimpleList<Object> *> *l, const string &name, const string &type, ofstream &outFile) {
        //If the desired Stack or Queue already exists, output error
        if(search_list(l, name) != nullptr) {
                outFile << "ERROR: This name already exists!" << endl;
        }

        //Otherwise, check if SimpleList that is going to be created is Stack or Queue and create respective new SimpleList
        else {
                if(type == "stack") {
                        SimpleList<Object> *stack = new Stack<Object>(name);
                        l->push_back(stack);
                }
                else {
                        SimpleList<Object> *queue = new Queue<Object>(name);
                        l->push_back(queue);
                }
        }
}

//Push function used to push data to a specific SimpleList in the list of pointers to SimpleLists
template <typename Object>
void push_value(list<SimpleList<Object> *> *l, const string &name, Object data, ofstream &outFile) {
        SimpleList<Object> *temp = search_list(l, name);

        //If the Stack or Queue exists (is not pointing to NULL) push the data to that Stack or Queue
        if(temp != NULL) {
                temp->push(data);
        }
        
        //Otherwise output error because Stack or Queue does not exist
        else {
                outFile << "ERROR: This name does not exist!" << endl;
        }
}

//Pop function used to pop data from a specific SimpleList in the list of pointers to SimpleLists
template <typename Object>
void pop_value(list<SimpleList<Object> *> *l, const string &name, ofstream &outFile) {
        SimpleList<Object> *temp = search_list(l, name);

        //If the Stack or Queue exists (is not pointing to NULL) check the size of the SimpleList
        if(search_list(l, name) != NULL) {

                //If the SimpleList is not empty, retrieve the value popped
                if(temp->get_size() != 0) {
                        outFile << "Value popped: " << temp->pop() << endl;
                }

                //Otherwise, output error because the SimpleList is empty
                else {
                        outFile << "ERROR: This list is empty!" << endl;
                }
        }

        //Otherwise, if no Stack or Queue exists, output error
        else {
                outFile << "ERROR: This name does not exist!" << endl;
        }
}

//Function used to parse through the input file and write to the output file
void parse_file(const string &input, const string &output) {
        //Initialize three large lists of pointers to Stacks and Queues of ints, doubles, and strings
        list<SimpleList<int> *> listSLi;
        list<SimpleList<double> *> listSLd;
        list<SimpleList<string> *> listSLs;
        
        //Open the input and output files for reading and writing respectively
        ifstream inFile(input);
        ofstream outFile(output);

        //If the file exists and is opened, parse through it
        if(inFile.is_open()) {
                //Declare the variables that are going to be used to interperet commands
                string action, name, data, commands;
                char type;
                
                //Continue to go through this algorithm while a new line can be retrieved from the input file
                while(getline(inFile, commands)) {
                        //Function used to break up line into seperate strings
                        istringstream iss(commands);

                        //Get the first string from the line and store it to action
                        iss >> action;

                        //Get the second string from the line and store it to name
                        iss >> name;

                        //Store the first character from the "name" string to type
                        type = name.at(0);
                        
                        //Writes processing command to output file
                        outFile << "PROCESSING COMMAND: " << commands << endl;

                        //If the action is "create", check the SimpleList type and call the respective function to add a new SimpleList to the list of pointers to SimpleLists
                        if(action == "create") {
                                iss >> data;
                                if(type == 'i') {
                                        create_list<int>(&listSLi, name, data, outFile);
                                }
                                else if(type == 'd') {
                                        create_list<double>(&listSLd, name, data, outFile);
                                }
                                else {
                                        create_list<string>(&listSLs, name, data, outFile);
                                }
                        }
                        
                        //If the action is "push", check the SimpleList type and call the respective function to add a new value to that specified SimpleList
                        else if(action == "push") {
                                iss >> data;
                                if(type == 'i') {
                                        push_value<int>(&listSLi, name, stoi(data), outFile);
                                }
                                else if(type == 'd') {
                                        push_value<double>(&listSLd, name, stod(data), outFile);
                                }
                                else {
                                        push_value<string>(&listSLs, name, data, outFile);
                                }
                        }
                        
                        //If the action is "pop", check the SimpleList type and call the respective function to retrieve the value popped and modify the SimpleList
                        else {
                                if(type == 'i') {
                                        pop_value<int>(&listSLi, name, outFile);
                                }
                                else if(type == 'd') {
                                        pop_value<double>(&listSLd, name, outFile);
                                }
                                else {
                                        pop_value<string>(&listSLs, name, outFile);
                                }
                        }
                }

                //Close files so they are saved and readable
                inFile.close();
                outFile.close();
        }

        //Otherwise, output error because the input file does not exist
        else {
                outFile << "ERROR: The input file does not exist!" << endl;
        }
}

//Function used to retrieve the name of the input file
string get_input() {
        string input;
        cout << "Enter name of input file: ";
        cin >> input;
        return input;
}

//Function used to retrieve the name of the output file
string get_output() {
        string output;
        cout << "Enter name of output file: ";
        cin >> output;
        return output;
}

int main() {
        //Create two strings that hold the data for input and output file names
        string s1 = get_input();
        string s2 = get_output();

        //Call the parse function with two strings as parameters
        parse_file(s1, s2);

        return 0;
}
