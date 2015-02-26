#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "sosemanuk.h"

int
main(void)
{
	uint8_t key1[32] = { 0x00, 0x11, 0x22, 0x33,
			     0x44, 0x55, 0x66, 0x77,
			     0x88, 0x99, 0xAA, 0xBB,
			     0xCC, 0xDD, 0xEE, 0xFF,
			     0x00, 0x00, 0x00, 0x00,
			     0x00, 0x00, 0x00, 0x00,
			     0x00, 0x00, 0x00, 0x00,
			     0x00, 0x00, 0x00, 0x00 };

	uint8_t iv1[16] = { 0x88, 0x99, 0xAA, 0xBB,
			    0xCC, 0xDD, 0xEE, 0xFF,
			    0x00, 0x11, 0x22, 0x33,
			    0x44, 0x55, 0x66, 0x77 };
	
	struct sosemanuk_context *ctx;

	if((ctx = sosemanuk_context_new()) == NULL) {
		printf("Memory allocation error!\n");
		exit(1);
	}

	if(sosemanuk_set_key_and_iv(ctx, key1, 32, iv1)) {
		printf("Filling sosemanuk context error!\n");
		exit(1);
	}

	sosemanuk_test_vectors(ctx);

	sosemanuk_context_free(&ctx);

	return 0;
}
