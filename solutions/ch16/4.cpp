// EXERCISES
// 16-3. Read the introductory documentation for Boost IOStream.
// 16-4. Write a program that accepts a file path, opens the file, and prints summary
//       information about the contents, including word count, average word length,
//       and a histogram of the characters.
#include <iostream>
#include <fstream>
#include <unordered_map>

constexpr char pos_A{ 65 }, pos_Z{ 90 }, pos_a{ 97 }, pos_z{ 122 };
constexpr bool within_AZ(char x) { return pos_A <= x && pos_Z >= x; }
constexpr bool within_az(char x) { return pos_a <= x && pos_z >= x; }

std::ifstream open(const char* path, std::ios_base::openmode mode = std::ios_base::in) {
    std::ifstream file{ path, mode };
    if(!file.is_open()) {
        std::string err{ "Unable to open file " };
        err.append(path);
        throw std::runtime_error{ err };
    }
    file.exceptions(std::ifstream::badbit);
    return file;
}

struct AlphaHistogram {
    void ingest(std::string_view x) {
        size_t index{};
        for (const char &ch : x){
            if (within_AZ(ch)) counts[ch]++;
            else if (within_az(ch)) counts[ch - (pos_a - pos_A)]++;
        }
    }
    void print() const {
        for(char index{ pos_A }; index <= pos_Z; index++) {
            printf("%c: ", index);
            if(counts.count(index)) {
                unsigned int n_asterisks = counts.at(index);
                while (n_asterisks--) printf("*");
            }
            printf("\n");
        }
    }
    private:
        std::unordered_map<char, unsigned int> counts;
};

int main(int argc, char const *argv[]){
    if(argc != 2) {
        std::cout << "Please pass one argument - a file path." << std::endl;
        return 1;
    }

    std::ifstream input = open(argv[1]);
    std::string str;

    int word_count{};
    int total_length{};
    AlphaHistogram hist{};

    while(input >> str) {
        word_count++;
        total_length += str.length();
        hist.ingest(str);
    }
    std::cout << "Word count: " << word_count << '\n';
    std::cout << "Average length: " << double(total_length) / word_count << '\n';
    hist.print();
}