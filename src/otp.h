#ifndef OTP_H
#define OTP_H

void otp_encrypt(
    char *clear_text,
    char *cipher_text,
    char *key,
    size_t length
);

void otp_decrypt(
    char *cipher_text,
    char *clear_text,
    char *key,
    size_t length
);

#endif