# GameMath Library

A header-only C++ library for game mathematics, providing commonly used data structures and functions.

## Features

-   **Matrix Class**: A template-based matrix class with support for various arithmetic types and operations, built on top of Eigen.
-   **Vector Class**: A template-based vector class for 2D, 3D, and 4D vectors with common operations.
-   **Matrix Transformations**: Functions for rotating and flipping matrices.
-   **Game Math Algorithms**: Includes linear interpolation, cross product, and collision detection functions.
-   **Random Number Generation**: A random number generator with utility functions for generating random points within a circle or on its circumference.
-   **Easing Functions**: Common easing functions for smooth transitions.

## Dependencies

-   Eigen: Used for matrix and vector operations.
```shell
sudo apt install libeigen3-dev # linux
```

## Usage

Include the `GameMath.hpp` header file in your project.

```cpp
#include "GameMath.hpp"

int main() {
    // Use the library here
    return 0;
}