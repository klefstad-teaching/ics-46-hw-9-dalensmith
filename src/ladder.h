#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

void error(std::string word1, std::string word2, std::string msg);
//bool edit_distance_within(const std::string& str1, const std::string& str2, int d);
bool is_adjacent(const std::string& word1, const std::string& word2);
bool same_length_adj(const std::string& word1, const std::string& word2, int length);
bool dif_length_adj(const std::string& word1, const std::string& word2, int length1, int length2);
std::vector<std::string> generate_word_ladder(const std::string& begin_word, const std::string& end_word, const std::set<std::string>& word_list);
void load_words(std::set<std::string>& word_list, const std::string& file_name);
void print_word_ladder(const std::vector<std::string>& ladder);
void verify_word_ladder();