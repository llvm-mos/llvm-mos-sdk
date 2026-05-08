-- Use this script with Mesen to direct libc stdout to the debug console.
-- For example:
--   $ mesen my-project.nes $LLVM_MOS_SDK/utils/printf-mesen.lua

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

function log_err()
  emu.log("Error: unknown Mesen API")
end

mesen_callbackType = nil

if emu.memCallbackType and emu.memCallbackType.cpuWrite then
  mesen_callbackType = emu.memCallbackType.cpuWrite
elseif emu.callbackType and emu.callbackType.write then
  mesen_callbackType = emu.callbackType.write
end

if (mesen_callbackType ~= nil) then
  emu.addMemoryCallback(cb, mesen_callbackType, 0x401B)
else
  log_err()
end
