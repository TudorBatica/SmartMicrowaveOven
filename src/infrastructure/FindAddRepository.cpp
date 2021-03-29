#include "FindAddRepository.h"

namespace Infrastructure
{
    template <typename T>
    std::vector<T> FindAddRepository<T>::findAll()
    {
        return entities;
    }

    template <typename T>
    void FindAddRepository<T>::add(T entity)
    {
        entities.push_back(entity);
    }
}