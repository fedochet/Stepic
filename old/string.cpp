#include <cstddef> // size_t
#include <cstring> // strlen, strcpy
struct String {
    // для аллокации памяти не используйте malloc
    // иначе ваша программа может не пройти
    // тестирование
    String(const char *str = "") {
        int i = strlen(str);

        str_ = new char[i];
        strcpy(str_,str);
        // put your code here
    }
    String(size_t n, char c) {
        size_ = n;
        str_ = new char [size_];
        for (int i = 0; i<size_; i++)
            str_[i] = c;
        // put your code here
    }
    // не изменяйте эти имена, иначе ваша программа
    // не пройдет тестирование
    size_t size_;
    char *str_;
};  



int main()
{
    String s("");
    std::cout<<s.str_<<std::endl;
    return 0;
}