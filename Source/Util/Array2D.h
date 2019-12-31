#ifndef ARRAY2D_H_INCLUDED
#define ARRAY2D_H_INCLUDED

#include <algorithm>
#include <array>

template <typename T, int WIDTH> class Array2D {
    using Array = std::array<T, WIDTH * WIDTH>;

  public:
    T &get(int x, int z)
    {
        return m_array[x * WIDTH + z];
    }

    const T &get(int x, int z) const
    {
        return m_array[x * WIDTH + z];
    }

    T &getMaxValue()
    {
        return *std::max_element(m_array.begin(), m_array.end());
    }

    void setAll(T val)
    {
        m_array.fill(val);
    }

  private:
    Array m_array;
};

#endif // ARRAY2D_H_INCLUDED
