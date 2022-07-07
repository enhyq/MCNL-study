#include <iostream>
#include <unistd.h>         // sleep function
#include <string>           // for string type

// strtok
#include <stdio.h>
#include <string.h>

// istingstream
#include <iostream>
#include <sstream>


#include <fstream>          // file read
#include <iostream>         // file read

#include <vector>           // vector for returning multiple found
#include <queue>            // for getting top 10 result (priority queue)
// #include <map>              
#include <unordered_map>    

// need to compile with -lncurses option!
#include <ncurses.h>         // ncurses lib


using namespace std;


// converts A-Z and space
// upper and lower case letters are not distinguished
int atoidx(char c) {
    if(c == ' ') return c - 32 + 26;    // space; space comes after alphabet
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
            if(curNode->children[idx] == NULL) {        // if letter does not exist and has no child
                return NULL;                            // return NULL if not found
            }
            curNode = curNode->children[idx];           // follow the child
        }
        
        return curNode;                                 // return found node
    }

    // vector[node]
    priority_queue<pair<int,string> > find_all(string str) {
        priority_queue<pair<int,string> > priority_q;           // create vector to store all possible children
        if(str != "") {
            node *curNode = find_node(str);
            if(curNode != NULL)                                 // if find_node returns NULL
                find_recur(priority_q, curNode, str);
        }
        // DEBUG PRINT
        // cout << "hi:" << priority_q.empty() << endl;

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

            // usleep(500);                                     // sleep microseconds
        }
    }
};


