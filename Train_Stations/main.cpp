#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct tour{
    vector<vector<int>> trains;
    int src_train, src_sta, dest_train, dest_sta;
};

const int step_delay = 1, change_delay = 2;

void read_input(tour &inf, vector<vector<bool>> &visit_flag);
int find_shortest_path (tour &inf, vector<vector<bool>> visit_flag, int curr_train, int curr_sta, int time = 0);
int min_time(int time1, int time2, int time3);
int pos_in_vec(const vector<int> &train, int element);

int main(){
    int num_trains;
    cin >> num_trains;

    tour inf;
    inf.trains.resize(num_trains);
    vector<vector<bool>> visit_flag(num_trains);

    read_input(inf, visit_flag);

    int time = find_shortest_path(inf, visit_flag, inf.src_train-1, inf.src_sta-1);
    cout << time << endl;
    return 0;
}

int pos_in_vec(const vector<int> &train, int element){
    auto it = find(train.begin(), train.end(), element);
    if (it != train.end()) {
        int position = distance(train.begin(), it);
        return position;
    } else {
        cout << "Element not found" << endl;
    }
    return -1;
}

int min_time(int time1, int time2, int time3){
    vector<int> arr = {time1, time2, time3};
    int time;
    for (auto it = arr.begin(); it != arr.end();) {
        if (*it < 0)
            it = arr.erase(it);
        else
            ++it;
    }
    auto min_element_it = min_element(arr.begin(), arr.end());
    if (min_element_it != arr.end())
        time = *min_element_it;
    else
        time = -1;
    
    return time;
}

int find_shortest_path (tour &inf, vector<vector<bool>> visit_flag, int curr_train, int curr_sta, int time){
    int time1 = -1, time2 = -1, time3 = -1;
    visit_flag[curr_train][curr_sta] = true;
    if (curr_sta+1 == inf.dest_sta && curr_train+1 == inf.dest_train)
        return time;

    int joint_train = inf.trains[curr_train][curr_sta];
    if (joint_train != 0){
        int joint_sta = pos_in_vec(inf.trains[joint_train-1], curr_train+1);
        if (!visit_flag[joint_train-1][joint_sta]){
            time1 = change_delay + time;
            time1 = find_shortest_path(inf, visit_flag, joint_train-1, joint_sta, time1);
        }
    }
    time += step_delay;

    if (curr_sta+1 != inf.trains[curr_train].size() && !visit_flag[curr_train][curr_sta+1])
        time2 = find_shortest_path(inf, visit_flag, curr_train, curr_sta+1, time);

    if (curr_sta != 0 && !visit_flag[curr_train][curr_sta-1])
        time3 = find_shortest_path(inf, visit_flag, curr_train, curr_sta-1, time);

    time = min_time(time1, time2, time3);
    return time;
}

void read_input(tour &inf, vector<vector<bool>> &visit_flag){
    int num_stations, station;
    for (size_t i=0; i < inf.trains.size(); i++){
        cin >> num_stations;
        for (int j=0; j < num_stations; j++){
            cin >> station;

            inf.trains[i].push_back(station);
            visit_flag[i].push_back(false);
        }
    }
    cin >> inf.src_train >> inf.src_sta >> inf.dest_train >> inf.dest_sta;
    return;
}