#pragma once

#include <string>

using std::string;

struct Channel {
    Channel(const string name, const size_t module, const size_t channel)
        : name(name), module(module), channel(channel) {}

    const string name;
    const size_t module, channel;

    virtual void reset() = 0;
};