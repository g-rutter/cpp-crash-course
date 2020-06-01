#ifndef PRIME_ITER_H_
#define PRIME_ITER_H_

struct PrimeNumberIterator {
    bool operator!=(const int x);
    int operator*();
    PrimeNumberIterator& operator++();

    private:
        int current{ 2 };
};

struct PrimeNumberRange {
    explicit PrimeNumberRange(const int max);
    PrimeNumberIterator begin() const;
    int end() const;

    private:
        const int max;
};

#endif