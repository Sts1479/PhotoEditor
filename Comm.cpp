/*
 * Comm.cpp
 *
 *  Created on: Apr 16, 2019
 *      Author: root
 */
#include "Comm.hpp"
#include <stdlib.h>
#include "utils/StringUtils.hpp"
#include "ImageOpers.hpp"
using namespace strutils;
using namespace std;

ImgParamsDto imgParamsDto;
ImageOpers imageOpers;



/**
 * \brief выход из терминала
 */
void Comm::Quit() { exit(0); }

/**
 * \brief работает с командами из терминала
 * \param[in] inString - строка с командой
 * \return enum, соотвествующий команде терминала
 */
Comm::CommEnums Comm::toswitch(std::string const &inString){
	if (inString == "q") return eQuit;
	if (inString == "quit") return eQuit;
	if (inString == "exit") return eQuit;
	if (inString == "ld") return eLoad;
	if (inString == "load") return eLoad;
	if (inString == "help") return eHelp;
	if (inString == "h") return eHelp;
	if (inString == "resize") return eResize;
	if (inString == "rs") return eResize;
	if (inString == "s") return eSave;
	if (inString == "store") return eSave;
	if (inString == "blur") return eBlur;
	if (inString == "bl") return eBlur;
	return (Error);
}
/**
 * \brief основной метод
 * \details обработка команд терминала и вызов ImageMain()
 */
void Comm::TerminalCommander() {
  for (string line;
       cout << "Command ('h,help' for help) > " && getline(cin, line);) {
    if (!line.empty()) {
      std::vector<string> args = strutils::StringUtils::split(line, ' ');
      switch (toswitch(args[0])) {
        case eQuit:
          cout << "Bye!" << endl;
          Quit();
          break;
        case eHelp:
          Help();
          break;
        case eLoad:
          imgParamsDto.nameOfImg = args[1];
          imgParamsDto.pathToFile = args[2];
          imgParamsDto.operCode = OperCode::LOAD;
		  break;
        case eResize:
          imgParamsDto.nameOfImg = args[1];
          imgParamsDto.nameOfImgNew = args[2];
          try {
			  imgParamsDto.newWidth = stoi(args[3].c_str());
			  imgParamsDto.newHeight = stoi(args[4].c_str());
          }
          catch (...) {
        	  cout << "Wrong parameter!" << endl;
        	  break;
          }
          if ((imgParamsDto.newWidth <= 0) || (imgParamsDto.newHeight <= 0)){
        	  cout << "Height or Width <= 0!" << endl;
        	  break;
          }
          imgParamsDto.operCode = OperCode::RESIZE;
		  break;
        case eSave:
		  imgParamsDto.nameOfImg = args[1];
		  imgParamsDto.pathToFile = args[2];
		  imgParamsDto.operCode = OperCode::SAVE;
		  break;
        case eBlur:
          imgParamsDto.nameOfImg = args[1];
          imgParamsDto.nameOfImgNew = args[2];
          try {
        	  imgParamsDto.blurCore = stoi(args[3].c_str());
          }
          catch (...) {
              cout << "Wrong parameter!" << endl;
              break;
          }
          if (imgParamsDto.blurCore <= 0){
        	  cout << "Core <= 0!" << endl;
        	  break;
          }
          imgParamsDto.operCode = OperCode::BLUR;
          break;
        default:
        	cout << "Unrecognized command: "<< args[0] << endl;
      }
      imageOpers.ImageMain();
    }
  }
}
/**
 * \brief справка по командам
 */
void Comm::Help() {
  cout << "===============================================" << endl;
  cout << "Entering of the commands case insensitive!" << endl;
  cout << "===============================================" << endl;
  cout << "ld,load - Loading the new file of jpg format and associate with the image name" << endl;
  cout << "Format: ld,load <name of the image> <path to a file of jpg format>. Example: ld img1 /Users/user1/Pictures/nat.jpg " << endl;
  cout << "" << endl;
  cout << "rs,resize - Resize the image and save result in a new image" << endl;
  cout << "Format: rs,resize <name of the image_old> <name of the image_new> <height> <width>. Example: rs img1 img2 800 800" << endl;
  cout << "" << endl;
  cout << "blur - Blur the image and save result in a new image" << endl;
  cout << "Format: blur <name of the image_old> <name of the image_new> <core size>. Example: blur img1 img2 5" << endl;
  cout << "" << endl;
  cout << "s,store - Store to a new image file, that associated with the image name" << endl;
  cout << "Format: s,store <name of the image> <path to a file of jpg format>. Example: s img1 /Users/user1/Pictures/nat.jpg" << endl;
  cout << "" << endl;
  cout << "quit,exit,q - Exiting the program" << endl;
}
