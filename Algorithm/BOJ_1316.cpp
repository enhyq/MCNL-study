/**
 * @author Eunhyeok Kwon
 * @date 2022-07-18 ~ 2022-07-18
 * @link https://www.acmicpc.net/problem/1316
 */

#include <iostream>
#include <string>

using namespace std;

/*
 * given a word, if a letter in the word is separated, it is not considered a group word
 * else it is group word
 * ex) aabbcc == group word
 * ex2) aabbaa == not a group word
 */

int main(int argc, char const *argv[])
{
    int N, i, j, count=0;
    cin >> N;
    bool group_word_check[26]; // a-z (97~)
    for(i=0; i<26; i++) group_word_check[i] = false;      // reset group_word array
    string word;
    char letter;
    for(i=0; i<N; i++) {
        cin >> word;
        for(j=0; j<26; j++) group_word_check[j] = false;      // reset group_word array
        
        for(j=0; j<word.length(); j++) {
            letter = word[j];
            // if letter is already checked, it's not a group word
            if(group_word_check[(letter-97)] == true) {
                break;
            }
            else {
                group_word_check[(letter-97)] = true;
                while(word[++j] == letter) {}
                if(word[j] == '\0') { 
                    count++;                // if EOF
                    // cout << "YES";
                }
                // cout << "w:" << word[j];
                // cout << "j:" << j << " ";
                j--;
            }
        }
        // cout << endl;
    }
    cout << count << endl;
    

    return 0;
}