void initialize_ncurses() {
    initscr();                          // initializes ncurses
    if(has_colors() == false) {         // checks whether user's terminal supports colors
        endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
    use_default_colors();               // use default terminal color
    start_color();                      // start color
    init_pair(1, COLOR_CYAN, -1);       // define color pair for highlight, -1 means to use default
    cbreak();                           // Line buffering disabled
    noecho();                           // no print out on screen
    // keypad(stdscr, true);            // ???
    mvprintw(0, 0, "(Press ESC to quit)");    // 화면의 0행, 0열부터 출력
    mvprintw(1, 0, "Search Word: ");
    mvprintw(2, 0, "---------------------------------------------");
    move(1,13);                         // input cursor position
    refresh();                          // 화면에 출력하도록 합니다
}

void terminate_ncurses() {
    endwin();                           // restores terminal
}


/*
 * Assumes that duplicate entries does not exist in the data file
 */


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
    // it will cause error if it's not CSV format -> TODO:: terminate program when error occurs
    ifstream openFile(filePath.data());
    string line, temp;                                  // variable for file reading
    int score;
	if( openFile.is_open() ){
        // CONSOLE PRINT
        cout << "making trie..." << endl;
        while(true) {
            if(!getline(openFile, line, ',')) break;
            getline(openFile, temp, '\n');              // delimiter is '\n' by default
            score = stoi(temp);
            
            // DEBUG PRINT
            // cout << line << " :: " << score << endl;

            trie.add(line, score);                      // add to trie
        }
		// openFile.close();
	}
    else {
        cout << "Unable to open file" << endl;          // if file could not be opened
        return 0;
    }

    // CONSOLE PRINT
    cout << "making word table..." << endl;

    // TODO :: when making trie, store each word into map
    // create hash(?) map of all the 
    // read string from second word
    openFile.clear();                                   // reset eof and fail flags
    openFile.seekg(0);                                  // go to the beginning of the file
    // map element is also accessed using first, and second keyword, like pair
    unordered_map<string, vector<pair<int, string> > > suffixWordMap;
    unordered_map<string, vector<pair<int, string> > >::iterator mapItr;
    vector<pair<int, string> >::iterator vItr;
    // ignore first word;                               // first word can be found using tree
    while(true) {
        if(!getline(openFile, line, ',')) break;        // get line
        getline(openFile, temp, '\n');
        score = stoi(temp);                             // get score of the line

        /* Question: diff between .data() and .c_str() ? */
       
        string word;                                    // to store each word of line
        bool flagFirst = true;
        for(istringstream is(line) ; is >> word ; ) {
            if(flagFirst) {
                flagFirst = false;
                continue;
            }

            /* Use trie DS just to create map and use the map for searching auto completion? */
            /* this part only creates map for single words in the middle, no */

            // search if element already in map
            mapItr = suffixWordMap.find(word);
            if(mapItr == suffixWordMap.end()) {            // word is not found in Map
                // insert
                // vector<pair<int, string> >(make_pair(score, line))
                vector<pair<int, string> > v;
                v.push_back(make_pair(score, line));
                suffixWordMap.insert( make_pair( word, v )  );
            } else {
                // add to vector
                // value 값인 vector에 (score, word) pair를 추가한다
                (*mapItr).second.push_back(make_pair(score, line));
                
                // DEBUG PRINT
                /****
                cout << (*mapItr).first << " :---: ";
                vItr = (*mapItr).second.begin();
                while(vItr != (*mapItr).second.end()) {
                    cout << "(" << (*vItr).first << "," << (*vItr).second << ")";
                    vItr++;
                }
                cout << endl;
                ****/
            }
        }
    }

    openFile.close();                                   // close file


    // DEBUG CODE
    /*
    priority_queue<pair<int,string> > a = trie.find_all("");
    priority_queue<pair<int,string> > b = trie.find_all("e");
    priority_queue<pair<int,string> > priority_q = trie.find_all("grape");
    for(int i=0; i<10; i++) {
        if(priority_q.empty()) break;
        pair<int, string> data = priority_q.top();
        priority_q.pop();
        cout << data.second << " " << data.first << endl;
    }
    */

    initialize_ncurses();
    char ch;
    string queryStr = "", currentWord, tempWord;
    priority_queue<pair<int,string> > queryResult;      // max heap by default, ordered by first in the pair
    pair<int, string> topQueryResult;
    int printNum = 20, i;

    while(true) {
        ch = getch();                                   // getch has refresh() internally
        if(ch == '\x1B') break;                         // ESC key
        
        if('a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z' || ch == ' ') {
            queryStr.push_back(ch);                     // when Alphabet key is pressed
        }
        else if(ch == '\x7F') {                         // Backspace is DEL
            if(queryStr.length() != 0)
                queryStr.pop_back();
        }
        else continue;                                  // do nothing for other keys
        // TODO :: do something when ENTER is pressed

        // Find currently typing word
        for(istringstream is(queryStr) ; is >> tempWord ; ) {
            currentWord = tempWord;
        }
        if(queryStr.length() == 0) currentWord.clear(); // clear currentWord when there is no queryStr
        
        // DEBUG PRINT
        // mvprintw(0, 21, "%s", currentWord.c_str()); clrtoeol();

        mvprintw(1, 13, "%s", queryStr.c_str());        // row, col, str
        clrtoeol();                                     // from current position, clear to end of line

        // search query string in trie
        queryResult = trie.find_all(queryStr);
        
        // if data file does not contain duplicate words, there will be no duplicate word in the suffixWordMap
        // find currentWord in suffixWordMap
        mapItr = suffixWordMap.find(currentWord);
        if(mapItr != suffixWordMap.end()) {
            for(vItr = (*mapItr).second.begin(); vItr != (*mapItr).second.end(); vItr++) {
                queryResult.push(*vItr);
            }
        } // else the word is not found in the suffixWordMap so pass

        move(3,0);                                      // output top line
        for(i=0; i<printNum; i++) {
            if(queryResult.empty()) break;

            topQueryResult = queryResult.top();         // get the top element
            
            queryResult.pop();                          // remove top element


            // need to fix below code after implementing reading searching string in the middle

            // find word index
            string queryStrNoSpace = queryStr;
            if(queryStrNoSpace.back() == ' ')
                queryStrNoSpace.pop_back();

            int idxBegin = topQueryResult.second.find(queryStrNoSpace);
            if(idxBegin != 0) {
                if(idxBegin + queryStrNoSpace.length() != topQueryResult.second.length())
                    if(!(topQueryResult.second[idxBegin-1] == ' ' && topQueryResult.second[idxBegin + queryStrNoSpace.length()] == ' ')) {
                        // mvprintw(0, 30, "%d", idxBegin);
                        idxBegin = topQueryResult.second.find(queryStrNoSpace, idxBegin+queryStrNoSpace.length());
                        // mvprintw(0, 35, "%d", idxBegin);
                    }
            }
            int idxEnd = idxBegin + queryStrNoSpace.length();

            move(3+i, 0);
            printw("%s", topQueryResult.second.substr(0, idxBegin).c_str());
            attron(COLOR_PAIR(1));
            printw("%s", queryStr.c_str());
            attroff(COLOR_PAIR(1));
            printw("%s %d", topQueryResult.second.substr(idxEnd, topQueryResult.second.length()).c_str(), topQueryResult.first);
            clrtoeol();                                 // clear to end of line
        }
        clrtobot();                                     // clear from cursor until the last line
        move(1,13+queryStr.length());                   // input cursor position

    }
    terminate_ncurses();


    return 0;
}


// TODO :: when TAB  is pressed enter "selection mode"
// in selection mode, trie search is not processed
// move through prediction list using TAB or SHIFT + TAB or ARROW keys
// selected input is updated on the input cursor but prediction list is not updated
// When DEL is pressed, quit selection mode
// When ENTER is pressed update input string to selected prediction string and quit selection mode

// TODO :: when ENTER is pressed in query mode
// do a search on google?

// TODO :: make a loading screen at file read (for very large files?)


// Currently there is a bug where first word in the data file is not properlly found
// though it is added to the trie

// When two same word appear multiple times in a string
// the highlighter doesn't work properly