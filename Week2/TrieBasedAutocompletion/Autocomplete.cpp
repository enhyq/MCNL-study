#include <iostream>
#include <unistd.h>         // sleep function
#include <string>           // for string type

#include <fstream>          // file read
#include <iostream>         // file read

#include <vector>           // vector for returning multiple found
#include <queue>            // for getting top 10 result (priority queue)
#include <map>              // pair

// need to compile with -lncurses option!
#include <ncurses.h>         // ncurses lib


using namespace std;


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


void initialize_ncurses() {
    initscr();                          // initializes ncurses
    cbreak();                           // Line buffering disabled
    noecho();                           // no print out on screen
    // keypad(stdscr, true);            // ???
    mvprintw(0, 0, "(Press ESC to quit)");    // 화면의 0행, 0열부터 출력
    mvprintw(1, 0, "Search Word: ");
    mvprintw(2, 0, "---------------------------------------------");
    move(1,13);
    refresh();                          // 화면에 출력하도록 합니다
}

void terminate_ncurses() {
    endwin();                           // restores terminal
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


    initialize_ncurses();
    char ch;
    string queryText = "";
    // trie.find_node(ss.data()->c_str());
    while(true) {
        ch = getch();                               // getch has refresh() internally
        if(ch == '\x1B') break;                     // ESC key
        
        if('a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z' || ch == ' ') {
            queryText.push_back(ch);
        }
        else if(ch == '\x7F') {                     // Backspace is DEL
            queryText.pop_back();
        }
        else continue;

        // TODO :: do something when ENTER is pressed

        mvprintw(1, 13, "%s", queryText.c_str());    // row, col, str
        clrtoeol();
    }
    
    // sleep(5);
    terminate_ncurses();

	// for (int i=1;i>=0;i--) {
	// 	cout << "Count Down : "<< i << "\r";
    //     cout << "\a" << flush;
	// 	// fflush(stdout);
    //     sleep(1);
    // }


    return 0;
}
