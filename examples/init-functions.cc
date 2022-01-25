#include <stdio.h>
#include <stdlib.h>

namespace {
    struct GlobalClass {
      GlobalClass() { puts("INITIALIZING GLOBAL VAR"); }
      ~GlobalClass() { puts("DESTROYING GLOBAL VAR"); }
    };

    struct FunctionStaticClass {
      FunctionStaticClass() { puts("INITIALIZING FUNCTION STATIC VAR"); }
      ~FunctionStaticClass() { puts("DESTROYING FUNCTION STATIC VAR"); }
    };

    void InitStatic() { static FunctionStaticClass nontrivial; }

    void C_AtExit() {
      puts("C-STYLE ATEXIT FUNCTION CALLED");
    }
}

GlobalClass nontrivial;

int main() {
    puts("IN MAIN");

    InitStatic();

    ::atexit(C_AtExit);

    puts("LEAVING MAIN");

    return 40;
}
