#include <string> // std::string
#include <cassert>
#include <cmath>  // sqrt и fabs

// эти классы определять заново не нужно
struct Expression;
struct BinaryOperation;
struct Number;


struct FunctionCall : Expression
{
    /**
     * @name имя функции, возможные варианты
     *       "sqrt" и "abs".
     *
     *       Объекты, std::string можно
     *       сравнивать с C-строками используя
     *       обычный синтаксис ==.
     *
     * @arg  выражение аргумент функции
     */
    FunctionCall(std::string const &name, Expression const *arg)
        : name_(name), arg_(arg)
    {
        assert(arg_);
        assert(name_ == "sqrt" || name_ == "abs");
    }

    // реализуйте оставшие методы из
    // интерфейса Expression и не забудьте
    // удалить arg_, как это сделано в классе
    // BinaryOperation

    std::string const & name() const
    {
        // put your code here
        return name_;
    }

    Expression const *arg() const
    {
        return arg_;
        // here
    }

    //возвращает значение
    double value() const
    { return arg_->evaluate(); }

    // считает значение 
    double evaluate() const
    { 
        if (name_ == "sqrt")
            return sqrt(arg_->evaluate());
        if (name_ == "abs")
            return fabs(arg_->evaluate());
    }

    // destructor
    ~FunctionCall()
    {
        delete arg_;
    }
    // and here

private:
    std::string const name_;
    Expression const *arg_;
};