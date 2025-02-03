## **Hexadecimal Representation and Pin Configuration**
In embedded systems, hexadecimal representation is commonly used to configure registers. Registers often consist of 32 bits (4 bytes), and each bit controls a specific feature or behavior.

One hexadecimal digit represents 4 bits (a nibble). This makes it compact and readable format for binary values.

- Example
  ~~~c
        IOMUX->SECCFG.PINCM[48] = 0x00060081;
  ~~~
 
The above sets the Pin Control Management Register (PINCM) index 48 (associated with PB21) with hexadecimal
value 0x00060081. (Or in binary  0000 0000 0000 0110 0000 0000 1000 0001)
Now what do the binary values mean? According to the technical reference manual.

![alt text](https://github.com/amedina64/LP-MSPM0G3507-Micro1-Labs/blob/main/images/PINCM_TRM_1.png)

![alt text](https://github.com/amedina64/LP-MSPM0G3507-Micro1-Labs/blob/main/images/PINCM_TRM_2.png)

From here we just look at the bits that are enabled and read the manual.
0x00060081. (Or in binary  0000 0000 0000 0110 0000 0000 1000 0001)

        Bit 18 (INENA) is set to 1
            i.e. input enabled
        Bit 17 (PIPU) is set to 1
            i.e. Pull-up configuration enabled
        Bit 7 (PC) is set to 1
            i.e. peripheral is connected
        Bit 1 (PF or Peripheral Function) is set to 1
            i.e. the mode is just a simple GPIO
            
The other bits are set to 0, meaning those features are disabled
