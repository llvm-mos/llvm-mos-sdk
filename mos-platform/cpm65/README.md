This directory contains a platform for producing CP/M-65 binaries. See:

https://github.com/davidgiven/cpm65

It should contain bindings to all the CP/M and BIOS system calls, allowing you
to write arbitrary programs. Noted quirks are:

  - it's up to you to decide whether to return to the CCP by exiting from
	`main()`, or reloading the CCP by performing a warm start by calling
	`cpm_warmboot()`. You do _not_ need to worry about overwriting the CCP's
	zero page allocation, only the TPA.
  - there's no heap support yet, but you can get at the base of program
    workspace via `cpm_ram`. For now use `cpm_bios_gettpa()` to find the TPA
	bounds.
  - command parameters aren't parsed --- `argc` and `argv` contain garbage.
	Instead, use `cpm_cmdline` and `cpm_cmdlinelen`.
  - the pblock layout is going to change... lots.

