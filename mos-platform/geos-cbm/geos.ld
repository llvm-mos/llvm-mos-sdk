/* GEOS zero page variable definitions: */

__r0              = 0x0002;
__r1              = 0x0004;
__r2              = 0x0006;
__r3              = 0x0008;
__r4              = 0x000a;
__r5              = 0x000c;
__r6              = 0x000e;
__r7              = 0x0010;
__r8              = 0x0012;
__r9              = 0x0014;
__r10             = 0x0016;
__r11             = 0x0018;
__r12             = 0x001a;
__r13             = 0x001c;
__r14             = 0x001e;
__r15             = 0x0020;

__r0L             = 0x02;
__r0H             = 0x03;
__r1L             = 0x04;
__r1H             = 0x05;
__r2L             = 0x06;
__r2H             = 0x07;
__r3L             = 0x08;
__r3H             = 0x09;
__r4L             = 0x0a;
__r4H             = 0x0b;
__r5L             = 0x0c;
__r5H             = 0x0d;
__r6L             = 0x0e;
__r6H             = 0x0f;
__r7L             = 0x10;
__r7H             = 0x11;
__r8L             = 0x12;
__r8H             = 0x13;
__r9L             = 0x14;
__r9H             = 0x15;
__r10L            = 0x16;
__r10H            = 0x17;
__r11L            = 0x18;
__r11H            = 0x19;
__r12L            = 0x1a;
__r12H            = 0x1b;
__r13L            = 0x1c;
__r13H            = 0x1d;
__r14L            = 0x1e;
__r14H            = 0x1f;
__r15L            = 0x20;
__r15H            = 0x21;

/***********************************************************************
 * GEOS symbols
 ***********************************************************************/

CPU_DDR           = 0x0000;
CPU_DATA          = 0x0001;
STATUS            = 0x0090;
curDevice         = 0x00ba;
zpage             = 0x0000;
curPattern        = 0x22;
string            = 0x24;
baselineOffset    = 0x26;
curSetWidth       = 0x27;
curHeight         = 0x29;
curIndexTable     = 0x2a;
cardDataPntr      = 0x2c;
currentMode       = 0x2e;
dispBufferOn      = 0x2f;
mouseOn           = 0x30;
msePicPtr         = 0x31;
windowTop         = 0x33;
windowBottom      = 0x34;
leftMargin        = 0x35;
rightMargin       = 0x37;
pressFlag         = 0x39;
mouseXPos         = 0x3a;
mouseYPos         = 0x3c;
returnAddress     = 0x3d;
graphMode         = 0x3f;
TURBO_DD00        = 0x8e;
TURBO_DD00_CPY    = 0x8f;

__a0                = 0xfb;
__a0L               = 0xfb;
__a0H               = 0xfc;
__a1                = 0xfd;
__a1L               = 0xfd;
__a1H               = 0xfe;

bkvec               = 0x0316;
nmivec              = 0x0318;
kernalVectors       = 0x031a;

