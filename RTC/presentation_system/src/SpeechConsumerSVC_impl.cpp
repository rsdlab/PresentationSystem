// -*-C++-*-
/*!
 * @file  SpeechConsumerSVC_impl.cpp
 * @brief Service implementation code of SpeechConsumer.idl
 *
 */

#include "SpeechConsumerSVC_impl.h"

/*
 * Example implementational code for IDL interface Consumer::SpeechConsumer
 */
Consumer_SpeechConsumerSVC_impl::Consumer_SpeechConsumerSVC_impl()
{
  // Please add extra constructor code here.
}


Consumer_SpeechConsumerSVC_impl::~Consumer_SpeechConsumerSVC_impl()
{
  // Please add extra destructor code here.
}


/*
 * Methods corresponding to IDL attributes and operations
 */
void Consumer_SpeechConsumerSVC_impl::write(::CORBA::Long speechstate)
{
  // Please insert your code here and remove the following warning pragma
#ifndef WIN32
  #warning "Code missing in function <void Consumer_SpeechConsumerSVC_impl::write(::CORBA::Long speechstate)>"

  std::ifstream ifs("../../data.csv");
  while(getline(ifs, str)){
    istringstream stream(str);
    while(getline(stream, field, ',')){
      data.push_back(field);
      csvdatacount++;
    }
  }
  if (speechstate == 1){
    m_slide = m_slide + speechstate;
    csvdatacount = csvdatacount - csvdatacountafter;
    std::cout << "csvdatacount : " << csvdatacount  << std::endl;
    for(vector<string>::size_type i = 3; i < data.size(); i+=3){
      if(atoi(data[i].c_str()) == m_slide){
      m_speechdata = data [i+1];
      m_bodylang = data [i+2];
      }
    }
    home = "home";
    csvdatacountafter = csvdatacount;
    Flag = 1;
  }
  
#endif
}



// End of example implementational code
