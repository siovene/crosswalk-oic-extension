// Copyright (c) 2013 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <stdio.h>
#include <stdlib.h>
#include "../xw_extension/XW_Extension.h"
#include "../xw_extension/XW_Extension_SyncMessage.h"

extern const char kSource_iotivity_api[];
XW_Extension g_extension = 0;
const XW_CoreInterface* g_core = NULL;
const XW_MessagingInterface* g_messaging = NULL;
const XW_Internal_SyncMessagingInterface* g_sync_messaging = NULL;

void instance_created(XW_Instance instance) {
  printf("Instance %d created!\n", instance);
}

void instance_destroyed(XW_Instance instance) {
  printf("Instance %d destroyed!\n", instance);
}

void handle_message(XW_Instance instance, const char* message) {
  g_messaging->PostMessage(instance, message);
}

void handle_sync_message(XW_Instance instance, const char* message) {
  g_sync_messaging->SetSyncReply(instance, message);
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
