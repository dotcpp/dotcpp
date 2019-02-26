/*
Copyright (C) 2003-2016 CompatibL

This file is part of TapeScript, an open source library and tape encoding
standard for adjoint algorithmic differentiation (AAD), available from

http://github.com/compatibl/tapescript (source)
http://tapescript.org (documentation)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

# ifndef cl_tape_impl_struct_archive_std_archive_hpp
# define cl_tape_impl_struct_archive_std_archive_hpp

#include <string>
#include <functional>
#include <locale>
#include <codecvt>
#include <algorithm>
//#include <fstream>
#include <memory>
#include <map>

namespace cl
{
    //TODO
    typedef double tvalue;
    struct default_archive_strategy
    {
        enum { merge = 0 }; 
    };
    
    struct printer_strategy
    {

    };

    class base_extern_archive
    {
    public:
#   if !defined NDEBUG
        virtual ~base_extern_archive()
        {}
#   endif
    };

    template<typename Strategy /*= default_archive_strategy*/
            , typename Stream /*= std::fstream*/>
    class std_iarchive : public Strategy
        , public base_extern_archive
    {
    public:
        typedef std_iarchive<Strategy, Stream> this_type;
        typedef typename Stream::pos_type pos_type;
        typedef typename Stream stream_type;
        typedef typename this_type ifstream;
        typedef typename this_type istream;

        std_iarchive()
            : stream_() {}

        explicit std_iarchive(const std::shared_ptr<Stream>& reader, std::string )
            : stream_(reader), filename_() {}

        explicit std_iarchive(const std::string& filename)
            : stream_(std::make_shared<Stream>(filename))
            , filename_(filename)
        { }

        template <typename T, typename A0, typename A1>
        inline std::shared_ptr<T>
        make_shared__(A0 const& a0, A1 const& a1)
        {
            return std::shared_ptr<T>(new T(a0, a1));
        }

        template <typename Arg>
        explicit std_iarchive(const std::string& filename, Arg const& arg)
            : stream_(this-> template make_shared__<Stream>(filename, arg))
            , filename_(filename)
        { }

        template <typename A0, typename A1>
        explicit std_iarchive(const std::string& filename, A0 const& a0, A1 const& a1)
            : stream_(std::make_shared<Stream>(filename, a0, a1))
            , filename_(filename)
        { }

        template <typename A0, typename A1, typename A2, typename A3>
        explicit std_iarchive(const std::string& filename, A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3)
            : stream_(std::make_shared<Stream>(filename, a0, a1, a2, a3))
            , filename_(filename)
        { }

        template <typename A0, typename A1, typename A2, typename A3, typename A4>
        explicit std_iarchive(const std::string& filename, A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4)
            : stream_(std::make_shared<Stream>(filename, a0, a1, a2, a3, a4))
            , filename_(filename)
        { }

        operator bool() const
        {
            return (bool)stream_;
        }

        template <typename T>
        std_iarchive& operator &(T& v)
        {
            return read(v);
        }

        template <typename Type>
        std_iarchive<Strategy,Stream>& operator = (Type const& other)
        {
            stream_ = other.stream_;
            filename_ = other.filename_;
            return *this;
        }

        inline void skipg(size_t to_skip)
        {
            pos_type pos = stream_->tellg() + pos_type(to_skip);
            stream_->seekg(pos, std::ios::beg);
        }

        inline pos_type tellg()
        {
            return stream_->tellg();
        }

        inline this_type& seekg(pos_type pos)
        {
            stream_->seekg(pos);
            return *this;
        }

        inline this_type& seekg(pos_type pos, std::ios::seekdir dir)
        {
            stream_->seekg(pos, dir);
            return *this;
        }

        template<typename T>
        this_type & operator >> (T & t)
        {
            return this->read(t);
        }

        Stream const& ss() { return *stream_.get(); }

    private:
        template<typename T>
        this_type& read(T& v);
        template<typename K, typename V>
        this_type& read(std::map<K, V>&);
        this_type& read(std::string&);

        std::shared_ptr<Stream> stream_;
    public:
        std::string filename_;
    };

    template<typename Strategy, typename  Stream>
    template<typename T>
    std_iarchive<Strategy, Stream>& std_iarchive<Strategy, Stream>::read(T& v)
    {
        static_assert(std::is_pod<T>::value, "This type cannot be deserialized");
        char* p = reinterpret_cast<char*>(&v);
        stream_->read(p, sizeof(T));
        return *this;
    }

    template<typename Strategy, typename Stream>
    inline std_iarchive<Strategy, Stream>& std_iarchive<Strategy, Stream>::read(std::string& s)
    {
        size_t size;
        stream_->read(reinterpret_cast<char*>(&size), sizeof(size_t));
        s.resize(size);
        stream_->read(&s[0], size);
        return *this;
    }

    template<typename Strategy, typename Stream>
    template<typename K, typename V>
    std_iarchive<Strategy, Stream>& std_iarchive<Strategy, Stream>::read(std::map<K, V>& v)
    {
        static_assert(std::is_pod<K>::value || std::is_same<K, std::string>::value, "Map keys cannot be serialized");
        static_assert(std::is_pod<V>::value || std::is_same<K, std::string>::value, "Map values cannot be serialized");

        size_t size;
        stream_->read(reinterpret_cast<char*>(&size), sizeof(size));
        v.clear();
        auto hint = v.begin();
        for (size_t i = 0; i < size; i++)
        {
            std::pair<K, V> temp;
            read(temp.first);
            read(temp.second);
            hint = v.insert(hint, std::move(temp));
        }
        return *this;
    }

    template<typename Archive>
    struct default_output_strategy
    {
        inline Archive* this_()
        {
            return static_cast<Archive*>(this);
        }

        template<typename T>
        inline void write_size_(T size)
        {
            this_()->operator &(size);
        }
        template<typename T>
        inline void write_(T& a)
        {
            this_()->write(a);
        }
    };

    template<typename Archive>
    struct printer_output_strategy
    {
        inline Archive* this_()
        {
            return static_cast<Archive*>(this);
        }

        template<typename T>
        inline void write_size_(T size)
        {
        }

        template<typename T>
        inline void write_(T& a)
        {
            this_()->write(std::to_string(a));
        }
        template<>
        inline void write_(std::string& a)
        {
            this_()->write(a);
        }
    };

    template<typename Strategy = default_archive_strategy, typename Stream = std::fstream, template<typename> class OutputStrategy = default_output_strategy>
    class std_oarchive : public Strategy, public OutputStrategy<std_oarchive<Strategy, Stream, OutputStrategy>>
    {
    public:
        typedef std_oarchive<Strategy, Stream, OutputStrategy> this_type;
        typedef typename Stream::pos_type pos_type;
        typedef typename Stream stream_type;
        typedef typename this_type ofstream;
        typedef typename this_type ostream;
        typedef typename  OutputStrategy<std_oarchive<Strategy, Stream, OutputStrategy>> output_strat;
        friend typename output_strat;

        std_oarchive()
            : stream_() {}

        explicit std_oarchive(const std::shared_ptr<Stream>& reader)
            : stream_(reader) {}

        template <typename Arg>
        explicit std_oarchive(const std::string& filename, Arg const& arg)
            : stream_(std::make_shared<Stream>(filename, arg))
            , filename_(filename)
        { }

        template <typename T>
        this_type& operator &(T& v)
        {
            write_(v);
            stream_->flush();
            return *this;
        }

        inline void skipp(size_t to_skip)
        {
            pos_type pos = stream_->tellp() + pos_type(to_skip);
            stream_->seekp(pos, std::ios::beg);
        }

        inline pos_type tellp()
        {
            return stream_->tellp();
        }


        inline this_type& seekp(pos_type pos)
        {
            stream_->seekp(pos);
            return *this;
        }

        inline this_type& seekp(pos_type pos, std::ios::seekdir dir)
        {
            stream_->seekp(pos, dir);
            return *this;
        }

        template<typename T>
        this_type & operator << (T & t)
        {
            return this->operator &(t);
        }

        Stream const& ss() { return *stream_.get(); }
    protected:
        template<typename T>
        std_oarchive& write(const T& v);
        template<typename K, typename V>
        std_oarchive& write(std::map<K, V>&);
        std_oarchive& write(const std::string&);

        std::shared_ptr<Stream> stream_;
    public:
        std::string filename_;
    };

    template<typename Strategy, typename Stream, template<typename> class OutputStrategy>
    template<typename T>
    std_oarchive<Strategy, Stream, OutputStrategy>& std_oarchive<Strategy, Stream, OutputStrategy>::write(const T& v)
    {
        static_assert(std::is_pod<T>::value, "This type cannot be serialized");
        const char* p = reinterpret_cast<const char*>(&v);
        stream_->write(p, sizeof(T));
        return *this;
    }


    template<typename Strategy, typename Stream, template<typename> class OutputStrategy>
    inline std_oarchive<Strategy, Stream, OutputStrategy>& std_oarchive<Strategy, Stream, OutputStrategy>::write(const std::string& s)
    {
        auto size = s.size();
        write_size_(size);
        stream_->write(&s[0], size);
        return *this;
    }

    template<typename Strategy, typename Stream, template<typename> class OutputStrategy>
    template<typename K, typename V>
    std_oarchive<Strategy, Stream, OutputStrategy>& std_oarchive<Strategy, Stream, OutputStrategy>::write(std::map<K, V>& v)
    {
        static_assert(std::is_pod<K>::value || std::is_same<K, std::string>::value, "Map keys cannot be serialized");
        static_assert(std::is_pod<V>::value || std::is_same<K, std::string>::value, "Map values cannot be serialized");
        auto size = v.size();
        stream_->write(reinterpret_cast<char*>(&size), sizeof(size));
        for (auto p : v)
        {
            write(p.first);
            write(p.second);
        }
        return *this;
    }

    template <typename Archive>
    struct stream_type_trait;

    template <typename Strategy, typename Stream>
    struct stream_type_trait<std_iarchive<Strategy, Stream>>
    {
        enum { is_out = 0 };
        static const std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out | std::ios_base::binary;
        typedef typename std_iarchive<Strategy, Stream>::ifstream fstream_type;
        typedef typename std_iarchive<Strategy, Stream>::istream stream_type;

        typedef cl::struct_archive<cl::tvalue, cl::std_iarchive<Strategy, Stream>> reader_type;
        typedef cl::struct_archive<cl::tvalue, cl::std_oarchive<Strategy, Stream>> writer_type;

        template <typename F>
        inline static typename fstream_type::pos_type
            tell(F& f) { return f.tellg(); }
    };

    template<typename Strategy, typename Stream>
    struct stream_type_trait<std_oarchive<Strategy, Stream>>
    {
        enum { is_out = 1 };
        static const std::ios_base::openmode mode = std::ios_base::out | std::ios_base::binary;
        typedef typename std_oarchive<Strategy, Stream>::ofstream fstream_type;
        typedef typename std_oarchive<Strategy, Stream>::ostream stream_type;
        typedef cl::struct_archive<cl::tvalue, cl::std_iarchive<Strategy, Stream>> reader_type;
        typedef cl::struct_archive<cl::tvalue, cl::std_oarchive<Strategy, Stream>> writer_type;

        template <typename F>
        inline static typename fstream_type::pos_type
            tell(F& f) { return f.tellp(); }
    };
    template<typename Strategy, typename Stream>
    struct stream_type_trait<std_oarchive<Strategy, Stream, printer_output_strategy>>
    {
        enum { is_out = 1 };
        static const std::ios_base::openmode mode = std::ios_base::out | std::ios_base::binary;
        typedef typename std_oarchive<Strategy, Stream, printer_output_strategy>::ofstream fstream_type;
        typedef typename std_oarchive<Strategy, Stream, printer_output_strategy>::ostream stream_type;
        typedef cl::struct_archive<cl::tvalue, cl::std_iarchive<Strategy, Stream>> reader_type;
        typedef cl::struct_archive<cl::tvalue, cl::std_oarchive<Strategy, Stream>> writer_type;
        struct printer_type_tag {};
        template <typename F>
        inline static typename fstream_type::pos_type
            tell(F& f) { return f.tellp(); }
    };

}
# endif
