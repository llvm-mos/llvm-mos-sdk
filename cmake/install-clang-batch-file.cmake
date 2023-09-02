# Creates a Windows batch file that uses the config file for a given platform
# and forwards to the underlying compiler driver. This works around the lack of
# unpriveleged symlinks on Windows.
function(install_clang_batch_file bindir platform suffix)
  set(file mos-${platform}-${suffix}.bat)
  message(STATUS "Creating redirecting batch file ${file}")
  file(WRITE ${bindir}/${file} "@ECHO OFF\n\"%~dp0\\mos-${suffix}\" --config mos-${platform}.cfg %*\n")
endfunction()
