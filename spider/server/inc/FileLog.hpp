//
// Logs.hpp for spider in /home/Volto/Rendu/cpp_spider/spider/server
// 
// Made by Probola
// Login   <Volto@epitech.net>
// 
// Started on  Tue Oct 27 13:53:01 2015 Probola
// Last update Tue Oct 27 15:54:22 2015 Probola
//

#ifndef				_FILELOG_HPP_
# define			_FILELOG_HPP_

# include			<cstring>
# include			<cerrno>
# include			<exception>
# include			<unistd.h>
# include			<iostream>
# include			<fstream>

class				FileLog
{
private:
  std::ofstream			_fichier;

public:
  FileLog();
  ~FileLog();

  void				WriteLog(const std::string &);
  void				OpenLog(const std::string &);
  void				CloseLog();
};

#endif
