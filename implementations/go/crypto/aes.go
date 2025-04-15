package crypto

import (
	"crypto/aes"
	"crypto/cipher"
	"math/rand"
	"time"
)

// 生成随机数据
func GenerateRandomData(size int) []byte {
	rand.Seed(time.Now().UnixNano())
	data := make([]byte, size)
	rand.Read(data)
	return data
}

// AES加密
func AESEncrypt(data, key, iv []byte) ([]byte, error) {
	block, err := aes.NewCipher(key)
	if err != nil {
		return nil, err
	}
	
	// 确保数据长度是块大小的倍数
	blockSize := block.BlockSize()
	paddedData := pkcs7Padding(data, blockSize)
	
	// 创建加密器
	mode := cipher.NewCBCEncrypter(block, iv)
	
	// 加密数据
	encrypted := make([]byte, len(paddedData))
	mode.CryptBlocks(encrypted, paddedData)
	
	return encrypted, nil
}

// AES解密
func AESDecrypt(encrypted, key, iv []byte) ([]byte, error) {
	block, err := aes.NewCipher(key)
	if err != nil {
		return nil, err
	}
	
	// 创建解密器
	mode := cipher.NewCBCDecrypter(block, iv)
	
	// 解密数据
	decrypted := make([]byte, len(encrypted))
	mode.CryptBlocks(decrypted, encrypted)
	
	// 去除填充
	unpaddedData := pkcs7Unpadding(decrypted)
	
	return unpaddedData, nil
}

// PKCS7填充
func pkcs7Padding(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padtext := make([]byte, padding)
	for i := 0; i < padding; i++ {
		padtext[i] = byte(padding)
	}
	return append(data, padtext...)
}

// PKCS7去除填充
func pkcs7Unpadding(data []byte) []byte {
	length := len(data)
	unpadding := int(data[length-1])
	return data[:(length - unpadding)]
}
