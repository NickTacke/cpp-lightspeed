# cpp-lightspeed: C++ Client for Lightspeed eCom API

`cpp-lightspeed` is a C++ library for interacting with the Lightspeed eCom API. It provides a simple interface to access various API endpoints, handling HTTP communication and JSON parsing.

## Features

- Easy-to-use C++ interface for Lightspeed API.
- Supports API Key and Secret authentication.
- Handles requests to different Lightspeed API clusters (EU1, US1) or custom base URLs.
- Provides methods for common HTTP operations: GET, POST, PUT, DELETE.
- Includes pre-defined DTOs (Data Transfer Objects) for API resources like Account and Products.
- Uses `nlohmann/json` for robust JSON parsing and serialization.
- Uses `cpp-httplib` for HTTP/HTTPS communication (with OpenSSL for HTTPS).
- Cross-platform (utilizes CMake for building).

## Dependencies

The library relies on the following external libraries:

- **OpenSSL**: For HTTPS communication. This is expected to be installed on the system.
- **[cpp-httplib](https://github.com/yhirose/cpp-httplib)**: A C++ HTTP/HTTPS server and client library. Included directly in `lib/httplib/`.
- **[nlohmann/json](https://github.com/nlohmann/json)**: A C++ JSON library. Included directly in `lib/nlohmann/`.

## Building

The project uses CMake for building.

1.  **Prerequisites**:

    - CMake (version 3.10 or higher)
    - A C++17 compliant compiler (e.g., GCC, Clang, MSVC)
    - OpenSSL development libraries installed.

2.  **Build Steps**:

    ```bash
    # Create a build directory
    mkdir build
    cd build

    # Configure the project
    cmake ..

    # Build the library
    cmake --build .
    ```

    This will build the static library `libcpp-lightspeed.a` (or `cpp-lightspeed.lib` on Windows) in the `build` directory.

## Basic Usage

```cpp
#include "lightspeed.h" // Main library header
#include <iostream>
#include <vector>

int main() {
    try {
        // Initialize the API client for the EU1 cluster
        LightspeedApi api("YOUR_API_KEY", "YOUR_API_SECRET", LightspeedApi::Cluster::EU1);

        auto products = api.products.getPage(1);
        auto product = products.at(10);
        auto variants = api.getResource(product.variants);

        std::cout << "Product: " << product.title << std::endl;
        for (auto variant : variants) {
            std::cout << "Article code: " << variant.articleCode << std::endl;
            std::cout << "Stock level: " << variant.stockLevel << std::endl;
        }

        auto rateLimitInfo = api.getLastRateLimitInfo();
        std::cout << "--------------------------------" << std::endl;
        std::cout << "5 minute limit: " << rateLimitInfo.limit5Min.remaining;
        std::cout << "/" << rateLimitInfo.limit5Min.limit << std::endl;
        std::cout << "Resets in " << rateLimitInfo.limit5Min.reset << " seconds" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
```

**Note**: You will need to link against the `cpp-lightspeed` library and OpenSSL when compiling your application. With CMake, you can use `find_package(OpenSSL REQUIRED)` and then link with `cpp-lightspeed` and `OpenSSL::SSL OpenSSL::Crypto`.

## Available Endpoints

The library currently provides access to the following endpoints:

- **Account**:
  - `get()`: Retrieves account details.
- **Products**:
  - `getPage(int page)`: Retrieves a paginated list of products.
  - `getCount()`: Retrieves the total number of products.
  - `get(int id)`: Retrieves a specific product by its ID.
  - `create(Lightspeed::dto::Product product)`: Creates a new product.

## License

This project is licensed under the MIT License - see the LICENSE.md file for details.

## Contributing

Contributions are welcome! If you'd like to contribute to `cpp-lightspeed`, please follow these general guidelines:

1.  **Reporting Bugs**:

    - Check the existing issues to see if your bug has already been reported.
    - If not, open a new issue. Please include a clear title and description, as much relevant information as possible, and a code sample or an executable test case demonstrating the expected behavior that is not occurring.

2.  **Suggesting Enhancements**:

    - Open an issue with the tag `[enhancement]` or `[feature request]`.
    - Provide a clear and detailed explanation of the proposed enhancement and its potential benefits.

3.  **Pull Requests**:

    - Fork the repository and create your branch from `main` (or the relevant development branch).
    - If you've added code that should be tested, add tests.
    - Make sure your commit messages are clear and descriptive.
    - Open a pull request to the `main` branch. Provide a clear description of the changes and link to any relevant issues.

4.  **Coding Style**:

    - Try to follow the existing coding style to maintain consistency.
    - Ensure code is well-commented, especially for complex logic.

5.  **License**:
    - By contributing, you agree that your contributions will be licensed under the project's MIT License.

We appreciate your help in making `cpp-lightspeed` better!
