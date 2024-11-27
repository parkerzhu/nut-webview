// Copyright (c) 2024 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=51da21d569dd41e38cb2dc6e0f2dea0bd88dbdce$
//

#include "libcef_dll/cpptoc/frame_handler_cpptoc.h"

#include "libcef_dll/ctocpp/browser_ctocpp.h"
#include "libcef_dll/ctocpp/frame_ctocpp.h"
#include "libcef_dll/shutdown_checker.h"

namespace {

// MEMBER FUNCTIONS - Body may be edited by hand.

void CEF_CALLBACK
frame_handler_on_frame_created(struct _cef_frame_handler_t* self,
                               cef_browser_t* browser,
                               cef_frame_t* frame) {
  shutdown_checker::AssertNotShutdown();

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self) {
    return;
  }
  // Verify param: browser; type: refptr_diff
  DCHECK(browser);
  if (!browser) {
    return;
  }
  // Verify param: frame; type: refptr_diff
  DCHECK(frame);
  if (!frame) {
    return;
  }

  // Execute
  CefFrameHandlerCppToC::Get(self)->OnFrameCreated(
      CefBrowserCToCpp::Wrap(browser), CefFrameCToCpp::Wrap(frame));
}

void CEF_CALLBACK
frame_handler_on_frame_destroyed(struct _cef_frame_handler_t* self,
                                 cef_browser_t* browser,
                                 cef_frame_t* frame) {
  shutdown_checker::AssertNotShutdown();

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self) {
    return;
  }
  // Verify param: browser; type: refptr_diff
  DCHECK(browser);
  if (!browser) {
    return;
  }
  // Verify param: frame; type: refptr_diff
  DCHECK(frame);
  if (!frame) {
    return;
  }

  // Execute
  CefFrameHandlerCppToC::Get(self)->OnFrameDestroyed(
      CefBrowserCToCpp::Wrap(browser), CefFrameCToCpp::Wrap(frame));
}

void CEF_CALLBACK
frame_handler_on_frame_attached(struct _cef_frame_handler_t* self,
                                cef_browser_t* browser,
                                cef_frame_t* frame,
                                int reattached) {
  shutdown_checker::AssertNotShutdown();

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self) {
    return;
  }
  // Verify param: browser; type: refptr_diff
  DCHECK(browser);
  if (!browser) {
    return;
  }
  // Verify param: frame; type: refptr_diff
  DCHECK(frame);
  if (!frame) {
    return;
  }

  // Execute
  CefFrameHandlerCppToC::Get(self)->OnFrameAttached(
      CefBrowserCToCpp::Wrap(browser), CefFrameCToCpp::Wrap(frame),
      reattached ? true : false);
}

void CEF_CALLBACK
frame_handler_on_frame_detached(struct _cef_frame_handler_t* self,
                                cef_browser_t* browser,
                                cef_frame_t* frame) {
  shutdown_checker::AssertNotShutdown();

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self) {
    return;
  }
  // Verify param: browser; type: refptr_diff
  DCHECK(browser);
  if (!browser) {
    return;
  }
  // Verify param: frame; type: refptr_diff
  DCHECK(frame);
  if (!frame) {
    return;
  }

  // Execute
  CefFrameHandlerCppToC::Get(self)->OnFrameDetached(
      CefBrowserCToCpp::Wrap(browser), CefFrameCToCpp::Wrap(frame));
}

void CEF_CALLBACK
frame_handler_on_main_frame_changed(struct _cef_frame_handler_t* self,
                                    cef_browser_t* browser,
                                    cef_frame_t* old_frame,
                                    cef_frame_t* new_frame) {
  shutdown_checker::AssertNotShutdown();

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self) {
    return;
  }
  // Verify param: browser; type: refptr_diff
  DCHECK(browser);
  if (!browser) {
    return;
  }
  // Unverified params: old_frame, new_frame

  // Execute
  CefFrameHandlerCppToC::Get(self)->OnMainFrameChanged(
      CefBrowserCToCpp::Wrap(browser), CefFrameCToCpp::Wrap(old_frame),
      CefFrameCToCpp::Wrap(new_frame));
}

}  // namespace

// CONSTRUCTOR - Do not edit by hand.

CefFrameHandlerCppToC::CefFrameHandlerCppToC() {
  GetStruct()->on_frame_created = frame_handler_on_frame_created;
  GetStruct()->on_frame_destroyed = frame_handler_on_frame_destroyed;
  GetStruct()->on_frame_attached = frame_handler_on_frame_attached;
  GetStruct()->on_frame_detached = frame_handler_on_frame_detached;
  GetStruct()->on_main_frame_changed = frame_handler_on_main_frame_changed;
}

// DESTRUCTOR - Do not edit by hand.

CefFrameHandlerCppToC::~CefFrameHandlerCppToC() {
  shutdown_checker::AssertNotShutdown();
}

template <>
CefRefPtr<CefFrameHandler> CefCppToCRefCounted<
    CefFrameHandlerCppToC,
    CefFrameHandler,
    cef_frame_handler_t>::UnwrapDerived(CefWrapperType type,
                                        cef_frame_handler_t* s) {
  DCHECK(false) << "Unexpected class type: " << type;
  return nullptr;
}

template <>
CefWrapperType CefCppToCRefCounted<CefFrameHandlerCppToC,
                                   CefFrameHandler,
                                   cef_frame_handler_t>::kWrapperType =
    WT_FRAME_HANDLER;
