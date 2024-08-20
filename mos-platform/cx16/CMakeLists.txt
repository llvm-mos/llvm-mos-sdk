platform(cx16 COMPLETE HOSTED PARENT commodore)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES
  ../commodore/_6522.h
  charset.h
  cx16.h
TYPE INCLUDE)
install(FILES imag-regs.ld link.ld TYPE LIB)

add_platform_library(cx16-crt0)
merge_libraries(cx16-crt0
  common-init-stack
  common-exit-return
)

install(FILES cx16.inc DESTINATION ${ASMINCDIR})

add_platform_object_file(cx16-basic-header basic-header.o basic-header.S)

add_platform_library(cx16-c
 cx16_k_bsave.s
 cx16_k_clock_get_date_time.s
 cx16_k_clock_set_date_time.s
 cx16_k_console_get_char.s
 cx16_k_console_init.s
 cx16_k_console_put_char.s
 cx16_k_console_put_image.s
 cx16_k_console_set_paging_message.s
 cx16_k_enter_basic.s
 cx16_k_entropy_get.s
 cx16_k_fb_cursor_next_line.s
 cx16_k_fb_cursor_position.s
 cx16_k_fb_fill_pixels.s
 cx16_k_fb_filter_pixels.s
 cx16_k_fb_get_info.s
 cx16_k_fb_get_pixel.s
 cx16_k_fb_get_pixels.s
 cx16_k_fb_init.s
 cx16_k_fb_move_pixels.s
 cx16_k_fb_set_8_pixels.s
 cx16_k_fb_set_8_pixels_opaque.s
 cx16_k_fb_set_palette.s
 cx16_k_graph_clear.s
 cx16_k_graph_draw_image.s
 cx16_k_graph_draw_line.s
 cx16_k_graph_draw_oval.s
 cx16_k_graph_draw_rect.s
 cx16_k_graph_get_char_size.s
 cx16_k_graph_init.s
 cx16_k_graph_move_rect.s
 cx16_k_graph_put_char.s
 cx16_k_graph_set_colors.s
 cx16_k_graph_set_font.s
 cx16_k_graph_set_window.s
 cx16_k_i2c_read_byte.s
 cx16_k_i2c_write_byte.s
 cx16_k_joystick_get.c
 cx16_k_joystick_scan.s
 cx16_k_kbdbuf_get_modifiers.s
 cx16_k_kbdbuf_peek.s
 cx16_k_kbdbuf_put.s
 cx16_k_keymap_get_id.s
 cx16_k_keymap_set.s
 cx16_k_macptr.s
 cx16_k_memory_copy.s
 cx16_k_memory_crc.s
 cx16_k_memory_decompress.s
 cx16_k_memory_fill.s
 cx16_k_monitor.s
 cx16_k_mouse_config.s
 cx16_k_mouse_get.s
 cx16_k_mouse_scan.s
 cx16_k_rdtim.s
 cx16_k_screen_mode_get.s
 cx16_k_screen_mode_set.s
 cx16_k_screen_set_charset.s
 cx16_k_sprite_set_image.s
 cx16_k_sprite_set_position.s
 filevars.s
 get_numbanks.s
 get_ostype.s
 get_tv.s
 set_tv.s
 vera_layer_enable.s
 vera_sprites_enable.s
 videomode.s
 vpeek.s
 vpoke.s
 waitvsync.s
 kernal.S

 char-conv.c
)

target_include_directories(cx16-c BEFORE PUBLIC .)
target_compile_definitions(cx16-c PUBLIC __CX16__)
target_compile_options(cx16-c PUBLIC -mcpu=mosw65c02)
target_link_libraries(cx16-c PRIVATE common-asminc)
