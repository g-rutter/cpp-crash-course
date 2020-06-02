// 9-2. Implement a program that accepts an arbitrary number of command line arguments,
//      counts the length in characters of each argument,
//      and prints a histogram of the argument length distribution.
#include <cstdio>
#include <unordered_map>


struct LengthHistogram {
    void ingest_args(const int argc, char const *argv[]){
        int n_chars{};
        for (size_t i = 0; i < argc; i++){
            const char* chars = argv[i];
            n_chars = strlen(chars);
            counts[n_chars]++;

            max = max < n_chars ? n_chars : max;
            min = min > n_chars ? n_chars : min;
        };
    }

    void printf_hist() {
        int n_asterisks{};
        for(int i=min; i <= max; i++){
            n_asterisks = counts[i];
            printf("%2d:", i);
            while(n_asterisks--) printf("*");
            printf("\n");
        }
    }

    private:
        std::unordered_map<int, int> counts{};
        int max{};
        int min{};
};

int main(int argc, char const *argv[])
{
    LengthHistogram lh{};
    lh.ingest_args(argc, argv);
    lh.printf_hist();
    return 0;
}
