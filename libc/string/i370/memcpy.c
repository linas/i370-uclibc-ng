#include <string.h>

/* Dead stupid implementation, because the default crashes. */
void *memcpy(void *to, const void *from, size_t len)
{
	int i;
	unsigned char *cto = (unsigned char*) to;
	unsigned char *cfrom = (unsigned char*) from;
	for (i=0; i< len; i++)
		cto[i] = cfrom[i];

	return to;
}
libc_hidden_def(memcpy)
