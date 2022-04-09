/* Flags 6:
 *   Mapper 0
 *   No hard-wired four-screen mode.
 *   No trainer.
 *   No battery.
 */
BYTE(__hard_wired_mirroring)

/* Flags 7:
 *   Mapper 0.
 *   NES 2.0 identifier.
 *   NES/Family Computer console type.
 */
BYTE(8)

/* Mapper MSB/Submapper:
 *   Submapper 0.
 *   Mapper 0.
 */
BYTE(0)

/* PRG-ROM/CHR-ROM size MSB (counting by 8K) :
 *   16K PRG-ROM.
 *   8K  CHR-ROM.
 */
BYTE(0)

/* PRG-RAM/EEPROM size
 *   No PRG-RAM.
 *   No PRG-EEPROM.
 */
BYTE(0)

/* CHR-RAM/NVRAM size
 *   No CHR-RAM.
 *   No CHR-NVRAM.
 */
BYTE(0)

/* CPU/PPU Timing */
BYTE(__timing)

/* VS system type/Extended Console Type: N/A */
BYTE(0)

/* Miscellaneous ROMs: 0 */
BYTE(0)

/* Default Expansion Device: N/A */
BYTE(0)
