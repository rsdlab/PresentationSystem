// -*-C++-*-
/*!
 * @file  SpeechProviderSVC_impl.h
 * @brief Service implementation header of SpeechProvider.idl
 *
 */

#include "SpeechProviderSkel.h"

#ifndef SPEECHPROVIDERSVC_IMPL_H
#define SPEECHPROVIDERSVC_IMPL_H

#include <iostream>
 
/*!
 * @class Provider_SpeechProviderSVC_impl
 * Example class implementing IDL interface Provider::SpeechProvider
 */
class Provider_SpeechProviderSVC_impl
 : public virtual POA_Provider::SpeechProvider,
   public virtual PortableServer::RefCountServantBase
{
 private:
   // Make sure all instances are built on the heap by making the
   // destructor non-public
   //virtual ~Provider_SpeechProviderSVC_impl();

 public:
  /*!
   * @brief standard constructor
   */
   Provider_SpeechProviderSVC_impl();
  /*!
   * @brief destructor
   */
   virtual ~Provider_SpeechProviderSVC_impl();

   // attributes and operations
   void read(const char* speechcontents);

   std::string m_speechdata;
   int Flag;
   double sleeptime;

};



#endif // SPEECHPROVIDERSVC_IMPL_H


