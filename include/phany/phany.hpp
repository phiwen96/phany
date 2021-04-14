#ifndef PHANY_HPP
#define PHANY_HPP
#include <ph_memory/arena.hpp>

using namespace std;

struct test
{
    inline static int tot {0};
    int i {tot++};
    
//    test ()
//    {
//        cout << i << endl;
//    }
    
    ~test ()
    {
//        cout << i << endl;
        --tot;
    }
};

struct _phany
{
    
    
    using arena_type = arena <500000>;
    
    inline static arena_type m_arena;
//    template <typename T>
//    explicit phany (phany&) = delete;
    
    
//    template <typename T>
//    requires (not is_same_v <T, phany&>)
//    phany (T const& value) : m_value {m_arena}, m_destruct {[] (byte* value) {reinterpret_cast <T*> (value)->~T ();}}//, m_allocate {[] (arena_type& a) {return (T*) a;}}//, m_construct {[] (byte* dst) {}}
//    {
//        new (m_value) T {value};
//    }
    
    template <typename T>
    requires (not is_class_v <T>)
    _phany (T&& value) : m_value {m_arena}
    {
        new (m_value) T {move (value)};
    }
    
    template <typename T>
    requires (not is_same_v <T, _phany&> and is_class_v <T>)
    _phany (T&& value) :
        m_value {m_arena},
        m_destruct {[](byte*& value){
            reinterpret_cast <T*> (value)->~T ();
        }}
    {
        new (m_value) T {forward <T> (value)};
    }
    
  
    
   
    _phany (_phany&& other) : _phany ()
    {
        swap (*this, other);
    }
    
//    phany (phany const& other)
//    {
//    }
    
//    auto operator= (phany const& other) -> phany&
//    {
//        return *this;
//    }
    
//    auto operator= (phany other) -> phany&
//    {
//        swap (*this, other);
//        return *this;
//    }
    
    
    friend auto swap (_phany& lhs, _phany& rhs) -> void
    {
        using std::swap;

        swap (lhs.m_value, rhs.m_value);
        swap (lhs.m_destruct, rhs.m_destruct);
    }
    
    
    
    
//    template <typename T>
    
    
    _phany () : m_destruct {[](byte*&){}}
    {
        
    }
  
    
    ~_phany ()
    {
        m_destruct (m_value);
        m_arena (m_value);
    }
    
private:
    byte* m_value {nullptr};
    void (*m_destruct) (byte*&);
//    function <void (byte*)> m_destruct;
    // = [](byte*){};
//    byte* (*m_allocate) (arena_type&) = [](arena_type&) -> byte* {return nullptr;};
//    void (*m_construct) (byte*) = [](byte*){};
//    void (*m_construact) (byte*) = [](byte*){};
//    void (*m_construkact) (byte*) = [](byte*){auto a = []{};auto b = []{}; auto c = []{};};
//    inline static constexpr void (*m_construlkkact) (int i) = []<typename T>(auto i) constexpr {if constexpr(is_same_v <int, T>){}auto a = []{};auto b = []{}; auto c = []{};};

    
//    decltype ([]<typename T>(auto i) constexpr {if constexpr(is_same_v <int, T>){}auto a = []{};auto b = []{}; auto c = []{};}) a;
    
};



template <typename T>
struct phany
{
    T t;
};

template <typename T>
phany (T) -> phany <decay_t <T>>;



#endif
