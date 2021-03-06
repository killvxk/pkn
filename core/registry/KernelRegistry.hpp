#pragma once

#include "Registry.hpp"

#if (NTDDI_VERSION >= NTDDI_WIN2K)
//@[comment("MVI_tracked")]
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwClose(
    _In_ HANDLE Handle
);
#endif

class KernelRegistry : public Registry
{
public:
    KernelRegistry(const estr_t &registry_path)
        : Registry(registry_path, &KernelRegistry::zwClose)
    {}
    virtual ~KernelRegistry() override = default;
protected:
    // Inherited via Registry

    virtual NTSTATUS zwOpenKey(PHANDLE KeyHandle,
                               uint32_t DesiredAccess,
                               POBJECT_ATTRIBUTES ObjectAttributes
    ) override
    {
        return ::ZwOpenKey(KeyHandle,
                           DesiredAccess,
                           ObjectAttributes);
    }

    virtual NTSTATUS zwCreateKey(PHANDLE KeyHandle,
                                 ACCESS_MASK DesiredAccess,
                                 POBJECT_ATTRIBUTES ObjectAttributes,
                                 ULONG TitleIndex,
                                 PUNICODE_STRING Class,
                                 ULONG CreateOptions,
                                 PULONG Disposition) override
    {
        return ::ZwCreateKey(KeyHandle,
                             DesiredAccess,
                             ObjectAttributes,
                             TitleIndex,
                             Class,
                             CreateOptions,
                             Disposition);
    }


    virtual NTSTATUS zwQueryValueKey(HANDLE KeyHandle,
                                     PUNICODE_STRING ValueName,
                                     KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
                                     PVOID KeyValueInformation,
                                     ULONG Length,
                                     PULONG ResultLength
    ) override
    {
        return ::ZwQueryValueKey(KeyHandle,
                                 ValueName,
                                 KeyValueInformationClass,
                                 KeyValueInformation,
                                 Length,
                                 ResultLength
        );
    }

    virtual NTSTATUS zwSetValueKey(HANDLE KeyHandle,
                                   PUNICODE_STRING ValueName,
                                   ULONG TitleIndex,
                                   ULONG Type,
                                   PVOID Data,
                                   ULONG DataSize
    ) override
    {
        return ::ZwSetValueKey(KeyHandle,
                               ValueName,
                               TitleIndex,
                               Type,
                               Data,
                               DataSize
        );
    }

    virtual NTSTATUS zwDeleteKey(HANDLE Handle
    ) override
    {
        return ::ZwDeleteKey(Handle);
    }

    virtual NTSTATUS zwEnumerateKey(
        HANDLE                KeyHandle,
        ULONG                 Index,
        KEY_INFORMATION_CLASS KeyInformationClass,
        PVOID                 KeyInformation,
        ULONG                 Length,
        PULONG                ResultLength
    ) override
    {
        return ::ZwEnumerateKey(
            KeyHandle,
            Index,
            KeyInformationClass,
            KeyInformation,
            Length,
            ResultLength
        );
    }


    static NTSTATUS zwClose(HANDLE handle)
    {
        return ::ZwClose(handle);
    }
};