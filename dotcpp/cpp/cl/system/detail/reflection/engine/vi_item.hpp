/*
Copyright (C) 2013-present CompatibL. All rights reserved.

This file is part of CompatibL TapeLib (the "Software"); you may not use the
Software except by obtaining a written commercial license from CompatibL.
The Software contains valuable trade secrets and may be used, copied, stored,
or distributed only in compliance with the terms of its license and with the
inclusion of this copyright notice.
*/

# ifndef cl_tape_impl_reflection_engine_vi_item_hpp
# define cl_tape_impl_reflection_engine_vi_item_hpp

namespace cl
{
    template <typename Type, typename Base, int I>
    struct v_item
    {
        typedef Type type;
        typedef Base base;
    };
}

namespace cl
{
    template <typename Type, typename Base, int I>
    struct vi_type
    {
        typedef cl::v_item<Type, Base, I> type;
    };
}

#endif
