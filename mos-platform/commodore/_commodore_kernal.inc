; Copyright 2022 LLVM-MOS Project
;
; Licensed under the Apache License, Version 2.0 (the "License");
; you may not use this file except in compliance with the License.
; You may obtain a copy of the License at
;
;     http://www.apache.org/licenses/LICENSE-2.0
;
; Unless required by applicable law or agreed to in writing, software
; distributed under the License is distributed on an "AS IS" BASIS,
; WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; See the License for the specific language governing permissions and
; limitations under the License.

; Originally from cc65. Modified from original version.

;
; Olli Savia <ops@iki.fi>
; Greg King
;
; Commodore-compatibles Kernal functions
;

CHKIN          = $FFC6
CKOUT          = $FFC9
CHKOUT         = $FFC9
CLRCH          = $FFCC
CLRCHN         = $FFCC
BASIN          = $FFCF
CHRIN          = $FFCF
BSOUT          = $FFD2
CHROUT         = $FFD2

STOP           = $FFE1
GETIN          = $FFE4
CLALL          = $FFE7
UDTIM          = $FFEA
