#include <bits/stdc++.h>
#include <cstring>
#ifndef EQUATION_H
#define EQUATION_H


class equation
{
    public:
        equation();
        char key;
        int num1;
        int num2;
        int num3;
        virtual ~equation();
        void getEquation(int level);

    protected:

    private:
};

#endif // EQUATION_H
