/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}
//德摩根律

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(~x & ~y) & ~(x & y);
}
/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    int fx = x >> 31;
    int fy = y >> 31;
    int same = !(fx ^ fy);
    if (!x) {
        return !y;
    }
    if (!y) {
        return 0;
    }
    return same;
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int r = 0;
    int shift;
    int cond;

    cond = (v >> 16) > 0;//二分操作，找最高位序号1是否在16位之外
    shift = cond << 4;//和下一步一起负责把这个至少有的计数加上去
    r |= shift;//
    v = v >> shift;//对数操作方便下一阶段操作数字

    cond = (v >> 8) > 0;
    shift = cond << 3;
    r |= shift;
    v = v >> shift;

    cond = (v >> 4) > 0;
    shift = cond << 2;
    r |= shift;
    v = v >> shift;

    cond = (v >> 2) > 0;
    shift = cond << 1;
    r |= shift;
    v = v >> shift;

    cond = (v >> 1) > 0;
    shift = cond;          // 等价于 cond << 0，省一个操作符
    r |= shift;
    v = v >> shift;

    return r;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int n_shift = n << 3;//用于把需要交换的字节移到前面
    int m_shift = m << 3;
    int xn = (x >> n_shift) & 0xFF;//存储需要交换的字节
    int xm = (x >> m_shift) & 0xFF;
    int mask = ~((0xFF << n_shift) | (0xFF << m_shift));
    int x_cleared = x & mask;//清位转换
    return x_cleared | (xm << n_shift) | (xn << m_shift);
}


/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned r = 0;
    int i;
    for (i = 0; i - 32; i = i + 1) {
        r = (r << 1) | (v & 1);
        v = v >> 1;
    }
    return r;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int mask = ~(((1 << 31) >> n) << 1);
    return (x >> n) & mask;//使用掩码把移位之后的顶端换了
}
/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int count = 0;
    int cond;

    cond = !(((x >> 16) & 0xFFFF) ^ 0xFFFF);
    count += cond << 4;
    x = x << (cond << 4);

    cond = !(((x >> 24) & 0xFF) ^ 0xFF);
    count += cond << 3;
    x = x << (cond << 3);

    cond = !(((x >> 28) & 0xF) ^ 0xF);
    count += cond << 2;
    x = x << (cond << 2);

    cond = !(((x >> 30) & 0x3) ^ 0x3);
    count += cond << 1;
    x = x << (cond << 1);

    cond = !(((x >> 31) & 1) ^ 1);
    count += cond;
    x = x << cond;

    count += (x >> 31) & 1;

    return count;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned sign = x & 0x80000000;
    unsigned abs_x;
    int e = 0;
    int shift;
    unsigned frac;
    unsigned remainder;
    unsigned half;
    unsigned mask;
    int exp;

    if (x == 0) return 0;

    abs_x = x;                  // 隐式转换
    if (x < 0) abs_x = -abs_x;  // 取绝对值

    unsigned temp = abs_x;      // 改成 unsigned
    while (temp >>= 1) e++;

    exp = e + 127;

    if (e <= 23) {
        frac = (abs_x << (23 - e)) & 0x7FFFFF;
    } else {
        shift = e - 23;
        frac = (abs_x >> shift) & 0x7FFFFF;   // 加 & 0x7FFFFF
        mask = (1 << shift) - 1;
        half = 1 << (shift - 1);
        remainder = abs_x & mask;
        if (remainder > half) {
            frac++;
        } else if (remainder == half) {
            if (frac & 1) frac++;
        }
        if (frac >> 23) {
            frac = 0;
            exp++;
        }
        frac = frac & 0x7FFFFF;
    }

    return sign | (exp << 23) | frac;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign = uf & 0x80000000;
    unsigned exp = (uf >> 23) & 0xFF;
    unsigned frac = uf & 0x7FFFFF;

    if (exp == 0xFF) {
        return uf;
    }
    if (exp == 0) {
        return sign | ((uf & 0x7FFFFFFF) << 1);
    }
    exp = exp + 1;
    if (exp == 0xFF) {
        return sign | (0xFF << 23);
    }
    return sign | (exp << 23) | frac;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned sign = uf2 >> 31;
    unsigned exp = (uf2 >> 20) & 0x7FF;
    unsigned frac_high = uf2 & 0xFFFFF;
    unsigned frac_low = uf1;

    if ((exp + 1) >> 11) {
        return 0x80000000;   // NaN 或 Inf，溢出
    }
    if (!exp) {
        return 0;            // 非规格化数，下溢为 0
    }

    int e = exp - 1023;      // 实际指数

    if (e < 0) {
        return 0;            // 值小于 1，向零舍入为 0
    }
    if (e >= 31) {
        return 0x80000000;   // 溢出
    }

    // 0 <= e <= 30
    unsigned result;
    if (e <= 20) {
        result = (1 << e) | (frac_high >> (20 - e));
    } else {
        unsigned high_part = frac_high << (e - 20);
        unsigned low_part = frac_low >> (32 - (e - 20));
        result = (1 << e) | high_part | low_part;
    }

    if (sign) {
        result = -result;
    }
    return result;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x >= 128) {
        return 0x7F800000;   // +INF
    }
    if (x >= -126) {
        return (x + 127) << 23;   // 规格化数
    }
    if (x >= -149) {
        return 1 << (x + 149);    // 非规格化数
    }
    return 0;                     // 下溢
}
