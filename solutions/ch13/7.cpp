// 13-7. Implement a Matrix class like SquareMatrix in Listing 13-38.
//       Your Matrix should allow unequal numbers of rows and columns.
//       Accept as your constructor’s first argument the number of rows in Matrix.

#include <cmath>
#include <stdexcept>
#include <initializer_list>
#include <vector>
size_t square_root(size_t x) {
    const auto result = static_cast<size_t>(sqrt(x));
    if (result * result != x) throw std::logic_error{ "Not a perfect square." };
    return result;
}

template <typename T>
struct Matrix {
    Matrix(size_t n_rows, std::initializer_list<T> val)
        : m_n_rows{n_rows},
          m_n_cols{val.size() / m_n_rows},
          m_data(m_n_rows, std::vector<T>{}) {
        auto itr = val.begin();
        for(size_t row{}; row<m_n_rows; row++){
            m_data[row].assign(itr, itr+m_n_cols);
            itr += m_n_cols;
        }
    }
    T& at(size_t row, size_t col) {
        if (row >= m_n_rows || col >= m_n_cols)
            throw std::out_of_range{ "Index invalid." };
        return m_data[row][col];
    }

    const size_t m_n_rows;
    const size_t m_n_cols;

    private:
        std::vector<std::vector<T>> m_data;
};

int main() {
    Matrix mymatrix(2, {2, 3, 4, 5});
    printf("%d\n", mymatrix.at(1, 1)); // Expect 5. See 5.
}