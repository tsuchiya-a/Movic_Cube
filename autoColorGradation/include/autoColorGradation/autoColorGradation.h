// -*- C++ -*-
/*!
 * @file  autoColorGradation.h
 * @brief auto output RGB color based on gradation
 * @date  $Date$
 *
 * @author 土屋彩茜
 * ma14076@shibaura-it.ac.jp
 *
 * $Id$
 */

#ifndef AUTOCOLORGRADATION_H
#define AUTOCOLORGRADATION_H

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">

// </rtc-template>

using namespace RTC;

/*!
 * @class autoColorGradation
 * @brief auto output RGB color based on gradation
 *
 * フルカラーLEDをグラデーションに光らせるためのコンポーネント。
 * Configurationによってパターンの調整を行うことができる。
 *
 * InPort:<name>/<datatype>/<documentation>
 * no port
 * OutPort: <name>/<datatype>/<documentation>
 * RGBColor/TimedRGBColour/RGB値を出力するポート。
 * Configuration:<name>/<datatype>/<default>
 * /<widget>/<documentation>
 * color_order/string/RGB/radio/グラデーション変更のパターンをRGBの
 * 順にするか、RBGの順にするか選択できる。
 * cycle_time/int/50（x>0）/text/変化させる時間の調整をする。
 * params_01_Red/std::vector<int>/0,255/text/Redの範囲を指定する。
 * 実行中はこの範囲内で値が変更される。
 * params_02_Green/std::vector<int>/0,255/text/Greenの範囲を指定す
 * る。実行中はこの範囲内で値が変更される。
 * params_03_Blue/std::vector<int>/0,255/text/Blueの範囲を指定する
 * 。実行中はこの範囲内で値が変更される。
 *
 */
class autoColorGradation
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  autoColorGradation(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~autoColorGradation();

  // <rtc-template block="public_attribute">
  
  // </rtc-template>

  // <rtc-template block="public_operation">
  
  // </rtc-template>

  /***
   *
   * The initialize action (on CREATED->ALIVE transition)
   * formaer rtc_init_entry() 
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onInitialize();

  /***
   *
   * The finalize action (on ALIVE->END transition)
   * formaer rtc_exiting_entry()
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onFinalize();

  /***
   *
   * The startup action when ExecutionContext startup
   * former rtc_starting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id);

  /***
   *
   * The shutdown action when ExecutionContext stop
   * former rtc_stopping_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id);

  /***
   * 初期化処理を行う。
   *
   * The activated action (Active state entry action)
   * former rtc_active_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);

  /***
   * 終了処理を行う。
   *
   * The deactivated action (Active state exit action)
   * former rtc_active_exit()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

  /***
   * グラデーションになるようにRGBの値を出力する。
   *
   * The execution action that is invoked periodically
   * former rtc_active_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

  /***
   *
   * The aborting action when main logic error occurred.
   * former rtc_aborting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id);

  /***
   *
   * The error action in ERROR state
   * former rtc_error_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id);

  /***
   *
   * The reset action that is invoked resetting
   * This is same but different the former rtc_init_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id);
  
  /***
   *
   * The state update action that is invoked after onExecute() action
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id);

  /***
   *
   * The action that is invoked when execution context's rate is changed
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id);


 protected:
  // <rtc-template block="protected_attribute">
  
  // </rtc-template>

  // <rtc-template block="protected_operation">
  
  // </rtc-template>

  // Configuration variable declaration
  // <rtc-template block="config_declare">
  /*!
   * グラデーション変更のパターンをRGBの順にするか、RBGの順にするか
   * 選択できる。
   * - Name: color_order color_order
   * - DefaultValue: RGB
   */
  std::string m_color_order;
  /*!
   * 色の変化周期を調整する。
   * - Name: param_Green cycle_time
   * - DefaultValue: 50
   * - Constraint: x>0
   */
  int m_cycle_time;
  /*!
   * Redの範囲を指定する。
   * 実行中はこの範囲内で値が変更される。
   * - Name: param_01_Red params_01_Red
   * - DefaultValue: 0,255
   */
  std::vector<int> m_params_01_Red;
  /*!
   * Greenの範囲を指定する。
   * 実行中はこの範囲内で値が変更される。
   * - Name: param_02_Green params_02_Green
   * - DefaultValue: 0,255
   */
  std::vector<int> m_params_02_Green;
  /*!
   * Blueの範囲を指定する。
   * 実行中はこの範囲内で値が変更される。
   * - Name: param_03_Blue params_03_Blue
   * - DefaultValue: 0,255
   */
  std::vector<int> m_params_03_Blue;

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  RTC::TimedRGBColour m_RGBColor;
  /*!
   * RGB値を出力するポート。
   * - Type: TimedRGBColour
   */
  OutPort<RTC::TimedRGBColour> m_RGBColorOut;
  
  // </rtc-template>

  // CORBA Port declaration
  // <rtc-template block="corbaport_declare">
  
  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">
  
  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">
  
  // </rtc-template>

 private:
  // <rtc-template block="private_attribute">
  int counter;
  std::string prev_conf;

  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


extern "C"
{
  DLL_EXPORT void autoColorGradationInit(RTC::Manager* manager);
};

#endif // AUTOCOLORGRADATION_H
