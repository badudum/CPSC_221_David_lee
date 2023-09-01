/**
 * @file common_words.cpp
 * Implementation of the CommonWords class.
 *
 * @author Zach Widder
 * @date Fall 2014
 */

#include "common_words.h"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::endl;
using std::feof;

string remove_punct(const string& str)
{
    string ret;
    std::remove_copy_if(str.begin(), str.end(), std::back_inserter(ret),
                        [](int c) { return std::ispunct(c); });
    return ret;
}

CommonWords::CommonWords(const vector<string>& filenames)
{
    // initialize all member variables
    init_file_word_maps(filenames);
    init_common();
}

void CommonWords::init_file_word_maps(const vector<string>& filenames)
{
    // go through all files
    for (size_t i = 0; i < filenames.size(); i++) {
        // get the corresponding vector of words that represents the current file
        vector<string> words = file_to_vector(filenames[i]);
        map<std::string,unsigned int> word_map;
        for(auto const & x : words){
            auto it = word_map.find(x);
            if(it == word_map.end()){
                word_map[x] = 1;
            }
            else{
                it->second++;
            }
        }
        file_word_maps.push_back(word_map);

    }
}

void CommonWords::init_common()
{
    for(auto const & x: file_word_maps){
        for(auto const& y: x){
            auto find = common.find(y.first);
            if(find == common.end()){
                common[y.first] = 1;
            }
            else{
                find->second++;
            }
        }
    }

}

/**
 * @param n The number of times to word has to appear.
 * @return A vector of strings. The vector contains all words that appear
 * in each file >= n times.
 */
vector<string> CommonWords::get_common_words(unsigned int n) const
{
    vector<string> out;
    unsigned int threshold = file_word_maps.size();
    vector<string> keep;

    for(auto const& x: common){
        if(x.second >= threshold){
            keep.push_back(x.first);
        }
    }
    for(auto y: keep){
        bool keep =true;
        for(auto const& x: file_word_maps){
            auto find = x.find(y);
            if(find->second < n){
                keep = false;
            }
        }
        if(keep == true){
            out.push_back(y);
        }
           
    }
    
    return out;
}

/**
 * Takes a filename and transforms it to a vector of all words in that file.
 * @param filename The name of the file that will fill the vector
 */
vector<string> CommonWords::file_to_vector(const string& filename) const
{
    ifstream words(filename);
    vector<string> out;

    if (words.is_open()) {
        std::istream_iterator<string> word_iter(words);
        while (!words.eof()) {
            out.push_back(remove_punct(*word_iter));
            ++word_iter;
        }
    }
    return out;
}
