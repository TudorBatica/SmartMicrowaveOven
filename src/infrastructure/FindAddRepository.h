#pragma once
#include <vector>

namespace Infrastructure
{
    template <typename T>
    class FindAddRepository
    {
    public:
        std::vector<T> findAll();
        void add(T entity);

    protected:
        std::vector<T> entities;
    };
}