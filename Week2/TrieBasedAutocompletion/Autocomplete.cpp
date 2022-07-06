#include <iostream>
#include <unistd.h>         // sleep function
#include <string>           // for string type

#include <fstream>          // file read
#include <iostream>         // file read

#include <vector>           // vector for returning multiple found
#include <queue>            // for getting top 10 result (priority queue)
#include <map>              // pair

// need to compile with -lcurses option!
#include <curses.h>         // cursor lib


using namespace std;

#define ANSI_COLOR_DEFAULT 	"\x1b[0m"
#define ANSI_COLOR_YELLOW   "\x1b[33m"


// converts A-Z and space
// upper and lower case letters are not distinguished
int atoidx(char c) {
    if(c == ' ') return c - 32 + 26;    // space
    if(c < 97) return int(c) - 65;      // uppercase
    return int(c) - 97;                 // lowercase
}

// return lower case alphabet
char idxtoa(int i) {
    if(i == 26) return ' ';
    else return char(97+i);
}

// node to represent letter
typedef struct t_node {
    bool terminal;
    int score;
    t_node *children[27];         // A-Z + space

    // constructor for the node
    t_node() {
        terminal = false;
        score = 0;
        for(int i=0; i<27; i++) {
            children[i] = NULL;
        }
    }
} node;

// trie
class Trie {
    private:
        node *root;

    public:
    // constructor, initializes root
    Trie() {
        root = new node();
    }

    void add(string str, int score) {
        int i, idx;
        node *curNode = root;
        for(i=0; i<str.length(); i++) {
            idx = atoidx(str[i]);

            if(curNode->children[idx] == NULL) {        // if letter does not exist
                curNode->children[idx] = new node();
            }
            curNode = curNode->children[idx];           // follow the child
        }
        curNode->terminal = true;
        curNode->score = score;
    }

    // does not check whether the found node is terminal or not
    node* find_node(string str) {
        int i, idx;
        node *curNode = root;
        for(i=0; i<str.length(); i++) {
            idx = atoidx(str[i]);
            if(curNode->children[idx] == NULL) {        // if letter does not exist
                return NULL;                            // return NULL if not found
            }
            curNode = curNode->children[idx];           // follow the child
        }
        
        return curNode;                                 // return found node
    }

    // vector[node]
    priority_queue<pair<int,string> > find_all(string str) {
        priority_queue<pair<int,string> > priority_q;           // create vector to store all possible children
        node *curNode = find_node(str);
        find_recur(priority_q, curNode, str);
        return priority_q;
    }

    // recursively finds all child node and add the word to vector
    // used internally in find_all function
    void find_recur(priority_queue<pair<int,string> > &priority_q, node* curNode, string str) {
        // DEBUG PRINT
        // cout << str << endl;

        if(curNode->terminal == true)
            priority_q.push(make_pair(curNode->score, str));    // if current node is terminal, add to list

        for(int i=0; i<27; i++) {                               // 27 is size of possible characters
            string newStr = str + idxtoa(i);
            if(curNode->children[i] == NULL) {
                // DEBUG PRINT
                // cout << "NO  " << newStr << endl;
                continue;
            }
            // DEBUG PRINT
            // cout << "YES " << newStr << endl; 
            find_recur(priority_q, curNode->children[i], newStr);

            // usleep(500);                                 // sleep microseconds
        }
    }
};


int func1(){
    initscr();
    mvprintw(0, 0, "Hello, World"); // 화면의 0행, 0열부터 Hello, World를 출력합니다.
    refresh(); // 화면에 출력하도록 합니다.
    sleep(5);
    endwin();
    return 0;
}



int main(int argc, char const *argv[])
{   
    // if usgage is wrong
    if(argc != 2) {
        cout << "usage: searchword [file path]" << endl;
        return 0;
    }

    string filePath = argv[1];

    Trie trie;

    // maybe create loading bar for reading large textfile
    // read CSV file and add to trie
    // it will cause error if it's not CSV file -> TODO:: terminate program when error occurs
    ifstream openFile(filePath.data());
	if( openFile.is_open() ){
		string line, temp;
        int score;
        while(true) {
            if(!getline(openFile, line, ',')) break;
            getline(openFile, temp);
            score = stoi(temp);
            
            // DEBUG PRINT
            // cout << line << " :: " << score << endl;

            trie.add(line, score);                      // add to trie
        }
		openFile.close();
	}
    else {
        cout << "Unable to open file";
        return 0;
    }    


    // DEBUG CODE
    priority_queue<pair<int,string> > priority_q = trie.find_all("grape");
    for(int i=0; i<10; i++) {
        if(priority_q.empty()) break;
        pair<int, string> data = priority_q.top();
        priority_q.pop();
        cout << data.second << " " << data.first << endl;
    }

    // while(true) {

    // }
    // cbreak();
    // getc(stdin);
    // getchar
    func1();

    cout << ANSI_COLOR_YELLOW << "HELLO" << endl;
    // getch();
    cout << "hi" << endl;
    // getch();
    cout << "doing well" << endl;
	// for (int i=1;i>=0;i--) {
	// 	cout << "Count Down : "<< i << "\r";
    //     cout << "\a" << flush;
	// 	// fflush(stdout);
    //     sleep(1);
    // }


    return 0;
}
