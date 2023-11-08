// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.230706.1

#pragma once
#ifndef WINRT_Windows_Storage_Pickers_2_H
#define WINRT_Windows_Storage_Pickers_2_H
#include "winrt/impl/Windows.Foundation.Collections.1.h"
#include "winrt/impl/Windows.Storage.1.h"
#include "winrt/impl/Windows.System.1.h"
#include "winrt/impl/Windows.Storage.Pickers.1.h"
WINRT_EXPORT namespace winrt::Windows::Storage::Pickers
{
    struct WINRT_IMPL_EMPTY_BASES FileExtensionVector : winrt::Windows::Foundation::Collections::IVector<hstring>
    {
        FileExtensionVector(std::nullptr_t) noexcept {}
        FileExtensionVector(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::Collections::IVector<hstring>(ptr, take_ownership_from_abi) {}
    };
    struct WINRT_IMPL_EMPTY_BASES FileOpenPicker : winrt::Windows::Storage::Pickers::IFileOpenPicker,
        impl::require<FileOpenPicker, winrt::Windows::Storage::Pickers::IFileOpenPicker2, winrt::Windows::Storage::Pickers::IFileOpenPickerWithOperationId, winrt::Windows::Storage::Pickers::IFileOpenPicker3>
    {
        FileOpenPicker(std::nullptr_t) noexcept {}
        FileOpenPicker(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Storage::Pickers::IFileOpenPicker(ptr, take_ownership_from_abi) {}
        FileOpenPicker();
        using winrt::Windows::Storage::Pickers::IFileOpenPicker::PickSingleFileAsync;
        using impl::consume_t<FileOpenPicker, winrt::Windows::Storage::Pickers::IFileOpenPickerWithOperationId>::PickSingleFileAsync;
        static auto ResumePickSingleFileAsync();
        static auto CreateForUser(winrt::Windows::System::User const& user);
    };
    struct WINRT_IMPL_EMPTY_BASES FilePickerFileTypesOrderedMap : winrt::Windows::Foundation::Collections::IMap<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>
    {
        FilePickerFileTypesOrderedMap(std::nullptr_t) noexcept {}
        FilePickerFileTypesOrderedMap(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::Collections::IMap<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>(ptr, take_ownership_from_abi) {}
    };
    struct WINRT_IMPL_EMPTY_BASES FilePickerSelectedFilesArray : winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Storage::StorageFile>
    {
        FilePickerSelectedFilesArray(std::nullptr_t) noexcept {}
        FilePickerSelectedFilesArray(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Storage::StorageFile>(ptr, take_ownership_from_abi) {}
    };
    struct WINRT_IMPL_EMPTY_BASES FileSavePicker : winrt::Windows::Storage::Pickers::IFileSavePicker,
        impl::require<FileSavePicker, winrt::Windows::Storage::Pickers::IFileSavePicker2, winrt::Windows::Storage::Pickers::IFileSavePicker3, winrt::Windows::Storage::Pickers::IFileSavePicker4>
    {
        FileSavePicker(std::nullptr_t) noexcept {}
        FileSavePicker(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Storage::Pickers::IFileSavePicker(ptr, take_ownership_from_abi) {}
        FileSavePicker();
        static auto CreateForUser(winrt::Windows::System::User const& user);
    };
    struct WINRT_IMPL_EMPTY_BASES FolderPicker : winrt::Windows::Storage::Pickers::IFolderPicker,
        impl::require<FolderPicker, winrt::Windows::Storage::Pickers::IFolderPicker2, winrt::Windows::Storage::Pickers::IFolderPicker3>
    {
        FolderPicker(std::nullptr_t) noexcept {}
        FolderPicker(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Storage::Pickers::IFolderPicker(ptr, take_ownership_from_abi) {}
        FolderPicker();
        static auto CreateForUser(winrt::Windows::System::User const& user);
    };
}
#endif
