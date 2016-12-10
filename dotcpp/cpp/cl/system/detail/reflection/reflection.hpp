/*
Copyright (C) 2013-present CompatibL. All rights reserved.

This file is part of CompatibL TapeLib (the "Software"); you may not use the
Software except by obtaining a written commercial license from CompatibL.
The Software contains valuable trade secrets and may be used, copied, stored,
or distributed only in compliance with the terms of its license and with the
inclusion of this copyright notice.
*/

# ifndef cl_tape_impl_reflection_reflection_hpp
# define cl_tape_impl_reflection_reflection_hpp

# include <cl/system/detail/reflection/engine/register_type.hpp>

namespace cl
{

  // Default for extract
  struct refl_branch;

  // This class allows iteration by metadata storage
  template <int I>
  struct ftbl_iterator ;

  // Meta storage 
  template <template <int > class ftbl
    , typename Branch = refl_branch
    , int II = 0
    , int fin = cl::reg_sfinae<ftbl<II >, Branch >::value
    >
  struct refl_iterator
  {
    enum { value = II };
  };

  template <template <int > class ftbl
    , int II
    , typename Branch  >
  struct refl_iterator <ftbl, Branch, II, 1>
  {
    enum { value = refl_iterator<ftbl, Branch, II + 1 >::value };
  };

  
  // This class allows take a class metadata
  template<
      template <int > class ftbl
    , typename Branch = refl_branch
    , template <typename, typename, int > class base = cl::vi_type
    , int II = 0
    , int fin = ::cl::reg_sfinae<ftbl<II>, Branch >::value
    >
  struct refl_extract
  {
    // Current step describer
    typedef typename
      ftbl<II>::type type_;

    
    // This is a recursive call
    typedef typename
      refl_extract<ftbl, Branch, base, II + 1>::type next_type;

    // Make a list
   typedef typename
       base<type_, next_type, 1 >::type next_;
    
    // Get next type
    typedef next_ type;
  };

  // Last extraction step
  template <
      template <int > class ftbl
    , typename Branch
    , template <class, class, int > class base
    , int II>
  struct refl_extract<ftbl, Branch, base, II, 0 >
  {
    typedef cl::null_type type;
  };

} // namespace cl

namespace cl {

#ifndef REFL_EXTRACTOR_MAX_DEPTH
    #define REFL_EXTRACTOR_MAX_DEPTH 400
#endif

template <int Depth = REFL_EXTRACTOR_MAX_DEPTH>
struct refl_extract_deep
            : refl_extract_deep <Depth - 1>
{   };

template <>
struct refl_extract_deep<0> {   };


// This is a struct which used as converter template class to type.
template <template <typename > class iterator_type >
struct reflection_shell__;

} //namespace cl


#define HL_DEFINE_META_STORAGE(ftbl)                                            \
    template <int >																\
    struct ftbl                                                                 \
                                                                                
// Registration of new type                                                     
#define HL_REGISTRATE_REFLACTION_TYPE_IMPL(ftbl, type_)                         \
    template <>																	\
    struct ftbl<cl::refl_iterator<ftbl, type_>::value >							\
    {                                                                           \
      struct registered;                                                        \
      typedef type_ type;                                                       \
    }                                                                           
                                                                                
#define HL_REGISTRATE_REFLACTION_TYPE(ftbl, type_)                              \
    HL_DEFINE_META_STORAGE(ftbl);                                               \
    HL_REGISTRATE_REFLACTION_TYPE_IMPL(ftbl, type_)                             \


#endif // cl_tape_impl_reflection_reflection_hpp
