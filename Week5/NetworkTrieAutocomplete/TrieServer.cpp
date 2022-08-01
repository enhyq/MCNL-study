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
// #include <ncurses.h>         // ncurses lib
// Windows OS doesn't have ncurses

// Network
#include <unistd.h>         // for data transfer
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>


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
        // cout << "a" << endl;
        // cout << "print: ";
        // for(int j=0; j<str.length(); j++)
        //     cout << (int)str[j] << " ";
        // cout << endl;

        for(i=0; i<str.length(); i++) {
            if(str[i] == '\0') break;
            // cout << "*** " << str << " " << str.length() << " " << atoidx(str[i]) << endl;

            idx = atoidx(str[i]);

            if(curNode->children[idx] == NULL) {        // if letter does not exist
                // cout << str << endl;
                curNode->children[idx] = new node();
            }
            // cout << "+++" << endl;
            curNode = curNode->children[idx];           // follow the child
            // cout << "---" << endl;
        }
        // cout << "b" << endl;
        curNode->terminal = true;
        curNode->score = score;
        // cout << "c" << endl;
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


int create_listening_socket(sockaddr_in *myaddr, int port)
{
    /*
     * int socket(int domain, int type, int protocol);
     *
     * :: domain ::
     *  communication domain
     *      - AF_INET   /   PF_INET
     *      - AF_INET6  /   PF_INET6
     *
     * :: type ::
     *  communication type
     *      - SOCK_STREAM
     *      - SOCK_DGRAM
     *
     * :: protocol ::
     *  Protocol value for Internet Protocol(IP)
     *  This is the same number which appears on protocol field in the IP header of a packet.
     */
    int ss = socket(PF_INET, SOCK_STREAM, 0);
    if (ss == -1)
    {
        cout << "failed to create socket" << endl;
        return -1; // socket creation fail
    }

    // sockaddr_in *myaddr = new sockaddr_in();
    /*
     * sockaddr_in
     *
     * :: sin_family ::
     *  AF_INET
     *  AF_INET6
     *  AF_LOCAL
     *      what does AF mean?
     *
     * :: sin_port ::
     *  16bit Network byte
     * 
     * :: sin_addr.s_addr ::
     * 
     * :: sin_zero ::
     */

    memset(myaddr->sin_zero, 0, sizeof(myaddr->sin_zero));
    myaddr->sin_family = AF_INET;
    myaddr->sin_port = htons(port);
    myaddr->sin_len = sizeof(*myaddr);      // not sure
    // myaddr->sin_addr.s_addr = inet_addr(ip.c_str());
    myaddr->sin_addr.s_addr = htonl(INADDR_ANY);
    // inet_addr();
    // inet_aton();


    /*
     * int bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen);
     *
     * :: sockfd ::
     *  socket file descripter
     * 
     * :: myaddr ::
     *  struct used for storing IP address
     * 
     * :: addrlen
     *  what is this?
     */
    if (bind(ss, (sockaddr *)myaddr, sizeof(*myaddr)) == -1)   // ignore red wiggly line
    {
        cout << "failed to bind socket" << endl;
        return -1; // socket bind fail
    }

    /*
     * int listen(int sockfd, int backlog);
     * 
     * :: sockfd ::
     * 
     * :: backlog ::
     *  specifies the number of pending connections the queue will hold.
     *
     */
    if (listen(ss, 5) == -1)
    {
        cout << "failed to listen socket" << endl;
        return -1; // socket listen fail
    }

    /*
     * int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
     *  - returns fd (file descriptor) of the connected socket
     * 
     * :: sockfd ::
     * 
     * :: addr ::
     *  pass variable to save socket address of connected device
     * 
     * :: addrlen ::
     *  pass variable to save socket address length
     *
     */

    return ss;
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
            // line = "";
            // cout << "1" << endl;
            if(!getline(openFile, line, ',')) break;
            // cout << "2" << endl;
            getline(openFile, temp, '\n');              // delimiter is '\n' by default
            // cout << "3" << endl;
            score = stoi(temp);
            // cout << "4" << endl;
            // DEBUG PRINT
            // cout << line << " :: " << score << endl;

            trie.add(line, score);                      // add to trie
            // cout << line << endl;
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

    char ch;
    string queryStr = "", currentWord, tempWord;
    priority_queue<pair<int,string> > queryResult;      // max heap by default, ordered by first in the pair
    pair<int, string> topQueryResult;

    struct response{
        char found_phrases[20][100];
    };

    response r;
    string rq;

    int printNum = 20, i;


    // MAKE SERVER - CLIENT CONNECTION

    sockaddr_in *myaddr = new sockaddr_in();
    sockaddr_in *caddr = new sockaddr_in();
    unsigned int caddr_len;

    int ss_fd = create_listening_socket(myaddr, 12358);
    if(ss_fd == -1)
    {
        cout << "failed to create listening socket" << endl;
        return 1;
    }

    cout << "listening for client connection" << endl;

    int cs_fd = accept(ss_fd, (sockaddr *)caddr, &caddr_len);


    // debug print
    cout << "client connected!" << endl;
    cout << "client fd: " << cs_fd << endl << endl;

    char buf[1000];

    while(true) {

        // *****
        // wait for request
        // receive request from client and set queryStr and currentWord
        // *****
        long len;
        recv(cs_fd, &len, sizeof(len), MSG_WAITALL);

        rq.resize(len+1, 0x00);

        cout << "Size: " << len << " " << rq.length() << endl;
        recv(cs_fd, &(buf[0]), len, MSG_WAITALL);
        buf[len] = 0;
        queryStr = buf;
        // currentWord = rq.currentWord;

        cout << "Client request phrase: " << queryStr << endl;

        // DEBUG PRINT
        // mvprintw(0, 21, "%s", currentWord.c_str()); clrtoeol();

        // TODO :: 단어가 하나인 경우만 search 하도록 만들기
        // 이렇게 안하면 검색할 때 오류생긴다.
        // ex) "a city    " 검색시 버그 있음

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

        // STORE QUERY RESULT IN response STRUCT AND SEND TO CLIENT

        memset(&r, 0x00, sizeof(r));
        for(i=0; i<printNum; i++) {
            if(queryResult.empty())
            {
                r.found_phrases[i][0] = '\0';
                break;
            }

            topQueryResult = queryResult.top();         // get the top element
            queryResult.pop();                          // remove top element

            strcpy(r.found_phrases[i], topQueryResult.second.c_str());
        }

        // SEND response to CLIENT
        write(cs_fd, &r, sizeof(r));
        cout << "found: " << endl;
        for(int i=0; i<printNum; i++){
            cout << i+1 << " " << r.found_phrases[i] << endl;
        }

        cout << "successfully sent response to client" << endl;
        
    }

    // END SERVER - CLIENT CONNECTION

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
// though it is properly added to the trie (???) <- need to check this
// I think there is problem with the recursive function finding ?