#include <openssl/dh.h>
#include <stdio.h>
#include <stdlib.h> // Include stdlib.h for malloc and free

int main() {
    DH *dh;
    int size;
    BIGNUM *pub_key, *priv_key;
    unsigned char *secret;

    dh = DH_new();
    DH_generate_parameters_ex(dh, 1024, 2, NULL);
    DH_generate_key(dh);

    pub_key = BN_new();//Allocates memory
    priv_key = BN_new();
    DH_get0_key(dh, &pub_key, &priv_key);

    size = DH_size(dh);
    secret = malloc(size);

    
    DH_compute_key(secret, DH_get0_pub_key(dh), dh);

    // Print Public and Private Keys
    char *pub_key_str = BN_bn2hex(pub_key);
    printf("Public Key: \n%s\n", pub_key_str);
    OPENSSL_free(pub_key_str);

    char *priv_key_str = BN_bn2hex(priv_key);
    printf("Private Key: \n%s\n", priv_key_str);
    OPENSSL_free(priv_key_str);

    printf("Shared Secret: \n");
    for (int i = 0; i < size; i++) {
        printf("%02x", secret[i]);
    }
    printf("\n");

    BN_free(pub_key);
    BN_free(priv_key);
    free(secret);
    DH_free(dh);
    return 0;
}
