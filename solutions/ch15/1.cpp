// EXERCISES
// 15-1. Refactor the histogram calculator in Listings 9-30 and 9-31 to use std::string.
//       Construct a string from the program’s input and modify AlphaHistogram to accept a
//       string_view or a const string& in its ingest method. Use a range-based for loop to
//       iterate over the ingested elements of string. Replace the counts field’s type with an
//       associative container.
#include <cstdio>
#include <string_view>
#include <unordered_map>

constexpr char pos_A{ 65 }, pos_Z{ 90 }, pos_a{ 97 }, pos_z{ 122 };
constexpr bool within_AZ(char x) { return pos_A <= x && pos_Z >= x; }
constexpr bool within_az(char x) { return pos_a <= x && pos_z >= x; }

struct AlphaHistogram {
    void ingest(std::string_view x);
    void print() const;
    private:
        std::unordered_map<char, unsigned int> counts;
};

void AlphaHistogram::ingest(std::string_view x) {
    size_t index{};
    for (const char &ch : x){
        if (within_AZ(ch)) counts[ch]++;
        else if (within_az(ch)) counts[ch - (pos_a - pos_A)]++;
    }
}

void AlphaHistogram::print() const {
    for(char index{ pos_A }; index <= pos_Z; index++) {
        printf("%c: ", index);
        if(counts.count(index)) {
            unsigned int n_asterisks = counts.at(index);
            while (n_asterisks--) printf("*");
        }
        printf("\n");
    }
}

int main(int argc, char** argv) {
    AlphaHistogram hist;
    for(int i{ 1 }; i<argc; i++) {
        hist.ingest(argv[i]);
    }
    hist.print();
}