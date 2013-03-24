
struct Null;

// number definition

template<typename Volume=Null>
struct Number
{
    typedef Volume Dec;
    typedef Number<Volume> Value;
    typedef Number<Number<Volume> > Inc;
};

template<typename Op1,typename Op2>
struct Add
    :public Add<typename Op1::Inc,typename Op2::Dec>{};

template<typename Volume>
struct Add<Volume,Number<Null> >
    :public Volume{};

template<typename Op1,typename Op2,typename Count=Number<Null> >
struct Mul
    :public Mul<Op1,typename Op2::Dec,Add<Count,Op1> >{};

template<typename Op1,typename Count>
struct Mul<Op1,Number<Null>,Count>
    :public Count{};

template<typename Op1,typename Op2,typename Count=Number<> >
struct Rem
    :public Rem<typename Op1::Dec,Op2,typename Count::Inc>{};

template<typename Op1,typename Op2>
struct Rem<Op1,Op2,Op2 >
    :public Rem<Op1,Op2>{};

template<typename Op2,typename Count>
struct Rem<Number<>,Op2,Count>
    :public Count{};

template<typename Op2>
struct Rem<Number<Null>,Op2,Op2>
    :public Number<>{};

template<typename Op1,typename Op2,typename Count=Number<>,typename Count2=Number<> >
struct Div
    :public Div<typename Op1::Dec,Op2,typename Count::Inc,Count2>{};

template<typename Op1,typename Op2,typename Count2>
struct Div<Op1,Op2,Op2,Count2>
    :public Div<Op1,Op2,Number<>,typename Count2::Inc>{};

template<typename Op2,typename Count,typename Count2>
struct Div<Number<>,Op2,Count,Count2>
    :public Count2{};

template<typename Op2,typename Count2>
struct Div<Number<>,Op2,Op2,Count2>
    :public Count2::Inc{};

// decimal definition

typedef Number<> Zero;
typedef Zero::Inc One;
typedef One::Inc Two;
typedef Two::Inc Three;
typedef Three::Inc Four;
typedef Four::Inc Five;
typedef Five::Inc Six;
typedef Six::Inc Seven;
typedef Seven::Inc Eight;
typedef Eight::Inc Nine;
typedef Nine::Inc Ten;

template<typename Value>struct Print;

#include <stdio.h>
template<>struct Print<Zero >{static void print(){printf("0");}};
template<>struct Print<One  >{static void print(){printf("1");}};
template<>struct Print<Two  >{static void print(){printf("2");}};
template<>struct Print<Three>{static void print(){printf("3");}};
template<>struct Print<Four >{static void print(){printf("4");}};
template<>struct Print<Five >{static void print(){printf("5");}};
template<>struct Print<Six  >{static void print(){printf("6");}};
template<>struct Print<Seven>{static void print(){printf("7");}};
template<>struct Print<Eight>{static void print(){printf("8");}};
template<>struct Print<Nine >{static void print(){printf("9");}};

// print digit

template<typename Value,typename Base=One>
struct PrintNumber{
    static void print(){
        PrintNumber<Div<Value,Ten>::Value,Base::Inc>::print();
        Print<Rem<Value,Ten>::Value >::print();
    }
};

template<typename Base>
struct PrintNumber<Zero,Base>{
    static void print(){
    }
};

template<>
struct PrintNumber<Zero,One>{
    static void print(){
        Print<Zero>::print();
    }
};

// fizz buzz definition

template<typename Count,typename Fizz=Rem<Count,Three>::Value,typename Buzz=Rem<Count,Five>::Value >
struct FizzBuzz{
    static void count(){
        FizzBuzz<Count::Dec>::count();
        PrintNumber<Count>::print();
        printf("\n");
    }
};

template<typename Count>
struct FizzBuzz<Count,Zero,Zero>{
    static void count(){
        FizzBuzz<Count::Dec>::count();
        printf("FizzBuzz\n");
    }
};

template<typename Count,typename Buzz>
struct FizzBuzz<Count,Zero,Buzz>{
    static void count(){
        FizzBuzz<Count::Dec>::count();
        printf("Fizz\n");
    }
};

template<typename Count,typename Fizz>
struct FizzBuzz<Count,Fizz,Zero>{
    static void count(){
        FizzBuzz<Count::Dec>::count();
        printf("Buzz\n");
    }
};

template<>struct FizzBuzz<Zero,Zero,Zero>{static void count(){}};

void main()
{
    FizzBuzz<Mul<Ten,Ten>::Value>::count();
}

