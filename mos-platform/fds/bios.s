.include "bios.inc"

.macro weakdef name:req
  .weak \name
  __\name = \name
  .global __\name
.endm

weakdef LOAD_FILES
weakdef APPEND_FILE
weakdef WRITE_FILE
weakdef CHECK_FILE_COUNT
weakdef ADJUST_FILE_COUNT
weakdef SET_FILE_COUNT_1
weakdef SET_FILE_COUNT
weakdef GET_DISK_INFO

weakdef CHECK_DISK_HEADER
weakdef GET_NUM_FILES
weakdef SET_NUM_FILES
weakdef FILE_MATCH_TEST
weakdef SKIP_FILES

weakdef DELAY_131
weakdef DELAY_MS
weakdef DIS_PF_OBJ
weakdef EN_PF_OBJ
weakdef DIS_OBJ
weakdef EN_OBJ
weakdef DIS_PF
weakdef EN_PF
weakdef VINT_WAIT
weakdef VRAM_STRUCT_WRITE
weakdef FETCH_DIRECT_PTR
weakdef WRITE_VRAM_BUFFER
weakdef READ_VRAM_BUFFER
weakdef PREPARE_VRAM_STRING
weakdef PREPARE_VRAM_STRINGS
weakdef GET_VRAM_BUFFER_BYTE
weakdef PIXEL_TO_NAM_CONV
weakdef NAM_TO_PIXEL_CONV
weakdef RANDOM
weakdef SPRITE_DMA
weakdef COUNTER_LOGIC
weakdef READ_PADS
weakdef OR_PADS
weakdef READ_DOWN_PADS
weakdef READ_OR_DOWN_PADS
weakdef READ_DOWN_VERIFY_PADS
weakdef READ_OR_DOWN_VERIFY_PADS
weakdef READ_DOWN_EXP_PADS
weakdef VRAM_FILL
weakdef MEM_FILL
weakdef SET_SCROLL
weakdef JUMP_ENGINE
weakdef READ_KEYBOARD
weakdef LOAD_TILESET
weakdef UPLOAD_OBJECT
