// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.230706.1

#pragma once
#ifndef WINRT_Windows_Phone_Devices_Notification_2_H
#define WINRT_Windows_Phone_Devices_Notification_2_H
#include "winrt/impl/Windows.Phone.Devices.Notification.1.h"
WINRT_EXPORT namespace winrt::Windows::Phone::Devices::Notification
{
    struct WINRT_IMPL_EMPTY_BASES VibrationDevice : winrt::Windows::Phone::Devices::Notification::IVibrationDevice
    {
        VibrationDevice(std::nullptr_t) noexcept {}
        VibrationDevice(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Phone::Devices::Notification::IVibrationDevice(ptr, take_ownership_from_abi) {}
        static auto GetDefault();
    };
}
#endif
