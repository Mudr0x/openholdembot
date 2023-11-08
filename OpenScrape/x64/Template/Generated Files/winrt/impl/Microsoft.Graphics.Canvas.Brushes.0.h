// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.230706.1

#pragma once
#ifndef WINRT_Microsoft_Graphics_Canvas_Brushes_0_H
#define WINRT_Microsoft_Graphics_Canvas_Brushes_0_H
WINRT_EXPORT namespace winrt::Microsoft::Graphics::Canvas
{
    enum class CanvasAlphaMode : int32_t;
    enum class CanvasBufferPrecision : int32_t;
    enum class CanvasColorSpace : int32_t;
    struct CanvasDevice;
    enum class CanvasEdgeBehavior : int32_t;
    enum class CanvasImageInterpolation : int32_t;
    struct ICanvasImage;
    struct ICanvasResourceCreator;
}
WINRT_EXPORT namespace winrt::Windows::Foundation
{
    template <typename T> struct WINRT_IMPL_EMPTY_BASES IReference;
    struct Rect;
}
WINRT_EXPORT namespace winrt::Windows::Foundation::Numerics
{
}
WINRT_EXPORT namespace winrt::Windows::UI
{
    struct Color;
}
WINRT_EXPORT namespace winrt::Microsoft::Graphics::Canvas::Brushes
{
    struct ICanvasBrush;
    struct ICanvasImageBrush;
    struct ICanvasImageBrushFactory;
    struct ICanvasLinearGradientBrush;
    struct ICanvasLinearGradientBrushFactory;
    struct ICanvasLinearGradientBrushStatics;
    struct ICanvasRadialGradientBrush;
    struct ICanvasRadialGradientBrushFactory;
    struct ICanvasRadialGradientBrushStatics;
    struct ICanvasSolidColorBrush;
    struct ICanvasSolidColorBrushFactory;
    struct ICanvasSolidColorBrushStatics;
    struct CanvasImageBrush;
    struct CanvasLinearGradientBrush;
    struct CanvasRadialGradientBrush;
    struct CanvasSolidColorBrush;
    struct CanvasGradientStop;
    struct CanvasGradientStopHdr;
}
namespace winrt::impl
{
    template <> struct category<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasBrush>{ using type = interface_category; };
    template <> struct category<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasImageBrush>{ using type = interface_category; };
    template <> struct category<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasImageBrushFactory>{ using type = interface_category; };
    template <> struct category<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasLinearGradientBrush>{ using type = interface_category; };
    template <> struct category<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasLinearGradientBrushFactory>{ using type = interface_category; };
    template <> struct category<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasLinearGradientBrushStatics>{ using type = interface_category; };
    template <> struct category<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasRadialGradientBrush>{ using type = interface_category; };
    template <> struct category<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasRadialGradientBrushFactory>{ using type = interface_category; };
    template <> struct category<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasRadialGradientBrushStatics>{ using type = interface_category; };
    template <> struct category<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasSolidColorBrush>{ using type = interface_category; };
    template <> struct category<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasSolidColorBrushFactory>{ using type = interface_category; };
    template <> struct category<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasSolidColorBrushStatics>{ using type = interface_category; };
    template <> struct category<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasImageBrush>{ using type = class_category; };
    template <> struct category<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasLinearGradientBrush>{ using type = class_category; };
    template <> struct category<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasRadialGradientBrush>{ using type = class_category; };
    template <> struct category<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasSolidColorBrush>{ using type = class_category; };
    template <> struct category<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasGradientStop>{ using type = struct_category<float, winrt::Windows::UI::Color>; };
    template <> struct category<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasGradientStopHdr>{ using type = struct_category<float, winrt::Windows::Foundation::Numerics::float4>; };
    template <> inline constexpr auto& name_v<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasImageBrush> = L"Microsoft.Graphics.Canvas.Brushes.CanvasImageBrush";
    template <> inline constexpr auto& name_v<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasLinearGradientBrush> = L"Microsoft.Graphics.Canvas.Brushes.CanvasLinearGradientBrush";
    template <> inline constexpr auto& name_v<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasRadialGradientBrush> = L"Microsoft.Graphics.Canvas.Brushes.CanvasRadialGradientBrush";
    template <> inline constexpr auto& name_v<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasSolidColorBrush> = L"Microsoft.Graphics.Canvas.Brushes.CanvasSolidColorBrush";
    template <> inline constexpr auto& name_v<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasGradientStop> = L"Microsoft.Graphics.Canvas.Brushes.CanvasGradientStop";
    template <> inline constexpr auto& name_v<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasGradientStopHdr> = L"Microsoft.Graphics.Canvas.Brushes.CanvasGradientStopHdr";
    template <> inline constexpr auto& name_v<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasBrush> = L"Microsoft.Graphics.Canvas.Brushes.ICanvasBrush";
    template <> inline constexpr auto& name_v<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasImageBrush> = L"Microsoft.Graphics.Canvas.Brushes.ICanvasImageBrush";
    template <> inline constexpr auto& name_v<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasImageBrushFactory> = L"Microsoft.Graphics.Canvas.Brushes.ICanvasImageBrushFactory";
    template <> inline constexpr auto& name_v<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasLinearGradientBrush> = L"Microsoft.Graphics.Canvas.Brushes.ICanvasLinearGradientBrush";
    template <> inline constexpr auto& name_v<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasLinearGradientBrushFactory> = L"Microsoft.Graphics.Canvas.Brushes.ICanvasLinearGradientBrushFactory";
    template <> inline constexpr auto& name_v<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasLinearGradientBrushStatics> = L"Microsoft.Graphics.Canvas.Brushes.ICanvasLinearGradientBrushStatics";
    template <> inline constexpr auto& name_v<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasRadialGradientBrush> = L"Microsoft.Graphics.Canvas.Brushes.ICanvasRadialGradientBrush";
    template <> inline constexpr auto& name_v<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasRadialGradientBrushFactory> = L"Microsoft.Graphics.Canvas.Brushes.ICanvasRadialGradientBrushFactory";
    template <> inline constexpr auto& name_v<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasRadialGradientBrushStatics> = L"Microsoft.Graphics.Canvas.Brushes.ICanvasRadialGradientBrushStatics";
    template <> inline constexpr auto& name_v<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasSolidColorBrush> = L"Microsoft.Graphics.Canvas.Brushes.ICanvasSolidColorBrush";
    template <> inline constexpr auto& name_v<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasSolidColorBrushFactory> = L"Microsoft.Graphics.Canvas.Brushes.ICanvasSolidColorBrushFactory";
    template <> inline constexpr auto& name_v<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasSolidColorBrushStatics> = L"Microsoft.Graphics.Canvas.Brushes.ICanvasSolidColorBrushStatics";
    template <> inline constexpr guid guid_v<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasBrush>{ 0xF5D58591,0xC803,0x41B4,{ 0x87,0x8E,0x79,0xD9,0x2A,0xB1,0x32,0x95 } }; // F5D58591-C803-41B4-878E-79D92AB13295
    template <> inline constexpr guid guid_v<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasImageBrush>{ 0x5A21C4E7,0xD450,0x4942,{ 0x8B,0xBD,0xF0,0x17,0x09,0x7A,0xB7,0x63 } }; // 5A21C4E7-D450-4942-8BBD-F017097AB763
    template <> inline constexpr guid guid_v<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasImageBrushFactory>{ 0xC40CCB59,0x1B87,0x4394,{ 0xA6,0xA6,0xEC,0xD2,0x78,0xE8,0x77,0xD6 } }; // C40CCB59-1B87-4394-A6A6-ECD278E877D6
    template <> inline constexpr guid guid_v<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasLinearGradientBrush>{ 0xA4FFBCB1,0xEC22,0x48C8,{ 0xB1,0xAF,0x09,0xBC,0xFD,0x34,0xEE,0xBD } }; // A4FFBCB1-EC22-48C8-B1AF-09BCFD34EEBD
    template <> inline constexpr guid guid_v<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasLinearGradientBrushFactory>{ 0xA2E8E34A,0x8592,0x4B9D,{ 0xBA,0x1C,0x00,0xD3,0xF3,0xC3,0x4F,0x54 } }; // A2E8E34A-8592-4B9D-BA1C-00D3F3C34F54
    template <> inline constexpr guid guid_v<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasLinearGradientBrushStatics>{ 0xE9DE3392,0x8FBF,0x478C,{ 0x8E,0x6A,0xD0,0xA0,0xEA,0x75,0x3B,0x37 } }; // E9DE3392-8FBF-478C-8E6A-D0A0EA753B37
    template <> inline constexpr guid guid_v<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasRadialGradientBrush>{ 0x4D27D756,0x14A9,0x4EB7,{ 0x97,0x3F,0xE6,0x61,0x4D,0x4F,0x89,0xE7 } }; // 4D27D756-14A9-4EB7-973F-E6614D4F89E7
    template <> inline constexpr guid guid_v<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasRadialGradientBrushFactory>{ 0x7933A51F,0xA910,0x4548,{ 0x84,0x9F,0x42,0xDD,0xEC,0x46,0x6F,0x41 } }; // 7933A51F-A910-4548-849F-42DDEC466F41
    template <> inline constexpr guid guid_v<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasRadialGradientBrushStatics>{ 0x3B0D4DAE,0x3E21,0x4818,{ 0x99,0xB4,0x77,0x9A,0xCA,0xAF,0x18,0xBE } }; // 3B0D4DAE-3E21-4818-99B4-779ACAAF18BE
    template <> inline constexpr guid guid_v<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasSolidColorBrush>{ 0x8BC30F87,0xBAD5,0x4871,{ 0x88,0xB8,0x9F,0xE3,0xC6,0x3D,0x20,0x4A } }; // 8BC30F87-BAD5-4871-88B8-9FE3C63D204A
    template <> inline constexpr guid guid_v<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasSolidColorBrushFactory>{ 0x8ABF4780,0x4EDD,0x4F2B,{ 0xBF,0x63,0x2C,0x38,0x51,0x15,0xB2,0x01 } }; // 8ABF4780-4EDD-4F2B-BF63-2C385115B201
    template <> inline constexpr guid guid_v<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasSolidColorBrushStatics>{ 0x629B7244,0x5B9E,0x4EF8,{ 0x8E,0x09,0x26,0x47,0x14,0x20,0x1E,0xE8 } }; // 629B7244-5B9E-4EF8-8E09-264714201EE8
    template <> struct default_interface<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasImageBrush>{ using type = winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasImageBrush; };
    template <> struct default_interface<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasLinearGradientBrush>{ using type = winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasLinearGradientBrush; };
    template <> struct default_interface<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasRadialGradientBrush>{ using type = winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasRadialGradientBrush; };
    template <> struct default_interface<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasSolidColorBrush>{ using type = winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasSolidColorBrush; };
    template <> struct abi<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasBrush>
    {
        struct WINRT_IMPL_NOVTABLE type : inspectable_abi
        {
            virtual int32_t __stdcall get_Opacity(float*) noexcept = 0;
            virtual int32_t __stdcall put_Opacity(float) noexcept = 0;
            virtual int32_t __stdcall get_Transform(winrt::Windows::Foundation::Numerics::float3x2*) noexcept = 0;
            virtual int32_t __stdcall put_Transform(winrt::Windows::Foundation::Numerics::float3x2) noexcept = 0;
            virtual int32_t __stdcall get_Device(void**) noexcept = 0;
        };
    };
    template <> struct abi<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasImageBrush>
    {
        struct WINRT_IMPL_NOVTABLE type : inspectable_abi
        {
            virtual int32_t __stdcall get_Image(void**) noexcept = 0;
            virtual int32_t __stdcall put_Image(void*) noexcept = 0;
            virtual int32_t __stdcall get_ExtendX(int32_t*) noexcept = 0;
            virtual int32_t __stdcall put_ExtendX(int32_t) noexcept = 0;
            virtual int32_t __stdcall get_ExtendY(int32_t*) noexcept = 0;
            virtual int32_t __stdcall put_ExtendY(int32_t) noexcept = 0;
            virtual int32_t __stdcall get_SourceRectangle(void**) noexcept = 0;
            virtual int32_t __stdcall put_SourceRectangle(void*) noexcept = 0;
            virtual int32_t __stdcall get_Interpolation(int32_t*) noexcept = 0;
            virtual int32_t __stdcall put_Interpolation(int32_t) noexcept = 0;
        };
    };
    template <> struct abi<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasImageBrushFactory>
    {
        struct WINRT_IMPL_NOVTABLE type : inspectable_abi
        {
            virtual int32_t __stdcall Create(void*, void**) noexcept = 0;
            virtual int32_t __stdcall CreateWithImage(void*, void*, void**) noexcept = 0;
        };
    };
    template <> struct abi<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasLinearGradientBrush>
    {
        struct WINRT_IMPL_NOVTABLE type : inspectable_abi
        {
            virtual int32_t __stdcall get_StartPoint(winrt::Windows::Foundation::Numerics::float2*) noexcept = 0;
            virtual int32_t __stdcall put_StartPoint(winrt::Windows::Foundation::Numerics::float2) noexcept = 0;
            virtual int32_t __stdcall get_EndPoint(winrt::Windows::Foundation::Numerics::float2*) noexcept = 0;
            virtual int32_t __stdcall put_EndPoint(winrt::Windows::Foundation::Numerics::float2) noexcept = 0;
            virtual int32_t __stdcall get_Stops(uint32_t* __valueElementsSize, struct struct_Microsoft_Graphics_Canvas_Brushes_CanvasGradientStop**) noexcept = 0;
            virtual int32_t __stdcall get_StopsHdr(uint32_t* __valueElementsSize, struct struct_Microsoft_Graphics_Canvas_Brushes_CanvasGradientStopHdr**) noexcept = 0;
            virtual int32_t __stdcall get_EdgeBehavior(int32_t*) noexcept = 0;
            virtual int32_t __stdcall get_PreInterpolationSpace(int32_t*) noexcept = 0;
            virtual int32_t __stdcall get_PostInterpolationSpace(int32_t*) noexcept = 0;
            virtual int32_t __stdcall get_BufferPrecision(int32_t*) noexcept = 0;
            virtual int32_t __stdcall get_AlphaMode(int32_t*) noexcept = 0;
        };
    };
    template <> struct abi<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasLinearGradientBrushFactory>
    {
        struct WINRT_IMPL_NOVTABLE type : inspectable_abi
        {
            virtual int32_t __stdcall CreateSimple(void*, struct struct_Windows_UI_Color, struct struct_Windows_UI_Color, void**) noexcept = 0;
            virtual int32_t __stdcall CreateWithStops(void*, uint32_t, struct struct_Microsoft_Graphics_Canvas_Brushes_CanvasGradientStop*, void**) noexcept = 0;
            virtual int32_t __stdcall CreateWithEdgeBehaviorAndAlphaMode(void*, uint32_t, struct struct_Microsoft_Graphics_Canvas_Brushes_CanvasGradientStop*, int32_t, int32_t, void**) noexcept = 0;
            virtual int32_t __stdcall CreateWithEdgeBehaviorAndInterpolationOptions(void*, uint32_t, struct struct_Microsoft_Graphics_Canvas_Brushes_CanvasGradientStop*, int32_t, int32_t, int32_t, int32_t, int32_t, void**) noexcept = 0;
        };
    };
    template <> struct abi<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasLinearGradientBrushStatics>
    {
        struct WINRT_IMPL_NOVTABLE type : inspectable_abi
        {
            virtual int32_t __stdcall CreateHdrSimple(void*, winrt::Windows::Foundation::Numerics::float4, winrt::Windows::Foundation::Numerics::float4, void**) noexcept = 0;
            virtual int32_t __stdcall CreateHdrWithStops(void*, uint32_t, struct struct_Microsoft_Graphics_Canvas_Brushes_CanvasGradientStopHdr*, void**) noexcept = 0;
            virtual int32_t __stdcall CreateHdrWithEdgeBehaviorAndAlphaMode(void*, uint32_t, struct struct_Microsoft_Graphics_Canvas_Brushes_CanvasGradientStopHdr*, int32_t, int32_t, void**) noexcept = 0;
            virtual int32_t __stdcall CreateHdrWithEdgeBehaviorAndInterpolationOptions(void*, uint32_t, struct struct_Microsoft_Graphics_Canvas_Brushes_CanvasGradientStopHdr*, int32_t, int32_t, int32_t, int32_t, int32_t, void**) noexcept = 0;
            virtual int32_t __stdcall CreateRainbow(void*, float, void**) noexcept = 0;
        };
    };
    template <> struct abi<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasRadialGradientBrush>
    {
        struct WINRT_IMPL_NOVTABLE type : inspectable_abi
        {
            virtual int32_t __stdcall get_Center(winrt::Windows::Foundation::Numerics::float2*) noexcept = 0;
            virtual int32_t __stdcall put_Center(winrt::Windows::Foundation::Numerics::float2) noexcept = 0;
            virtual int32_t __stdcall get_OriginOffset(winrt::Windows::Foundation::Numerics::float2*) noexcept = 0;
            virtual int32_t __stdcall put_OriginOffset(winrt::Windows::Foundation::Numerics::float2) noexcept = 0;
            virtual int32_t __stdcall get_RadiusX(float*) noexcept = 0;
            virtual int32_t __stdcall put_RadiusX(float) noexcept = 0;
            virtual int32_t __stdcall get_RadiusY(float*) noexcept = 0;
            virtual int32_t __stdcall put_RadiusY(float) noexcept = 0;
            virtual int32_t __stdcall get_Stops(uint32_t* __valueElementsSize, struct struct_Microsoft_Graphics_Canvas_Brushes_CanvasGradientStop**) noexcept = 0;
            virtual int32_t __stdcall get_StopsHdr(uint32_t* __valueElementsSize, struct struct_Microsoft_Graphics_Canvas_Brushes_CanvasGradientStopHdr**) noexcept = 0;
            virtual int32_t __stdcall get_EdgeBehavior(int32_t*) noexcept = 0;
            virtual int32_t __stdcall get_PreInterpolationSpace(int32_t*) noexcept = 0;
            virtual int32_t __stdcall get_PostInterpolationSpace(int32_t*) noexcept = 0;
            virtual int32_t __stdcall get_BufferPrecision(int32_t*) noexcept = 0;
            virtual int32_t __stdcall get_AlphaMode(int32_t*) noexcept = 0;
        };
    };
    template <> struct abi<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasRadialGradientBrushFactory>
    {
        struct WINRT_IMPL_NOVTABLE type : inspectable_abi
        {
            virtual int32_t __stdcall CreateSimple(void*, struct struct_Windows_UI_Color, struct struct_Windows_UI_Color, void**) noexcept = 0;
            virtual int32_t __stdcall CreateWithStops(void*, uint32_t, struct struct_Microsoft_Graphics_Canvas_Brushes_CanvasGradientStop*, void**) noexcept = 0;
            virtual int32_t __stdcall CreateWithEdgeBehaviorAndAlphaMode(void*, uint32_t, struct struct_Microsoft_Graphics_Canvas_Brushes_CanvasGradientStop*, int32_t, int32_t, void**) noexcept = 0;
            virtual int32_t __stdcall CreateWithEdgeBehaviorAndInterpolationOptions(void*, uint32_t, struct struct_Microsoft_Graphics_Canvas_Brushes_CanvasGradientStop*, int32_t, int32_t, int32_t, int32_t, int32_t, void**) noexcept = 0;
        };
    };
    template <> struct abi<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasRadialGradientBrushStatics>
    {
        struct WINRT_IMPL_NOVTABLE type : inspectable_abi
        {
            virtual int32_t __stdcall CreateHdrSimple(void*, winrt::Windows::Foundation::Numerics::float4, winrt::Windows::Foundation::Numerics::float4, void**) noexcept = 0;
            virtual int32_t __stdcall CreateHdrWithStops(void*, uint32_t, struct struct_Microsoft_Graphics_Canvas_Brushes_CanvasGradientStopHdr*, void**) noexcept = 0;
            virtual int32_t __stdcall CreateHdrWithEdgeBehaviorAndAlphaMode(void*, uint32_t, struct struct_Microsoft_Graphics_Canvas_Brushes_CanvasGradientStopHdr*, int32_t, int32_t, void**) noexcept = 0;
            virtual int32_t __stdcall CreateHdrWithEdgeBehaviorAndInterpolationOptions(void*, uint32_t, struct struct_Microsoft_Graphics_Canvas_Brushes_CanvasGradientStopHdr*, int32_t, int32_t, int32_t, int32_t, int32_t, void**) noexcept = 0;
            virtual int32_t __stdcall CreateRainbow(void*, float, void**) noexcept = 0;
        };
    };
    template <> struct abi<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasSolidColorBrush>
    {
        struct WINRT_IMPL_NOVTABLE type : inspectable_abi
        {
            virtual int32_t __stdcall get_Color(struct struct_Windows_UI_Color*) noexcept = 0;
            virtual int32_t __stdcall put_Color(struct struct_Windows_UI_Color) noexcept = 0;
            virtual int32_t __stdcall get_ColorHdr(winrt::Windows::Foundation::Numerics::float4*) noexcept = 0;
            virtual int32_t __stdcall put_ColorHdr(winrt::Windows::Foundation::Numerics::float4) noexcept = 0;
        };
    };
    template <> struct abi<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasSolidColorBrushFactory>
    {
        struct WINRT_IMPL_NOVTABLE type : inspectable_abi
        {
            virtual int32_t __stdcall Create(void*, struct struct_Windows_UI_Color, void**) noexcept = 0;
        };
    };
    template <> struct abi<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasSolidColorBrushStatics>
    {
        struct WINRT_IMPL_NOVTABLE type : inspectable_abi
        {
            virtual int32_t __stdcall CreateHdr(void*, winrt::Windows::Foundation::Numerics::float4, void**) noexcept = 0;
        };
    };
    template <typename D>
    struct consume_Microsoft_Graphics_Canvas_Brushes_ICanvasBrush
    {
        [[nodiscard]] auto Opacity() const;
        auto Opacity(float value) const;
        [[nodiscard]] auto Transform() const;
        auto Transform(winrt::Windows::Foundation::Numerics::float3x2 const& value) const;
        [[nodiscard]] auto Device() const;
    };
    template <> struct consume<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasBrush>
    {
        template <typename D> using type = consume_Microsoft_Graphics_Canvas_Brushes_ICanvasBrush<D>;
    };
    template <typename D>
    struct consume_Microsoft_Graphics_Canvas_Brushes_ICanvasImageBrush
    {
        [[nodiscard]] auto Image() const;
        auto Image(winrt::Microsoft::Graphics::Canvas::ICanvasImage const& value) const;
        [[nodiscard]] auto ExtendX() const;
        auto ExtendX(winrt::Microsoft::Graphics::Canvas::CanvasEdgeBehavior const& value) const;
        [[nodiscard]] auto ExtendY() const;
        auto ExtendY(winrt::Microsoft::Graphics::Canvas::CanvasEdgeBehavior const& value) const;
        [[nodiscard]] auto SourceRectangle() const;
        auto SourceRectangle(winrt::Windows::Foundation::IReference<winrt::Windows::Foundation::Rect> const& value) const;
        [[nodiscard]] auto Interpolation() const;
        auto Interpolation(winrt::Microsoft::Graphics::Canvas::CanvasImageInterpolation const& value) const;
    };
    template <> struct consume<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasImageBrush>
    {
        template <typename D> using type = consume_Microsoft_Graphics_Canvas_Brushes_ICanvasImageBrush<D>;
    };
    template <typename D>
    struct consume_Microsoft_Graphics_Canvas_Brushes_ICanvasImageBrushFactory
    {
        auto Create(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator) const;
        auto CreateWithImage(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, winrt::Microsoft::Graphics::Canvas::ICanvasImage const& image) const;
    };
    template <> struct consume<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasImageBrushFactory>
    {
        template <typename D> using type = consume_Microsoft_Graphics_Canvas_Brushes_ICanvasImageBrushFactory<D>;
    };
    template <typename D>
    struct consume_Microsoft_Graphics_Canvas_Brushes_ICanvasLinearGradientBrush
    {
        [[nodiscard]] auto StartPoint() const;
        auto StartPoint(winrt::Windows::Foundation::Numerics::float2 const& value) const;
        [[nodiscard]] auto EndPoint() const;
        auto EndPoint(winrt::Windows::Foundation::Numerics::float2 const& value) const;
        [[nodiscard]] auto Stops() const;
        [[nodiscard]] auto StopsHdr() const;
        [[nodiscard]] auto EdgeBehavior() const;
        [[nodiscard]] auto PreInterpolationSpace() const;
        [[nodiscard]] auto PostInterpolationSpace() const;
        [[nodiscard]] auto BufferPrecision() const;
        [[nodiscard]] auto AlphaMode() const;
    };
    template <> struct consume<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasLinearGradientBrush>
    {
        template <typename D> using type = consume_Microsoft_Graphics_Canvas_Brushes_ICanvasLinearGradientBrush<D>;
    };
    template <typename D>
    struct consume_Microsoft_Graphics_Canvas_Brushes_ICanvasLinearGradientBrushFactory
    {
        auto CreateSimple(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, winrt::Windows::UI::Color const& startColor, winrt::Windows::UI::Color const& endColor) const;
        auto CreateWithStops(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, array_view<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasGradientStop const> gradientStops) const;
        auto CreateWithEdgeBehaviorAndAlphaMode(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, array_view<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasGradientStop const> gradientStops, winrt::Microsoft::Graphics::Canvas::CanvasEdgeBehavior const& edgeBehavior, winrt::Microsoft::Graphics::Canvas::CanvasAlphaMode const& alphaMode) const;
        auto CreateWithEdgeBehaviorAndInterpolationOptions(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, array_view<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasGradientStop const> gradientStops, winrt::Microsoft::Graphics::Canvas::CanvasEdgeBehavior const& edgeBehavior, winrt::Microsoft::Graphics::Canvas::CanvasAlphaMode const& alphaMode, winrt::Microsoft::Graphics::Canvas::CanvasColorSpace const& preInterpolationSpace, winrt::Microsoft::Graphics::Canvas::CanvasColorSpace const& postInterpolationSpace, winrt::Microsoft::Graphics::Canvas::CanvasBufferPrecision const& bufferPrecision) const;
    };
    template <> struct consume<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasLinearGradientBrushFactory>
    {
        template <typename D> using type = consume_Microsoft_Graphics_Canvas_Brushes_ICanvasLinearGradientBrushFactory<D>;
    };
    template <typename D>
    struct consume_Microsoft_Graphics_Canvas_Brushes_ICanvasLinearGradientBrushStatics
    {
        auto CreateHdr(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, winrt::Windows::Foundation::Numerics::float4 const& startColorHdr, winrt::Windows::Foundation::Numerics::float4 const& endColorHdr) const;
        auto CreateHdr(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, array_view<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasGradientStopHdr const> gradientStopsHdr) const;
        auto CreateHdr(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, array_view<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasGradientStopHdr const> gradientStopsHdr, winrt::Microsoft::Graphics::Canvas::CanvasEdgeBehavior const& edgeBehavior, winrt::Microsoft::Graphics::Canvas::CanvasAlphaMode const& alphaMode) const;
        auto CreateHdr(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, array_view<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasGradientStopHdr const> gradientStopsHdr, winrt::Microsoft::Graphics::Canvas::CanvasEdgeBehavior const& edgeBehavior, winrt::Microsoft::Graphics::Canvas::CanvasAlphaMode const& alphaMode, winrt::Microsoft::Graphics::Canvas::CanvasColorSpace const& preInterpolationSpace, winrt::Microsoft::Graphics::Canvas::CanvasColorSpace const& postInterpolationSpace, winrt::Microsoft::Graphics::Canvas::CanvasBufferPrecision const& bufferPrecision) const;
        auto CreateRainbow(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, float eldritchness) const;
    };
    template <> struct consume<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasLinearGradientBrushStatics>
    {
        template <typename D> using type = consume_Microsoft_Graphics_Canvas_Brushes_ICanvasLinearGradientBrushStatics<D>;
    };
    template <typename D>
    struct consume_Microsoft_Graphics_Canvas_Brushes_ICanvasRadialGradientBrush
    {
        [[nodiscard]] auto Center() const;
        auto Center(winrt::Windows::Foundation::Numerics::float2 const& value) const;
        [[nodiscard]] auto OriginOffset() const;
        auto OriginOffset(winrt::Windows::Foundation::Numerics::float2 const& value) const;
        [[nodiscard]] auto RadiusX() const;
        auto RadiusX(float value) const;
        [[nodiscard]] auto RadiusY() const;
        auto RadiusY(float value) const;
        [[nodiscard]] auto Stops() const;
        [[nodiscard]] auto StopsHdr() const;
        [[nodiscard]] auto EdgeBehavior() const;
        [[nodiscard]] auto PreInterpolationSpace() const;
        [[nodiscard]] auto PostInterpolationSpace() const;
        [[nodiscard]] auto BufferPrecision() const;
        [[nodiscard]] auto AlphaMode() const;
    };
    template <> struct consume<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasRadialGradientBrush>
    {
        template <typename D> using type = consume_Microsoft_Graphics_Canvas_Brushes_ICanvasRadialGradientBrush<D>;
    };
    template <typename D>
    struct consume_Microsoft_Graphics_Canvas_Brushes_ICanvasRadialGradientBrushFactory
    {
        auto CreateSimple(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, winrt::Windows::UI::Color const& startColor, winrt::Windows::UI::Color const& endColor) const;
        auto CreateWithStops(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, array_view<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasGradientStop const> gradientStops) const;
        auto CreateWithEdgeBehaviorAndAlphaMode(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, array_view<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasGradientStop const> gradientStops, winrt::Microsoft::Graphics::Canvas::CanvasEdgeBehavior const& edgeBehavior, winrt::Microsoft::Graphics::Canvas::CanvasAlphaMode const& alphaMode) const;
        auto CreateWithEdgeBehaviorAndInterpolationOptions(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, array_view<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasGradientStop const> gradientStops, winrt::Microsoft::Graphics::Canvas::CanvasEdgeBehavior const& edgeBehavior, winrt::Microsoft::Graphics::Canvas::CanvasAlphaMode const& alphaMode, winrt::Microsoft::Graphics::Canvas::CanvasColorSpace const& preInterpolationSpace, winrt::Microsoft::Graphics::Canvas::CanvasColorSpace const& postInterpolationSpace, winrt::Microsoft::Graphics::Canvas::CanvasBufferPrecision const& bufferPrecision) const;
    };
    template <> struct consume<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasRadialGradientBrushFactory>
    {
        template <typename D> using type = consume_Microsoft_Graphics_Canvas_Brushes_ICanvasRadialGradientBrushFactory<D>;
    };
    template <typename D>
    struct consume_Microsoft_Graphics_Canvas_Brushes_ICanvasRadialGradientBrushStatics
    {
        auto CreateHdr(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, winrt::Windows::Foundation::Numerics::float4 const& startColorHdr, winrt::Windows::Foundation::Numerics::float4 const& endColorHdr) const;
        auto CreateHdr(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, array_view<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasGradientStopHdr const> gradientStops) const;
        auto CreateHdr(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, array_view<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasGradientStopHdr const> gradientStops, winrt::Microsoft::Graphics::Canvas::CanvasEdgeBehavior const& edgeBehavior, winrt::Microsoft::Graphics::Canvas::CanvasAlphaMode const& alphaMode) const;
        auto CreateHdr(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, array_view<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasGradientStopHdr const> gradientStops, winrt::Microsoft::Graphics::Canvas::CanvasEdgeBehavior const& edgeBehavior, winrt::Microsoft::Graphics::Canvas::CanvasAlphaMode const& alphaMode, winrt::Microsoft::Graphics::Canvas::CanvasColorSpace const& preInterpolationSpace, winrt::Microsoft::Graphics::Canvas::CanvasColorSpace const& postInterpolationSpace, winrt::Microsoft::Graphics::Canvas::CanvasBufferPrecision const& bufferPrecision) const;
        auto CreateRainbow(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, float eldritchness) const;
    };
    template <> struct consume<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasRadialGradientBrushStatics>
    {
        template <typename D> using type = consume_Microsoft_Graphics_Canvas_Brushes_ICanvasRadialGradientBrushStatics<D>;
    };
    template <typename D>
    struct consume_Microsoft_Graphics_Canvas_Brushes_ICanvasSolidColorBrush
    {
        [[nodiscard]] auto Color() const;
        auto Color(winrt::Windows::UI::Color const& value) const;
        [[nodiscard]] auto ColorHdr() const;
        auto ColorHdr(winrt::Windows::Foundation::Numerics::float4 const& value) const;
    };
    template <> struct consume<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasSolidColorBrush>
    {
        template <typename D> using type = consume_Microsoft_Graphics_Canvas_Brushes_ICanvasSolidColorBrush<D>;
    };
    template <typename D>
    struct consume_Microsoft_Graphics_Canvas_Brushes_ICanvasSolidColorBrushFactory
    {
        auto Create(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, winrt::Windows::UI::Color const& color) const;
    };
    template <> struct consume<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasSolidColorBrushFactory>
    {
        template <typename D> using type = consume_Microsoft_Graphics_Canvas_Brushes_ICanvasSolidColorBrushFactory<D>;
    };
    template <typename D>
    struct consume_Microsoft_Graphics_Canvas_Brushes_ICanvasSolidColorBrushStatics
    {
        auto CreateHdr(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, winrt::Windows::Foundation::Numerics::float4 const& colorHdr) const;
    };
    template <> struct consume<winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasSolidColorBrushStatics>
    {
        template <typename D> using type = consume_Microsoft_Graphics_Canvas_Brushes_ICanvasSolidColorBrushStatics<D>;
    };
    struct struct_Microsoft_Graphics_Canvas_Brushes_CanvasGradientStop
    {
        float Position;
        struct{ uint8_t A; uint8_t R; uint8_t G; uint8_t B; } Color;
    };
    template <> struct abi<Microsoft::Graphics::Canvas::Brushes::CanvasGradientStop>
    {
        using type = struct_Microsoft_Graphics_Canvas_Brushes_CanvasGradientStop;
    };
    struct struct_Microsoft_Graphics_Canvas_Brushes_CanvasGradientStopHdr
    {
        float Position;
        winrt::Windows::Foundation::Numerics::float4 Color;
    };
    template <> struct abi<Microsoft::Graphics::Canvas::Brushes::CanvasGradientStopHdr>
    {
        using type = struct_Microsoft_Graphics_Canvas_Brushes_CanvasGradientStopHdr;
    };
}
#endif