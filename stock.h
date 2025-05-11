#ifndef STOCKS_H
#define STOCKS_H

#include <QString>
#include <vector>

class Stock {
    public:
    QString name;
    int quantity;
    double price;
    QString category;
    QString supplier;
    Stock() : name(""), quantity(0), price(0.0), category(""), supplier("") {}
    Stock(const QString& n, int q, double p, const QString& c, const QString& s)
        : name(n), quantity(q), price(p), category(c), supplier(s) {}
    private:
};

extern std::vector<Stock> stocks;


#endif
