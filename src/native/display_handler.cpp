// Copyright (c) 2014 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "display_handler.h"
#include "client_handler.h"

#include "jni_util.h"
#include "util.h"

DisplayHandler::DisplayHandler(JNIEnv* env, jobject handler) {
  jhandler_ = env->NewGlobalRef(handler);
}

DisplayHandler::~DisplayHandler() {
  JNIEnv* env = GetJNIEnv();
  env->DeleteGlobalRef(jhandler_);
}

void DisplayHandler::OnAddressChange(CefRefPtr<CefBrowser> browser,
                             CefRefPtr<CefFrame> frame,
                             const CefString& url) {
  JNIEnv* env = GetJNIEnv();
  if (!env)
  	return;
  JNI_CALL_VOID_METHOD(env, jhandler_, 
                       "onAddressChange", 
                       "(Lorg/cef/CefBrowser;Ljava/lang/String;)V", 
                       GetJNIBrowser(browser),
                       NewJNIString(env, url));
}

void DisplayHandler::OnTitleChange(CefRefPtr<CefBrowser> browser,
                           const CefString& title) {
  JNIEnv* env = GetJNIEnv();
  if (!env)
  	return;
  JNI_CALL_VOID_METHOD(env, jhandler_, 
                       "onTitleChange", 
                       "(Lorg/cef/CefBrowser;Ljava/lang/String;)V", 
                       GetJNIBrowser(browser),
                       NewJNIString(env, title));
}

bool DisplayHandler::OnTooltip(CefRefPtr<CefBrowser> browser,
                       CefString& text) {
  return false;
}

void DisplayHandler::OnStatusMessage(CefRefPtr<CefBrowser> browser,
                             const CefString& value) {
  return;
}

bool DisplayHandler::OnConsoleMessage(CefRefPtr<CefBrowser> browser,
                              const CefString& message,
                              const CefString& source,
                              int line) {
  REQUIRE_UI_THREAD();
  return false;
}