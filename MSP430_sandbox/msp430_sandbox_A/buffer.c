#include "buffer.h"

// Define the circular buffer structure
struct cbuf_t
{
    uint8_t *buffer;
    size_t   head;
    size_t   tail;
    size_t   max;
    bool     full;
};

// Initialize the circular buffer
cbuf_handle_t cbuf_init(uint8_t* buffer, size_t size)
{
    cbuf_handle_t cbuf = (cbuf_handle_t)malloc(sizeof(struct cbuf_t));
    if (cbuf == NULL)
        return NULL;

    cbuf->buffer = buffer;
    cbuf->max    = size;
    cbuf_reset(cbuf);

    return cbuf;
}

// Reset the circular buffer
void cbuf_reset(cbuf_handle_t cbuf)
{
    cbuf->head = 0;
    cbuf->tail = 0;
    cbuf->full = false;
}

// Free the circular buffer structure
void cbuf_free(cbuf_handle_t cbuf)
{
    free(cbuf);
}

// Check if the circular buffer is full
bool cbuf_full(cbuf_handle_t cbuf)
{
    return cbuf->full;
}

// Check if the circular buffer is empty
bool cbuf_empty(cbuf_handle_t cbuf)
{
    return (!cbuf->full && (cbuf->head == cbuf->tail));
}

// Get the maximum capacity of the circular buffer
size_t cbuf_max_size(cbuf_handle_t cbuf)
{
    return cbuf->max;
}

// Get current size of the circular buffer
size_t cbuf_get_size(cbuf_handle_t cbuf)
{
    size_t size = cbuf->max;

    if (!cbuf->full)
    {
        if (cbuf->head >= cbuf->tail)
            size = cbuf->head - cbuf->tail;
        else
            size = cbuf->max + cbuf->head - cbuf->tail;
    }
    return size;
}

// Put data into the circular buffer, overwriting oldest data if full
int cbuf_put(cbuf_handle_t cbuf, uint8_t data)
{
    cbuf->buffer[cbuf->head] = data;

    int r_val = 0;

    if (cbuf->full)
    {
        r_val = -1;

        if (cbuf->tail == (cbuf->max - 1))
            cbuf->tail = 0;
        else
            cbuf->tail++;
    }

    if (cbuf->head == (cbuf->max - 1))
        cbuf->head = 0;
    else
        cbuf->head++;

    cbuf->full = (cbuf->head == cbuf->tail);

    return r_val;
}

// Get data from the circular buffer
int cbuf_get(cbuf_handle_t cbuf, uint8_t *data)
{
    if (cbuf_empty(cbuf))
        return -1; // Buffer is empty

    *data = cbuf->buffer[cbuf->tail];

    if (cbuf->tail == (cbuf->max - 1))
        cbuf->tail = 0;
    else
        cbuf->tail++;

    cbuf->full = false;

    return 0;
}
