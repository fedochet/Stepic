// Определите шаблон SameType с двумя типовыми
// параметрами. В шаблоне должна быть определена
// одна статическая константа типа bool с именем
// value

template<typename T, typename S>
    struct SameType{
    public:    
    static bool const value = false;
};

template<typename T>
    struct SameType<T, T>{
    public:    
    static bool const value = true;
};

