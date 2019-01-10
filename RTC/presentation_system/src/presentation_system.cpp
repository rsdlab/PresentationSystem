// -*- C++ -*-
/*!
 * @file  presentation_system.cpp
 * @brief presentation_system
 * @date $Date$
 *
 * $Id$
 */

#include "presentation_system.h"

#include <iostream>
#include <string>

std::string home = "home";

// Module specification
// <rtc-template block="module_spec">
static const char* presentation_system_spec[] =
  {
    "implementation_id", "presentation_system",
    "type_name",         "presentation_system",
    "description",       "presentation_system",
    "version",           "1.0.0",
    "vendor",            "hiroyasu_tsuji",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
presentation_system::presentation_system(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_presentationopOut("presentationop", m_presentationop),
    m_actionmanagePort("actionmanage"),
    m_speechconsumerPort("speechconsumer"),
    m_speechproviderPort("speechprovider")

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
presentation_system::~presentation_system()
{
}



RTC::ReturnCode_t presentation_system::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  addOutPort("presentationop", m_presentationopOut);
  
  // Set service provider to Ports
  m_speechproviderPort.registerProvider("SpeechConsumer", "Consumer::SpeechConsumer", m_SpeechConsumerProvider);
  
  // Set service consumers to Ports
  m_actionmanagePort.registerConsumer("ActionManage", "Action::ActionManage", m_ActionManageRequire);
  m_speechconsumerPort.registerConsumer("SpeechProvider", "Provider::SpeechProvider", m_SpeechProviderRequire);
  
  // Set CORBA Service Ports
  addPort(m_actionmanagePort);
  addPort(m_speechconsumerPort);
  addPort(m_speechproviderPort);
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t presentation_system::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t presentation_system::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t presentation_system::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t presentation_system::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t presentation_system::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t presentation_system::onExecute(RTC::UniqueId ec_id)
{
  if (m_SpeechConsumerProvider.Flag == 1){

    if (m_SpeechConsumerProvider.m_slide > (m_SpeechConsumerProvider.csvdatacount -3)/3){
      return RTC::RTC_OK;
    }
    
    if (m_SpeechConsumerProvider.m_slide > 1){
      m_presentationop.data = 1;
      m_presentationopOut.write();
      std::cout << "slide next" << std::endl;
      m_presentationop.data = 0;
    }
    speechcontents = m_SpeechConsumerProvider.m_speechdata;
    actionid = m_SpeechConsumerProvider.m_bodylang;
    std::cout << "speechdata : " << speechcontents.c_str() << std::endl;
    std::cout << "actionid : " << actionid.c_str() << std::endl;
    m_SpeechProviderRequire->read(speechcontents.c_str());
    m_ActionManageRequire->read(actionid.c_str());
    m_SpeechConsumerProvider.Flag = 0;
  }
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t presentation_system::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t presentation_system::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t presentation_system::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t presentation_system::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t presentation_system::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

extern "C"
{
 
  void presentation_systemInit(RTC::Manager* manager)
  {
    coil::Properties profile(presentation_system_spec);
    manager->registerFactory(profile,
                             RTC::Create<presentation_system>,
                             RTC::Delete<presentation_system>);
  }
  
};


