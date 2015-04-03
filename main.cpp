#include <algorithm>
#include <cstddef>
#include <utility>

template<typename T>
void tree_sort(T array[], std::size_t size) noexcept
{
    struct tree_t
    {
        tree_t(T &&_value = T())
        {
            left = right = nullptr;
            value = std::forward<T>(_value);
        }
 
        T* operator()(T array[])
        {
            if (this->left) array = this->left->operator()(array);
            *array++ = std::move(this->value);
            if (this->right) array = this->right->operator()(array);
            return array;
        }
 
        tree_t *left, *right;
        T value;
    } root(std::move(array[0]));
 
    for (std::size_t idx = 1; idx < size; idx++)
    {
        bool inserted = false;
        tree_t *p_root = &root;
        while (!inserted)
        {
            if (array[idx] < p_root->value)
            {
                if (p_root->left) p_root = p_root->left;
                else
                {
                    p_root->left = new tree_t(std::move(array[idx]));
                    inserted = true;
                }
            }
            else
            {
                if (p_root->right) p_root = p_root->right;
                else
                {
                    p_root->right = new tree_t(std::move(array[idx]));
                    inserted = true;
                }
            }
        }
    }
 
    root(array);
}

