#ifndef F1_H
#define F1_H
#include <random>
#include <cstdlib>
using namespace std;
class F1
{
    public:
        F1();
        double f(int N,int m,float** D,int** X, int* L, int* U);
        bool subjectToOnlyOneVariable(int N, int m, int** X);
        bool subjectToBounds(int N, int m, int** X, int* L, int* U);
        int* solutionInistial(int N, int m, int* L, int* U);
        virtual ~F1();
        std::default_random_engine gen;
    protected:

    private:
};

#endif // F1_H
