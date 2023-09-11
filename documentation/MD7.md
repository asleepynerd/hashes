
MD7 Message Digest Calculator
=============================

This C++ program calculates the MD7 message digest (hash) of input data using the MD7 algorithm. MD7 is a cryptographic hash function designed for message integrity and data authentication.

Table of Contents
-----------------

*   [Usage](#usage)
*   [Compilation](#compilation)
*   [Options](#options)
*   [Examples](#examples)
*   [License](#license)

Usage
-----

```
md7 [-h --help
       -v --version
       -f --file <filename>
      ] [input data]
```


Compilation
-----

### Building from source

To use this program, follow these steps:

1.  Clone or download this repository to your local machine.
    
2.  Open a terminal or command prompt and navigate to the directory containing the program files.
    
3.  Compile the program using make.
    
    `make md7`
    
4.  Run the program with one of the following options:
    
    *   To calculate the MD7 digest of a message:
        

        
        `./md7 "your_message_here"`
        
    *   To calculate the MD7 digest of a message from a file:
        

        
        `./md7 -f <filename>`
        
    *   To display the help message:
        

        
        `./md7 -h`
        
    *   To display the program's version:
        
        
        `./md7 -v`
        

Replace `"your_message_here"` with the message for which you want to calculate the MD7 digest, and `<filename>` with the name of the file containing the message.

### Using the release version
-----
You can download the `md7` executable from the [releases](https://github.com/joshiewtf/hashes/releases) page.


Options
-------

The program supports the following options:

*   `-h` or `--help`: Display the help message.
    
*   `-v` or `--version`: Display the program's version.
    
*   `-f <filename>`: Calculate the MD7 digest of a message from a file. Provide the filename as an argument.
    

Examples
--------

### Calculate MD7 Digest of a Message

To calculate the MD7 digest of a message, run the following command:

bashCopy code

`./md7 "Hello, MD7!"`

The program will output the MD7 digest in hexadecimal format.

### Calculate MD7 Digest from a File

To calculate the MD7 digest of a message stored in a file, use the `-f` option with the filename as an argument. For example:

bashCopy code

`./md7 -f input.txt`

The program will read the contents of the `input.txt` file and calculate the MD7 digest.

License
-------

This program is provided under the [MIT License](LICENSE).

Feel free to use and modify the code according to your needs. If you have any questions or encounter issues, please create an [issue](https://github.com/yourusername/md7/issues) in the GitHub repository. I'll be happy to help you out.
