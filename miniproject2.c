/* steps to approach
1. figure out how to take a file, read whats in it, and store it somewhere
2. figure out how to take the data in that file, and convert it to enrcrypt it
3. figure out how to produce a encrypted file*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void encryptFile(FILE *in, FILE *out); //
void decryptFile(FILE *in, FILE *out);
char* generateOutputFilename(char* inputFilename, char mode);
char encryptChar(char c);
char decryptPair(char hex1, char hex2);

int main(int argc, char *argv[]) {
    // Ensure proper arguments are passed
    if (argc < 2) {
        printf("Usage: cryptoMagic [-E/-D] filename\n");
        return 1;
    }

    char *inputFileName = argv[argc - 1];
    char mode = 'E';  // Default mode is encryption

    // Check for -E or -D switch for encrypt or decrypt
    if (argc == 3 && strcmp(argv[1], "-D") == 0) {
        mode = 'D';  // Decryption mode
    }

    // Open the input file
    FILE *inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return 1;
    }

    // Generate the output file name
    char *outputFileName = generateOutputFilename(inputFileName, mode);

    // Open the output file
    FILE *outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        fclose(inputFile);
        return 1;
    }

    // Call the respective function based on mode
    if (mode == 'E') {
        encryptFile(inputFile, outputFile);
    } else if (mode == 'D') {
        decryptFile(inputFile, outputFile);
    }

    // Close the files
    fclose(inputFile);
    fclose(outputFile);

    printf("Process completed successfully.\n");

    return 0;
}




int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int ch;
    while ((ch = fgetc(file)) != EOF) {
        // Print each character for demonstration
        putchar(ch);  // Can be replaced with encryption or other logic
    }

    fclose(file);
    return 0;
}