diskBlkBuf          = 0x8000;
fileHeader          = 0x8100;
curDirHead          = 0x8200;
fileTrScTab         = 0x8300;
dirEntryBuf         = 0x8400;
DrACurDkNm          = 0x841e;
DrBCurDkNm          = 0x8430;
dataFileName        = 0x8442;
dataDiskName        = 0x8453;
PrntFilename        = 0x8465;
PrntDiskName        = 0x8476;
curDrive            = 0x8489;
diskOpenFlg         = 0x848a;
isGEOS              = 0x848b; 
interleave          = 0x848c;
numDrives           = 0x848d;
driveType           = 0x848e;
turboFlags          = 0x8492;
curRecord           = 0x8496;
usedRecords         = 0x8497;
fileWritten         = 0x8498;
fileSize            = 0x8499;
appMain             = 0x849b;
intTopVector        = 0x849d;
intBotVector        = 0x849f;
mouseVector         = 0x84a1;
keyVector           = 0x84a3;
inputVector         = 0x84a5;
mouseFaultVec       = 0x84a7;
otherPressVec       = 0x84a9;
StringFaultVec      = 0x84ab;
alarmTmtVector      = 0x84ad;
BRKVector           = 0x84af;
RecoverVector       = 0x84b1;
selectionFlash      = 0x84b3;
alphaFlag           = 0x84b4;
iconSelFlg          = 0x84b5;
faultData           = 0x84b6;
menuNumber          = 0x84b7;
mouseTop            = 0x84b8;
mouseBottom         = 0x84b9;
mouseLeft           = 0x84ba;
mouseRight          = 0x84bc;
stringX             = 0x84be;
stringY             = 0x84c0;
mousePicData        = 0x84c1;
maxMouseSpeed       = 0x8501;
minMouseSpeed       = 0x8502;
mouseAccel          = 0x8503;
keyData             = 0x8504;
mouseData           = 0x8505;
inputData           = 0x8506;
mouseSpeed          = 0x8507;
random              = 0x850a;
saveFontTab         = 0x850c;
dblClickCount       = 0x8515;
year                = 0x8516;
month               = 0x8517;
day                 = 0x8518;
hour                = 0x8519;
minutes             = 0x851a;
seconds             = 0x851b;
alarmSetFlag        = 0x851c;
sysDBData           = 0x851d;
screencolors        = 0x851e;
dlgBoxRamBuf        = 0x851f;

savedmoby2          = 0x88bb;
scr80polar          = 0x88bc;
scr80colors         = 0x88bd;
vdcClrMode          = 0x88be;
driveData           = 0x88bf;
ramExpSize          = 0x88c3;         
sysRAMFlg           = 0x88c4;         
firstBoot           = 0x88c5;
curType             = 0x88c6;
ramBase             = 0x88c7;
inputDevName        = 0x88cb;
DrCCurDkNm          = 0x88dc;
DrDCurDkNm          = 0x88ee;
dir2Head            = 0x8900;
sprpic              = 0x8a00;
objPointer          = 0x8ff8;

bootName            = 0xc006;
version             = 0xc00f;
nationality         = 0xc010;
sysFlgCopy          = 0xc012;
dateCopy            = 0xc018;

mobpos              = 0xd000;
msbxpos             = 0xd010;
grcntrl1            = 0xd011;
rasreg              = 0xd012;
lpxpos              = 0xd013;
lpypos              = 0xd014;
mobenble            = 0xd015;
grcntrl2            = 0xd016;
moby2               = 0xd017;
grmemptr            = 0xd018;
grirq               = 0xd019;
grirqen             = 0xd01a;
mobprior            = 0xd01b;
mobmcm              = 0xd01c;
mobx2               = 0xd01d;
mobmobcol           = 0xd01e;
mobbakcol           = 0xd01f;
extclr              = 0xd020;
bakclr              = 0xd021;
mcmclr              = 0xd025;
mobclr              = 0xd027;
keyreg              = 0xd02f;
clkreg              = 0xd030;

NMI_VECTOR          = 0xfffa;
RESET_VECTOR        = 0xfffc;
IRQ_VECTOR          = 0xfffe;

/***********************************************************************
 * GEOS routines
 ***********************************************************************/

/* Jump addresses within printer drivers */

__InitForPrint            = 0x7900;
__StartPrint              = 0x7903;
__PrintBuffer             = 0x7906;
__StopPrint               = 0x7909;
__GetDimensions           = 0x790c;
__PrinsASCII              = 0x790f;
__StartASCII              = 0x7912;
__SetNLQ                  = 0x7915;

/* Jump addresses within disk drivers: these are only valid for non-1541 disk
 * drive types, and for the 128 versions of the 1541 driver. */

__Get1stDirEntry          = 0x9030;
__GetNxtDirEntry          = 0x9033;
__GetOffPageTrSc          = 0x9036;
__AddDirBlock             = 0x9039;
__ReadBuff                = 0x903c;
__WriteBuff               = 0x903f;
__SendTSBytes             = 0x9042;
__CheckErrors             = 0x9045;
__AllocateBlock           = 0x9048;
__ReadLink                = 0x904b;

/* MISC */;

__BootGEOS                = 0xc000;
__ResetHandle             = 0xc003;
__InterruptMain           = 0xc100;

