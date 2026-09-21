#pragma once
#include <stdint.h>
#include <stddef.h>
#include "xbox360_iso_stream.h"

namespace pcm_transfer {

typedef void (*Completion)(int status, void* context);

struct Api {
    // Adapter supplied by the Xbox 360 integration layer. The implementation
    // will build the native USB transfer request used by UsbdQueueAsyncTransfer.
    bool (*queue_iso)(xbox360_iso::Stream* stream,
                      void* buffer,
                      uint32_t length,
                      Completion completion,
                      void* context);
};

struct Buffer {
    void* data;
    uint32_t capacity;
    uint32_t length;
    bool queued;
};

struct Engine {
    xbox360_iso::Stream* stream;
    Buffer buffers[2];
    uint8_t next_buffer;
    bool running;
    bool stopping;
};

void set_api(const Api& api);
bool api_ready();

bool initialize(Engine* engine,
                xbox360_iso::Stream* stream,
                void* buffer0,
                void* buffer1,
                uint32_t buffer_size);

bool queue(Engine* engine, const void* pcm, uint32_t bytes);
void stop(Engine* engine);

}
