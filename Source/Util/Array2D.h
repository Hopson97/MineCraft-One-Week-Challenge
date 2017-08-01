#ifndef ARRAY2D_H_INCLUDED
#define ARRAY2D_H_INCLUDED

#include <array>
#include <algorithm>

template<typename T, int WIDTH>
class Array2D
{
    using Array = std::array<T, WIDTH * WIDTH>;

    public:
        T& get(int x, int z) noexcept
        {
            return m_array[x * WIDTH + z];
        }

        const T& get(int x, int z) const noexcept
        {
            return m_array[x * WIDTH + z];
        }

        T& getMaxValue()
        {
            return *std::max_element(m_array.begin(), m_array.end());
        }

    private:
        Array m_array;
};


#endif // ARRAY2D_H_INCLUDED
