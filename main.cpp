#include <iostream>

void free_matrix(int** a, size_t n)
{
    for (size_t i = 0; i < n; ++i) {
        delete[] a[i];
    }
    delete[] a;
}

size_t max_size(size_t x, size_t y)
{
    if (x > y) {
        return x;
    }
    return y;
}

int** read_matrix(size_t n, size_t m, int& err)
{
    err = 0;

    int** a;
    try {
        a = new int*[n];
    } catch (...) {
        err = 2;
        return nullptr;
    }

    for (size_t i = 0; i < n; ++i) {
        try {
            a[i] = new int[m];
        } catch (...) {
            free_matrix(a, i);
            err = 2;
            return nullptr;
        }
    }

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            std::cin >> a[i][j];
            if (std::cin.fail()) {
                free_matrix(a, n);
                err = 1;
                return nullptr;
            }
        }
    }
    return a;
}

size_t row_len(size_t i, size_t n1, size_t m1, size_t n2, size_t m2)
{
    size_t k = 0;
    if (i < n1) k += m1;
    if (i < n2) k += m2;
    return k;
}

int** concat_rows(
    const int* const* lhs, size_t n1, size_t m1,
    const int* const* rhs, size_t n2, size_t m2
)
{
    size_t n = max_size(n1, n2);

    int** res;
    try {
        res = new int*[n];
    } catch (...) {
        return nullptr;
    }

    for (size_t i = 0; i < n; ++i) {
        try {
            res[i] = new int[row_len(i, n1, m1, n2, m2)];
        } catch (...) {
            free_matrix(res, i);
            return nullptr;
        }

        size_t k = 0;
        if (i < n1) {
            for (size_t j = 0; j < m1; ++j) {
                res[i][k++] = lhs[i][j];
            }
        }
        if (i < n2) {
            for (size_t j = 0; j < m2; ++j) {
                res[i][k++] = rhs[i][j];
            }
        }
    }
    return res;
}

int main()
{
    int n1, m1, n2, m2;
    int err;

    std::cin >> n1 >> m1;
    if (std::cin.fail()) {
        std::cerr << "Input error\n";
        return 1;
    }
    if (n1 <= 0 || m1 <= 0) {
        std::cerr << "Input error\n";
        return 1;
    }
    int** a = read_matrix(n1, m1, err);
    if (a == nullptr) {
        std::cerr << "Error\n";
        return err;
    }

    std::cin >> n2 >> m2;
    if (std::cin.fail()) {
        std::cerr << "Input error\n";
        free_matrix(a, n1);
        return 1;
    }
    if (n2 <= 0 || m2 <= 0) {
        std::cerr << "Input error\n";
        free_matrix(a, n1);
        return 1;
    }
    int** b = read_matrix(n2, m2, err);
    if (b == nullptr) {
        std::cerr << "Error\n";
        free_matrix(a, n1);
        return err;
    }

    int** c = concat_rows(a, n1, m1, b, n2, m2);
    if (c == nullptr) {
        std::cerr << "Memory error\n";
        free_matrix(a, n1);
        free_matrix(b, n2);
        return 2;
    }

    size_t n = max_size(n1, n2);
    for (size_t i = 0; i < n; ++i) {
        size_t len = row_len(i, n1, m1, n2, m2);
        for (size_t j = 0; j < len; ++j) {
            std::cout << c[i][j] << " ";
        }
        std::cout << "\n";
    }

    free_matrix(a, n1);
    free_matrix(b, n2);
    free_matrix(c, n);
    return 0;
}
