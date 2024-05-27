#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

#define MAX_BUF_SIZE 1024
int main() 
{
    // Generate RSA key pair
    		RSA *rsa_keypair = RSA_generate_key(2048, RSA_F4, NULL, NULL);
    	if (rsa_keypair == NULL) 
{
        		fprintf(stderr, "Error generating RSA key pair\n");
        		return 1;
    	}
    	// Open input file
    		FILE *input_file = fopen("input.txt", "r");
    	if (input_file == NULL) 
{
        		fprintf(stderr, "Error opening input file\n");
        		return 1;
   	 }
    	// Open output file for encrypted data
    		FILE *encrypted_file = fopen("encrypted.txt", "w");

    	if (encrypted_file == NULL) 
{
        		fprintf(stderr, "Error opening encrypted file\n");
        		return 1;
    	}
    	// Open output file for decrypted data
    		FILE *decrypted_file = fopen("decrypted.txt", "w");
    	if (decrypted_file == NULL) 
{
        		fprintf(stderr, "Error opening decrypted file\n");
        		return 1;
    	}
    	// Read data from input file
    		char buffer[MAX_BUF_SIZE];
    		size_t bytes_read;
    	while ((bytes_read = fread(buffer, 1, sizeof(buffer), input_file)) > 0) 
{
        		// Encrypt data
        		unsigned char encrypted[MAX_BUF_SIZE];
int encrypted_length = RSA_public_encrypt(bytes_read, (unsigned char *)buffer, encrypted, rsa_keypair, RSA_PKCS1_PADDING);
        	if (encrypted_length == -1) 
{
            	fprintf(stderr, "Error encrypting data\n");
            	return 1;
        	}
        	// Write encrypted data to file
        		fwrite(encrypted, 1, encrypted_length, encrypted_file);
       	 // Decrypt data
        		unsigned char decrypted[MAX_BUF_SIZE];
        		int decrypted_length = RSA_private_decrypt(encrypted_length, encrypted, decrypted, rsa_keypair, RSA_PKCS1_PADDING);
        	if (decrypted_length == -1) 
{
            	fprintf(stderr, "Error decrypting data\n");
            	return 1;
        	}
        		// Write decrypted data to file
        		fwrite(decrypted, 1, decrypted_length, decrypted_file);
    	}

    // Clean up
    RSA_free(rsa_keypair);
    fclose(input_file);
    fclose(encrypted_file);
    fclose(decrypted_file);

    return 0;
}
