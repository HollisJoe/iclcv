/*
  ICLException.h

  Written by: Michael G�tting (2006)
              University of Bielefeld
              AG Neuroinformatik
              mgoettin@techfak.uni-bielefeld.de
*/

#ifndef ICLEXCEPTION_H
#define ICLEXCEPTION_H

#include <iostream>
#include <exception>

namespace icl {
  
  class ICLException : public std::exception
  {
  private:
    std::string m_sMessage;
    
  public:
    ICLException (const std::string &msg) throw() : m_sMessage(msg) {}
    virtual ~ICLException() throw() {};
    virtual const char* what() const throw() {return m_sMessage.c_str();}
    void report();
  };

  //TODO: rename to InvalidFileFormatException
  class ICLInvalidFileFormat : public ICLException {
  public:
    ICLInvalidFileFormat () throw() : 
       ICLException (std::string("invalid file format")) {}
    virtual ~ICLInvalidFileFormat() throw() {}
  };

  class FileOpenException : public ICLException {
  public:
    FileOpenException (const std::string& sFileName) throw() : 
       ICLException (std::string("Can't open file: ") + sFileName) {}
    virtual ~FileOpenException() throw() {}
  };
 
  class InvalidImgParamException : public ICLException {
    public:
    InvalidImgParamException(const std::string &param) throw():
      ICLException(std::string("Invalid Img-Parameter: ")+param) {}
    virtual ~InvalidImgParamException() throw() {}
  };
}

#endif // ICLEXCEPTION
