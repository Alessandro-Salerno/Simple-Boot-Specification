#ifndef SBS_H
#define SBS_H

#include <stdint.h>
#include <stddef.h>

#define SBS_VERSION_1_0 "SIMPLEBOOT 1.0.0"
#define SBS_LATEST      SBS_VERSION_1_0


struct SimpleBootFramebuffer {
    void*    _BaseAddress;      // Framebuffer Base
    size_t   _BufferSize;       // Framebuffer Size
    uint32_t _Width;            // Screen Width
    uint32_t _Height;           // Screen Height
};

struct SimpleBootFontHeader {
    uint8_t _Magic[2];      // PSF1 Magic Bytes
    uint8_t _Mode;          // PSF1 Mode
    uint8_t _CharSize;      // PSF1 Char Height
};

struct SimpleBootFont {
    struct SimpleBootFontHeader _Header;    // PSF1 Header
    void*                       _Buffer;    // Font buffer
};

struct SimpleBootMemoryDescriptor {
    uint32_t _Type;                 // EFI Memory Map entry type
    void*    _PhysicalAddress;      // EFI Memory Map entry physical address
    void*    _VirtualAddress;       // EFI Memory Map entry virtual address
    uint64_t _Pages;                // EFI Memory Map entry size (In pages)
    uint64_t _Attributes;           // EFI Memory Map entry attributes
};

struct SimpleBootMemoryInformationTable {
    struct SimpleBootMemoryDescriptor* _MemoryMap;          // Pointer to EFI Memory Map
    uint64_t                           _MemoryMapSize;      // Size of the EFI Memory Map
    uint64_t                           _DescriptorSize;     // Size of each EFI Memory Map Descriptor
};

struct SimpleBootRootSystemDescriptor {
    uint8_t  _Signature[8];     // RSD Signature
    uint8_t  _Checksum;         // Checksum
    uint8_t  _OEM[6];           // OEM Signature
    uint8_t  _Revision;         // RSD Revision
    uint32_t _RSDTAddress;      // Root System Descriptor Table Address
    uint32_t _Length;           // RSD Length
    uint64_t _XSDTAddress;      // Extended System Descriptor Table Address
    uint8_t  _ExtChecksum;      // Extended System Descriptor Table Checksum
    uint8_t  _Reserved[3];      // Reserved bytes
} __attribute__((packed));

struct SimpleBootInformationTable {
    // Standard Information
    const char*                              _Signature = SBS_LATEST;   // SBS Signature

    // Bootloader Information
    const char*                              _BootloaderName;           // Name of the Bootloader
    const char*                              _BootlaoderAuthor;         // Author of the Bootlaoder
    const char*                              _BootloaderVersion;        // Version of the Bootloader
    const char*                              _BootloaderCopyright;      // Copyright notce + license name of the Bootloader

    // OS Information
    struct SimpleBootFramebuffer             _Framebuffer;              // SBS Framebuffer struct
    struct SimpleBootFont                    _Font;                     // SBS PSF1 Font struct
    void*                                    _OSSpecific;               // Pointer to a structure containing OS-Spacific Information (NULL if absent)
    void*                                    _Extensions;               // Pointer to SBS table extensions (NULL if absent)

    // Hardware
    struct SimpleBootMemoryInformationTable  _Memory;                   // SBS Memory Inforamtion struct
    void*                                    _RSDP;                     // Root System Descriptor Pointer
};

#endif
