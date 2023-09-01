/**
 * @file char_counter.cpp
 * Implementation of the CharFreq class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */

using std::pair;
using std::string;
using std::vector;

/**
 * Constructs a CharFreq object based on the name of a file.
 *
 * @param ifilename Input file to read characters from.
 */
template <template <class K, class V> class Dict>
CharFreq<Dict>::CharFreq(const string& filename)
    : dict(256) {
    TextFile infile(filename);

    while (infile.good()) {
        for (char c : infile.getNextWord()) dict[c]++;
    }
}

/**
 * Returns a vector of pairs, where the first element is the character and
 * the second element is the frequency with which the character appeared in
 * the file for the CharFreq object. Only characters with frequency greater
 * than or equal to the threshold are placed in the vector.
 *
 * @param threshold The threshold at which a character, frequency pair is
 *    added to the vector.
 * @return A vector of pairs of characters and frequencies.
 */
template <template <class K, class V> class Dict>
vector<pair<char, int>> CharFreq<Dict>::getChars(int threshold) {
    vector<pair<char, int>> ret;
    // we iterate over the hash tables using a for each loop: kv.first will give
    // us the key, kv.second will give us the value.
    for (const auto& kv : dict) {
        if (kv.second >= threshold) ret.push_back(kv);
    }

    return ret;
}
