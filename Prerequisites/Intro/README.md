## **Binary Operators**

- Binary OR Operator
    ~~~c
    //Bit OR is use with an single vertical bar |
    uint8_t x = 1;
    uint8_t y = 2;
    x |= y; // or x = x | y, 
    //   0000 0001
    //             | -> BIT OR
    //   0000 0010
    //---------------
    //   0000 0011 -> 3
    ~~~

- Binary AND Operator
    ~~~c
    // Bit AND is use with an single &
    uint8_t x = 1;
    uint8_t y = 3;

    x &= y; // or x = x & y;
    // 0000 0001
    //          & -> BIT AND
    // 0000 0011
    //----------
    // 0000 0001 -> 1
    ~~~

- Binary One's Complement Operator
    ~~~c
    uint8_t x  = 1;
    x = ~(x); //flip bits
    // 0000 0001
    //          ~ -> 
    // 1111 1110 -> 254
    ~~~~

 - Binary XOR
    ~~~c 
    uint8_t x = 1;
    x ^= x; // toggle the bit
    // 0000 0001
    //           ^ -> BIT XOR    
    // 0000 0001 
    // -----------
    // 0000 0000 -> 0    
    x ^= 1;
    // 0000 0000
    //           ^ -> BIT XOR
    // 0000 0001  
    // ------------
    // 0000 0001 -> 1
    ~~~

## **Hexadecimal Representation and Pin Configuration**
In embedded systems, hexadecimal representation is commonly used to configure registers. Registers often consist of 32 bits (4 bytes), and each bit controls a specific feature or behavior.

One hexadecimal digit represents 4 bits (a nibble). This makes it compact and readable format for binary values/

    - Example

        ~~~c 
        IOMUX->SECCFG.PINCM[48] = 0x00060081;
        ~~~
 
        The above sets the Pin Control Management Register (PINCM) index 48 (associated with PB21) with hexadecimal value 0x00060081.

        0x00060081 = 0000 0000 0000 0110 0000 0000 1000 0001
        Now what do the binary values mean? According to the technical reference manual.

        ![alt text](https://github.com/amedina64/LP-MSPM0G3507-Micro1-Labs/blob/main/images/PINCM_TRM_1.png)

        Bit 18 (INENA) is set to 1
            i.e. input enabled
        Bit 17 (PIPU) is set to 1
            i.e. Pull-up configuration enabled
        Bit 7 (PC) is set to 1
            i.e. peripheral is connected
        Bit 1 (PF or Peripheral Function) is set to 1
            i.e. the mode is just a simple GPIO
        The other bits are set to 0, meaning those features are disabled
        


