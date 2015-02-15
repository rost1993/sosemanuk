#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/time.h>

#include "sosemanuk.h"

#define BUFLEN	100000000

struct timeval t1, t2;

uint8_t buf[BUFLEN];
uint8_t out1[BUFLEN];
uint8_t out2[BUFLEN];
uint8_t key[32];
uint8_t iv[16];

static void
time_start(void)
{
	gettimeofday(&t1, NULL);
}

static uint32_t
time_stop(void)
{
	gettimeofday(&t2, NULL);

	t2.tv_sec -= t1.tv_sec;
	t2.tv_usec -= t1.tv_usec;

	if(t2.tv_usec < 0) {
		t2.tv_sec--;
		t2.tv_usec += 1000000;
	}

	return (t2.tv_sec * 1000 + t2.tv_usec/1000);
}

int
main()
{
	//uint32_t i;
	ECRYPT_ctx x;

	memset(buf, 'q', sizeof(buf));
	memset(key, 'k', sizeof(key));
	memset(iv, 'i', sizeof(iv));
	
	/*for(i = 0; i < BUFLEN; i++)
		printf("%c ", (char)buf[i]);
	printf("\n\n\n");*/

	time_start();
	ECRYPT_init();

	ECRYPT_keysetup(&x, key, 256, 128);
	ECRYPT_ivsetup(&x, iv);
	
	ECRYPT_process_bytes(0, &x, buf, out1, BUFLEN);

	/*for(i = 0; i < BUFLEN; i++)
		printf("%c ", (char)out1[i]);
	printf("\n\n\n");*/

	ECRYPT_ivsetup(&x, iv);

	ECRYPT_process_bytes(1, &x, out1, out2, BUFLEN);
	
	/*for(i = 0; i < BUFLEN; i++)
		printf("%c ", (char)out2[i]);
	printf("\n\n\n");*/

	printf("Run time = %d\n\n", time_stop());

	return 0;
}

