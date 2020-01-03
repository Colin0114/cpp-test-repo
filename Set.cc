#include <string>
#include <set>
#include <map>
#include <iostream>

// set 不支持下标访问，而 map 支持
// set 和 map 底层存储结构都是 RB-Tree
int main(){

    std::set<std::string> my_set;
    my_set.insert(my_set.begin(), std::string("hello, "));
    my_set.insert("my ");
    my_set.insert("world, ");
    my_set.insert("glad ");
    my_set.insert("to ");
    my_set.insert("see ");
    my_set.insert("you.");
   
    for(auto iter = my_set.begin(); iter!=my_set.end(); iter++){
        std::cout << *iter ;
    } // "glad hello, my see to world, you." 

    std::cout << std::endl;


    std::map<std::string, int> my_map;
    my_map.insert(std::pair<std::string, int>("hello, ", 1));
    my_map.insert(std::pair<std::string, int>("my ", 2));
    my_map.insert(std::pair<std::string, int>("world, ", 3));
    my_map.insert(std::pair<std::string, int>("glad ", 4));
    my_map.insert(std::pair<std::string, int>("to ", 5));
    my_map.insert(std::pair<std::string, int>("see ", 6));
    my_map.insert(std::pair<std::string, int>("you.", 7));

    for(auto iter = my_map.begin(); iter!=my_map.end(); iter++){
        std::cout << (iter->first) ;
    } // same as set: "glad hello, my see to world, you." 

    std::cout << std::endl;

    //output 4
    std::cout << "my_map[\"glad \"]: " << my_map[std::string("glad ")] << std::endl;

    return 0;
}
