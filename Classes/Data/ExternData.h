
#ifndef _ExternData_h_
#define _ExternData_h_
#include <iostream>



class PlayerData
{
public:
    std::string player_name;
    std::string player_role;
    int         player_id;
    
    PlayerData(std::string name, std::string role, int id) : player_name(name), player_role(role), player_id(id){}
    
};


#endif /* ExternData_h */

