#pragma once
#include <algorithm>
#include "iterator.h"

template <class T>
class stack
{
public:
    stack()
    {
        capacity = 1;
        size = 0;
        mem = std::shared_ptr<T[]>(new T[1]);
    }
    
    stack(int a)
    {
        capacity = a+1; 
        size = a;
        mem = std::shared_ptr<T[]>(new T[a]);
    }

    stack(int newsize,stack<T>& cpb)
    {
        capacity = newsize;
        size = cpb.size;
        mem = std::shared_ptr<T[]>(new T[capacity]);

        for (int i = 0; i < std::min(cpb.size, size); ++i)
        {
            mem[i] = cpb.mem[i];
        }
    }

    ~stack()
    {
        capacity = 1;
        size = 0; 
    }

    void replicate(stack<T>& cpb)
    {
        capacity = cpb.capacity;
        size = cpb.size;
        mem = std::shared_ptr<T[]>(new T[capacity]);

        for (int i = 0; i < std::min(cpb.size,size); ++i)
        {
            mem[i] = cpb.mem[i];
        }
    }

    int push(T &inp)
    {
        if (size+1 >= capacity)
        {
            stack<T> stc(capacity*2, *this);
            stc.push(inp);
            this->replicate(stc);
        }
        else
        {
            mem[size] = inp;
            ++size;
        }

        return 1;
    }

    int pop()
    {
        try
        {
            if (size < 1)
            {
                throw 10;//out of bounds
            }

            if (size * 2 <= capacity)
            {
                stack<T> stc(capacity / 2, *this);
                stc.pop();
                this->replicate(stc);
                //destroy(stc);
            }
            else
            {
                //mem[size] = nullptr;
                --size;
            }
            return 0;
        }

        catch (int er)
        {
            return er;
        }
    }

    int insert(iterator<T> iter,T &inp)
    {
        try
        {
            if (iter->get_position() > size || iter->get_position() < 0)
            {
                throw 10;
            }

            int pos = iter.get_position();
            stack<T> stc(0);
            for (int i = 0; i < size; ++i)
            {
                if (i < pos)
                {
                    stc.push(mem[i]);
                }
                else
                {
                    if (i == pos)
                    {
                        stc.push(inp);
                    }

                    stc.push(mem[i + 1]);
                }

            }
            this->replicate(stc);

            return 1;
        }
        
        catch (int er)
        {
            return er;
        }
    }

    int erase(iterator<T> iter)
    {
        try
        {
            if (iter.get_position() > size || iter.get_position() < 0)
            {
                throw 10;
            }

            int pos = iter.get_position();
            stack<T> stc(0);
            for (int i = 0; i < size; ++i)
            {
                if (i == pos)
                {
                    continue;
                }
                stc.push(mem[i]);
            }
            this->replicate(stc);

            return 0;
        }

        catch (int er)
        {
            return er;
        }  
    }

    int get_size()
    {
        return size;
    }

    int get_capacity()
    {
        return capacity;
    }

    std::weak_ptr<T> top()
    {
        if (size > 0)
        {
            std::cout << "\t" << " rt " << size << " <-size|capacity-> " << capacity << std::endl;
            return std::weak_ptr<T> (&mem[size-1]);
        }
        else
        {
            return std::weak_ptr<T> (nullptr);
        }
    }

    iterator<T> begin()
    {
        return iterator<T>(&mem[0],0);
    }

    iterator<T> end()
    {
        return iterator<T>(&mem[size],size);
    }

private:
    int capacity;
    int size; 
    std::shared_ptr<T[]> mem;
};