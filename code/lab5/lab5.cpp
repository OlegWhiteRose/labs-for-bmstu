#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "methods.h"
#include "headers.h"

int main(){

    setlocale(LC_ALL, "Russian");

    srand(time(NULL));

    int size = 5;
    int* nums = new int[size]; fill_array(nums, size);
    int* nums_copy = new int[size]; copy_array(nums_copy, nums, size);
    int op = 0, chg = 0;

    //1
    std::cout << "Начальный этап" << std::endl;
    std::cout << "begin_array: ";

    print_array(nums, size);

    mx_sort(nums, size, op, chg);
    std::cout << "mx_sorted with " << chg << " changes done and with " << op << " operations done: " << std::endl;
    op = 0; chg = 0;

    print_array(nums, size);

    bubble_sort(nums_copy, size, op, chg);
    std::cout << "bubble_sorted with " << chg << " changes done and with " << op << " operations done: " << std::endl;
    op = 0; chg = 0;

    print_array(nums_copy, size);
    //

    //2
    std::cout << "Проходимся по отсортированному массиву" << std::endl;
    std::cout << "begin_array: ";

    print_array(nums, size);

    mx_sort(nums, size, op, chg);
    std::cout << "mx_sorted with " << chg << " changes done and with " << op << " operations done: " << std::endl;
    op = 0; chg = 0;

    print_array(nums, size);

    bubble_sort(nums_copy, size, op, chg);
    std::cout << "bubble_sorted with " << chg << " changes done and with " << op << " operations done: " << std::endl;
    op = 0; chg = 0;

    print_array(nums_copy, size);
    //

    //3
    reverse_array(nums, size);
    reverse_array(nums_copy, size);

    std::cout << "Переворачиваем отсортированный массив" << std::endl;
    std::cout << "begin_array: ";

    print_array(nums, size);

    mx_sort(nums, size, op, chg);
    std::cout << "mx_sorted with " << chg << " changes done and with " << op << " operations done: " << std::endl;
    op = 0; chg = 0;

    print_array(nums, size);

    bubble_sort(nums_copy, size, op, chg);
    std::cout << "bubble_sorted with " << chg << " changes done and with " << op << " operations done: " << std::endl;
    op = 0; chg = 0;

    print_array(nums_copy, size);
    //

    delete[] nums;
    delete[] nums_copy;

    std::cout << "С разным количеством элементов" << std::endl;

    //10
    size = 10;
    step(size);
    //

    //100
    size = 100;
    step(size);
    //

    //1000
    size = 1000;
    step(size);
    //
}
