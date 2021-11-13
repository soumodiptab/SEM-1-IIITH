/**
 * @file Q2.cpp
 * @author Soumodipta Bose
 * @brief External Merge Sort
 * @version 0.1
 * @date 2021-11-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <fstream>
#define LONG long long int
using namespace std;
const LONG BLOCK_SIZE = 100000;
const string TEMP_PATH = "./temp/";
const string TEMP_FILE = "tmp";
vector<LONG> temp_vector;
LONG total_file_data_count;
class priority_queue_custom
{
    vector<pair<LONG, LONG>> key_value;
    int max = -1;
    int parent(LONG index)
    {
        return (index - 1) / 2;
    }
    int left_child(LONG index)
    {
        return ((2 * index) + 1);
    }
    int right_child(LONG index)
    {
        return ((2 * index) + 2);
    }
    void max_heapify(LONG index)
    {
        LONG smallest = index;
        LONG l = left_child(index);
        LONG r = right_child(index);
        if (l <= max && key_value[l] < key_value[smallest])
        {
            smallest = l;
        }
        if (r <= max && key_value[r] < key_value[smallest])
        {
            smallest = r;
        }
        if (smallest != index)
        {
            key_value[index].swap(key_value[smallest]);
            max_heapify(smallest);
        }
    }
    void fix_heap_up(LONG index)
    {
        while (index > 0 && key_value[parent(index)] > key_value[index])
        {
            key_value[parent(index)].swap(key_value[index]);
            index = parent(index);
        }
    }
    void insert_key(pair<LONG, LONG> k_v)
    {
        max++;
        key_value.push_back(k_v);
        fix_heap_up(max);
    }
    void delete_min()
    {
        if (max == -1)
            return;
        if (max > 0)
        {
            key_value[0].swap(key_value[max]);
            max--;
            key_value.pop_back();
            max_heapify(0);
        }
        else
        {
            max--;
            key_value.pop_back();
        }
    }
    //-----------------------------------------------------------------------
public:
    pair<LONG, LONG> top()
    {
        return key_value[0];
    }
    void push(pair<LONG, LONG> ele)
    {
        insert_key(ele);
    }
    void pop()
    {
        delete_min();
    }
    bool empty()
    {
        if (max == -1)
        {
            return true;
        }
        return false;
    }
};
void merge(vector<LONG> &arr, LONG start, LONG mid, LONG end)
{
    //cout << "start=" << start << " end= " << end << " arr1=" << mid - start + 1 << " arr2=" << end - mid << endl;
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
    //cout << "";
}

void merge_sort(vector<LONG> &arr, LONG start, LONG end)
{
    if (start == end)
        return;
    int middle = start + (end - start) / 2;
    //cout << "mid=" << middle << endl;
    merge_sort(arr, start, middle);
    merge_sort(arr, middle + 1, end);
    merge(arr, start, middle, end);
}
LONG get_data_count(string filename)
{
    LONG data_count = 0;
    fstream file;
    string buffer;
    file.open(filename, ios::in);
    while (getline(file, buffer, ','))
    {
        data_count++;
    }
    file.close();
    return data_count;
}
void block_to_vector(fstream &file, LONG data_count)
{
    temp_vector.clear();
    string buffer = "";
    while (data_count--)
    {
        getline(file, buffer, ',');
        LONG val = stoll(buffer, nullptr, 10);
        temp_vector.push_back(val);
    }
}
void apply_merge_Sort()
{
    merge_sort(temp_vector, 0, temp_vector.size() - 1);
}
void create_temp_file(LONG offset)
{
    fstream file;
    string path = "";
    path.append(TEMP_FILE + to_string(offset));
    file.open(path, ios::out | ios::trunc);
    for (LONG number : temp_vector)
    {
        string number_string = to_string(number).append(",");
        file.write(number_string.c_str(), number_string.size());
    }
    file.close();
}
LONG create_sorted_blocks(string input)
{
    total_file_data_count = get_data_count(input);
    LONG blocks = total_file_data_count / BLOCK_SIZE;
    LONG last_block_count = total_file_data_count % BLOCK_SIZE;
    if (last_block_count)
        blocks += 1;
    else
        last_block_count = BLOCK_SIZE;
    fstream file;
    file.open(input, ios::in);
    LONG k = blocks;
    while (k--)
    {
        if (k != 0)
            block_to_vector(file, BLOCK_SIZE);
        else
            block_to_vector(file, last_block_count);
        sort(temp_vector.begin(), temp_vector.end());
        create_temp_file(blocks - k - 1);
    }
    file.close();
    return blocks;
}
void merge_blocks(string path, LONG blocks)
{
    priority_queue_custom pq = priority_queue_custom();
    fstream output_file;
    fstream temp_files[blocks];
    output_file.open(path, ios::out | ios::trunc);
    string buffer;
    LONG read_files = 0, current_data_count = 0;
    for (int i = 0; i < blocks; i++)
    {
        string temp_file_path = TEMP_FILE + to_string(i);
        temp_files[i].open(temp_file_path, ios::in);
        if (!getline(temp_files[i], buffer, ','))
            read_files++;
        else
            pq.push(make_pair(stoll(buffer), i));
    }
    while (read_files != blocks)
    {
        pair<LONG, LONG> item = pq.top();
        pq.pop();
        LONG block_number = item.second;
        string number_string = to_string(item.first);
        if (current_data_count < total_file_data_count - 1)
            number_string.append(",");
        output_file.write(number_string.c_str(), number_string.size());
        if (!getline(temp_files[block_number], buffer, ','))
            read_files++;
        else
            pq.push(make_pair(stoll(buffer), block_number));
        current_data_count++;
    }
    for (int i = 0; i < blocks; i++)
    {
        temp_files[i].close();
        remove((TEMP_FILE + to_string(i)).c_str());
    }
    output_file.close();
}
void external_sort(string input, string output)
{
    LONG blocks = create_sorted_blocks(input);
    merge_blocks(output, blocks);
}
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "Provide input output file" << endl;
        exit(1);
    }
    string input_file(argv[1]);
    string output_file(argv[2]);
    auto start_time = std::chrono::high_resolution_clock::now();
    external_sort(input_file, output_file);
    auto end_time = std::chrono::high_resolution_clock::now();
    cout << "Time elapsed:" << chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count() << "ms" << endl;
    return 0;
}