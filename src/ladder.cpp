#include "ladder.h"
#include "dijkstras.h"
#include <queue> 
#include <set>
#include <string>
#include <fstream>

void error(string word1, string word2, string msg) { 
    cout << "ERROR: " << word1 << " " << word2 << " " << msg <<endl;
}
bool edit_distance_within(const std::string& str1, const std::string& str2, int d) { 
    if (str1.size() == str2.size()) { 
       return (char_differ (str1, str2) == d);
    }
        
    if (str1.size() + 1 ==  str2.size()) {
            //string copyWrd2 = str2;
    
            for (int i = 0; i < str1.size(); i++) { 
                if (str1[i] != str2[i]) { 
                    string copyWrd2 = str2;
                    copyWrd2.erase(i, 1);
                    return (char_differ (copyWrd2, str1) == d);
                }
            }
        string copyWrd2 = str2;
        copyWrd2.erase(str2.size() - 1, 1);
        return (char_differ(copyWrd2, str1) == d);

        }
    else if (str2.size() + 1 == str1.size()){ 
            for (int i = 0; i < str2.size(); i++) { 
                if (str1[i] != str2[i]) { 
                    string copyWrd1 = str1;
                    copyWrd1.erase(i, 1);
                    return (char_differ (copyWrd1, str2) == d);
                }
            }
            string copyWrd1 = str1;    //  word1 is longer
            copyWrd1.erase(str1.size() - 1, 1);
            return (char_differ (copyWrd1,  str2) == d);
    }

    return false;
}
int char_differ(const string& word1, const string& word2) { 
    int editDist = 0;
    for (int i = 0; i < word1.size(); i++) { 
        if (word1[i] != word2[i]) { 
            editDist++; 

            if (editDist > 1) { 
            return -1;
            }
        }
    }   //  end for 
    return editDist;
}
bool is_adjacent(const string& word1, const string& word2) { 
    return edit_distance_within(word1, word2, 1);
}
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) { 
    queue <vector<string> > wordLdder;
    wordLdder.push({begin_word});

    set <string> isVisited;
    isVisited.insert(begin_word);

    while (!wordLdder.empty()) { 
        vector<string> currLdder = wordLdder.front();
        wordLdder.pop();
        string lstWord = currLdder.back();

        for (auto currWord : word_list) { 
            if (is_adjacent(lstWord, currWord) && isVisited.find(currWord) == isVisited.end()) { 
                isVisited.insert(currWord);

                vector<string> newLdder = currLdder;
                newLdder.push_back(currWord);

                if (currWord == end_word) { 
                    return newLdder;
                }
                wordLdder.push(newLdder);
            }
        }   //  end for
    }
    return {};
}
void load_words(set<string> & word_list, const string& file_name) { 
    ifstream in(file_name);

     if (!in) {
        error(" File:  ", file_name, "could NOT be opened!");
        return;
    }
    for (std::string word; (in >> word);) { 
        word_list.insert(word);
    }
    in.close();
}
void print_word_ladder(const vector<string>& ladder) { 
    for (int i = 0; i < ladder.size(); i++) { 
        cout << ladder[i] << " ";
    }
    cout << endl;
};
void my_assert(int wrdLdderResult, int expected) { 
    if (wrdLdderResult == expected) { 
        cout << "PASSED!" << endl; ;
        cout << "Actual: " << wrdLdderResult <<endl;
        cout << "Expected: " << expected <<endl;
    } 
    else { 
        cout << "FAILED! " << endl;
        cout << "Actual: " << wrdLdderResult <<endl;
        cout << "Expected: " << expected <<endl;
    }
    cout <<endl;
}
void verify_word_ladder() { 
    set<string> word_list;
    load_words (word_list,"src/words.txt");

    vector <string> wrdldder = generate_word_ladder("cat", "dog", word_list);
    my_assert(wrdldder.size(), 4);
    print_word_ladder (wrdldder);

    vector <string> wrdldder2 = generate_word_ladder("marty", "curls", word_list);
    my_assert(wrdldder2.size(),6);
    print_word_ladder (wrdldder2);

    vector <string> wrdldder3 = generate_word_ladder("code", "data", word_list);
    my_assert(wrdldder3.size(),6);
    print_word_ladder (wrdldder3);

    vector <string> wrdldder4 = generate_word_ladder("work", "play", word_list);
    my_assert(wrdldder4.size(), 6);
    print_word_ladder (wrdldder4);

    vector <string> wrdldder5 = generate_word_ladder("sleep", "awake", word_list);
    my_assert(wrdldder5.size(), 8);
    print_word_ladder (wrdldder5);

    vector <string> wrdldder6 = generate_word_ladder("car", "cheat", word_list);
    my_assert(wrdldder6.size(), 4);
    print_word_ladder (wrdldder6);
}