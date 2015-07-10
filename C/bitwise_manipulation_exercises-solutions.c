#include <stdio.h>
#include <stdlib.h>

int tmax(void) {
    return ~(0x8 << 28);
}

int div_pow_2(int x, int n) {
    return (x >> n) + !!(x >> 31);
}

int is_less(int x, int y) {
    return !((y - x) >> 31);
}

int is_non_negative(int x) {
    return (x >> 31) + 1;
}

int logical_right_shift(int x, int n) {
    int MSK = (0x8 << 28) >> (n - 1);
    return (x >> n) & ~MSK;
}

int multi_by_five_eights(int x) {
    int TMP = (x << 2) + x;
    return div_pow_2(TMP, 3);
}

int abs(int x) {
    int t = x >> 31;
    return ( x ^ t ) - t;
}

int not(int x) {
    int nx = -abs(x);
    nx >>= 31;
    return nx + 1;
}

int tc2sm(int x) {
    int condition(int x, int a, int b) {
        int norm_x = !!x;
        return (a + b) - (b * norm_x) - ( a * !norm_x);
    }
    
    const int MSK = 0x7FFFFFFF;
    int sign_x = x & ~MSK;
    return condition(sign_x, ((x ^ MSK) +1) | sign_x, x);
}

int is_pow_2(int x) {
    return not(x & (x - 1));
}

int leave_only_MSb(int x) {
    // Set all bits from MSb to LSb to '1'
    x |= x >> 1; x |= x >> 2; x |= x >> 4; x |= x >> 8; x |= x >> 16;
    return (x + 1) >> 1;
}

int leave_only_LSb_set_1(int x) {
    return x ^ ( x & (x - 1) );
}

int main(unsigned int argc, char** argv) {
    printf("tmax() = 0x%08x\n\n", tmax());

    printf("div_pow_2(%d, %d) = %d (0x%08x)\n\n", -110, 3, div_pow_2(-110, 3), div_pow_2(-110, 3));
    
    printf("is_less(%d, %d) = %d (0x%08x)\n\n", 33, 4, is_less(33, 4), is_less(33,4));
    
    printf("is_non_negative(%d) = %d (0x%08x)\n\n", -3, is_non_negative(-3), is_non_negative(-3));
    
    printf("logical_right_shift(0x%08x, %d) = 0x%08x\n\n", 0x82345678, 4, logical_right_shift(0x82345678, 4));
    
    printf("multi_by_five_eights(%d) = %d\n\n", -22, multi_by_five_eights(-22));
    
    printf("not(%d) = %d - not(%d) = %d \n\n", -3, not(-3), 0, not(0));
    
    printf("tc2sm(0x%08x) = %d (0x%08x)\n\n", 0x80000005, tc2sm(0x80000005), tc2sm(0x80000005));
    
    printf("is_pow_2(%d) = %d\n", 7, is_pow_2(7));
    printf("is_pow_2(%d) = %d\n\n", 8, is_pow_2(8));
    
    printf("leave_only_MSb(0x%08x) = 0x%08x\n\n", 0x98473, leave_only_MSb(0x98473));
    
    printf("leave_only_LSb_set_1(0x%08x) = 0x%08x\n\n", 0x98473, leave_only_LSb_set_1(0x98473));
}