/*
 * Comm.hpp
 *
 *  Created on: Feb 8, 2019
 *      Author: root
 */

#ifndef X86UTILS_COMM_HPP_
#define X86UTILS_COMM_HPP_


#include <string>
/**
 * \brief класс обработки команд с терминала
 */
enum OperCode {
	RESET = 0,
	LOAD,
	RESIZE,
	SAVE,
	BLUR,
};
class Comm  {
 private:
  enum CommEnums {  // enumerate of the commands in menu
    eQuit = 1,
    eLoad,
	eHelp,
	eResize,
	eSave,
	eBlur,
    Error
  };



 public:
  Comm() {};
  ~Comm() {};
  CommEnums toswitch(std::string const &inString);
  void Help();
  void TerminalCommander();
  void Quit();
};

#endif /* X86UTILS_COMM_HPP_ */
