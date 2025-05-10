/*
Title: cryptoMagic Encryption/Decryption
Author: Nikita Upadhyay
Summary: The program processes files by either encrypting or decrypting them
based on the user’s input. The user can provide a file (within the folder
"miniproject2") and choose whether to encrypt or decrypt it by specifying flags
-E (for encryption) or -D (for decryption) when running the program.

ENCRYPTION FORMATTING: ./cryptoMagic.exe -E <filename>
DECRYPTION FORMATTING: ./cryptoMagic.exe -D <filename>

WARNING: The code will NOT produce a file .txt or .crp if there already exists a
file with the same name
*/

#include <ctype.h>
#include <stdio.h>  
#include <stdlib.h>
#include <string.h>

// Variable declaration
void encrypt(const char *input_filename);
void decrypt(const char *input_filename);
void process_line_for_encryption(const char *line, FILE *output_file);
void process_line_for_decryption(const char *line, FILE *output_file);
void write_output_file(const char *filename, const char *content);
void generate_output_filename(const char *input_filename, const char *mode,
                              char *output_filename);

// Entry point of the program
// The program checks if user provided the correct number of arguments (a mode
// -E or -D and a filename)
// If not, it outputs message and breaks the program
int main(int argc, char *argv[]) {  // arg represents the amount of arguments
  if (argc < 2) {                   // If less than 2 arguments are provided
    printf("Usage: cryptoMagic [-E|-D] <filename>\n");  // Informs user how to
                                                        // use program
    return 1;
  }

  // This initializes a flag that will control whether the program performs
  // encryption or decryption. By default, it is set to 1 (true), meaning the
  // program will perform encryption unless told otherwise.
  int encrypt_flag = 1;
  char *input_filename =
      argv[argc - 1];  // Sets the input_filename to the last argument provided
                       // (the filename (either encrypted or plain text)).

  if (argc == 3) {                     // Checks for if 3 arguments are provided
    if (strcmp(argv[1], "-D") == 0) {  // If decryption, encrypt_flag returns 0
      encrypt_flag = 0;
    } else if (strcmp(argv[1], "-E") !=
               0) {  // If neither -E or -D, it is invalid and prints an error
                     // message
      printf("Invalid option. Use -E for encryption or -D for decryption.\n");
      return 1;
    }
  }

  // Ensure the input filename is valid
  if (input_filename == NULL || strlen(input_filename) == 0) {
    printf("Error: No input file provided.\n");  // Error message if the file is
                                                 // not valid
    return 1;
  }

  // Encrypt or decrypt based on the flag
  if (encrypt_flag) {
    encrypt(input_filename);  // Encrypt the file
  } else {
    decrypt(input_filename);  // Decrypt the file
  }

  return 0;
}

// Encryption function
// The job of this function is to read the file, encrypt its contents, and write
// the encrypted contents to a new file
void encrypt(const char *input_filename) {
  // Opens the input file in "read" mode ("r"). fopen gives back a pointer to
  // the file, which we store in input_file.
  FILE *input_file = fopen(input_filename, "r");
  if (!input_file) {
    printf("Error opening input file");
    exit(1);
  }

  // Generate output filename with .crp extension
  char output_filename[255];
  generate_output_filename(input_filename, "E", output_filename);

  FILE *output_file = fopen(output_filename, "w");
  if (!output_file) {
    perror(
        "Error opening output file");  // Stores the name of the new file that
                                       // will contain the encrypted text
    exit(1);
  }

  char line[121];  // Declare a buffer to hold a single line from the input file

  // Read a line from the input file and store it in 'line'. 'fgets' reads up to
  // 120 characters or until a newline ('\n') or EOF is encountered. The loop
  // continues as long as 'fgets' successfully reads a line.
  while (fgets(line, sizeof(line), input_file)) {
    process_line_for_encryption(
        line, output_file);  // Encrypt the line read from the input file.
  }
  fclose(input_file);
  fclose(output_file);
}

