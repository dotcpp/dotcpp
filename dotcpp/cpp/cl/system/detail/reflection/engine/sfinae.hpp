/*
Copyright (C) 2013-present CompatibL. All rights reserved.

This file is part of CompatibL TapeLib (the "Software"); you may not use the
Software except by obtaining a written commercial license from CompatibL.
The Software contains valuable trade secrets and may be used, copied, stored,
or distributed only in compliance with the terms of its license and with the
inclusion of this copyright notice.
*/

# ifndef cl_tape_impl_reflection_engine_sfinae_hpp
# define cl_tape_impl_reflection_engine_sfinae_hpp

namespace cl
{

  struct sfinae_empty;

  template <typename type>
  struct refl_dummy { typedef sfinae_empty dummy_type; };

} // namespace cl

#endif
