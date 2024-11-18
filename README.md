> [!WARNING]
> The Simple Boot Specification was meant to be part of the [OpenBIT Specifications](https://github.com/OpenBitt/OpenBit-Specs) (a collection of OS specifications to be used by operating systems developed on the OpenBIT Discord server which never saw the light of day). SBS was initially adopted by [SalernOS](https://github.com/Alessandro-Salerno/SalernOS), but was later dropped due to fundamental design flaws. In its current state, SBS **should not be used in ANY capacity**.

## Simple Boot Specification
The Simple Boot Specification is, as the name implies, a stripped-down standard for Hobby OS Bootloaders.
The Simple Boot Specification governs how information is exchanged between the loader and the OS Kernel.

## Simple Boot Specification Information Table
The Simple Boot Specification dictates that, when jumping to the Kernel's entry point (Using the SYS-V ABI), the loader must pass a pointer to an Information Table. The Information Table is layed out as follows
```
+---------------------+-------------+---------+------------+
| ITEM                | TYPE        | SIZE    | ADDRESS    |
+---------------------+-------------+---------+------------+
| Signature           | const char* | 8 bytes | Base       |
| Loader Name         | const char* | 8 bytes | Base + 8   |
| Loader Author       | const char* | 8 bytes | Base + 16  |
| Loader Version      | const char* | 8 bytes | Base + 24  |
| Loader Copyright    | const char* | 8 bytes | Base + 32  |
| Framebuffer Base    | void*       | 8 bytes | Base + 40  |
| Framebuffer Size    | size_t      | 8 bytes | Base + 48  |
| Framebuffer Wisdth  | uint32_t    | 4 bytes | Base + 56  |
| Framebuffer Height  | uint32_t    | 4 bytes | Base + 60  |
| Font Magic 0        | uint8_t     | 1 byte  | Base + 64  |
| Font Magic 1        | uint8_t     | 1 byte  | Base + 65  |
| Font Mode           | uint8_t     | 1 byte  | Base + 66  |
| Font Height         | uint8_t     | 1 byte  | Base + 67  |
| Padding Space       |             | 4 bytes | Base + 68  |
| Font Buffer         | void*       | 8 bytes | Base + 72  |
| OS Specific Info    | void*       | 8 bytes | Base + 80  |
| SBS Extensions Ptr  | void*       | 8 bytes | Base + 88  |
| EFI Memory Map Ptr  | efidesc*    | 8 bytes | Base + 96  |
| EFI Memory Map Size | uint64_t    | 8 bytes | Base + 104 |
| EFI Descriptor Size | uint64_t    | 8 bytes | Base + 112 |
| RSD Ptr             | RSD*        | 8 bytes | Base + 120 |
+---------------------+-------------+---------+------------+
```

Optionally, the table can be split up in to structs, as long as the size and padding of the table ramain the same.
The `.h` file in this repository uses structs for the framebuffer, font header, font, memory information table and RSD.
