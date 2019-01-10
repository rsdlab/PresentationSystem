// -*-C++-*-
/*!
 * @file  SpeechProviderSVC_impl.cpp
 * @brief Service implementation code of SpeechProvider.idl
 *
 */

#include "SpeechProviderSVC_impl.h"

#include <iostream>
#include <stdio.h>
#include <string.h>

/*
 * Example implementational code for IDL interface Provider::SpeechProvider
 */
Provider_SpeechProviderSVC_impl::Provider_SpeechProviderSVC_impl()
{
  // Please add extra constructor code here.
}


Provider_SpeechProviderSVC_impl::~Provider_SpeechProviderSVC_impl()
{
  // Please add extra destructor code here.
}


/*
 * Methods corresponding to IDL attributes and operations
 */
void Provider_SpeechProviderSVC_impl::read(const char* speechcontents)
{
  // Please insert your code here and remove the following warning pragma
#ifndef WIN32
  #warning "Code missing in function <void Provider_SpeechProviderSVC_impl::read(const char* speechcontents)>"
#endif

  m_speechdata = std::string(speechcontents);
  sleeptime = strlen(speechcontents)/13;
  Flag = 1;
}



// End of example implementational code



