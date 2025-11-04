# FDS target notes

The Famicom Disk System target outputs raw executables intended to be written to a [properly formatted disk](https://www.nesdev.org/wiki/FDS_disk_format). llvm-mos does not include tools for creating/packing FDS disk images; you will need to use a third-party tool (e.g. [FDSPacker](https://github.com/ClusterM/fdspacker)) for this.

## Interrupt handling

The FDS BIOS has a built-in NMI and IRQ multiplexer. Alongside the built-in handlers, it provides support for three custom NMI handlers and one custom IRQ handler. The IRQ handler is exposed as `irq`, while the NMI handlers are exposed as `nmi_user_1`, `nmi_user_2`, and `nmi_user_3`.

Here's an example showing how to define a custom NMI handler from C:

```c
__attribute__((interrupt)) void nmi_user_1(void) {
  ...
}
```

To tell the BIOS to call this specific handler, you can call `fds_set_nmi_action` from `irq.h`:
```c
fds_set_nmi_action(NMI_ACTION_USER_1);
```

For the IRQ handler, `fds_set_irq_action` can be used similarly.

## Vectors

The start/reset, IRQ, and NMI vectors will need to be loaded into memory via a separate file on disk. For convenience, the ELF file output when compiling your program includes a `.vectors` section that can be extracted into its own file using `objcopy`:

```sh
llvm-objcopy --dump-section .vectors=vectors.bin mygame.prg.elf
```

This will output a file named `vectors.bin` that can be written to your disk image. This needs to be loaded as a Program file at memory address `$DFF6`. Example with FDSPacker:

```json
{
  ...
  "files": [
    ...
    {
      "file_number": 1,
      "file_indicate_code": 1,
      "file_name": "VECTORS",
      "file_address": "$dff6",
      "file_kind": "Program",
      "data": "vectors.bin"
    },
    ...
  ]
}
```

## License bypass

The FDS BIOS performs a license check on initial load. This target includes code for performing the "license bypass" trick, which is commonly used with homebrew; however, this means you will need to create/pack your disk image differently.

Start by creating a file containing only a single byte with value `$90` (this is named `bypass.bin` in the following example). This will need to be added to your disk as the last file loaded by the BIOS, and it needs to be a Program file set to load at address `$2000`. The disk's file count will also need to be set to the actual loaded file count + 1. Example with FDSPacker:

```json
{
  ...
  "boot_file": 2,
  "file_amount": 4,
  "files": [
    ...
    {
      "file_number": 0,
      "file_indicate_code": 0,
      "file_name": "PROGRAM",
      "file_address": "$6000",
      "file_kind": "Program",
      "data": "main.prg"
    },
    {
      "file_number": 1,
      "file_indicate_code": 1,
      "file_name": "VECTORS",
      "file_address": "$dff6",
      "file_kind": "Program",
      "data": "vectors.bin"
    },
    {
      "file_number": 2,
      "file_indicate_code": 2,
      "file_name": "BYPASS",
      "file_address": "$2000",
      "file_kind": "Program",
      "data": "bypass.bin"
    },
    ...
  ]
}
```
