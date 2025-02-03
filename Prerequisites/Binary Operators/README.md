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
