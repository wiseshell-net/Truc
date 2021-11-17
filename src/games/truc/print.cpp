#include "headers/print.h"
#include <iostream>
#include <sstream>

std::string Print::title_blackjack(){
    // https://patorjk.com/software/taag/#p=display&f=Blocks&t=TRUC
    constexpr auto title_blackjack = R"(
 /$$$$$$$$ /$$$$$$$  /$$   /$$  /$$$$$$ 
|__  $$__/| $$__  $$| $$  | $$ /$$__  $$
   | $$   | $$  \ $$| $$  | $$| $$  \__/
   | $$   | $$$$$$$/| $$  | $$| $$      
   | $$   | $$__  $$| $$  | $$| $$      
   | $$   | $$  \ $$| $$  | $$| $$    $$
   | $$   | $$  | $$|  $$$$$$/|  $$$$$$/
   |__/   |__/  |__/ \______/  \______/ 
    )";

    std::ostringstream toReturn;
    toReturn << title_blackjack;
    return toReturn.str();

}

std::string Print::begin_menu(){
    constexpr auto begin_menu = R"(
            1 - Start a New Game
            2 - Load from Game
            3 - Statistics
            4 - How to Play
            5 - Exit
    )";
    
    std::ostringstream toReturn;
    toReturn << begin_menu;
    return toReturn.str();
}

std::string Print::statistics(){
    constexpr auto statistics = R"(
     ____  ____  __  ____  __  ____  ____  __  ___  ____ 
    / ___)(_  _)/ _\(_  _)(  )/ ___)(_  _)(  )/ __)/ ___)
    \___ \  )( /    \ )(   )( \___ \  )(   )(( (__ \___ \
    (____/ (__)\_/\_/(__) (__)(____/ (__) (__)\___)(____/
    )";
    
    std::ostringstream toReturn;
    toReturn << statistics << "\n\n";
    return toReturn.str();
}
    
std::string Print::instructions(){
    // TODO: Escriure Instruccions
    constexpr auto instructions = R"(
            FALTEN INSTRUCCIONS!
    )";

    std::ostringstream toReturn;
    toReturn << instructions;
    return toReturn.str();
}

std::string Print::bust(){
    constexpr auto bust = R"(
     ___            _    _ 
    | _ ) _  _  ___| |_ | |
    | _ \| || |(_-<|  _||_|
    |___/ \_,_|/__/ \__|(_)        
    )";

    std::ostringstream toReturn;
    toReturn << bust;
    return toReturn.str();
}

std::string Print::blackjack(){
    constexpr auto blackjack = R"(
     ___  _            _     _            _    _ 
    | _ )| | __ _  __ | |__ (_) __ _  __ | |__| |
    | _ \| |/ _` |/ _|| / / | |/ _` |/ _|| / /|_|
    |___/|_|\__,_|\__||_\_\_/ |\__,_|\__||_\_\(_)
                          |__/                   
    )";

    std::ostringstream toReturn;
    toReturn << blackjack;
    return toReturn.str();
}

std::string Print::dealer_wins(){
    constexpr auto dealer_wins = R"(
     ___           _                  _           
    |   \ ___ __ _| |___ _ _  __ __ _(_)_ _  ___  
    | |) / -_/ _` | / -_| '_| \ V  V | | ' \(_-<_ 
    |___/\___\__,_|_\___|_|    \_/\_/|_|_||_/__(_)                                            
    )";

    std::ostringstream toReturn;
    toReturn << dealer_wins;
    return toReturn.str();
}

std::string Print::you_win(){
    constexpr auto you_win = R"(
    __   __                    _        _ 
    \ \ / /___  _  _  __ __ __(_) _ _  | |
     \ V // _ \| || | \ V  V /| || ' \ |_|
      |_| \___/ \_,_|  \_/\_/ |_||_||_|(_)
    )";

    std::ostringstream toReturn;
    toReturn << you_win;
    return toReturn.str();
}

std::string Print::draw(){
    constexpr auto draw = R"(
     ___            _     _ 
    | _ \ _  _  ___| |_  | |
    |  _/| || |(_-<| ' \ |_|
    |_|   \_,_|/__/|_||_|(_)
    )";

    std::ostringstream toReturn;
    toReturn << draw;
    return toReturn.str();
}

std::string Print::dealer_border(){
    constexpr auto dealer_border = R"(
                     _  __ _     __ _ 
/)/)/)/)/)/)/)/)/)  | \|_ |_||  |_ |_)  /)/)/)/)/)/)/)/)/)
(/(/(/(/(/(/(/(/(/  |_/|__| ||__|__| \  (/(/(/(/(/(/(/(/(/  
    )";

    std::ostringstream toReturn;
    toReturn << dealer_border;
    return toReturn.str();
}

std::string Print::player_border(){
    constexpr auto player_border = R"(
                     _     _     __ _ 
/)/)/)/)/)/)/)/)/)  |_)|  |_|\/ |_ |_)  /)/)/)/)/)/)/)/)/)
(/(/(/(/(/(/(/(/(/  |  |__| | | |__| \  (/(/(/(/(/(/(/(/(/                          
    )";

    std::ostringstream toReturn;
    toReturn << player_border;
    return toReturn.str();
}
