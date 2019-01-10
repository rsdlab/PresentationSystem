// -*- C++ -*-
/*!
 * @file  presentation_seednoid.cpp
 * @brief presentation_seednoid
 * @date $Date$
 *
 * $Id$
 */

#include "presentation_seednoid.h"
#include <math.h>

// Module specification
// <rtc-template block="module_spec">
static const char* presentation_seednoid_spec[] =
  {
    "implementation_id", "presentation_seednoid",
    "type_name",         "presentation_seednoid",
    "description",       "presentation_seednoid",
    "version",           "1.0.0",
    "vendor",            "rsdlab",
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
presentation_seednoid::presentation_seednoid(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_facedetectionmoveIn("facedetectionmove", m_facedetectionmove),
    m_RightManipulatorCommonInterface_CommonPort("RightManipulatorCommonInterface_Common"),
    m_RightManipulatorCommonInterface_MiddlePort("RightManipulatorCommonInterface_Middle"),
    m_LeftManipulatorCommonInterface_CommonPort("LeftManipulatorCommonInterface_Common"),
    m_LeftManipulatorCommonInterface_MiddlePort("LeftManipulatorCommonInterface_Middle"),
    m_WaistInterfacePort("WaistInterface"),
    m_NeckInterfacePort("NeckInterface"),
    m_actionmanagePort("actionmanage")

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
presentation_seednoid::~presentation_seednoid()
{
}



RTC::ReturnCode_t presentation_seednoid::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("facedetectionmove", m_facedetectionmoveIn);
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  m_actionmanagePort.registerProvider("ActionManage", "Action::ActionManage", m_ActionManageProvider);
  
  // Set service consumers to Ports
  m_RightManipulatorCommonInterface_CommonPort.registerConsumer("ManipulatorCommonInterface_Common", "JARA_ARM::ManipulatorCommonInterface_Common", m_ManipulatorCommonInterface_Common);
  m_RightManipulatorCommonInterface_MiddlePort.registerConsumer("ManipulatorCommonInterface_Middle", "JARA_ARM::ManipulatorCommonInterface_Middle", m_ManipulatorCommonInterface_Middle);
  m_LeftManipulatorCommonInterface_CommonPort.registerConsumer("LeftManipulatorCommonInterface_Common", "JARA_ARM_LEFT::LeftManipulatorCommonInterface_Common", m_LeftManipulatorCommonInterface_Common);
  m_LeftManipulatorCommonInterface_MiddlePort.registerConsumer("LeftManipulatorCommonInterface_Middle", "JARA_ARM_LEFT::LeftManipulatorCommonInterface_Middle", m_LeftManipulatorCommonInterface_Middle);
  m_WaistInterfacePort.registerConsumer("WaistInterface", "WaistNeck::WaistInterface", m_WaistInterface);
  m_NeckInterfacePort.registerConsumer("NeckInterface", "WaistNeck::NeckInterface", m_NeckInterface);
  
  // Set CORBA Service Ports
  addPort(m_RightManipulatorCommonInterface_CommonPort);
  addPort(m_RightManipulatorCommonInterface_MiddlePort);
  addPort(m_LeftManipulatorCommonInterface_CommonPort);
  addPort(m_LeftManipulatorCommonInterface_MiddlePort);
  addPort(m_WaistInterfacePort);
  addPort(m_NeckInterfacePort);
  addPort(m_actionmanagePort);
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t presentation_seednoid::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t presentation_seednoid::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t presentation_seednoid::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t presentation_seednoid::onActivated(RTC::UniqueId ec_id)
{
  //プロバイダより遅くActivateするため
  sleep(1);
  return RTC::RTC_OK;
}


RTC::ReturnCode_t presentation_seednoid::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t presentation_seednoid::onExecute(RTC::UniqueId ec_id)
{
  if (m_ActionManageProvider.Flag == 1){
    //RightArm
    JARA_ARM::ManipInfo_var Rminfovar;
    JARA_ARM::ManipInfo Rminfo;
    JARA_ARM::JointPos RjointPoint;
    m_ManipulatorCommonInterface_Common->getManipInfo(Rminfovar);
    Rminfo = Rminfovar;
    RjointPoint.length(Rminfo.axisNum);
    RjointPoint[0] = m_ActionManageProvider.Rarm0;
    RjointPoint[1] = m_ActionManageProvider.Rarm1;
    RjointPoint[2] = m_ActionManageProvider.Rarm2;
    RjointPoint[3] = m_ActionManageProvider.Rarm3;
    RjointPoint[4] = m_ActionManageProvider.Rarm4;
    RjointPoint[5] = m_ActionManageProvider.Rarm5;
    RjointPoint[6] = m_ActionManageProvider.Rarm6;
    m_rid_right=m_ManipulatorCommonInterface_Middle->movePTPJointAbs(RjointPoint);

    JARA_ARM::ULONG RangleRatio;
    RangleRatio = m_ActionManageProvider.handpara;
    m_rid_right=m_ManipulatorCommonInterface_Middle->moveGripper(RangleRatio);

    //LeftArm
    JARA_ARM_LEFT::ManipInfo_var Lminfovar;
    JARA_ARM_LEFT::ManipInfo Lminfo;
    JARA_ARM_LEFT::JointPos LjointPoint;
    m_LeftManipulatorCommonInterface_Common->getManipInfo(Lminfovar);
    Lminfo = Lminfovar;
    LjointPoint.length(Lminfo.axisNum);
    LjointPoint[0] = m_ActionManageProvider.Larm0;
    LjointPoint[1] = m_ActionManageProvider.Larm1;
    LjointPoint[2] = m_ActionManageProvider.Larm2;
    LjointPoint[3] = m_ActionManageProvider.Larm3;
    LjointPoint[4] = m_ActionManageProvider.Larm4;
    LjointPoint[5] = m_ActionManageProvider.Larm5;
    LjointPoint[6] = m_ActionManageProvider.Larm6;
    m_rid_left=m_LeftManipulatorCommonInterface_Middle->movePTPJointAbs(LjointPoint);

    JARA_ARM_LEFT::ULONG LangleRatio;
    LangleRatio = m_ActionManageProvider.handpara;
    m_rid_left=m_LeftManipulatorCommonInterface_Middle->moveGripper(LangleRatio);

    WaistNeck::NeckPos neckPoint;
    neckPoint.length(3);
    if (m_ActionManageProvider.neckyoo == 0){
      m_facedetectionmoveIn.read();
      neckPoint[0] = -1 * m_facedetectionmove.data /10;
      std::cout << "Moveamount" << neckPoint[0] << std::endl;
    }
    else {
      //頭ヨー(回転)-90~90
      neckPoint[0] = m_ActionManageProvider.neckyoo;
    }
    //頭ピッチ(前後)-20~+60
    neckPoint[1] = m_ActionManageProvider.neckpich;
    //頭ロール(左右)-20~+20
    neckPoint[2] = m_ActionManageProvider.neckrole;
    m_rid_neck=m_NeckInterface->movePTPNeckAbs(neckPoint);

    WaistNeck::WaistPos waistPoint;
    waistPoint.length(3);
    if (m_ActionManageProvider.waistyoo == 0){
      m_facedetectionmoveIn.read();
      waistPoint[0] = -1 * m_facedetectionmove.data /6;
      std::cout << "Moveamount" << waistPoint[0] << std::endl;
    }
    else {
      //腰ヨー(回転)-90~90
      waistPoint[0] = m_ActionManageProvider.waistyoo;
    }
    //腰ピッチ(前後)-9~+39
    waistPoint[1] = m_ActionManageProvider.waistpich;
    //腰ロール(左右)-9~+9
    waistPoint[2] = m_ActionManageProvider.waistrole;
    m_rid_waist=m_WaistInterface->movePTPWaistAbs(waistPoint);

    if(m_rid_left->id != 0){//Error
      std::cout<<"movePTPJointAbs ERROR"<<std::endl;
      std::cout<<m_rid_left->comment<<std::endl;
    }
    if(m_rid_left->id != 0){//Error
      std::cout<<"moveGripper ERROR"<<std::endl;
      std::cout<<m_rid_left->comment<<std::endl;
    }
    if(m_rid_right->id != 0){//Error
      std::cout<<"moveGripper ERROR"<<std::endl;
      std::cout<<m_rid_right->comment<<std::endl;
    }
    if(m_rid_right->id != 0){//Error
      std::cout<<"movePTPJointAbs ERROR"<<std::endl;
      std::cout<<m_rid_right->comment<<std::endl;
    }
    
    m_ActionManageProvider.Flag = 0;

  }
    return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t presentation_seednoid::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t presentation_seednoid::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t presentation_seednoid::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t presentation_seednoid::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t presentation_seednoid::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void presentation_seednoidInit(RTC::Manager* manager)
  {
    coil::Properties profile(presentation_seednoid_spec);
    manager->registerFactory(profile,
                             RTC::Create<presentation_seednoid>,
                             RTC::Delete<presentation_seednoid>);
  }
  
};


