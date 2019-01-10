// -*-C++-*-
/*!
 * @file  SpeechConsumerSVC_impl.h
 * @brief Service implementation header of SpeechConsumer.idl
 *
 */

#include "SpeechConsumerSkel.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>

using namespace std;

#ifndef SPEECHCONSUMERSVC_IMPL_H
#define SPEECHCONSUMERSVC_IMPL_H
 
/*!
 * @class Consumer_SpeechConsumerSVC_impl
 * Example class implementing IDL interface Consumer::SpeechConsumer
 */
class Consumer_SpeechConsumerSVC_impl
 : public virtual POA_Consumer::SpeechConsumer,
   public virtual PortableServer::RefCountServantBase
{
 private:
   // Make sure all instances are built on the heap by making the
   // destructor non-public
   //virtual ~Consumer_SpeechConsumerSVC_impl();

 public:
  /*!
   * @brief standard constructor
   */
   Consumer_SpeechConsumerSVC_impl();
  /*!
   * @brief destructor
   */
   virtual ~Consumer_SpeechConsumerSVC_impl();

   // attributes and operations
   void write(::CORBA::Long speechstate);
   int Flag;

  int csvdatacount = 0;
  int csvdatacountafter = 0;
  
  vector<string> data;
  std::string str;
  string field;

  std::string m_speechdata;
  std::string m_bodylang;
  int m_slide = 0;

  std::string home;
  
};



#endif // SPEECHCONSUMERSVC_IMPL_H


