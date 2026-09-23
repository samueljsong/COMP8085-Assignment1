#include <stdio.h>
#include <limits.h>

/**
 * void print_binary - Prints out the binary form of an integer by iterating through each bit and using the bitwise operator to print the corresponding value.
 */
void convert_to_binary(int *cipher_text_decimal, int *cipher_text_binary, int length){
    int bits = 5;
    int current_pointer = 0;
    int binary_array_pointer = 0;
   
    while (current_pointer < length)
    {
        int number = cipher_text_decimal[current_pointer];
        // starts at the end work backwards
        for (int i = bits - 1; i >= 0; i--){
            // & is a bitwise and so after shifting the bits to the right we do a bitwise and with 1.
            // if the bit in the right most = 1 then we print 1 if not we do 0
            int bit = (number >> i) & 1;
            cipher_text_binary[binary_array_pointer] = bit;
            binary_array_pointer++;

            // puts a space after ever 4 bits
            if (i % 5 == 0){
                printf(" ");
                current_pointer++;
            }
        }
    }
}