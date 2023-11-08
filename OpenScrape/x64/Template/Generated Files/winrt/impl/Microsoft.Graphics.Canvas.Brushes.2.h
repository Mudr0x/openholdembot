// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.230706.1

#pragma once
#ifndef WINRT_Microsoft_Graphics_Canvas_Brushes_2_H
#define WINRT_Microsoft_Graphics_Canvas_Brushes_2_H
#include "winrt/impl/Microsoft.Graphics.Canvas.2.h"
#include "winrt/impl/Windows.Foundation.2.h"
#include "winrt/impl/Windows.Foundation.Numerics.2.h"
#include "winrt/impl/Windows.UI.2.h"
#include "winrt/impl/Microsoft.Graphics.Canvas.Brushes.1.h"
WINRT_EXPORT namespace winrt::Microsoft::Graphics::Canvas::Brushes
{
    struct CanvasGradientStop
    {
        float Position;
        winrt::Windows::UI::Color Color;
    };
    inline bool operator==(CanvasGradientStop const& left, CanvasGradientStop const& right) noexcept
    {
        return left.Position == right.Position && left.Color == right.Color;
    }
    inline bool operator!=(CanvasGradientStop const& left, CanvasGradientStop const& right) noexcept
    {
        return !(left == right);
    }
    struct CanvasGradientStopHdr
    {
        float Position;
        winrt::Windows::Foundation::Numerics::float4 Color;
    };
    inline bool operator==(CanvasGradientStopHdr const& left, CanvasGradientStopHdr const& right) noexcept
    {
        return left.Position == right.Position && left.Color == right.Color;
    }
    inline bool operator!=(CanvasGradientStopHdr const& left, CanvasGradientStopHdr const& right) noexcept
    {
        return !(left == right);
    }
    struct WINRT_IMPL_EMPTY_BASES CanvasImageBrush : winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasImageBrush
    {
        CanvasImageBrush(std::nullptr_t) noexcept {}
        CanvasImageBrush(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasImageBrush(ptr, take_ownership_from_abi) {}
        explicit CanvasImageBrush(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator);
        CanvasImageBrush(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, winrt::Microsoft::Graphics::Canvas::ICanvasImage const& image);
    };
    struct WINRT_IMPL_EMPTY_BASES CanvasLinearGradientBrush : winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasLinearGradientBrush
    {
        CanvasLinearGradientBrush(std::nullptr_t) noexcept {}
        CanvasLinearGradientBrush(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasLinearGradientBrush(ptr, take_ownership_from_abi) {}
        CanvasLinearGradientBrush(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, winrt::Windows::UI::Color const& startColor, winrt::Windows::UI::Color const& endColor);
        CanvasLinearGradientBrush(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, array_view<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasGradientStop const> gradientStops);
        CanvasLinearGradientBrush(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, array_view<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasGradientStop const> gradientStops, winrt::Microsoft::Graphics::Canvas::CanvasEdgeBehavior const& edgeBehavior, winrt::Microsoft::Graphics::Canvas::CanvasAlphaMode const& alphaMode);
        CanvasLinearGradientBrush(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, array_view<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasGradientStop const> gradientStops, winrt::Microsoft::Graphics::Canvas::CanvasEdgeBehavior const& edgeBehavior, winrt::Microsoft::Graphics::Canvas::CanvasAlphaMode const& alphaMode, winrt::Microsoft::Graphics::Canvas::CanvasColorSpace const& preInterpolationSpace, winrt::Microsoft::Graphics::Canvas::CanvasColorSpace const& postInterpolationSpace, winrt::Microsoft::Graphics::Canvas::CanvasBufferPrecision const& bufferPrecision);
        static auto CreateHdr(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, winrt::Windows::Foundation::Numerics::float4 const& startColorHdr, winrt::Windows::Foundation::Numerics::float4 const& endColorHdr);
        static auto CreateHdr(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, array_view<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasGradientStopHdr const> gradientStopsHdr);
        static auto CreateHdr(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, array_view<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasGradientStopHdr const> gradientStopsHdr, winrt::Microsoft::Graphics::Canvas::CanvasEdgeBehavior const& edgeBehavior, winrt::Microsoft::Graphics::Canvas::CanvasAlphaMode const& alphaMode);
        static auto CreateHdr(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, array_view<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasGradientStopHdr const> gradientStopsHdr, winrt::Microsoft::Graphics::Canvas::CanvasEdgeBehavior const& edgeBehavior, winrt::Microsoft::Graphics::Canvas::CanvasAlphaMode const& alphaMode, winrt::Microsoft::Graphics::Canvas::CanvasColorSpace const& preInterpolationSpace, winrt::Microsoft::Graphics::Canvas::CanvasColorSpace const& postInterpolationSpace, winrt::Microsoft::Graphics::Canvas::CanvasBufferPrecision const& bufferPrecision);
        static auto CreateRainbow(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, float eldritchness);
    };
    struct WINRT_IMPL_EMPTY_BASES CanvasRadialGradientBrush : winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasRadialGradientBrush
    {
        CanvasRadialGradientBrush(std::nullptr_t) noexcept {}
        CanvasRadialGradientBrush(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasRadialGradientBrush(ptr, take_ownership_from_abi) {}
        CanvasRadialGradientBrush(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, winrt::Windows::UI::Color const& startColor, winrt::Windows::UI::Color const& endColor);
        CanvasRadialGradientBrush(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, array_view<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasGradientStop const> gradientStops);
        CanvasRadialGradientBrush(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, array_view<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasGradientStop const> gradientStops, winrt::Microsoft::Graphics::Canvas::CanvasEdgeBehavior const& edgeBehavior, winrt::Microsoft::Graphics::Canvas::CanvasAlphaMode const& alphaMode);
        CanvasRadialGradientBrush(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, array_view<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasGradientStop const> gradientStops, winrt::Microsoft::Graphics::Canvas::CanvasEdgeBehavior const& edgeBehavior, winrt::Microsoft::Graphics::Canvas::CanvasAlphaMode const& alphaMode, winrt::Microsoft::Graphics::Canvas::CanvasColorSpace const& preInterpolationSpace, winrt::Microsoft::Graphics::Canvas::CanvasColorSpace const& postInterpolationSpace, winrt::Microsoft::Graphics::Canvas::CanvasBufferPrecision const& bufferPrecision);
        static auto CreateHdr(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, winrt::Windows::Foundation::Numerics::float4 const& startColorHdr, winrt::Windows::Foundation::Numerics::float4 const& endColorHdr);
        static auto CreateHdr(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, array_view<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasGradientStopHdr const> gradientStops);
        static auto CreateHdr(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, array_view<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasGradientStopHdr const> gradientStops, winrt::Microsoft::Graphics::Canvas::CanvasEdgeBehavior const& edgeBehavior, winrt::Microsoft::Graphics::Canvas::CanvasAlphaMode const& alphaMode);
        static auto CreateHdr(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, array_view<winrt::Microsoft::Graphics::Canvas::Brushes::CanvasGradientStopHdr const> gradientStops, winrt::Microsoft::Graphics::Canvas::CanvasEdgeBehavior const& edgeBehavior, winrt::Microsoft::Graphics::Canvas::CanvasAlphaMode const& alphaMode, winrt::Microsoft::Graphics::Canvas::CanvasColorSpace const& preInterpolationSpace, winrt::Microsoft::Graphics::Canvas::CanvasColorSpace const& postInterpolationSpace, winrt::Microsoft::Graphics::Canvas::CanvasBufferPrecision const& bufferPrecision);
        static auto CreateRainbow(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, float eldritchness);
    };
    struct WINRT_IMPL_EMPTY_BASES CanvasSolidColorBrush : winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasSolidColorBrush
    {
        CanvasSolidColorBrush(std::nullptr_t) noexcept {}
        CanvasSolidColorBrush(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Microsoft::Graphics::Canvas::Brushes::ICanvasSolidColorBrush(ptr, take_ownership_from_abi) {}
        CanvasSolidColorBrush(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, winrt::Windows::UI::Color const& color);
        static auto CreateHdr(winrt::Microsoft::Graphics::Canvas::ICanvasResourceCreator const& resourceCreator, winrt::Windows::Foundation::Numerics::float4 const& colorHdr);
    };
}
#endif