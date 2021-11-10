#include <iostream>
#include <vector>
#define LONG long long int
using namespace std;
void print_state(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << arr[i];
        if (i < size - 1)
            cout << " | ";
    }
    cout << endl;
}
void merge(vector<LONG> &arr, LONG start, LONG mid, LONG end)
{
    cout << "start=" << start << " end= " << end << " arr1=" << mid - start + 1 << " arr2=" << end - mid << endl;
    LONG arr1[mid - start + 1];
    LONG arr2[end - mid];
    for (LONG i = 0; i <= (mid - start); i++)
        arr1[i] = arr[start + i];
    for (LONG i = 0; i < (end - mid); i++)
        arr2[i] = arr[mid + 1 + i];
    LONG i, l = 0, r = 0;
    for (i = start; i <= end && l < mid - start + 1 && r < end - mid; i++)
    {
        if (arr1[l] <= arr2[r])
        {
            arr[i] = arr1[l++];
        }
        else
        {
            arr[i] = arr2[r++];
        }
    }
    for (; l < mid - start + 1; l++)
        arr[i++] = arr1[l];
    for (; r < end - mid; r++)
        arr[i++] = arr2[r];
    cout << "";
}

void merge_sort(vector<LONG> &arr, LONG start, LONG end)
{
    if (start == end)
        return;
    int middle = start + (end - start) / 2;
    cout << "mid=" << middle << endl;
    merge_sort(arr, start, middle);
    merge_sort(arr, middle + 1, end);
    merge(arr, start, middle, end);
}
int main()
{
    vector<LONG> arr = {10, 9, 1, 8, 7, 2, 3, 13, 6, 1, 7, 6, 5, 4, 11};
    merge_sort(arr, 0, arr.size()-1);
    cout << "hello";
    return 0;
}