// Decryption function
// The job of this function is to read the file, decrypt its contents, and write
// the decrypted contents to a new file
void decrypt(const char *input_filename) {
  // Opens the input file in "read" mode ("r"). fopen gives back a pointer to
  // the file, which we store in input_file.
  FILE *input_file = fopen(input_filename, "r");
  if (!input_file) {
    printf("Error opening input file");
    exit(1);
  }

  // Generate output filename with a .txt extension
  char output_filename[255];
  generate_output_filename(input_filename, "D", output_filename);

  FILE *output_file = fopen(output_filename, "w");
  if (!output_file) {
    printf(
        "Error opening output file");  // Stores the name of the new file that
                                       // will contain the encrypted text
    exit(1);
  }

  char line[256];  // Declare a buffer to hold a single line from the input file

  // Read a line from the input file and store it in 'line'. 'fgets' reads up to
  // 120 characters or until a newline ('\n') or EOF is encountered. The loop
  // continues as long as 'fgets' successfully reads a line.
  while (fgets(line, sizeof(line), input_file)) {
    process_line_for_decryption(
        line, output_file);  // Decrypt the current line and write the result to
                             // the output file
  }

  fclose(input_file);
  fclose(output_file);
}

// Encryption algorithm
void process_line_for_encryption(const char *line, FILE *output_file) {
  // Loop through each character in the line
  while (*line) {
    if (*line == '\t') {
      // If the character is a tab, replace it with "TT" in the output file
      fputs("TT", output_file);
    } else if (*line == '\n') {
      // If the character is a newline, keep it as is in the output file
      fputc('\n', output_file);
    } else {
      // For other characters, perform encryption
      int outChar = *line - 16;  // Shift the ASCII value by -16
      if (outChar < 32) {
        // If the result is below 32 (non-printable), wrap it into the range
        // 144-255
        outChar = (outChar - 32) + 144;
      }
      // Write the encrypted character as a 2-digit hexadecimal value to the
      // output file
      fprintf(output_file, "%02X", outChar);
    }
    line++;  // Move to the next character in the line
  }
}

// Decryption algorithm
void process_line_for_decryption(const char *line, FILE *output_file) {
  // Temporary buffer to hold two characters for each hex pair
  char hex_pair[3] = {0};
  int i = 0;  // Index for processing hex pairs (not explicitly used here but
              // helpful)

  // Loop through each character in the line
  while (*line) {
    if (*line == 'T' && *(line + 1) == 'T') {
      // If the sequence "TT" is found, convert it back to a tab
      fputc('\t', output_file);
      line += 2;  // Skip the next character since "TT" is two characters
    } else {
      // Read two characters to form a hex pair
      hex_pair[0] = *line++;
      hex_pair[1] = *line++;
      // Convert the hex pair to an integer (decimal value)
      int outChar = strtol(hex_pair, NULL, 16) + 16;

      if (outChar > 127) {
        // If the result is outside the printable range, wrap it back
        outChar = (outChar - 144) + 32;
      }

      // Write the decrypted character to the output file
      fputc(outChar, output_file);
    }
  }
}

// File name function
void generate_output_filename(const char *input_filename, const char *mode,
                              char *output_filename) {
  // Find the last occurrence of a '.' in the input filename (file extension)
  const char *ext = strrchr(input_filename, '.');
  if (ext) {
    // Copy everything up to the file extension into the output filename
    strncpy(output_filename, input_filename, ext - input_filename);
    output_filename[ext - input_filename] = '\0';  // Null-terminate the string
  } else {
    // If no file extension is found, copy the entire input filename
    strcpy(output_filename, input_filename);
  }

  if (strcmp(mode, "E") == 0) {
    // If mode is "E" (encryption), add a ".crp" extension
    strcat(output_filename, ".crp");
  } else {
    // If mode is "D" (decryption), add a ".txt" extension
    strcat(output_filename, ".txt");
  }
}
