void mx_sort(int* nums, int size, int& op, int& chg){
    for(int i = size - 1; i >= 0; --i){
        int cur_el = nums[i];
        int mx = nums[i];
        int ind = i;

        for(int j = 0; j < i; ++j){
            if(nums[j] > mx){
                mx = nums[j];
                ind = j;
            }
            op++;
        }

        nums[i] = mx;
        nums[ind] = cur_el;

        if(i != ind) chg++;
    }
}

void bubble_sort(int* nums, int size, int& op, int& chg){
    for(int i = 0; i < size; ++i){
        bool flag = false;
        for(int j = 0; j < size - i - 1; ++j){
            if(nums[j] > nums[j + 1]){
                std::swap(nums[j], nums[j + 1]);
                chg++;
                flag = true;
            }
            op++;
        }

        if(!flag) break;
    }
}

void print_array(int* nums, int size){
    for(int i = 0; i < size; ++i){
        std::cout << nums[i] << " ";
    }

    std::cout << std::endl;
    std::cout << std::endl;
}

void reverse_array(int* nums, int size){
    for(int i = 0; i < size / 2; ++i){
        int ind = size - i - 1;
        std::swap(nums[i], nums[ind]);
    }
}

void fill_array(int* nums, int size){
    for(int i = 0; i < size; ++i){
        int new_el = rand() % 201 - 100;
        nums[i] = new_el;
    }
}

void copy_array(int* nums_copy, int* nums, int size){
    for(int i = 0; i < size; ++i){
        nums_copy[i] = nums[i];
    }
}

void step(int size){
    int op = 0, chg = 0;

    int* a = new int[size]; fill_array(a, size);
    int* a_copy = new int[size]; copy_array(a_copy, a, size);

    std::cout << size << " элэментов" << std::endl;

    mx_sort(a, size, op, chg);
    std::cout << "mx_sorted with " << chg << " changes done and with " << op << " operations done" << std::endl << std::endl;
    op = 0; chg = 0;

    bubble_sort(a_copy, size, op, chg);
    std::cout << "bubble_sorted with " << chg << " changes done and with " << op << " operations done" << std::endl << std::endl;
    op = 0; chg = 0;

    delete[] a;
    delete[] a_copy;
}
