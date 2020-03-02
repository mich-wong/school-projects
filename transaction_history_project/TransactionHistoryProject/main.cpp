//
//  main.cpp
//  project_3
//
//  Created by Michelle Wong on 2019-11-26.
//  Copyright © 2019 Michelle Wong. All rights reserved.
//

#include <iostream>
#include "project3.hpp"
#include "History_Transaction_definitions.hpp"

unsigned int Transaction::assigned_trans_id = 0;
int main() {
    
    History trans_history{};
    trans_history.read_history();
    std::cout << "[Starting history]:" << std::endl;
    trans_history.print();
    trans_history.sort_by_date();
    std::cout << "[Sorted ]:" << std::endl;
    trans_history.print();
    
    trans_history.update_acb_cgl();
    trans_history.print();
    std::cout << "[CGL for 2018 ]: " << trans_history.compute_cgl(2018) << std::endl;
    std::cout << "[CGL for 2019 ]: " << trans_history.compute_cgl(2019) << std::endl;
    
  
    return 0;

}

