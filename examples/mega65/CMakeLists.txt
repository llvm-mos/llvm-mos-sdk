add_executable(viciv_test.prg viciv_test.c)
install_example(viciv_test.prg)

add_executable(plasma.prg plasma.cc)
install_example(plasma.prg)

add_executable(vertical_raster.prg vertical_raster.cc)
install_example(vertical_raster.prg)

add_executable(simple_dma.prg simple_dma.cc)
install_example(simple_dma.prg)

add_executable(dma_audio.prg dma_audio.c)
install_example(dma_audio.prg)
install(FILES drums.s8 TYPE BIN)

add_executable(mandelbrot.prg mandelbrot.cc)
install_example(mandelbrot.prg)

add_executable(mandelbrot_fcm.prg mandelbrot_fcm.cc)
install_example(mandelbrot_fcm.prg)

add_executable(vector_logo.prg vector_logo.cc)
install_example(vector_logo.prg)

