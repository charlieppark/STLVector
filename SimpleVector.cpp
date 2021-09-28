/**
 * Title    : HW1.cpp
 * Date     : 21.09.12
 * By       : Park Chan Ho
 * 
 * Tested on
 *  gcc version 9.3.0 (Ubuntu 9.3.0-17ubuntu1~20.04)
 *  gcc version 9.2.0 (Windows mingw64)
 *  Visual Studio (Visual C++ 2019 Debug x86)
 */

#include <iostream> // std::cout, std::initializer_list
#include <algorithm> // for_each, std::copy
#include <array> // std::array
#include <random> // std::mt19937, std::normal_distribution

class Vector {
private:
    // top for the last element in Vector
    size_t top;

    // available max size of array
    size_t size;

    float* array;

    /**
     * Vector class is dynamically reallocated
     * when a new element being pushed back at
     * an index that exceeds the size of Vector
     */
    void resize()
    {
        float* new_array = new float[size + 32]; // resizing by adding 32 to size

        // copying every element
        for (int i = 0; i < size; i++)
        {
            new_array[i] = array[i];
        }

        // deleting old array;
        delete[] array;

        array = new_array;

        return;
    }

public:
    // no arguments constructor
    Vector()
    {
        top = -1;
        size = 32;
        array = new float[size] {0, };
    }

    // constructor for {} initialization
    Vector(std::initializer_list<float> I)
    {
        top = I.size() - 1;

        if (top > 32)
        {
            size = (I.size() / 32 + 1) * 32;
        }
        else
        {
            size = 32;
        }

        array = new float[size];
        std::copy(I.begin(), I.end(), array);
    }

    // constructor when using std::array
    template<size_t arrSize>
    Vector(std::array<float, arrSize> newArray)
    {
        top = arrSize - 1;

        if (top > 32)
        {
            size = (arrSize / 32 + 1) * 32;
        }
        else
        {
            size = 32;
        }

        array = new float[size];
        std::copy(newArray.begin(), newArray.end(), array);
    }

    // to push back an element
    void push(float num)
    {
        top++;

        if (top == size)
        {
            this->resize();
        }
        
        array[top] = num;
    }

    // to modify a data at an index
    void modify(size_t idx, float data)
    {
        if (idx >= top)
        {
            std::cout << "ERROR : INDEX OVER TOP";
            return;
        }

        array[idx] = data;
    }

    // to check the size of Vector
    size_t getSize() const
    {
        return size;
    }

    // to check the top of Vector
    size_t getTop() const
    {
        return top;
    }

    // find element at an index
    float at(int i) const
    {
        if (i >= size)
        {
            std::cout << "ERROR : OVER THE VECTOR SIZE";
            throw NULL;
        }

        return array[i];
    }

    // multiply all elements in a vector by a scalar
    void multiply(float s)
    {
        for (int i = 0; i < size; i++)
        {
            array[i] *= s;
        }
    }

    // show all elements in a vector (1, 2, ...)
    void display()
    {
        std::cout << "\n(" << *array;
        std::for_each(array + 1, array + top + 1, [](float& array){ std::cout << ", " << array; });
        std::cout << ")\n";
    }

    // destructor
    ~Vector()
    {
        delete[] array;
    }
};

// Test Code
int main()
{
    // to put random number in vector
    std::mt19937 gen(310);
    std::normal_distribution<float> dist(0, 1);


    Vector v1 = Vector();

    for (int i = 0; i < 20; i++)
    {
        v1.push(dist(gen));
    }
    v1.display();

    // check if it works after exceeding the size of v1
    for (int i = 0; i < 20; i++)
    {
        v1.push(dist(gen));
    }
    v1.display();


    // modifying the value at index 3
    v1.modify(3, 2.2);
    v1.display();


    v1.multiply(1.2);    
    v1.display();

    // initializing by using {}
    Vector v2 = {1.2, 2.3, 3.4};
    v2.display();

    // multiply by scalar
    v2.multiply(2.0);
    v2.display();

    // initializing by std::array
    std::array<float, 4> arr = {1.3, 2.4, 3.5, 3.2};
    Vector v3 = Vector(arr);
    v3.display();

}