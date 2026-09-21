#include "pcm_transfer.h"
#include <string.h>

namespace {
    pcm_transfer::Api g_api = {};

    void transfer_complete(int status, void* context) {
        pcm_transfer::Buffer* buffer =
            static_cast<pcm_transfer::Buffer*>(context);
        if (buffer) buffer->queued = false;
        (void)status;
    }
}

namespace pcm_transfer {

void set_api(const Api& api) { g_api = api; }

bool api_ready() { return g_api.queue_iso != 0; }

bool initialize(Engine* engine,
                xbox360_iso::Stream* stream,
                void* buffer0,
                void* buffer1,
                uint32_t buffer_size) {
    if (!engine || !stream || !stream->open ||
        !buffer0 || !buffer1 || buffer_size == 0)
        return false;

    Engine e = {};
    e.stream = stream;
    e.buffers[0].data = buffer0;
    e.buffers[0].capacity = buffer_size;
    e.buffers[1].data = buffer1;
    e.buffers[1].capacity = buffer_size;
    *engine = e;
    return true;
}

bool queue(Engine* engine, const void* pcm, uint32_t bytes) {
    if (!engine || !engine->stream || !engine->stream->open ||
        !pcm || bytes == 0 || !api_ready() || engine->stopping)
        return false;

    Buffer& b = engine->buffers[engine->next_buffer & 1];
    if (b.queued || bytes > b.capacity) return false;

    memcpy(b.data, pcm, bytes);
    b.length = bytes;
    b.queued = true;

    if (!g_api.queue_iso(engine->stream, b.data, b.length,
                         transfer_complete, &b)) {
        b.queued = false;
        b.length = 0;
        return false;
    }

    engine->running = true;
    engine->stream->running = true;
    engine->next_buffer ^= 1;
    return true;
}

void stop(Engine* engine) {
    if (!engine) return;
    engine->stopping = true;

    // Native cancellation/flush is intentionally delegated to the integration
    // layer. Never reuse/free queued buffers until callbacks have completed.
    if (!engine->buffers[0].queued && !engine->buffers[1].queued) {
        engine->running = false;
        if (engine->stream) engine->stream->running = false;
    }
}

}