/* PROCESSES */

__InitProcesses           = 0xc103;
__RestartProcess          = 0xc106;
__EnableProcess           = 0xc109;
__BlockProcess            = 0xc10c;
__UnblockProcess          = 0xc10f;
__FreezeProcess           = 0xc112;
__UnfreezeProcess         = 0xc115;

/* GRAPHICS */

__HorizontalLine          = 0xc118;
__InvertLine              = 0xc11b;
__RecoverLine             = 0xc11e;
__VerticalLine            = 0xc121;
__Rectangle               = 0xc124;
__FrameRectangle          = 0xc127;
__InvertRectangle         = 0xc12a;
__RecoverRectangle        = 0xc12d;
__DrawLine                = 0xc130;
__DrawPoint               = 0xc133;
__GraphicsString          = 0xc136;
__SetPattern              = 0xc139;
__GetScanLine             = 0xc13c;
__TestPoint               = 0xc13f;

/* BACKGROUND GENERATION */

__BitmapUp                = 0xc142;

/* CHARACTER MANIPULATION */

__PutChar                 = 0xc145;
__PutString               = 0xc148;
__UseSystemFont           = 0xc14b;

/* MOUSE, MENUS, & ICONS */

__StartMouseMode          = 0xc14e;
__DoMenu                  = 0xc151;
__RecoverMenu             = 0xc154;
__RecoverAllMenus         = 0xc157;
__DoIcons                 = 0xc15a;

/* UTILITIES */

__DShiftLeft              = 0xc15d;
__BBMult                  = 0xc160;
__BMult                   = 0xc163;
__DMult                   = 0xc166;
__Ddiv                    = 0xc169;
__DSdiv                   = 0xc16c;
__Dabs                    = 0xc16f;
__Dnegate                 = 0xc172;
__Ddec                    = 0xc175;
__ClearRam                = 0xc178;
__FillRam                 = 0xc17b;
__MoveData                = 0xc17e;
__InitRam                 = 0xc181;
__PutDecimal              = 0xc184;
__GetRandom               = 0xc187;

/* MISC */

__MouseUp                 = 0xc18a;
__MouseOff                = 0xc18d;
__DoPreviousMenu          = 0xc190;
__ReDoMenu                = 0xc193;
__GetSerialNumber         = 0xc196;
__Sleep                   = 0xc199;
__ClearMouseMode          = 0xc19c;
__i_Rectangle             = 0xc19f;
__i_FrameRectangle        = 0xc1a2;
__i_RecoverRectangle      = 0xc1a5;
__i_GraphicsString        = 0xc1a8;

/* BACKGROUND GENERATION */

__i_BitmapUp              = 0xc1ab;

/* CHARACTER MANIPULATION */

__i_PutString             = 0xc1ae;
__GetRealSize             = 0xc1b1;

/* UTILITIES */

__i_FillRam               = 0xc1b4;
__i_MoveData              = 0xc1b7;

/* Routines added later */

