#ifndef OTP_H
#define OTP_H

void otp_encrypt(
    const unsigned char *clear_text,
    const unsigned char *key,
    unsigned char *cipher_text,
    int length
);

void otp_decrypt(
    const unsigned char *clear_text,
    const unsigned char *key,
    unsigned char *cipher_text,
    int length
);

#endif