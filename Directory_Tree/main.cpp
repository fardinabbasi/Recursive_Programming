#include <iostream>
#include <vector>
#include <string>

using namespace std;

const string indent_type1(3,' '), indent_type2 = "|  ", file_pre = "|__";

struct directory{
    string name;
    vector<int> children;
};

void read_input(vector<directory> &dirs);
void print_tree(const vector<directory> &dirs, const int max_depth, int depth = 0, string indent = "", int id = 0, bool last_child = false);

int main(){
    int num_dirs, max_depth;
    cin >> num_dirs >> max_depth;

    vector<directory> dirs(num_dirs+1);
    read_input(dirs);

    print_tree(dirs, max_depth);

    return 0;
}

void print_tree(const vector<directory> &dirs, const int max_depth, int depth, string indent, int id, bool last_child){
    if (depth > max_depth)
        return;

    string extra_indent = "";

    if (id != 0){
        cout << indent << file_pre << dirs[id].name << endl;
        if (last_child)
            extra_indent = indent_type1;
        else
            extra_indent = indent_type2;
    }

    for (size_t j = 0; j < dirs[id].children.size(); j++){
        if (j+1 == dirs[id].children.size())
            last_child = true;
        else
            last_child = false;
        print_tree(dirs, max_depth, depth+1, indent + extra_indent, dirs[id].children[j], last_child);
    }

    return;
}

void read_input(vector<directory> &dirs){
    string item_name;
    int parent;
    for (size_t i=1; i < dirs.size(); i++){
        cin >> item_name >> parent;

        dirs[i].name = item_name;
        dirs[parent].children.push_back(i);
    }
    return;
}