__GetString               = 0xc1ba;
__GotoFirstMenu           = 0xc1bd;
__InitTextPrompt          = 0xc1c0;
__MainLoop                = 0xc1c3;
__DrawSprite              = 0xc1c6;
__GetCharWidth            = 0xc1c9;
__LoadCharSet             = 0xc1cc;
__PosSprite               = 0xc1cf;
__EnablSprite             = 0xc1d2;
__DisablSprite            = 0xc1d5;
__CallRoutine             = 0xc1d8;
__CalcBlksFree            = 0xc1db;
__ChkDkGEOS               = 0xc1de;
__NewDisk                 = 0xc1e1;
__GetBlock                = 0xc1e4;
__PutBlock                = 0xc1e7;
__SetGEOSDisk             = 0xc1ea;
__SaveFile                = 0xc1ed;
__SetGDirEntry            = 0xc1f0;
__BldGDirEntry            = 0xc1f3;
__GetFreeDirBlk           = 0xc1f6;
__WriteFile               = 0xc1f9;
__BlkAlloc                = 0xc1fc;
__ReadFile                = 0xc1ff;
__SmallPutChar            = 0xc202;
__FollowChain             = 0xc205;
__GetFile                 = 0xc208;
__FindFile                = 0xc20b;
__CRC                     = 0xc20e;
__LdFile                  = 0xc211;
__EnterTurbo              = 0xc214;
__LdDeskAcc               = 0xc217;
__ReadBlock               = 0xc21a;
__LdApplic                = 0xc21d;
__WriteBlock              = 0xc220;
__VerWriteBlock           = 0xc223;
__FreeFile                = 0xc226;
__GetFHdrInfo             = 0xc229;
__EnterDeskTop            = 0xc22c;
__StartAppl               = 0xc22f;
__ExitTurbo               = 0xc232;
__PurgeTurbo              = 0xc235;
__DeleteFile              = 0xc238;
__FindFTypes              = 0xc23b;
__RstrAppl                = 0xc23e;
__ToBASIC                 = 0xc241;
__FastDelFile             = 0xc244;
__GetDirHead              = 0xc247;
__PutDirHead              = 0xc24a;
__NxtBlkAlloc             = 0xc24d;
__ImprintRectangle        = 0xc250;
__i_ImprintRectangle      = 0xc253;
__DoDlgBox                = 0xc256;
__RenameFile              = 0xc259;
__InitForIO               = 0xc25c;
__DoneWithIO              = 0xc25f;
__DShiftRight             = 0xc262;
__CopyString              = 0xc265;
__CopyFString             = 0xc268;
__CmpString               = 0xc26b;
__CmpFString              = 0xc26e;
__FirstInit               = 0xc271;
__OpenRecordFile          = 0xc274;
__CloseRecordFile         = 0xc277;
__NextRecord              = 0xc27a;
__PreviousRecord          = 0xc27d;
__PointRecord             = 0xc280;
__DeleteRecord            = 0xc283;
__InsertRecord            = 0xc286;
__AppendRecord            = 0xc289;
__ReadRecord              = 0xc28c;
__WriteRecord             = 0xc28f;
__SetNextFree             = 0xc292;
__UpdateRecordFile        = 0xc295;
__GetPtrCurDkNm           = 0xc298;
__PromptOn                = 0xc29b;
__PromptOff               = 0xc29e;
__OpenDisk                = 0xc2a1;
__DoInlineReturn          = 0xc2a4;
__GetNextChar             = 0xc2a7;
__BitmapClip              = 0xc2aa;
__FindBAMBit              = 0xc2ad;
__SetDevice               = 0xc2b0;
__IsMseInRegion           = 0xc2b3;
__ReadByte                = 0xc2b6;
__FreeBlock               = 0xc2b9;
__ChangeDiskDevice        = 0xc2bc;
__RstrFrmDialog           = 0xc2bf;
__Panic                   = 0xc2c2;
__BitOtherClip            = 0xc2c5;
__StashRAM                = 0xc2c8;
__FetchRAM                = 0xc2cb;
__SwapRAM                 = 0xc2ce;
__VerifyRAM               = 0xc2d1;
__DoRAMOp                 = 0xc2d4;

/* only in GEOS 128 */

__TempHideMouse           = 0xc2d7;
__SetNewMode              = 0xc2dd;
__NormalizeX              = 0xc2e0;
__MoveBData               = 0xc2e3;
__SwapBData               = 0xc2e6;
__VerifyBData             = 0xc2e9;
__DoBOp                   = 0xc2ec;
__AccessCache             = 0xc2ef;
__HideOnlyMouse           = 0xc2f2;
__SetColorMode            = 0xc2f5;
__ColorCard               = 0xc2f8;
__ColorRectangle          = 0xc2fb;

/* Jump addresses within input drivers */

/* for C64 */
__InitMouse               = 0xfe80;
__SlowMouse               = 0xfe83;
__UpdateMouse             = 0xfe86;
__SetMouse                = 0xfe89;

/* for C128 */
__InitMouse_128           = 0xfd00;
__SlowMouse_128           = 0xfd03;
__UpdateMouse_128         = 0xfd06;
__SetMouse_128            = 0xfd09;
