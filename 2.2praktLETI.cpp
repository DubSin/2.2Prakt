#include <iostream>
#include <chrono>
#include <conio.h>
using namespace std;

struct List {
    int data;
    List* head;
    List* tail;
};

List *createList(int& length, bool manual)
{
    List *curr = 0,     
        *next = 0;    
    if (manual){
        cout << "Enter numbers: " << endl;
        int num;
        while((cin >> num) && num != 0)
        {
            curr = new List;
            curr -> data = num;
            curr -> tail = next;
            if (next) 
                next -> head = curr;
            next = curr;
            length++;
        }
        curr -> head = nullptr;
        return curr;
    }
    else{     
        for (int i = 1; i <= length; ++i)
        {
            curr = new List;
            curr -> data = rand() % 100;
            curr -> tail = next;
            if (next) 
                next -> head = curr;
            next = curr;
        }
        curr -> head = nullptr;
        return curr;
    }
}

void getList(List* list, int index){
    int count = 0;
    while (count < index)
    {
        list = list -> tail;
        count++;
    }
    cout << "Data under index: " << list -> data << endl;
    
}

void insertList(List* &list, int& length, int index, int data){
    List* head = list;
    if(index == 0){
        List *item = new List;
        list -> head = item;
        item -> head = nullptr;
        item -> data = data;       
        item -> tail = list;      
        list = item;
        length++;
        return;
    }
    if(index == length){
        while (list -> tail)
        {
            list = list -> tail;
        }
        List* item = new List;
        list -> tail = item;
        item -> head = list;
        item -> data = data;
        item -> tail = nullptr;
        list = head;
    }
    else{   
        while (list -> tail)
        {
            if (index == 0)
                break;
            list = list -> tail;
            index--;
        }
        List *item = new List;
        item -> tail = list;
        item -> head = list -> head;
        item -> data = data;
        list -> head -> tail = item;
        list -> head = item;
        list = head;
    }
    length++;
}

void swapList(List*& list, int index1, int index2){
    List* head = list;
    List* prev = new List;
    while(list->tail){
        if(index1 == 0)
            prev = list;
        if(index2 == 0){
            break;
        }
        list = list -> tail;
        index1--;
        index2--;
    }
    if(prev->head)  prev->head->tail = list;
    if(list->head)  list->head->tail = prev;
    if(prev->tail) prev->tail->head= list;
    if(list->tail) list->tail->head= prev;
    List* temp;
    temp = prev->head;
    prev->head = list->head;    
    list->head = temp;
    temp = prev->tail;
    prev->tail = list->tail;    
    list->tail = temp;
    if(index1 != 0 && index2 != 0)
        list = head;
}

void deleteList(List* &list, int& length, int index, bool bydata){
    List* head = list;
    if(bydata){ // поиск элемента для удаления через значения
        if(list -> data == index){  // элемент для удаления из списка в начале
            List* nhead = list -> tail;
            nhead -> head = nullptr;
            nhead -> tail = list -> tail -> tail;
            list = nhead;
            return;
        }
        bool found = false;
        List *prev = new List;
        while(list -> tail){
            if(list -> data == index){
                found = true;
                break;
            }
            prev = list;
            list = list -> tail;
        }
        if(found){
            if(list->tail){
                list = list -> tail; // элемент для удаления из списка в середине
                list -> head = prev;
                prev -> tail = list;
            }
            else{
                prev -> tail = nullptr; // элемент для удаления из списка в конце
            }
        }
        else
            cout << "Nothing matched" << endl;
        list = head;
    }
    else{
        if(index == 0){
            List* nhead = list -> tail;
            nhead -> head = nullptr;
            nhead -> tail = list -> tail -> tail;
            list = nhead;
            return;
        }
        else{
            List *prev = new List;
            while(list -> tail){
                if (index == 0)
                    break;
                prev = list;
                list = list -> tail;
                index--;
            }
        
            if(list->tail){
                list = list -> tail; // элемент для удаления из списка в середине
                list -> head = prev;
                prev -> tail = list;
            }
            else{
                prev -> tail = nullptr; // элемент для удаления из списка в конце
            }
        }
        list = head;
    }
    length--;
}

