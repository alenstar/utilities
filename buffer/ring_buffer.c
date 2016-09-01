#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include "ring_buffer.h"


#define is_power_of_2(x) ((x) != 0 && (((x) & ((x) - 1)) == 0))
#define min(a, b) (((a) < (b)) ? (a) : (b))

struct ring_buffer* ring_buffer_init(uint32_t size)
{
 	struct ring_buffer *ring_buf = NULL;
	if (!is_power_of_2(size)) {
		printf("size must be power of 2.\n");
		return ring_buf;
	}

	V_MUTEX *f_lock = malloc(sizeof(V_MUTEX));
    V_MUTEX_INIT(f_lock);
	char *buffer = (char *)malloc(size);
	assert(buffer);

	ring_buf = (struct ring_buffer *)malloc(sizeof(struct ring_buffer));
	if (!ring_buf) {
		printf("Failed to malloc memory,errno:%u,reason", errno);
		return ring_buf;
	}
	memset(ring_buf, 0, sizeof(struct ring_buffer));
	ring_buf->buffer = (char *)buffer;
	ring_buf->size = size;
	ring_buf->in = 0;
	ring_buf->out = 0;
	ring_buf->f_lock = f_lock;
	return ring_buf;
}

void ring_buffer_free(struct ring_buffer *ring_buf)
{
	if (ring_buf)
	{
		if (ring_buf->buffer) {
			free(ring_buf->buffer);
			ring_buf->buffer = NULL;
		}

		if(ring_buf->f_lock) {
			V_MUTEX_DESTORY(ring_buf->f_lock);
		}
		free(ring_buf);
		ring_buf = NULL;
	}
}

inline uint32_t __ring_buffer_len(const struct ring_buffer *ring_buf)
{
	return (ring_buf->in - ring_buf->out);
}

inline uint32_t __ring_buffer_get(struct ring_buffer *ring_buf, void * buffer, uint32_t size)
{
	assert(ring_buf || buffer);
	uint32_t len = 0;
	size = min(size, ring_buf->in - ring_buf->out);
	/* first get the data from fifo->out until the end of the buffer */
	len = min(size, ring_buf->size - (ring_buf->out & (ring_buf->size - 1)));
	memcpy((char *)buffer, ring_buf->buffer + (ring_buf->out & (ring_buf->size - 1)), len);
	/* then get the rest (if any) from the beginning of the buffer */
	memcpy((char *)buffer + len, ring_buf->buffer, size - len);
	ring_buf->out += size;
	return size;
}

inline uint32_t __ring_buffer_put(struct ring_buffer *ring_buf, void *buffer, uint32_t size)
{
	assert(ring_buf || buffer);
	uint32_t len = 0;
	size = min(size, ring_buf->size - ring_buf->in + ring_buf->out);
	/* first put the data starting from fifo->in to buffer end */
	len = min(size, ring_buf->size - (ring_buf->in & (ring_buf->size - 1)));
	memcpy(ring_buf->buffer + (ring_buf->in & (ring_buf->size - 1)), buffer, len);
	/* then put the rest (if any) at the beginning of the buffer */
	memcpy(ring_buf->buffer, (char *)buffer + len, size - len);
	ring_buf->in += size;
	return size;
}

uint32_t ring_buffer_len(const struct ring_buffer *ring_buf)
{
	uint32_t len = 0;
	V_MUTEX_LOCK(ring_buf->f_lock);
	len = __ring_buffer_len(ring_buf);
	V_MUTEX_UNLOCK(ring_buf->f_lock);
	return len;
}

uint32_t ring_buffer_get(struct ring_buffer *ring_buf, void *buffer, uint32_t size)
{
	uint32_t ret;
	V_MUTEX_LOCK(ring_buf->f_lock);
	ret = __ring_buffer_get(ring_buf, buffer, size);
	if (ring_buf->in == ring_buf->out)
		ring_buf->in = ring_buf->out = 0;
	V_MUTEX_UNLOCK(ring_buf->f_lock);
	return ret;
}

uint32_t ring_buffer_put(struct ring_buffer *ring_buf, void *buffer, uint32_t size)
{
	uint32_t ret;
	V_MUTEX_LOCK(ring_buf->f_lock);
	ret = __ring_buffer_put(ring_buf, buffer, size);
	V_MUTEX_UNLOCK(ring_buf->f_lock);
	return ret;
}

uint32_t ring_buffer_empty(struct ring_buffer *ring_buf)
{
	uint32_t ret = 0;
	V_MUTEX_LOCK(ring_buf->f_lock);
	ring_buf->in  = 0;
	ring_buf->out = 0;
	memset(ring_buf->buffer, 0, ring_buf->size);
	V_MUTEX_UNLOCK(ring_buf->f_lock);
	return ret;
}


