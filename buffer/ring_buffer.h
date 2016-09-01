#ifndef KFIFO_HEADER_H 
#define KFIFO_HEADER_H

#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif
#ifdef WIN32
#include <windows.h>
#define  V_MUTEX                CRITICAL_SECTION 
#define  V_MUTEX_INIT(m)        InitializeCriticalSection(m)
#define  V_MUTEX_LOCK(m)        EnterCriticalSection(m)
#define  V_MUTEX_TRYLOCK(m)     TryEnterCriticalSection(m)
#define  V_MUTEX_UNLOCK(m)      LeaveCriticalSection(m)
#define  V_MUTEX_DESTORY(m)     DeleteCriticalSection(m)
#else
#include <pthread.h>
#define  V_MUTEX                pthread_mutex_t
#define  V_MUTEX_INIT(m)        pthread_mutex_init(m, NULL)
#define  V_MUTEX_LOCK(m)        pthread_mutex_lock(m)
#define  V_MUTEX_TRYLOCK(m)     pthread_mutex_trylock(m)
#define  V_MUTEX_UNLOCK(m)      pthread_mutex_unlock(m)
#define  V_MUTEX_DESTORY(m)     pthread_mutex_destroy(m)
#endif

struct ring_buffer
{
	char         *buffer;
	uint32_t     size;
	uint32_t     in;    
	uint32_t     out;     
	V_MUTEX      *f_lock;
};

struct ring_buffer* ring_buffer_init(uint32_t size);

void ring_buffer_free(struct ring_buffer *ring_buf);

uint32_t ring_buffer_len(const struct ring_buffer *ring_buf);

uint32_t ring_buffer_get(struct ring_buffer *ring_buf, void *buffer, uint32_t size);

uint32_t ring_buffer_put(struct ring_buffer *ring_buf, void *buffer, uint32_t size);

uint32_t ring_buffer_empty(struct ring_buffer *ring_buf);

#ifdef __cplusplus
}
#endif 

#endif
