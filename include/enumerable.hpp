#pragma once

#include <memory>   // std::shared_ptr
#include <optional> // std::optional
#include <utility>  // std::declval
#include <vector>   // std::vector

namespace linqxx
{

template <typename T>
class enumerator
{
private:
    std::optional<T> item;

public:
    virtual std::optional<T> next() = 0;
    // bool move();
    // T current();
};

template <typename T>
class enumerable
{
public:
    virtual std::unique_ptr<enumerator<T>> enumerate() = 0;
    std::shared_ptr<enumerable<T>> where(bool (*pred)(const T &));
    template <typename TF>
    auto select(TF selector) -> std::shared_ptr<enumerable<decltype(selector(std::declval<const T &>))>>;
    std::vector<T> to_vector();
    void for_each(void (*action)(T &));

protected:
    virtual std::shared_ptr<enumerable<T>> share() = 0;
};
/*
template <typename T>
bool enumerator<T>::move()
{
    auto temp = next();
    if (temp)
    {
        item = temp;
        return true;
    }
    else
        return false;
};

template <typename T>
T enumerator<T>::current()
{
    return item.value();
};
*/

} // namespace linqxx