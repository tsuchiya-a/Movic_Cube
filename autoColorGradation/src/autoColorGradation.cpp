// -*- C++ -*-
/*!
 * @file  autoColorGradation.cpp
 * @brief auto output RGB color based on gradation
 * @date $Date$
 *
 * @author 土屋彩茜
 * ma14076@shibaura-it.ac.jp
 *
 * $Id$
 */

#include "autoColorGradation.h"
#include <VectorConvert.h>

// 数値をある範囲から別の範囲に変換する。（参考：Arduino map関数）
int map(int data,int start,int end,int min_param,int max_param);
// 色相を回す速度を決めるパラメータ。
const int Hue_CycleTime=120;

// Module specification
// <rtc-template block="module_spec">
static const char* autocolorgradation_spec[] =
  {
    "implementation_id", "autoColorGradation",
    "type_name",         "autoColorGradation",
    "description",       "auto output RGB color based on gradation",
    "version",           "1.0.2",
    "vendor",            "Ayaka Tsuchiya",
    "category",          "expression",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.color_order", "RGB",
    "conf.default.cycle_time", "50",
    "conf.default.params_01_Red", "0,255",
    "conf.default.params_02_Green", "0,255",
    "conf.default.params_03_Blue", "0,255",
    // Widget
    "conf.__widget__.color_order", "radio",
    "conf.__widget__.cycle_time", "text",
    "conf.__widget__.params_01_Red", "text",
    "conf.__widget__.params_02_Green", "text",
    "conf.__widget__.params_03_Blue", "text",
    // Constraints
    "conf.__constraints__.color_order", "(RGB,RBG)",
    "conf.__constraints__.cycle_time", "x>0",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
autoColorGradation::autoColorGradation(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_RGBColorOut("RGBColor", m_RGBColor)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
autoColorGradation::~autoColorGradation()
{
}



RTC::ReturnCode_t autoColorGradation::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  addOutPort("RGBColor", m_RGBColorOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("color_order", m_color_order, "RGB");
  bindParameter("cycle_time", m_cycle_time, "50");
  bindParameter("params_01_Red", m_params_01_Red, "0,255");
  bindParameter("params_02_Green", m_params_02_Green, "0,255");
  bindParameter("params_03_Blue", m_params_03_Blue, "0,255");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t autoColorGradation::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t autoColorGradation::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t autoColorGradation::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*!
 * 初期化処理を行う。
 */

RTC::ReturnCode_t autoColorGradation::onActivated(RTC::UniqueId ec_id)
{
  m_RGBColor.data.r=0;
  m_RGBColor.data.g=0;
  m_RGBColor.data.b=0;
  m_RGBColorOut.write();
  counter=0;
  prev_conf="default";
  return RTC::RTC_OK;
}

/*!
 * 終了処理を行う。
 */

RTC::ReturnCode_t autoColorGradation::onDeactivated(RTC::UniqueId ec_id)
{
  // LEDを消灯する
  m_RGBColor.data.r=0;
  m_RGBColor.data.g=0;
  m_RGBColor.data.b=0;
  m_RGBColorOut.write();
  return RTC::RTC_OK;
}

/*!
 * グラデーションになるようにRGBの値を出力する。
 */

RTC::ReturnCode_t autoColorGradation::onExecute(RTC::UniqueId ec_id)
{
  int max_params[3];
  int min_params[3];
  int color[3]; // R=0,G=1,B=2
  int color_data[3];

  // パラメータの設定
  if(m_color_order=="RGB"){
	// RGB順にパラメータを保存。
	min_params[0]=m_params_01_Red[0];
	max_params[0]=m_params_01_Red[1];
	min_params[1]=m_params_02_Green[0];
	max_params[1]=m_params_02_Green[1];
	min_params[2]=m_params_03_Blue[0];
	max_params[2]=m_params_03_Blue[1];
	// RGBの順番を保存しておく。（color[i]=0:i番目はRed）
	color[0]=0;
	color[1]=1;
	color[2]=2;
	// 前回とパターンが変わっていたらメッセージを表示する
	if(prev_conf!=m_color_order) std::cout<<"Now Cycle -> RGB"<<std::endl;
	prev_conf=m_color_order;
  }
  else if(m_color_order=="RBG"){
	// RBG順にパラメータを保存。
	min_params[0]=m_params_01_Red[0];
	max_params[0]=m_params_01_Red[1];
	min_params[1]=m_params_03_Blue[0];
	max_params[1]=m_params_03_Blue[1];
	min_params[2]=m_params_02_Green[0];
	max_params[2]=m_params_02_Green[1];
	// RBGの順番を保存しておく。（color[i]=0:i番目はRed）
	color[0]=0;
	color[1]=2;
	color[2]=1;
	// 前回とパターンが変わっていたらメッセージを表示する
	if(prev_conf!=m_color_order) std::cout<<"Now Cycle -> RBG"<<std::endl;
	prev_conf=m_color_order;
  }

  // グラデーション
  if(counter<=Hue_CycleTime){
	color_data[0]=map(counter,0,Hue_CycleTime,max_params[0],min_params[0]);
	color_data[1]=map(counter,0,Hue_CycleTime,min_params[1],max_params[1]);
	color_data[2]=0;
  }
  else if(counter<=Hue_CycleTime*2){
	color_data[0]=0;
	color_data[1]=map(counter,Hue_CycleTime,Hue_CycleTime*2,max_params[1],min_params[1]);
	color_data[2]=map(counter,Hue_CycleTime,Hue_CycleTime*2,min_params[2],max_params[2]);
  }
  else{
	color_data[0]=map(counter,Hue_CycleTime*2,Hue_CycleTime*3,min_params[0],max_params[0]);
	color_data[1]=0;
	color_data[2]=map(counter,Hue_CycleTime*2,Hue_CycleTime*3,max_params[2],min_params[2]);
  }
  
  // i番目の色が何色か確認し、その色にi番目の値を代入する。
  for(int i=0;i<3;i++){
	switch(color[i]){
		case(0):m_RGBColor.data.r=color_data[i];
				break;
		case(1):m_RGBColor.data.g=color_data[i];
				break;
		case(2):m_RGBColor.data.b=color_data[i];
				break;
		default:std::cout<<"error:color"<<std::endl;
	}
  }

  // データの出力
    std::cout<<"R="<<m_RGBColor.data.r<<" ,G="<<m_RGBColor.data.g<<" ,B="<<m_RGBColor.data.b<<std::endl;
  m_RGBColorOut.write();
  Sleep(m_cycle_time);

  // カウンターの更新
  if(counter>Hue_CycleTime*3){
	counter=0;
  }
  else counter++;

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t autoColorGradation::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t autoColorGradation::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t autoColorGradation::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t autoColorGradation::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t autoColorGradation::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

// 数値をある範囲から別の範囲に変換する。
int map(int data,int start,int end,int min_param,int max_param){
  return (data-start)*(max_param-min_param)/(end-start)+min_param;
}

extern "C"
{
 
  void autoColorGradationInit(RTC::Manager* manager)
  {
    coil::Properties profile(autocolorgradation_spec);
    manager->registerFactory(profile,
                             RTC::Create<autoColorGradation>,
                             RTC::Delete<autoColorGradation>);
  }
  
};


