// -*- C++ -*-
/*!
 * @file  FaceDetectionMovement.cpp
 * @brief FaceDetectionMovement
 * @date $Date$
 *
 * $Id$
 */

#include "FaceDetectionMovement.h"
#include <iostream>

// Module specification
// <rtc-template block="module_spec">
static const char* facedetectionmovement_spec[] =
  {
    "implementation_id", "FaceDetectionMovement",
    "type_name",         "FaceDetectionMovement",
    "description",       "FaceDetectionMovement",
    "version",           "1.0.0",
    "vendor",            "Tsuji_Hiroyasu",
    "category",          "ImageProcessing",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.cascade", "haarcascade_frontalface_alt",

    // Widget
    "conf.__widget__.cascade", "text",
    // Constraints

    "conf.__type__.cascade", "string",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
FaceDetectionMovement::FaceDetectionMovement(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_inImageIn("inImage", m_inImage),
    m_outImageOut("outImage", m_outImage),
    m_moveamountOut("moveamount", m_moveamount)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
FaceDetectionMovement::~FaceDetectionMovement()
{
}



RTC::ReturnCode_t FaceDetectionMovement::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("inImage", m_inImageIn);
  
  // Set OutPort buffer
  addOutPort("outImage", m_outImageOut);
  addOutPort("moveamount", m_moveamountOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("cascade", m_cascade, "haarcascade_frontalface_alt");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t FaceDetectionMovement::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t FaceDetectionMovement::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t FaceDetectionMovement::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t FaceDetectionMovement::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t FaceDetectionMovement::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t FaceDetectionMovement::onExecute(RTC::UniqueId ec_id)
{
    /*        Image Input start		*/
    if (m_inImageIn.isNew())
    {
		m_inImageIn.read();

		width = m_inImage.data.image.width;
		height = m_inImage.data.image.height;
		channels = (m_inImage.data.image.format == CF_GRAY) ? 1 :
			(m_inImage.data.image.format == CF_RGB) ? 3 :
			(m_inImage.data.image.raw_data.length() / width / height);
		RTC_TRACE(("Capture image size %d x %d", width, height));
		RTC_TRACE(("Channels %d", channels));

		if (channels == 3)
			image.create(height, width, CV_8UC3);
		else
			image.create(height, width, CV_8UC1);

		for (int i = 0; i < height; ++i){
			memcpy(&image.data[i*image.step],
				&m_inImage.data.image.raw_data[i*width*channels],
				sizeof(unsigned char)*width*channels);
		}
		/*	Image Input end		*/

		// 輝度画像に変換
    		
    		cv::cvtColor(image, grayImage, CV_RGB2GRAY);

    		// 学習済み検出器の読み込み

   		std::string cascadeName = "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml";// + m_cascade + ".xml";
 		cv::CascadeClassifier cascade;
    		if(!cascade.load(cascadeName))
        		return RTC::RTC_OK;

    		// 顔検出を実行
    		std::vector<cv::Rect> faces;
    		cascade.detectMultiScale(
        		grayImage,   // 画像
        		faces,       // 出力される矩形
        		1.1,         // 縮小用のスケール
        		2,           // 最小の投票数
        		CV_HAAR_SCALE_IMAGE,  // フラグ
        		cv::Size(30, 30) // 最小の矩形
    		);
		//facedata =  cascade.detectMultiScale(grayImage,faces,1.1,2,CV_HAAR_SCALE_IMAGE,cv::Size(30, 30))
    
    		// 矩形を描く
    		for (std::vector<cv::Rect>::iterator iter = faces.begin(); iter != faces.end(); iter ++) {
        		cv::rectangle(image, *iter, cv::Scalar(255, 0, 0), 1);
			cv::Point center;
			center.x = cv::saturate_cast<int>((iter->x + iter->width*0.5)*1);
			center.y = cv::saturate_cast<int>((iter->y + iter->height*0.5)*1);
			std::cout << "facedataX : " << center.x << std::endl;
			std::cout << "facedataY : " << center.y << std::endl;
			moveamount = center.x;
    		}
		cv::waitKey(1);

		/*		Output start		*/
		m_outImage.data.image.width = width;
		m_outImage.data.image.height = height;
		m_outImage.data.image.raw_data.length(width * height * channels);
		m_outImage.data.image.format
			= (channels == 3) ? Img::CF_RGB :
			(channels == 1) ? Img::CF_GRAY : Img::CF_UNKNOWN;
		for (int i = 0; i<height; ++i){
			memcpy(&m_outImage.data.image.raw_data[i*width*channels],
				&image.data[i*image.step],
				sizeof(unsigned char)*width*channels);
		}

		m_moveamount.data = moveamount - 320;
		std::cout << "moveamount" << m_moveamount.data << std::endl;
		m_moveamountOut.write();
		m_outImageOut.write();
		/*		Output end		*/
    }
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t FaceDetectionMovement::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t FaceDetectionMovement::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t FaceDetectionMovement::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t FaceDetectionMovement::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t FaceDetectionMovement::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void FaceDetectionMovementInit(RTC::Manager* manager)
  {
    coil::Properties profile(facedetectionmovement_spec);
    manager->registerFactory(profile,
                             RTC::Create<FaceDetectionMovement>,
                             RTC::Delete<FaceDetectionMovement>);
  }
  
};


