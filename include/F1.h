#ifndef F1_H
#define F1_H


class F1
{
    public:
        F1();
        float f(int N,int m,float** D,int** X);
        bool subjectToOnlyOneVariable(int N, int m, int** X);
        bool subjectToBounds(int N, int m, int** X, int* L, int* U);
        virtual ~F1();

    protected:

    private:
};

#endif // F1_H
