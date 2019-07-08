#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
symbols: [ V, W, X, Y, Z ]
probabilities: [ 0.35, 0.3, 0.2, 0.1, 0.05]
bit combimation: [0, 10, 110, 1110, 1111]
code length: [1, 2, 3, 4, 4]
ASCI codes points:
    V = 0x56 or dec: 86
    Z = 0x5A or dec: 90

    // we can shift the array index to get the symbol from the lookup table
*/

#define NUM_SYMBOLS 6
// 2^ num bit representation = 2 ^ 5 = 32 values in LUT
// const may be faster
// T indexs : 00000, 00001, 00010, 00011, 00100, 00101, 00110, 00111, 01000, 01001, 01010, 01011, 01100, 01101, 01110, 01111
// V indexs: 10000, 10001, 10010, 10011, 10100, 10101, 10110, 10111
// W index: 11000, 11001, 11010, 11011
// X indexs: 11100, 11101
// Y indexs: 11110
// Z indexs: 11111
// process the input coded string and output the decoded string
void huffman_decode(char *coded_string, unsigned int code_length) {
  FILE *fp;
  fp = fopen("decoded_test_bench.txt", "w+");
  // These could be const for optimization
  // See if there is a way to minimize cache misses
  char *LUT_SYM = "TTTTTTTTTTTTTTTTVVVVVVVVWWWWXXYZ";
  int LUT_OFFSET[32] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2,
    3, 3, 3, 3,
    4, 4,
    5, 5
  };
  // could be made a register to be optimized
  int i = 0;
  // Take a chunk of input string of size 4 bits or 1/2 byte called nibble i.e. a char and shift right by 4 to get just the top 4 bits
  char* read_chunk = (char*)malloc(5 * sizeof(char) + 1);
  char *ptr;
  int int_val;
  for(; i < code_length; i++) {
    strncpy(read_chunk, coded_string, 5);
    if (!read_chunk[0]) {
      break;
    }
    while (strlen(read_chunk) < 5)
    {
      strcat(read_chunk, "0");
    }
    read_chunk[5] = '\0';
    int_val = strtol(read_chunk, NULL, 2);
    char symbol = (char)LUT_SYM[int_val];
    int shift_offset = LUT_OFFSET[int_val];
    coded_string = coded_string + shift_offset;
    fprintf (fp, "%c", symbol);
  }
  fprintf (fp, "\n");
  fclose (fp);
}

// Read the input string from file and call routine
int main() {
  FILE *fp;
  fp = fopen("test_bench.txt", "r");
  char *coded_string;
  char *char_count;
  char * line = NULL;
  size_t len = 0;
  if (fp == NULL) {
    perror("Error while opening file.\n");
    exit(0);
  }
  printf("Reading encoded string: \n");
  getline(&coded_string, &len, fp);
  coded_string = strtok(coded_string, " \r\n\t");
  printf("Encoded string %s\n", coded_string);
  fclose(fp);
  huffman_decode(coded_string, (unsigned int)strlen(coded_string));
}