void showList(List* list){
    while (list){
        cout << list -> data << " ";
        list = list -> tail;
    }
    cout << endl;
}

void showArray(int *arr, int length){
    for(int i=0; i < length; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

void deleteArray(int*& arr, int& length, int index, bool bydata){
    int* arr2 = new int[--length];
    int count = 0;
    for(int i=0; i < length + 1; i++){
        if (i != index && !bydata){
            arr2[count] = arr[i];
            count++;
        }
        if(arr[i] != index && bydata){
            arr2[count] = arr[i];
            count++;
        }
    }
    delete [] arr;
    arr = arr2;
}

void getArray(int* arr, int index){
    cout << "Data under index: " << arr[index];
}

void swapArray(int*& arr, int index1, int index2){
    int temp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = temp; 
}

void insertArray(int*& arr, int& length, int index, int data){
    int* arr2 = new int[++length];
    int count = 0;
    for(int i=0; i < length; i++){
        if (i == index){
            arr2[i] = data;
        }
        else{
            arr2[i] = arr[count];
            count++;
        }
    }
    delete [] arr;
    arr = arr2;
}

void createArray(int*& arr, int& length, bool manual){
    if (manual){
        cout << "Enter numbers: " << endl;
        int num, count = 0, capacity = 1;
        while((cin >> num) && num != 0){
            if (count == capacity) {
                int *tempArray = new int[capacity * 2];
                for (int i = 0; i < count; ++i) {
                    tempArray[i] = arr[i];
                }
                delete[] arr;
                arr = tempArray;
                capacity *= 2;
            }
            arr[count++] = num;
        }
    length = count;   
    }
    else{
        for (int i=0; i < length; i++){
            arr[i] = rand() % 100;
        }
    }   
}


void idz(int* arr, List* &list, int& arrLength, int& listLength){
    cout << "Array before: ";
    showArray(arr, arrLength);
    cout << "List before: ";
    showList(list);
    for(int i=0; i<arrLength; i++){
        arr[i] += rand() % 5;
        if(arr[i] > 0){
            insertList(list, listLength, listLength, arr[i]);
        }
    }
    cout << "Array after: ";
    showArray(arr, arrLength);
    cout << "List after: ";
    showList(list);

}

int main(){
    srand(time(0));
    char platform = 's';
    int arrLength = 0, listLength = 0;
    List* list;
    int* array;
    while (platform != 'e'){
        system("cls");
        cout << "1)Linked list" << endl;
        cout << "2)Dynamic array" << endl;
        cout << "3)IDZ(6)" << endl;
        cout << "Choose your platform(e - exit): ";
        cin >> platform;
        switch (platform){
            case '1':{
                char action = 's';
                while (action != 'b')
                {
                    system("cls");
                    cout << "1)Create object" << endl;
                    cout << "2)Insert data" << endl;
                    cout << "3)Delete data" << endl;
                    cout << "4)Get data" << endl;
                    cout << "5)Swap elements" << endl;
                    cout << "Choose your action(b - change platform): ";
                    cin >> action;
                    switch (action){
                        case '1':{
                            bool manual = false;
                            cout << "Input length(input 0 for manual entry): ";
                            cin >> listLength; 
                            if (listLength == 0){
                                manual = true;
                            }
                            auto start_time_create = chrono::steady_clock::now();
                            list = createList(listLength, manual);
                            auto end_time_create = chrono::steady_clock::now();
                            auto run_time_create = chrono::duration_cast<chrono::nanoseconds>(end_time_create - start_time_create);
                            showList(list);
                            cout << "Operation execution time: " << run_time_create.count() << "ns" << endl; 
                            getch();
                            break;
                        }
                        case '2':{
                            int index, data;
                            cout << "Input index: ";
                            cin >> index;
                            cout << "Input data: ";
                            cin >> data;
                            if(listLength != 0 && (index <= listLength && index >= 0)){
                                auto start_time_insert = chrono::steady_clock::now();
                                insertList(list, listLength, index, data);
                                auto end_time_insert = chrono::steady_clock::now();
                                auto run_time_insert = chrono::duration_cast<chrono::nanoseconds>(end_time_insert - start_time_insert);
                                showList(list);
                                cout << "Operation execution time: " << run_time_insert.count() << "ns" << endl; 
                            }
                            else{
                                cout << "Array not initialized or wrong index";
                            }
                            getch();
                            break;
                        }
                        case '3':{
                            bool bydata=false;
                            int index, data = -1;
                            cout << "Input index(-1 - if you delete by data): ";
                            cin >> index;
                            if (index == -1){
                                cout << "Input data: ";
                                cin >> data;
                                bydata = true;
                            }
                            if(listLength != 0 &&  ((index >= -1 && index < listLength) || data != -1)){
                                auto start_time_delete = chrono::steady_clock::now();
                                if (bydata)
                                    deleteList(list, listLength, data, bydata);
                                else
                                    deleteList(list, listLength, index, bydata);
                                auto end_time_delete = chrono::steady_clock::now();
                                auto run_time_delete = chrono::duration_cast<chrono::nanoseconds>(end_time_delete - start_time_delete);
                                showList(list);
                                cout << "Operation execution time: " << run_time_delete.count() << "ns" << endl; 
                            }
                            else{
                                cout << "Array not initialized or wrong index";
                            }
                            getch();
                            break;
                        }
                        case '4':{
                            int index;
                            cout << "Input index: ";
                            cin >> index;
                            if(listLength != 0 && (index < listLength && index >= 0)){
                                auto start_time_get = chrono::steady_clock::now();
                                getList(list, index);
                                auto end_time_get = chrono::steady_clock::now();
                                auto run_time_get = chrono::duration_cast<chrono::nanoseconds>(end_time_get - start_time_get);
                                cout << endl;
                                cout << "Operation execution time: " << run_time_get.count() << "ns" << endl; 
                            }
                            else{
                                cout << "list not initialized or wrong index";
                            }
                            getch();
                            break;
                        }
                        case '5':{
                            int index1, index2;
                            cout << "Input index1: ";
                            cin >> index1;
                            cout << "Input index2: ";
                            cin >> index2;
                            if(listLength != 0 && (index1 < listLength && index1 >= 0) && (index2 < listLength && index2 >= 0) && (index1 != index2)){
                                auto start_time_swap = chrono::steady_clock::now();
                                if (index1 > index2)
                                    swapList(list, index2, index1);
                                else
                                    swapList(list, index1, index2);
                                auto end_time_swap = chrono::steady_clock::now();
                                auto run_time_swap = chrono::duration_cast<chrono::nanoseconds>(end_time_swap - start_time_swap);
                                showList(list);
                                cout << "Operation execution time: " << run_time_swap.count() << "ns" << endl; 
                            }
                            else{
                                cout << "Array not initialized or wrong indexs";
                            }
                            getch();
                            break;
                        }
                    }
                }
                break;
            }
            case '2':{
                char action = 's';
                while (action != 'b')
                {
                    system("cls");
                    cout << "1)Create object" << endl;
                    cout << "2)Insert data" << endl;
                    cout << "3)Delete data" << endl;
                    cout << "4)Get data" << endl;
                    cout << "5)Swap elements" << endl;
                    cout << "Choose your action(b - change platform): ";
                    cin >> action;
                    switch (action){
                        case '1':{
                            bool manual = false;
                            cout << "Input length(input 0 for manual entry): ";
                            cin >> arrLength; 
                            if (arrLength <= 0){
                                manual = true;
                                arrLength = 1;
                            }
                            auto start_time_create = chrono::steady_clock::now();
                            array = new int[arrLength];
                            createArray(array, arrLength, manual);
                            auto end_time_create = chrono::steady_clock::now();
                            auto run_time_create = chrono::duration_cast<chrono::nanoseconds>(end_time_create - start_time_create);
                            showArray(array, arrLength);
                            cout << "Operation execution time: " << run_time_create.count() << "ns" << endl; 
                            getch();
                            break;
                        }
                        case '2':{
                            int index, data;
                            cout << "Input index: ";
                            cin >> index;
                            cout << "Input data: ";
                            cin >> data;
                            if(arrLength != 0 && (index <= arrLength && index >= 0)){
                                auto start_time_insert = chrono::steady_clock::now();
                                insertArray(array, arrLength, index, data);
                                showArray(array, arrLength);
                                auto end_time_insert = chrono::steady_clock::now();
                                auto run_time_insert = chrono::duration_cast<chrono::nanoseconds>(end_time_insert - start_time_insert);
                                cout << "Operation execution time: " << run_time_insert.count() << "ns" << endl; 
                            }
                            else{
                                cout << "Array not initialized or wrong index";
                            }
                            getch();
                            break;
                        }
                        case '3':{
                            bool bydata=false;
                            int index, data = -1;
                            cout << "Input index(-1 - if you delete by data): ";
                            cin >> index;
                            if (index == -1){
                                cout << "Input data: ";
                                cin >> data;
                                bydata = true;
                            }
                            if(arrLength != 0 && ((index < arrLength && index >= -1) || data != -1)){
                                auto start_time_delete = chrono::steady_clock::now();
                                if (bydata)
                                    deleteArray(array, arrLength, data, bydata);
                                else
                                    deleteArray(array, arrLength, index, bydata);
                                auto end_time_delete = chrono::steady_clock::now();
                                auto run_time_delete = chrono::duration_cast<chrono::nanoseconds>(end_time_delete - start_time_delete);
                                showArray(array, arrLength);
                                cout << "Operation execution time: " << run_time_delete.count() << "ns" << endl; 
                            }
                            else{
                                cout << "Array not initialized or wrong index";
                            }
                            getch();
                            break;
                        }
                        case '4':{
                            int index;
                            cout << "Input index: ";
                            cin >> index;
                            if(arrLength != 0 && (index < arrLength && index >= 0)){
                                auto start_time_get = chrono::steady_clock::now();
                                getArray(array, index);
                                auto end_time_get = chrono::steady_clock::now();
                                auto run_time_get = chrono::duration_cast<chrono::nanoseconds>(end_time_get - start_time_get);
                                cout << endl;
                                cout << "Operation execution time: " << run_time_get.count() << "ns" << endl; 
                            }
                            else{
                                cout << "Array not initialized or wrong index";
                            }
                            cout << endl;
                            getch();
                            break;
                        }
                        case '5':{
                            int index1, index2;
                            cout << "Input index1: ";
                            cin >> index1;
                            cout << "Input index2: ";
                            cin >> index2;
                            if(arrLength != 0 && (index1 < arrLength && index1 >= 0) && (index2 < arrLength && index2 >= 0) && (index1 != index2)){
                                auto start_time_swap = chrono::steady_clock::now();
                                swapArray(array, index1, index2);
                                auto end_time_swap = chrono::steady_clock::now();
                                auto run_time_swap = chrono::duration_cast<chrono::nanoseconds>(end_time_swap - start_time_swap);
                                showArray(array, arrLength);
                                cout << "Operation execution time: " << run_time_swap.count() << "ns" << endl; 
                            }
                            else{
                                cout << "Array not initialized or wrong index";
                            }
                            cout << endl;
                            getch();
                            break;
                        }
                    }
                }
                break;
            }
            case '3':{
                if(arrLength > 0 and listLength > 0){
                    idz(array, list, arrLength, listLength);
                }
                else{
                    cout << "Array or list not initialized" << endl;
                }
                getch();
                break;
            }
        } 
    }
    delete [] array;
    list = nullptr;
    return 0;
}