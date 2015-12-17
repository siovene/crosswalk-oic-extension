// Copyright (c) 2013 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <stdio.h>
#include <stdlib.h>
#include "../xw_extension/XW_Extension.h"
#include "../xw_extension/XW_Extension_SyncMessage.h"
#include "../json/mjson.h"


extern const char kSource_iotivity_api[];
XW_Extension g_extension = 0;
const XW_CoreInterface* g_core = NULL;
const XW_MessagingInterface* g_messaging = NULL;
const XW_Internal_SyncMessagingInterface* g_sync_messaging = NULL;

const size_t RESPONSE_SIZE = 512;
const size_t METHOD_NAME_SIZE = 64;

const char* json_status_ok() {
    return "{\"status\": \"OK\"}";
}

char* process_message(const char* message) {
    typedef struct {
        char method [METHOD_NAME_SIZE];
    } request_t;

    request_t request;
    const struct json_attr_t request_attrs[] = {
        {"method", t_string, .addr.string = request.method, .len = sizeof(request.method)},
        {NULL}
    };
    char* response;
    int status;

    response = (char*) malloc(RESPONSE_SIZE);
    status = json_read_object(message, request_attrs, NULL);

    if (status != 0) {
        strncpy(response, json_error_string(status), RESPONSE_SIZE);
    } else if (strcmp(request.method, "OCInit") == 0) {
        strncpy(response, json_status_ok(), RESPONSE_SIZE);
    }

    return response;
}

void instance_created(XW_Instance instance) {
    printf("Instance %d created!\n", instance);
}

void instance_destroyed(XW_Instance instance) {
    printf("Instance %d destroyed!\n", instance);
}

void handle_message(XW_Instance instance, const char* message) {
    char* response = process_message(message);
    g_messaging->PostMessage(instance, response);
    free(response);
}

void handle_sync_message(XW_Instance instance, const char* message) {
    char* response = process_message(message);
    g_sync_messaging->SetSyncReply(instance, response);
    free(response);
}

void shutdown(XW_Extension extension) {
    printf("Shutdown\n");
}

int32_t XW_Initialize(XW_Extension extension, XW_GetInterface get_interface) {
    static const char* kAPI = kSource_iotivity_api;  // generated from iotivity_api.js
    g_extension = extension;
    g_core = get_interface(XW_CORE_INTERFACE);
    g_core->SetExtensionName(extension, "iotivity");
    g_core->SetJavaScriptAPI(extension, kAPI);
    g_core->RegisterInstanceCallbacks(
            extension, instance_created, instance_destroyed);
    g_core->RegisterShutdownCallback(extension, shutdown);

    g_messaging = get_interface(XW_MESSAGING_INTERFACE);
    g_messaging->Register(extension, handle_message);

    g_sync_messaging = get_interface(XW_INTERNAL_SYNC_MESSAGING_INTERFACE);
    g_sync_messaging->Register(extension, handle_sync_message);

    return XW_OK;
}
