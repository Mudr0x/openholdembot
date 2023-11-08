// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.230706.1

#pragma once
#ifndef WINRT_Microsoft_Graphics_Canvas_UI_0_H
#define WINRT_Microsoft_Graphics_Canvas_UI_0_H
WINRT_EXPORT namespace winrt::Windows::Foundation
{
    struct IAsyncAction;
}
WINRT_EXPORT namespace winrt::Microsoft::Graphics::Canvas::UI
{
    enum class CanvasCreateResourcesReason : int32_t
    {
        FirstTime = 0,
        NewDevice = 1,
        DpiChanged = 2,
    };
    struct ICanvasCreateResourcesEventArgs;
    struct ICanvasCreateResourcesEventArgsFactory;
    struct CanvasCreateResourcesEventArgs;
    struct CanvasTimingInformation;
}
namespace winrt::impl
{
    template <> struct category<winrt::Microsoft::Graphics::Canvas::UI::ICanvasCreateResourcesEventArgs>{ using type = interface_category; };
    template <> struct category<winrt::Microsoft::Graphics::Canvas::UI::ICanvasCreateResourcesEventArgsFactory>{ using type = interface_category; };
    template <> struct category<winrt::Microsoft::Graphics::Canvas::UI::CanvasCreateResourcesEventArgs>{ using type = class_category; };
    template <> struct category<winrt::Microsoft::Graphics::Canvas::UI::CanvasCreateResourcesReason>{ using type = enum_category; };
    template <> struct category<winrt::Microsoft::Graphics::Canvas::UI::CanvasTimingInformation>{ using type = struct_category<int64_t, winrt::Windows::Foundation::TimeSpan, winrt::Windows::Foundation::TimeSpan, bool>; };
    template <> inline constexpr auto& name_v<winrt::Microsoft::Graphics::Canvas::UI::CanvasCreateResourcesEventArgs> = L"Microsoft.Graphics.Canvas.UI.CanvasCreateResourcesEventArgs";
    template <> inline constexpr auto& name_v<winrt::Microsoft::Graphics::Canvas::UI::CanvasCreateResourcesReason> = L"Microsoft.Graphics.Canvas.UI.CanvasCreateResourcesReason";
    template <> inline constexpr auto& name_v<winrt::Microsoft::Graphics::Canvas::UI::CanvasTimingInformation> = L"Microsoft.Graphics.Canvas.UI.CanvasTimingInformation";
    template <> inline constexpr auto& name_v<winrt::Microsoft::Graphics::Canvas::UI::ICanvasCreateResourcesEventArgs> = L"Microsoft.Graphics.Canvas.UI.ICanvasCreateResourcesEventArgs";
    template <> inline constexpr auto& name_v<winrt::Microsoft::Graphics::Canvas::UI::ICanvasCreateResourcesEventArgsFactory> = L"Microsoft.Graphics.Canvas.UI.ICanvasCreateResourcesEventArgsFactory";
    template <> inline constexpr guid guid_v<winrt::Microsoft::Graphics::Canvas::UI::ICanvasCreateResourcesEventArgs>{ 0xEDC52108,0xF6BA,0x4A09,{ 0x9F,0xA3,0x10,0xC9,0x7A,0x24,0xE4,0x9A } }; // EDC52108-F6BA-4A09-9FA3-10C97A24E49A
    template <> inline constexpr guid guid_v<winrt::Microsoft::Graphics::Canvas::UI::ICanvasCreateResourcesEventArgsFactory>{ 0x3A21C766,0x0781,0x4389,{ 0xBB,0xC3,0x86,0xB1,0xF5,0x02,0x2A,0xF1 } }; // 3A21C766-0781-4389-BBC3-86B1F5022AF1
    template <> struct default_interface<winrt::Microsoft::Graphics::Canvas::UI::CanvasCreateResourcesEventArgs>{ using type = winrt::Microsoft::Graphics::Canvas::UI::ICanvasCreateResourcesEventArgs; };
    template <> struct abi<winrt::Microsoft::Graphics::Canvas::UI::ICanvasCreateResourcesEventArgs>
    {
        struct WINRT_IMPL_NOVTABLE type : inspectable_abi
        {
            virtual int32_t __stdcall get_Reason(int32_t*) noexcept = 0;
            virtual int32_t __stdcall TrackAsyncAction(void*) noexcept = 0;
            virtual int32_t __stdcall GetTrackedAction(void**) noexcept = 0;
        };
    };
    template <> struct abi<winrt::Microsoft::Graphics::Canvas::UI::ICanvasCreateResourcesEventArgsFactory>
    {
        struct WINRT_IMPL_NOVTABLE type : inspectable_abi
        {
            virtual int32_t __stdcall Create(int32_t, void**) noexcept = 0;
        };
    };
    template <typename D>
    struct consume_Microsoft_Graphics_Canvas_UI_ICanvasCreateResourcesEventArgs
    {
        [[nodiscard]] auto Reason() const;
        auto TrackAsyncAction(winrt::Windows::Foundation::IAsyncAction const& action) const;
        auto GetTrackedAction() const;
    };
    template <> struct consume<winrt::Microsoft::Graphics::Canvas::UI::ICanvasCreateResourcesEventArgs>
    {
        template <typename D> using type = consume_Microsoft_Graphics_Canvas_UI_ICanvasCreateResourcesEventArgs<D>;
    };
    template <typename D>
    struct consume_Microsoft_Graphics_Canvas_UI_ICanvasCreateResourcesEventArgsFactory
    {
        auto Create(winrt::Microsoft::Graphics::Canvas::UI::CanvasCreateResourcesReason const& createResourcesReason) const;
    };
    template <> struct consume<winrt::Microsoft::Graphics::Canvas::UI::ICanvasCreateResourcesEventArgsFactory>
    {
        template <typename D> using type = consume_Microsoft_Graphics_Canvas_UI_ICanvasCreateResourcesEventArgsFactory<D>;
    };
    struct struct_Microsoft_Graphics_Canvas_UI_CanvasTimingInformation
    {
        int64_t UpdateCount;
        int64_t TotalTime;
        int64_t ElapsedTime;
        bool IsRunningSlowly;
    };
    template <> struct abi<Microsoft::Graphics::Canvas::UI::CanvasTimingInformation>
    {
        using type = struct_Microsoft_Graphics_Canvas_UI_CanvasTimingInformation;
    };
}
#endif
