#pragma once
#include "Theme.h"
#include <string>
#include <vector>
#include <QColor>
#include <bits/stdc++.h> //reading text file
#include <filesystem>

class ThemeLoader{
public:
    /*
    static void get_local_themes(std::vector<std::string> &themes){
        for (const auto &file : std::filesystem::directory_iterator("./")){
            if(is_theme_file(file)){
                themes.push_back(path_to_name(file));
            }
        }
    }


	static Theme load_theme(std::string themeName){
        std::filesystem::path filePath = "theme_" + themeName + ".txt";
        std::ifstream themeFile = {};
		if(!themeFile.is_open()){
			return Theme::Default();
		}
		std::vector<std::string> lines;
        int expectedColors = static_cast<int>(sizeof(Theme) / sizeof(QColor) + 1);
        for(int i = 0; i < expectedColors; i++){
			std::string current;
			if(!getline(themeFile,current)) break;
			lines.push_back(current);
		}
		themeFile.close();

        if(lines.size() == 0) return Theme::Default();

        ArrayTheme outputTheme = {};
        int iter = 0;
        const int colorCount = lines.size() - 1;
        const int colorTotal = sizeof(Theme) / sizeof(QColor);
        for(;iter < colorCount; iter++){
            outputTheme.colors[iter] = QColor::fromString(lines[iter + 1])
        }
        if(iter != colorCount){
            ArrayTheme defAT = {Theme::Default()};
            for(;iter < colorTotal; iter++){
                outputTheme.colors[iter] = defAT.colors[iter];
            }
        }
        return outputTheme.t;
	}
    */
private:

    /*
    bool is_theme_file(auto file){
        return false;
    }
*/
}
