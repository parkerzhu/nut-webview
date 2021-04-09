// Copyright 2020 The Chromium Embedded Framework Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "libcef/browser/chrome/chrome_browser_context.h"

#include "libcef/browser/prefs/browser_prefs.h"

#include "chrome/browser/browser_process.h"
#include "chrome/browser/profiles/off_the_record_profile_impl.h"

ChromeBrowserContext::ChromeBrowserContext(
    const CefRequestContextSettings& settings)
    : CefBrowserContext(settings), weak_ptr_factory_(this) {}

ChromeBrowserContext::~ChromeBrowserContext() = default;

content::BrowserContext* ChromeBrowserContext::AsBrowserContext() {
  return profile_;
}

Profile* ChromeBrowserContext::AsProfile() {
  return profile_;
}

void ChromeBrowserContext::InitializeAsync(base::OnceClosure initialized_cb) {
  initialized_cb_ = std::move(initialized_cb);

  CefBrowserContext::Initialize();

  if (!cache_path_.empty()) {
    auto* profile_manager = g_browser_process->profile_manager();
    const auto& user_data_dir = profile_manager->user_data_dir();

    if (cache_path_ == user_data_dir) {
      // Use the default disk-based profile.
      auto profile = profile_manager->GetActiveUserProfile();
      ProfileCreated(profile, Profile::CreateStatus::CREATE_STATUS_CREATED);
      ProfileCreated(profile, Profile::CreateStatus::CREATE_STATUS_INITIALIZED);
      return;
    } else if (cache_path_.DirName() == user_data_dir) {
      // Create or load a specific disk-based profile. May continue
      // synchronously or asynchronously.
      profile_manager->CreateProfileAsync(
          cache_path_,
          base::Bind(&ChromeBrowserContext::ProfileCreated,
                     weak_ptr_factory_.GetWeakPtr()),
          /*name=*/base::string16(), /*icon_url=*/std::string());
      return;
    } else {
      // All profile directories must be relative to |user_data_dir|.
      LOG(ERROR) << "Cannot create profile at path "
                 << cache_path_.AsUTF8Unsafe();
    }
  }

  // Default to creating a new/unique OffTheRecord profile.
  ProfileCreated(nullptr, Profile::CreateStatus::CREATE_STATUS_CANCELED);
}

void ChromeBrowserContext::Shutdown() {
  CefBrowserContext::Shutdown();
  // |g_browser_process| may be nullptr during shutdown.
  if (should_destroy_ && g_browser_process) {
    g_browser_process->profile_manager()
        ->GetActiveUserProfile()
        ->DestroyOffTheRecordProfile(profile_);
  }
  profile_ = nullptr;
}

void ChromeBrowserContext::ProfileCreated(Profile* profile,
                                          Profile::CreateStatus status) {
  Profile* parent_profile = nullptr;
  OffTheRecordProfileImpl* otr_profile = nullptr;

  if (status != Profile::CreateStatus::CREATE_STATUS_CREATED &&
      status != Profile::CreateStatus::CREATE_STATUS_INITIALIZED) {
    DCHECK(!profile);
    DCHECK(!profile_);

    // Creation of a disk-based profile failed for some reason. Create a
    // new/unique OffTheRecord profile instead.
    const auto& profile_id = Profile::OTRProfileID::CreateUniqueForCEF();
    parent_profile =
        g_browser_process->profile_manager()->GetActiveUserProfile();
    profile_ = parent_profile->GetOffTheRecordProfile(profile_id);
    otr_profile = static_cast<OffTheRecordProfileImpl*>(profile_);
    status = Profile::CreateStatus::CREATE_STATUS_INITIALIZED;
    should_destroy_ = true;
  }

  if (status == Profile::CreateStatus::CREATE_STATUS_CREATED) {
    DCHECK(profile);
    DCHECK(!profile_);
    profile_ = profile;
  } else if (status == Profile::CreateStatus::CREATE_STATUS_INITIALIZED) {
    DCHECK(profile_);
    browser_prefs::SetLanguagePrefs(profile_);

    // Must set |profile_| before Init() calls
    // ChromeContentBrowserClientCef::ConfigureNetworkContextParams so that
    // CefBrowserContext::FromBrowserContext can find us.
    if (otr_profile) {
      otr_profile->Init();
      parent_profile->NotifyOffTheRecordProfileCreated(otr_profile);
    }

    std::move(initialized_cb_).Run();
  }
}
