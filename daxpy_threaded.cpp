#include <iostream>
#include <vector>
#include <thread>
#include <cmath>
#include <iomanip> // For setprecision

void daxpy_chunk(double a, const std::vector<double>& x, std::vector<double>& y, size_t start, size_t end) {
    for (size_t i = start; i < end; ++i) {
        y[i] = a * x[i] + y[i];
    }
}

int main() {
    size_t size = 1000000;
    double alpha = 2.5;
    std::vector<double> x(size, 1.0);
    std::vector<double> y(size, 2.0);
    int num_threads = 4;
    std::vector<std::thread> threads;
    size_t chunk_size = std::ceil(static_cast<double>(size) / num_threads);

    for (int i = 0; i < num_threads; ++i) {
        size_t start = i * chunk_size;
        size_t end = std::min(start + chunk_size, size);
        threads.push_back(std::thread(daxpy_chunk, alpha, std::cref(x), std::ref(y), start, end));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    // Print a small portion of the result with higher precision
    std::cout << "DAXPY Result (first 10 elements):" << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    for (int i = 0; i < 10; ++i) {
        std::cout << "y[" << i << "] = " << y[i] << std::endl;
    }

    return 0;
}