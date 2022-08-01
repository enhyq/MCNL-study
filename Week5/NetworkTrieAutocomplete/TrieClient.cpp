#include <iostream>

// istingstream
#include <iostream>
#include <sstream>

// need to compile with -lncurses option!
#include <ncurses.h>         // ncurses lib

// Network
#include <unistd.h>         // for data transfer
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>

using namespace std;

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

    // default screen print
    mvprintw(0, 0, "(Press ESC to quit)");    // 화면의 0행, 0열부터 출력
    mvprintw(1, 0, "Search Word: ");
    mvprintw(2, 0, "---------------------------------------------");
    move(1,13);                         // input cursor position
    refresh();                          // 화면에 출력하도록 합니다
}

void terminate_ncurses() {
    endwin();                           // restores terminal
}

int main(int argc, char const *argv[])
{
    char ch;
    int printNum = 20, i;

    string queryStr = "", currentWord, tempWord;

      struct response{
        char found_phrases[20][100];
    };

    struct request {
        string queryString;
        string currentWord;
    };

    response r;
    request rq;

    // 0. CONNECT TO SERVER
    // sockaddr_in *serv_addr = new sockaddr_in();
    sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;

    int ss = socket(PF_INET, SOCK_STREAM, 0);
    if (ss == -1)
    {
        cout << "failed to create socket" << endl;
        return -1; // socket creation fail
    }

    string ip;
    int port;
    while(true)
    {
        cout << "Server IP address: ";
        cin >> ip;
        cout << "Server PORT: ";
        cin >> port;

        serv_addr.sin_port = htons(port);
        serv_addr.sin_addr.s_addr = inet_addr(ip.c_str());
        serv_addr.sin_len = sizeof(serv_addr);      // not sure

        if(connect(ss, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
		{
            cout << "Could not connect to server" << endl;
            continue;
        }
        cout << "Connected to the server!" << endl;
        break;
    }


    initialize_ncurses();

    /********************* *
     * 1. Get Input        *
     * ********************/
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
        else continue;

        for(istringstream is(queryStr) ; is >> tempWord ; ) {
            currentWord = tempWord;
        }
        if(queryStr.length() == 0) currentWord.clear(); // clear currentWord when there is no queryStr
        
        // print input word on console
        // cout << queryStr << endl;
        mvprintw(1, 13, "%s", queryStr.c_str());        // row, col, str
        clrtoeol();

        // // set request struct
        // rq.queryString = queryStr;
        // rq.currentWord = currentWord;

        // send request to server
        long len = queryStr.length();
        write(ss, &len, sizeof(len));
        write(ss, queryStr.c_str(), queryStr.size());

        // get response from server
        recv(ss, &r, sizeof(r), MSG_WAITALL);
        mvprintw(30, 0, "%s", "received response from server!");
        move(1,13+queryStr.length());                   // input cursor position
        string topQueryResult;
        move(3,0);                                      // output top line
        for(i=0; i<printNum; i++) {
            if(r.found_phrases[i][0] == '\0') break;

            topQueryResult = r.found_phrases[i];                        // remove top element

            // need to fix below code after implementing reading searching string in the middle

            // find word index
            string queryStrNoSpace = queryStr;
            if(queryStrNoSpace.back() == ' ')
                queryStrNoSpace.pop_back();

            int idxBegin = topQueryResult.find(queryStrNoSpace);
            if(idxBegin != 0) {
                if(idxBegin + queryStrNoSpace.length() != topQueryResult.length())
                    if(!(topQueryResult[idxBegin-1] == ' ' && topQueryResult[idxBegin + queryStrNoSpace.length()] == ' ')) {
                        // mvprintw(0, 30, "%d", idxBegin);
                        idxBegin = topQueryResult.find(queryStrNoSpace, idxBegin+queryStrNoSpace.length());
                        // mvprintw(0, 35, "%d", idxBegin);
                    }
            }
            int idxEnd = idxBegin + queryStrNoSpace.length();

            move(3+i, 0);
            printw("%s", topQueryResult.substr(0, idxBegin).c_str());
            attron(COLOR_PAIR(1));
            printw("%s", queryStrNoSpace.c_str());
            attroff(COLOR_PAIR(1));
            printw("%s", topQueryResult.substr(idxEnd, topQueryResult.length()).c_str());
            // DEBUG PRINT
            // printw("%s %d", topQueryResult.second.substr(idxEnd, topQueryResult.second.length()).c_str(), topQueryResult.first);
            clrtoeol();                                 // clear to end of line
        }
        clrtobot();                                     // clear from cursor until the last line
        move(1,13+queryStr.length());                   // input cursor position
    }

    terminate_ncurses();
    
    return 0;
}
