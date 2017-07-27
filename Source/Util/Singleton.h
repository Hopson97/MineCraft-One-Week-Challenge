#ifndef SINGLETON_H_INCLUDED
#define SINGLETON_H_INCLUDED

class Singleton
{
    public:
        Singleton(const Singleton&) = delete;
        Singleton(Singleton&&) = delete;

        Singleton& operator=(const Singleton&) = delete;
        Singleton& operator=(Singleton&&) = delete;

    protected:
        Singleton() = default;
};

#endif // SINGLETON_H_INCLUDED
