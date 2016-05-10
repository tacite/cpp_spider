//
// Logs.cpp for spider in /home/Volto/Rendu/cpp_spider/spider/server
//
// Made by Probola
// Login   <Volto@epitech.net>
//
// Started on  Tue Oct 27 13:54:34 2015 Probola
// Last update Tue Oct 27 16:02:24 2015 Probola
//

#include			<stdexcept>
#include			"../inc/FileLog.hpp"

FileLog::FileLog() {}

FileLog::~FileLog() {}

void				FileLog::WriteLog(const std::string &msg)
{
  if (this->_fichier.is_open())
    {
      this->_fichier.write(msg.c_str(), msg.size());
      if (this->_fichier.fail() == true)
	throw std::runtime_error("[ERROR] Write failed\n");
    }
  else
    throw std::runtime_error("[ERROR] Try to write while the file isn't open\n");
  return;
}

void				FileLog::OpenLog(const std::string &clt)
{
  this->_fichier.open(clt.c_str(), std::ios::out | std::ios::app);
  if (this->_fichier.fail() == true)
    throw std::runtime_error("[ERROR] Open failed\n");
  return;
}

void				FileLog::CloseLog()
{
  this->_fichier.close();
  if (this->_fichier.fail() == true)
    throw std::runtime_error("[ERROR] Close failed\n");
  return;
}