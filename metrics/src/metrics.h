#ifndef METRICS
#define METRICS

#include <iostream>
#include <list>
#include <map>

class Metric {      // Переписать на Singleton
    public:
    int data_;
    Metric() : data_(0){};
    Metric(int a) : data_(a){};
    virtual void print() {      // Мы можем не писать виртуал и просто переопределять? // Полиморфизм времени выполнения
        std::cout << "Data in unknown metric = " << data_ << std::endl;
    }
    virtual void update(int digit) = 0;
};

class My_max : public Metric {

    public:
    My_max() : Metric(0){};
    void print() override {
        std::cout << "Max element = " << data_ << std::endl;
    }
    void update(int digit) override {
        if (digit > data_) {
            data_ = digit;
            std::cout << "Update: ";
            this->print();
        }
    }
};

class My_min : public Metric {

    public:
    My_min() : Metric(1000000){};
    void print() override {
        std::cout << "Min element = " << data_ << std::endl;
    }
    void update(int digit) override {
        if (digit < data_) {
            data_ = digit;
            std::cout << "Update: ";
            this->print();
        }
    }
};

class Average : public Metric {
    int number_of_elements_;
    double data_;

    public:
    Average() : data_(0), number_of_elements_(0){};
    Average(int a) : data_(a), number_of_elements_(0){};
    void print() override {
        std::cout << "Average value = " << data_ << std::endl;
    }
    void update(int digit) override {
        data_ = (digit + data_ * number_of_elements_) / (number_of_elements_ + 1);
        number_of_elements_++;
        std::cout << "Update: ";
        this->print();
    }
};

class Unique_values : public Metric {
    // data_ - numbers of unique elements
    std::map<int, int> digit_info_;

    public:
    Unique_values() : Metric(0){};
    void print() override {
        std::cout << "Number of unique elements = " << data_ << std::endl;
    }
    void update(int digit) override {
        if (digit_info_.find(digit) == digit_info_.end()) {
            digit_info_.insert(std::pair<int, int>(digit, 1));
            data_++;
            std::cout << "New unique value = " << digit << std::endl;
            std::cout << "Update: ";
            this->print();
        }
    }
    void print_unique_values() {
        std::cout << "Unique values:\n";
        for (auto& item : digit_info_) {
            std::cout << item.first << " ";
        }
        std::cout << std::endl;
    }
};

class MetricsManager {
    std::map<std::string, std::shared_ptr<Metric>> metrics_;

    public:
    void register_metric(std::string name, std::shared_ptr<Metric> metric) {
        metrics_.insert(std::pair<std::string, std::shared_ptr<Metric>>(name, metric));
    }

    void handle(int digit) {
        std::cout << "New element = " << digit << std::endl;
        for (auto& metric : metrics_) {
            metric.second->update(digit);
        }
    }

    void print_all() {
        for (auto& metric : metrics_) {
            metric.second->print();
        }
    }

    void print_current_metric(std::string name) {
        if (metrics_.find(name)!= metrics_.end()) {
            metrics_[name]->print();
        }
        else {
            std::cout << "ERROR! Wrond name of metric = " << name << std::endl;
        }
    }
};


#endif

// Singleton для инициализации первого объекта