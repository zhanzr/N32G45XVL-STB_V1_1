# N32G457VEL STB V1.1
N32G457VEL

## dhrystone
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
MicroSecond for one run through Dhrystone[3-10491]:      1.049
Dhrystones per Second:  953470.625
DMIPS/MHz:      3.769
```

### Flash uncached, With FPU
```
-Omax
MicroSecond for one run through Dhrystone[22511-42030]:  1.952
Dhrystones per Second:  512321.312
DMIPS/MHz:      2.025
```

