#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>
#include <openssl/sha.h>

// Function to compute MD5 hash of a string
void compute_md5(const char *input, unsigned char *md5_hash) {
    MD5_CTX context;
    MD5_Init(&context);
    MD5_Update(&context, input, strlen(input));
    MD5_Final(md5_hash, &context);
}

// Function to compute SHA-1 hash of a string
void compute_sha1(const char *input, unsigned char *sha1_hash) {
    SHA_CTX context;
    SHA1_Init(&context);
    SHA1_Update(&context, input, strlen(input));
    SHA1_Final(sha1_hash, &context);
}

// Function to print hash value
void print_hash(unsigned char *hash, int length) {
    for (int i = 0; i < length; ++i) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int main() {
    char input[] = "Hello, world!";
    unsigned char md5_hash[MD5_DIGEST_LENGTH];
    unsigned char sha1_hash[SHA_DIGEST_LENGTH];

    // Compute MD5 hash
    compute_md5(input, md5_hash);
    printf("MD5 hash of \"%s\":\n", input);
    print_hash(md5_hash, MD5_DIGEST_LENGTH);

    // Compute SHA-1 hash
    compute_sha1(input, sha1_hash);
    printf("\nSHA-1 hash of \"%s\":\n", input);
    print_hash(sha1_hash, SHA_DIGEST_LENGTH);

    // Change the input slightly
    input[7] = 'W'; // Change 'w' to 'W'

    // Recompute MD5 hash
    compute_md5(input, md5_hash);
    printf("\nMD5 hash of modified input \"%s\":\n", input);
    print_hash(md5_hash, MD5_DIGEST_LENGTH);

    // Recompute SHA-1 hash
    compute_sha1(input, sha1_hash);
    printf("\nSHA-1 hash of modified input \"%s\":\n", input);
    print_hash(sha1_hash, SHA_DIGEST_LENGTH);

    return 0;
}
