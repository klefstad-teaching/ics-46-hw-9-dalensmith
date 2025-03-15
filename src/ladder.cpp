#include "ladder.h"

void error(std::string word1, std::string word2, std::string msg) {
    std::cerr << "ERROR: " << word1 << " and " << word2 << " " << msg << std::endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int length1 = str1.length();
    int length2 = str2.length();
    if(std::abs(length1 - length2) > d)
        return 0;
    int iter1 = 0;
    int iter2 = 0;
    int dif = std::abs(length1 - length2);
    while(iter1 < length1 && iter2 < length2) {
        if(str1[iter1] != str2[iter2]) {
            if(length1 < length2 && std::abs(iter1 - iter2) < dif)
                ++iter2;
            else if(length2 < length1 && std::abs(iter1 - iter2) < dif)
                ++iter1;
            else {
                ++dif;
                ++iter1;
                ++iter2;
            }
        } else {
            ++iter1;
            ++iter2;
        }
    }
    return dif <= d;
}

bool same_length_adj(const std::string& word1, const std::string& word2, int length) {
    int different = 0;
    for(int i = 0; i < length; ++i) {
        if(word1[i] != word2[i]) {
            if(different == 1)
                return 0;
            ++different;
        }
    }
    return 1;
}

bool dif_length_adj(const std::string& word1, const std::string& word2, int length1, int length2) {
    int different = 0;
    int iter1 = 0;
    int iter2 = 0;
    while(iter1 < length1 && iter2 < length2) {
        if(word1[iter1] != word2[iter2]) {
            if(different == 1)
                return 0;
            ++different;
            ++((length1 < length2) ? iter2 : iter1);
        } else {
            ++iter1;
            ++iter2;
        }
    }
    return 1;
}

bool is_adjacent(const std::string& word1, const std::string& word2) {
    int length1 = word1.length();
    int length2 = word2.length();
    if(length1 == length2)
        return same_length_adj(word1, word2, length1);
    else if(std::abs(length1 - length2) == 1)
        return dif_length_adj(word1, word2, length1, length2);
    return 0;
}

std::vector<std::string> generate_word_ladder(const std::string& begin_word, const std::string& end_word, const std::set<std::string>& word_list) {
    if(begin_word == end_word)
        return std::vector<std::string>();
    std::queue<std::vector<std::string>> ladder_q;
    ladder_q.push({begin_word});
    std::set<std::string> visited;
    visited.insert(begin_word);
    while(!ladder_q.empty()) {
        std::vector<std::string> ladder = ladder_q.front();
        ladder_q.pop();
        std::string last = ladder.back();
        for(const std::string& word : word_list) {
            if(is_adjacent(last, word) && visited.find(word) == visited.end()) {
                visited.insert(word);
                std::vector<std::string> cpy_ladder = ladder;
                cpy_ladder.push_back(word);
                if(word == end_word)
                    return cpy_ladder;
                ladder_q.push(cpy_ladder);
            }
        }
    }
    error(begin_word, end_word, "do not have a path between them.");
    return std::vector<std::string>();
}

void load_words(std::set<std::string>& word_list, const std::string& file_name) {
    std::ifstream in(file_name);
    std::string word;
    while(in >> word)
        word_list.insert(word);
    in.close();
}

void print_word_ladder(const std::vector<std::string>& ladder) {
    if(ladder.size() == 0) {
        std::cout << "No word ladder found." << std::endl;
        return;
    }
    std::cout << "Word ladder found: ";
    for(const std::string& word : ladder)
        std::cout << word << ' ';
    std::cout << std::endl;
}

#define my_assert(e) {std::cout << #e << ((e) ? " passed": " failed") << std::endl;}

void verify_word_ladder() {
    std::set<std::string> word_list;
    load_words(word_list, "src/words.txt");
    my_assert(generate_word_ladder("cat", "cat", word_list).size() == 0);
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}