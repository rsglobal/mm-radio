#pragma once

#include <memory>

#include <android-base/logging.h>
#include <libmm-glib.h>

// Create RAII class for gobject using std::shared_ptr
template <typename T>
struct GObjectDeleter {
    void operator()(T* ptr) {
        if (ptr) {
            g_object_unref(ptr);
        }
    }
};

template <typename T>
using SharedGObject = std::shared_ptr<T>;

template <typename T>
inline SharedGObject<T> makeSharedGObject(T* ptr) {
    return SharedGObject<T>(ptr, GObjectDeleter<T>());
}

// Create SharedGDBusConnection,SharedMmManager RAII based on SharedGObject
using SharedGDBusConnection = SharedGObject<GDBusConnection>;
using SharedMmManager = SharedGObject<MMManager>;
using SharedGdbusObject = SharedGObject<GDBusObject>;
using SharedMmObject = SharedGObject<MMObject>;

// Create MakeSharedGDBusConnection RAII based on SharedGObject
inline auto makeSharedGDBusConnection(GDBusConnection* connection) {
    return SharedGObject<GDBusConnection>(connection, GObjectDeleter<GDBusConnection>());
}

// Create MakeSharedMmManager RAII based on GObject
inline auto makeSharedMmManager(MMManager* manager) {
    return SharedGObject<MMManager>(manager, GObjectDeleter<MMManager>());
}

// Create MakeSharedGdbusObject RAII based on GObject
inline auto makeSharedGdbusObject(GDBusObject* object) {
    return SharedGObject<GDBusObject>(object, GObjectDeleter<GDBusObject>());
}

// Create MakeSharedMmObject RAII based on GObject
inline auto makeSharedMmObject(MMObject* object) {
    return SharedGObject<MMObject>(object, GObjectDeleter<MMObject>());
}
