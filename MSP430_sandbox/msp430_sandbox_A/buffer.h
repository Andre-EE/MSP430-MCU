#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

//#define NULL  ((void *)0)
//typedef unsigned int size_t;

// Opaque circular buffer struct
typedef struct cbuf_t cbuf_t;

// Accessible circular buffer handle
typedef cbuf_t* cbuf_handle_t;

// Pass in a storage buffer (array) and size
// Returns a circular buffer handle
cbuf_handle_t cbuf_init(uint8_t* buffer, size_t size);

// Reset the circular buffer to empty, head == tail
void cbuf_reset(cbuf_handle_t cbuf);

// Free a circular buffer structure.
// Does not free the storage buffer originally passed in
void cbuf_free(cbuf_handle_t cbuf);

// Returns true if the circular buffer is full
bool cbuf_full(cbuf_handle_t cbuf);

// Returns true if the circular buffer is empty
bool cbuf_empty(cbuf_handle_t cbuf);

// Returns the maximum capacity of the circular buffer
size_t cbuf_max_size(cbuf_handle_t cbuf);

size_t cbuf_get_size(cbuf_handle_t cbuf);

// put_overwrite adds data even if the buffer is full
// Returns 0 on success, -1 on overwrite
int cbuf_put(cbuf_handle_t cbuf, uint8_t data);

// Retrieve a value from the buffer
// Returns 0 on success, -1 if the buffer is empty
int cbuf_get(cbuf_handle_t cbuf, uint8_t *data);

void simple_buffer_test(void);

#endif /* BUFFER_H_ */
