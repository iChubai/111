#ifndef CRYPTO_H
#define CRYPTO_H

#include <stddef.h>
#include <stdint.h>

// AES密钥长度（以字节为单位）
#define AES_128_KEY_SIZE 16
#define AES_192_KEY_SIZE 24
#define AES_256_KEY_SIZE 32

// AES块大小（以字节为单位）
#define AES_BLOCK_SIZE 16

// SHA哈希长度（以字节为单位）
#define SHA1_HASH_SIZE 20
#define SHA256_HASH_SIZE 32
#define SHA512_HASH_SIZE 64

// RSA密钥长度（以比特为单位）
#define RSA_1024_BITS 1024
#define RSA_2048_BITS 2048
#define RSA_4096_BITS 4096

// AES上下文结构
typedef struct {
    uint8_t round_key[240];  // 最大密钥扩展空间
    int key_size;            // 密钥大小（128、192或256位）
    int rounds;              // 轮数（10、12或14）
} AES_ctx;

// RSA密钥结构
typedef struct {
    uint8_t* modulus;        // 模数 n = p * q
    uint8_t* exponent;       // 指数（公钥e或私钥d）
    size_t key_size;         // 密钥大小（字节）
} RSA_key;

// AES函数声明
void AES_init_ctx(AES_ctx* ctx, const uint8_t* key, int key_size);
void AES_encrypt(const AES_ctx* ctx, uint8_t* buffer);
void AES_decrypt(const AES_ctx* ctx, uint8_t* buffer);

// AES块加密模式
void AES_ECB_encrypt(const AES_ctx* ctx, uint8_t* data, size_t length);
void AES_ECB_decrypt(const AES_ctx* ctx, uint8_t* data, size_t length);
void AES_CBC_encrypt(const AES_ctx* ctx, uint8_t* iv, uint8_t* data, size_t length);
void AES_CBC_decrypt(const AES_ctx* ctx, uint8_t* iv, uint8_t* data, size_t length);
void AES_CTR_xcrypt(const AES_ctx* ctx, uint8_t* nonce_counter, uint8_t* data, size_t length);
void AES_GCM_encrypt(const AES_ctx* ctx, uint8_t* iv, uint8_t* data, size_t length, uint8_t* tag);
void AES_GCM_decrypt(const AES_ctx* ctx, uint8_t* iv, uint8_t* data, size_t length, uint8_t* tag);

// 哈希函数
void SHA1_hash(const uint8_t* data, size_t length, uint8_t* hash);
void SHA256_hash(const uint8_t* data, size_t length, uint8_t* hash);
void SHA512_hash(const uint8_t* data, size_t length, uint8_t* hash);

// HMAC函数
void HMAC_SHA1(const uint8_t* key, size_t key_length, const uint8_t* data, size_t data_length, uint8_t* hmac);
void HMAC_SHA256(const uint8_t* key, size_t key_length, const uint8_t* data, size_t data_length, uint8_t* hmac);

// RSA函数
void RSA_generate_key_pair(RSA_key* public_key, RSA_key* private_key, int key_bits);
void RSA_encrypt(const RSA_key* public_key, const uint8_t* data, size_t data_length, uint8_t* encrypted);
void RSA_decrypt(const RSA_key* private_key, const uint8_t* encrypted, size_t encrypted_length, uint8_t* decrypted);
void RSA_sign(const RSA_key* private_key, const uint8_t* data, size_t data_length, uint8_t* signature);
int RSA_verify(const RSA_key* public_key, const uint8_t* data, size_t data_length, const uint8_t* signature);

// 实用函数
void generate_random_bytes(uint8_t* buffer, size_t length);

#endif // CRYPTO_H
