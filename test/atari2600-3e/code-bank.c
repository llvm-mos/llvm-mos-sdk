
#include <test-lib-vcs.h>
#include <vcslib.h>
#include <mapper.h>

#define KERNEL_BANK 0

// Display kernel loop
CODE_BANK(KERNEL_BANK) static void do_kernel_iter() {
    kernel_1();
    kernel_2();
    kernel_3();
    kernel_4();
}

int main(void) {
    // make sure do_kernel_iter() is in a different bank than main()
    if ((((int)&main ^ (int)&do_kernel_iter) & 0xf800) == 0) {
        test_failed();
    }
    test_passed();
    return 0;
}
