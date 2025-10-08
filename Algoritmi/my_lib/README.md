# Custom Library

This project is a custom library designed to provide various functionalities related to transportation data management. It includes functions for reading data from files, calculating delays, and printing information about transportation routes.

## Project Structure

```
custom-library
├── include
│   └── custom_library.h      # Header file with function declarations
├── src
│   ├── custom_library.c      # Implementation of the main library functions
│   └── utils.c               # Additional utility functions
├── tests
│   └── test_custom_library.c  # Unit tests for the library functions
├── Makefile                   # Build instructions
└── README.md                  # Project documentation
```

## Installation

To build the library, navigate to the project directory and run:

```
make
```

This will compile the source files and create the library.

## Usage

To use the custom library in your project, include the header file:

```c
#include "custom_library.h"
```

You can then call the functions provided by the library, such as:

- `ritardo_tot`: Calculate the total delay for a specific route.
- `leggiFile`: Read data from a specified file.
- `stampaVoce`: Print information about a transportation route.

## Running Tests

To run the unit tests, execute the following command:

```
make test
```

This will compile and run the tests defined in `test_custom_library.c`.

## Contributing

Contributions are welcome! Please feel free to submit a pull request or open an issue for any enhancements or bug fixes.

## License

This project is licensed under the MIT License. See the LICENSE file for more details.