#include <iostream>  
#include <iomanip>   
#include <string>    
#include <cstring>  
#include <vector>   
#include <array>     
#include <algorithm> 
#include <numeric>   
#pragma once
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
};
