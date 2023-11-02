#include "util.h"
#include <iostream>

void logo()
{
    Util::SetColor(CYAN);
    std::cout << XorStr(R"(
                                          ____  ____   __    __  ____  ____  ____ 
                                         / ___)(  _ \ /  \  /  \(  __)(  __)(  _ \
                                         \___ \ ) __/(  O )(  O )) _)  ) _)  )   /
                                         (____/(__)   \__/  \__/(__)  (____)(__\_)
)") << '\n';
}