#include <iostream>
#include <vector>

// Annotated DAXPY kernel modified for chunks
void daxpy_chunk_annotated(double a,
                           const std::vector<double>& x, // Input vector x
                           std::vector<double>& y,       // Input/output vector y
                           size_t start,                 // Starting index for this chunk
                           size_t end) {                  // Ending index (exclusive) for this chunk
    for (size_t i = start; i < end; ++i) {
        y[i] = a * x[i] + y[i]; // Perform the DAXPY operation for this element
    }
}

int main() {
    // Example usage (you would integrate this with your threading logic)
    size_t size = 10;
    double alpha = 2.0;
    std::vector<double> x = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    std::vector<double> y = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};

    // Example of calling the chunked function for a portion
    daxpy_chunk_annotated(alpha, x, y, 0, 5); // Process the first half

    for (double val : y) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}