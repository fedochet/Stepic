// Эти классы реализовывать заново не нужно
struct ICloneable;

// Поле data_ типа T в классе ValueHolder
// открыто, к нему можно обращаться
template <typename T>
struct ValueHolder;

// Это класс, который вам нужно реализовать
class Any
{
private:
    ICloneable* v_;
    // В классе Any должен быть конструктор,
    // который можно вызвать без параметров,
    // чтобы работал следующий код:
    //    Any empty; // empty ничего не хранит
public:
    Any(){
        v_ = 0;
    };

    // В классе Any должен быть шаблонный
    // конструктор от одного параметра, чтобы
    // можно было создавать объекты типа Any,
    // например, следующим образом:
    //    Any i(10); // i хранит значение 10
    template<typename T>
    Any(T const &v)
    {
        v_ = new ValueHolder<T>(v);
    }

    // Не забудьте про деструктор. Все выделенные
    // ресурсы нужно освободить.
    ~Any()
    {
        delete v_;
    };

    ICloneable* clone() const
    {
        return v_->clone();
    } 

    // В классе Any также должен быть конструктор
    // копирования (вам поможет метод clone
    // интерфейса ICloneable)

    Any(Any const &a)
    {
        v_ = a.clone();
    }

    // В классе должен быть оператор    присваивания и/или
    // шаблонный оператор присваивания, чтобы работал
    // следующий код:
    //    Any copy(i); // copy хранит 10, как и i
    //    empty = copy; // empty хранит 10, как и copy
    //    empty = 0; // а теперь empty хранит 0
    template<typename T>
    Any& operator=(T const &a)
    {
        delete v_;
        v_ = new ValueHolder<T> (a);
        return *this;
    }

    Any& operator=(Any const &a)
    {
        if (this == &a)
            return *this;
        else
        {
            delete v_;
            v_ = a.clone();
        } 

        return *this;
    }


    // Ну и наконец, мы хотим уметь получать хранимое
    // значение, для этого определите в классе Any
    // шаблонный метод cast, который возвращает
    // указатель на хранимое значение, или нулевой
    // указатель в случае несоответствия типов или
    // если объект Any ничего не хранит:
    //    int *iptr = i.cast<int>(); // *iptr == 10
    //    char *cptr = i.cast<char>(); // cptr == 0,
    //        // потому что i хранит int, а не char
    //    Any empty2;
    //    int *p = empty2.cast<int>(); // p == 0
    // При реализации используйте dynamic_cast,
    // который мы уже обсуждали ранее.
    template <typename T>
    T *cast()
    {
        ValueHolder<T> *x = dynamic_cast< ValueHolder<T> *>(v_);
        if (x)
            return &(x->data_);
        else
            return 0;
    }

};