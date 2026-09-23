#ifndef OTP_H
#define OTP_H

void otp_encrypt(
    char *clear_text,
    int *cipher_text,
    char *key,
    int length
);

void otp_decrypt(
    char *clear_text,
    char *key,
    char *cipher_text,
    int length
);

#endif