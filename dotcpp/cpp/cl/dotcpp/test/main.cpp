/*
Copyright (C) 2003-present CompatibL. All rights reserved.

This code contains valuable trade secrets and may be copied, stored, used,
or distributed only in compliance with the terms of a written commercial
license from CompatibL and with the inclusion of this copyright notice.
*/

#include <cl/dotcpp/test/implement.hpp>

int main()
{
    try
    {
        std::cout << "Hello world" << std::endl;
    }
    catch(std::exception e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
