emu.addMemoryCallback(function(address, value) emu.stop(value) end,
                      emu.memCallbackType.cpuWrite, 0x4018)
