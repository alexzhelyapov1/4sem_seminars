#include "metrics.h"


My_Max::My_Max() : max_(INT_MIN){};



void My_Max::print() const
{
    std::cout << "Max element = " << max_ << std::endl;
}



void My_Max::update(const int& digit) 
{
    if (digit > max_) {
        max_ = digit;
        std::cout << "Update: ";
        // this->print();
    }
}



My_Min::My_Min() : min_(INT_MAX){};



void My_Min::print() const
{
    std::cout << "Min element = " << min_ << std::endl;
}



void My_Min::update(const int& digit) 
{
    if (digit < min_) {
        min_ = digit;
        std::cout << "Update: ";
        this->print();
    }
}



Average::Average() : data_(0), number_of_elements_(0){};
Average::Average(int a) : data_(a), number_of_elements_(0){};



void Average::print() const {
    std::cout << "Average value = " << data_ << std::endl;
}



void Average::update(const int& digit) {
    data_ = (digit + data_ * number_of_elements_) / (number_of_elements_ + 1);
    number_of_elements_++;
    std::cout << "Update: ";
    this->print();
}