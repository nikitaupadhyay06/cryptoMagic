# Mini Project 2: cryptoMagic Encryption/Decryption Tool 
### Author: Nikita Upadhyay

## 🔐 Summary  
This program is a command-line utility written in C that encrypts or decrypts the contents of text files based on user input. The user can provide a file located in the designated folder and choose to either encrypt (`-E`) or decrypt (`-D`) the file. The encryption algorithm transforms characters into hexadecimal representations with ASCII shifts and special handling for tabs and newlines. The program generates a `.crp` file for encryption and a `.txt` file for decryption, while ensuring existing output files are not overwritten.

This project highlights fundamental C programming techniques such as file I/O, string manipulation, ASCII encoding, and command-line argument handling.

## 🚀 Features  
- **Two Operation Modes**: Encrypt (`-E`) or decrypt (`-D`) any valid text-based file.  
- **Hexadecimal Encoding**: Encrypts characters into two-digit hexadecimal format.  
- **Tab and Newline Handling**: Tabs are replaced with `TT`; newlines are preserved.  
- **Custom Output File Naming**: Automatically generates `.crp` (encrypted) or `.txt` (decrypted) files.  
- **File Safety**: Does not overwrite existing output files.  
- **Robust Error Handling**: Detects missing files and invalid flags.  
- **Modular Code Structure**: Organized with clean, reusable functions for processing text lines.

## 📥 How to Use  

1. **Clone the repository**  
- Open your terminal and run:  
  ```bash  
  git clone https://github.com/nikitaupadhyayy/cryptoMagic.git  
  cd cryptoMagic

2. **Compile the program**
- Use GCC (or any C compiler) to compile:  
  ```bash  
  gcc cryptoMagic.c -o cryptoMagic.exe

3. **Run the program**
- To encrypt a file:  
  ```bash  
  ./cryptoMagic.exe -E filename.txt
- To decrypt a file:  
  ```bash  
  ./cryptoMagic.exe -D filename.crp
