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
        cout << i << endl;
        --tot;
    }
};

struct phany
{
    
    using arena_type = arena <50000000>;
    
    inline static arena_type m_arena;
//    template <typename T>
//    explicit phany (phany&) = delete;
    
    
    template <typename T>
    requires (not is_same_v <T, phany&>)
    phany (T const& value) : m_value {m_arena}, m_destruct {[] (byte* value) {reinterpret_cast <T*> (value)->~T ();}}, m_allocate {[] (arena_type& a) {return (T*) a;}}, m_construct {[] (byte* dst) {}}
    {
        new (m_value) T {value};
    }
    
  
    
    template <typename T>
    requires (not is_same_v <T, phany&>)
    phany (T&& value) : m_value {m_arena}, m_destruct {[] (byte* value) {reinterpret_cast <T*> (value)->~T ();}}
    {
        new (m_value) T {move (value)};
    }
    
   
    phany (phany&& other) : phany ()
    {
        swap (*this, other);
    }
    
    phany (phany const& other)
    {
    }
    
    auto operator= (phany const& other) -> phany&
    {
        return *this;
    }
    
    auto operator= (phany other) -> phany&
    {
        swap (*this, other);
        return *this;
    }
    
    
    friend auto swap (phany& lhs, phany& rhs) -> void
    {
        using std::swap;
        
        swap (lhs.m_value, rhs.m_value);
        swap (lhs.m_destruct, rhs.m_destruct);
    }
    
    
    
    
//    template <typename T>
    
    
    phany () = default;
  
    
    ~phany ()
    {
        m_destruct (m_value);
        m_arena (m_value);
    }
    
private:
    byte* m_value {nullptr};
    void (*m_destruct) (byte*) = []<typename T>(T*){};
    byte* (*m_allocate) (arena_type&) = [](arena_type&) -> byte* {return nullptr;};
    void (*m_construct) (byte*) = [](byte*){};
    void (*m_construact) (byte*) = [](byte*){};
    void (*m_construkact) (byte*) = [](byte*){auto a = []{};auto b = []{}; auto c = []{};};

    
    
    
};






#endif
