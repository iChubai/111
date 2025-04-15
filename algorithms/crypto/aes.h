#ifndef AES_H
#define AES_H

#include <stddef.h>
#include <stdint.h>

// AES密钥长度（以字节为单位）
#define AES_128_KEY_SIZE 16
#define AES_192_KEY_SIZE 24
#define AES_256_KEY_SIZE 32

// AES块大小（以字节为单位）
#define AES_BLOCK_SIZE 16

// AES上下文结构
typedef struct {
    uint8_t round_key[240];  // 最大密钥扩展空间
    int key_size;            // 密钥大小（128、192或256位）
    int rounds;              // 轮数（10、12或14）
} AES_ctx;

// AES函数声明
void AES_init_ctx(AES_ctx* ctx, const uint8_t* key, int key_size);
void AES_encrypt(const AES_ctx* ctx, uint8_t* buffer);
void AES_decrypt(const AES_ctx* ctx, uint8_t* buffer);

// CBC模式
void AES_CBC_encrypt(const AES_ctx* ctx, uint8_t* iv, uint8_t* data, size_t length);
void AES_CBC_decrypt(const AES_ctx* ctx, uint8_t* iv, uint8_t* data, size_t length);

#endif // AES_H
