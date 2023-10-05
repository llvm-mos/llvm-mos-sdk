-- Use this script with Mesen to direct libc stdout to the debug console.
-- For example:
--   $ mesen my-project.nes $LLVM_MOS_SDK/utils/printf.lua

str = ""
function cb(address, value)
  c = string.char(value)
  if (c == '\n') then
    emu.log(str)
    str = ""
  end
  str = str .. c
  if (string.len(str) > 80) then
    emu.log(str)
    str = ""
  end
end

emu.addMemoryCallback(cb, emu.memCallbackType.cpuWrite, 0x401B)
