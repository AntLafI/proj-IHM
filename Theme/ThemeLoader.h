#ifndef THEMELOADER_H
#define THEMELOADER_H
#include "Theme.h"
#include <string>
#include <vector>
#include <QColor>
#include <bits/stdc++.h> //reading text file
#include <filesystem>

class ThemeLoader{
private:
    static bool is_theme_file(std::filesystem::directory_entry file, std::string &filenameOut){
        if(!file.is_regular_file()) return false;
        if(file.path().extension() != ".txt") return false;
        auto pathStr = file.path().filename().string();
        const std::string prefix = "theme_";
        if(pathStr.rfind(prefix,0) == 0){
            filenameOut = pathStr.substr(prefix.size());
            return true;
        }
        return false;
    }
public:

    static void get_local_themes(std::vector<std::string> &themes){
        for (const auto &file : std::filesystem::directory_iterator("./")){
            std::string filename;
            if(is_theme_file(file,filename)){
                themes.push_back(filename);
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
            outputTheme.colors[iter] = QColor::fromString(lines[iter + 1]);
        }
        if(iter != colorCount){
            ArrayTheme defAT = {Theme::Default()};
            for(;iter < colorTotal; iter++){
                outputTheme.colors[iter] = defAT.colors[iter];
            }
        }
        return outputTheme.t;
	}

};
#endif
