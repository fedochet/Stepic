#include <cassert>
#include <string>
#include <cmath>

struct Transformer;
struct Number;
struct BinaryOperation;
struct FunctionCall;
struct Variable;

struct Expression
{
    virtual ~Expression() { }
    virtual double evaluate() const = 0;
    virtual Expression *transform(Transformer *tr) const = 0;
};

struct Transformer
{
    virtual ~Transformer() { }
    virtual Expression *transformNumber(Number const *) = 0;
    virtual Expression *transformBinaryOperation(BinaryOperation const *) = 0;
    virtual Expression *transformFunctionCall(FunctionCall const *) = 0;
    virtual Expression *transformVariable(Variable const *) = 0;
};

struct Number : Expression
{
    Number(double value);
    double value() const;
    double evaluate() const;
    Expression *transform(Transformer *tr) const;

private:
    double value_;
};

struct BinaryOperation : Expression
{
    enum {
        PLUS = '+',
        MINUS = '-',
        DIV = '/',
        MUL = '*'
    };
    BinaryOperation(Expression const *left, int op, Expression const *right);
    ~BinaryOperation();
    double evaluate() const;
    Expression *transform(Transformer *tr) const;
    Expression const *left() const;
    Expression const *right() const;
    int operation() const;

private:
    Expression const *left_;
    Expression const *right_;
    int op_;
};

struct FunctionCall : Expression
{
    FunctionCall(std::string const &name, Expression const *arg);
    ~FunctionCall();
    double evaluate() const;
    Expression *transform(Transformer *tr) const;
    std::string const &name() const;
    Expression const *arg() const;

private:
    std::string const name_;
    Expression const *arg_;
};

struct Variable : Expression
{
    Variable(std::string const name);
    std::string const & name() const;
    double evaluate() const;
    Expression *transform(Transformer *tr) const;

private:
    std::string const name_;
};


/**
 * реализуйте все необходимые методы
 * если считаете нужным, то можете
 * заводить любые вспомогательные
 * методы
 */
struct FoldConstants : Transformer
{
    Expression *transformNumber(Number const *number)
    {
        return new Number(number->value()); 
    }

    Expression *transformBinaryOperation(BinaryOperation const *binop)
    {
        Expression *right = binop->right()->transform(this);
        Expression *left  = binop->left()->transform(this); 

        if (dynamic_cast<Number *>(right))
            if (dynamic_cast<Number *>(left))
            {
                delete left;
                delete right; 
                return new Number(binop->evaluate());   
            }

        delete right;
        delete left;
        return new BinaryOperation(binop->left()->transform(this),binop->operation(),binop->right()->transform(this));

        //return new BinaryOperation(binop->left()->transform(this),binop->operation(),binop->right()->transform(this));
    }

    Expression *transformFunctionCall(FunctionCall const *fcall)
    {
        Expression *result = fcall->arg()->transform(this);
        if(dynamic_cast<Number *>(result))
        {
            delete result;
            return new Number(fcall->evaluate());
        }
           //FunctionCall(fcall->name(),fcall->arg()->transform(this)); 
        delete result;
        return new FunctionCall(fcall->name(),fcall->arg()->transform(this));
    }

    Expression *transformVariable(Variable const *var)
    { 
        return new Variable(var->name());
    }
};