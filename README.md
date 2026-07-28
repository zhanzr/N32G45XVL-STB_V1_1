# N32G457VEL STB V1.1
N32G457VEL

## coremark
144 MHz, Standard Lib
ARMCLANG 6.24

```C
/* Switch iCache , it is default Enabled*/
FLASH_iCacheCmd(FLASH_iCache_EN); 
FLASH_iCacheCmd(FLASH_iCache_DIS);
```

Execution starts, 10000000 runs through Dhrystone

### Flash enable, With FPU
```
-Omax
2K performance run parameters for coremark.
CoreMark Size    : 666
Total ticks      : 20088
Total time (secs): 20.088000
Iterations/Sec   : 497.809638
Iterations       : 10000
Compiler version : GCCClang 20.0.0git
Compiler flags   : -Omax
Memory location  : STATIC
seedcrc          : 0xe9f5
[0]crclist       : 0xe714
[0]crcmatrix     : 0x1fd7
[0]crcstate      : 0x8e3a
[0]crcfinal      : 0x988c
Correct operation validated. See readme.txt for run and reporting rules.
CoreMark 1.0 : 497.809638 / GCCClang 20.0.0git -Omax / STATIC
```

### Flash uncached, With FPU
```
-Omax
2K performance run parameters for coremark.
CoreMark Size    : 666
Total ticks      : 42696
Total time (secs): 42.696000
Iterations/Sec   : 234.213978
Iterations       : 10000
Compiler version : GCCClang 20.0.0git
Compiler flags   : -Omax
Memory location  : STATIC
seedcrc          : 0xe9f5
[0]crclist       : 0xe714
[0]crcmatrix     : 0x1fd7
[0]crcstate      : 0x8e3a
[0]crcfinal      : 0x988c
Correct operation validated. See readme.txt for run and reporting rules.
CoreMark 1.0 : 234.213978 / GCCClang 20.0.0git -Omax / STATIC
```

