#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/hmac.h>
#include <openssl/rand.h>
#include <openssl/evp.h>


#define CRYPTO_TAG_SIZE    16
#define CRYPTO_IV_SIZE    12

struct key {
	uint8_t byte[32];
};

struct aad {
	uint8_t byte[16];
};

struct iv {
	uint8_t byte[CRYPTO_IV_SIZE];
};

int generate_iv(struct iv *iv_out)
{
    int rand_ret;

    rand_ret = RAND_bytes(iv_out->byte, sizeof(iv_out->byte));
    if (!rand_ret) {
        printf("RAND_bytes failed\n");
    }
    return rand_ret ? 0 : -1;
}

enum CRYPTO_IV {
    IV_DB,   // iv for user.db
    IV_ENC,  // iv for encrypto data.

    IV_MAX,
};

#define IV_PATH_MAX     16
int _aes_256_gcm_encrypt(const struct key *key,
			const struct iv *iv, const struct aad *aad,
			const void *plain, uint32_t plain_size,
			void *out, uint32_t *out_size)
{
	int rc = -1;
	EVP_CIPHER_CTX *ctx;
	int out_len, cur_len;
	uint8_t *pout_buf = out;
	uint8_t tag[CRYPTO_TAG_SIZE] = {0};
	if ((key ==  NULL) ||  (iv ==  NULL) ||
            (plain ==  NULL) || (out ==  NULL) || (out_size ==  NULL)) {
		printf("invalid args!\n");
		return -1;
	}

	/*creat cipher ctx*/
	ctx = EVP_CIPHER_CTX_new();
	if (ctx == NULL) {
		printf("fail to create CTX....\n");
		goto exit;
	}

	/* Set cipher, key and iv */
	if (!EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), NULL,
				(unsigned char *)key, (unsigned char *)iv)) {
		printf("CipherInit fail\n");
		goto exit;
	}

	/* set iv length.*/
	if (!EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, sizeof(struct iv), NULL)) {
		printf("set iv length fail\n");
		goto exit;
	}

	/* set to aad info.*/
	if (NULL != aad) {
		if (!EVP_EncryptUpdate(ctx, NULL, &out_len, (uint8_t *)aad, sizeof(struct aad))) {
			printf("set aad info fail\n");
			goto exit;
		}
	}

	/* Encrypt plaintext */
	if (!EVP_EncryptUpdate(ctx, pout_buf, &out_len, plain, plain_size)) {
		printf("Encrypt plain text fail.\n");
		goto exit;
	}

	pout_buf += out_len;
	cur_len = out_len;
	/* get no output for GCM */
	if (!EVP_EncryptFinal_ex(ctx, pout_buf, &out_len)) {
		printf("EncryptFinal fail.\n");
		goto exit;
	}

	/*get TAG*/
	if (!EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG,
                                 CRYPTO_TAG_SIZE, tag)) {
		printf("get TAG fail.\n");
		rc = -1;
		goto exit;
	}

	if (memcpy(pout_buf,
                   tag, CRYPTO_TAG_SIZE)){
		printf("fail to copy encrypt tag.\n");
		goto exit;
	}
	cur_len += CRYPTO_TAG_SIZE;
	*out_size = cur_len;

	rc = 0;

exit:
	if (ctx)
		EVP_CIPHER_CTX_free(ctx);

	return rc;
}

int _aes_256_gcm_decrypt(const struct key *key,
			const struct iv *iv, const struct aad *aad,
			const void *cipher, uint32_t cipher_size,
			void *out, uint32_t *out_size)
{
	int rc = -1;
	EVP_CIPHER_CTX *ctx;
	int out_len, cur_len, data_len;
	uint8_t *pout_buf = out;
	uint8_t *ptag;

	if ((key ==  NULL) ||  (iv ==  NULL) ||
            (cipher ==  NULL) || (out ==  NULL) || (out_size ==  NULL))
	{
		printf("invalid args!\n");
		return -1;
	}

	/*creat cipher ctx*/
	ctx = EVP_CIPHER_CTX_new();
	if (ctx == NULL) {
		printf("fail to create CTX....\n");
		goto exit;
	}

	/* Set cipher, key and iv */
	if (!EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), NULL,
				(unsigned char *)key, (unsigned char *)iv)) {
		printf("CipherInit fail\n");
		goto exit;
	}

	/* set iv length.*/
	if (!EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, sizeof(struct iv), NULL)) {
		printf("set iv length fail\n");
		goto exit;
	}

	/* set to aad info.*/
	if (NULL != aad) {
		if (!EVP_EncryptUpdate(ctx, NULL, &out_len, (uint8_t *)aad, sizeof(struct aad))) {
			printf("set aad info fail\n");
			goto exit;
		}
	}

	/* Decrypt plaintext */
	data_len = cipher_size - CRYPTO_TAG_SIZE;
	if (!EVP_DecryptUpdate(ctx, pout_buf, &out_len, cipher, data_len)) {
		printf("Decrypt cipher text fail.\n");
		goto exit;
	}

	cur_len = out_len;
	ptag = (uint8_t *)cipher + data_len;
	/*set TAG*/
	if (!EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG,
				 CRYPTO_TAG_SIZE, ptag)) {
		printf("set TAG fail.\n");
		goto exit;
	}

	/* Check TAG */
	if (!EVP_DecryptFinal_ex(ctx, pout_buf, &out_len)) {
		printf("fail to check TAG.\n");
		rc = -1;
		goto exit;
	}

	*out_size = cur_len;

	rc = 0;

exit:
	if (ctx)
		EVP_CIPHER_CTX_free(ctx);

	return rc;
}

int main(void) {
    return 0;
}
