# CRC-64 Checksum Calculator

This C++ program calculates the CRC-64 checksum of input data using a lookup table. CRC-64 is a widely used error-checking algorithm for data transmission and storage systems.

Table of Contents
-----------------

*   [Usage](#usage)
*   [Compilation](#compilation)
*   [Options](#options)
*   [Example](#example)
*   [License](#license)

Usage
------

```
crc64 [-h --help
       -v --version
      ] [input data]
```


Compilation
-----

### Building from source
---

To use this program, follow these steps:

1.  Clone or download this repository to your local machine.
    
2.  Open a terminal or command prompt and navigate to the directory containing the program files.
    
3.  Compile the program using make:
    
    `make crc64`
    
4.  Run the program by providing input data as a command-line argument:
    
    `./crc64 "your_input_data_here"`
    

Replace `"your_input_data_here"` with the data for which you want to calculate the CRC-64 checksum.

### Using the release version
---
You can download the `crc64` executable from the [releases](https://github.com/joshiewtf/hashes/releases) page.

Options
-------

The program supports the following options:

*   `-h` or `--help`: Display the help message.
    
*   `-v` or `--version`: Display the program's version.
    

Example
-------

Here's how you can use the program to calculate the CRC-64 checksum of a string:


`./crc64 "Hello, CRC-64!"`

The program will output the 64-bit CRC checksum in the following format:


`64bit CRC: 0xXXXXXXXXXXXXXXXX`

License
-------

This program is provided under the [GNU GENERAL PUBLIC LICENSE](../LICENSE).

Feel free to use and modify the code according to your needs. If you have any questions or encounter issues, please create an [issue](https://github.com/joshiewtf/hashes/issues) in the GitHub repository. I'll be happy to help you out.