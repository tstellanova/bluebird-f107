//
// Created by Todd Stellanova on 2/12/17.
//

#include <stm32f1xx_hal_can.h>
#include <cmsis_os.h>
#include <uavcan/uavcan.hpp>
#include <uavcan_stm32/uavcan_stm32.hpp>

#include "can_reader_task.h"


extern void Error_Handler(void);


uavcan_stm32::CanInitHelper<128> canInitHelper;


/**
 * Memory pool size largely depends on the number of CAN ifaces and on application's logic.
 * Please read the documentation for the class uavcan::Node to learn more.
 */
constexpr unsigned NodeMemoryPoolSize = 16384;

typedef uavcan::Node<NodeMemoryPoolSize> Node;


uavcan::ICanDriver& getCanDriver() {
  return canInitHelper.driver;
}

uavcan::ISystemClock& getSystemClock() {
  return uavcan_stm32::SystemClock::instance();
}


/**
 * Node object will be constructed at the time of the first access.
 * Note that most library objects are noncopyable (e.g. publishers, subscribers, servers, callers, timers, ...).
 * Attempt to copy a noncopyable object causes compilation failure.
 */
static Node& getNode()
{
  static Node node(getCanDriver(), getSystemClock());
  return node;
}

class CanBusMasMacho
{
  CAN_HandleTypeDef* m_canHandle;

public:
  CanBusMasMacho() {};
  virtual ~CanBusMasMacho() {};

  void setCanHandle(CAN_HandleTypeDef* handle) { m_canHandle = handle; }
  void setup();
  void loop();

protected:
  void configureNodeInfo();


};

void CanBusMasMacho::configureNodeInfo()
{
  getNode().setName("org.uavcan.stm32_test_stm32f107");

  getNode().setNodeID(44);//TODO dynamic node ID
  getNode().setName("com.rawthought.test");

  uavcan::protocol::SoftwareVersion sw_version;  // Standard type uavcan.protocol.SoftwareVersion
  sw_version.major = 1;
  getNode().setSoftwareVersion(sw_version);
  //TODO:
//  swver.vcs_commit = GIT_HASH;
//  swver.optional_field_flags = swver.OPTIONAL_FIELD_FLAG_VCS_COMMIT;


  //TODO:
//  std::uint8_t uid[board::UniqueIDSize] = {};
//  board::readUniqueID(uid);
//  std::copy(std::begin(uid), std::end(uid), std::begin(hwver.unique_id));
  uavcan::protocol::HardwareVersion hw_version;  // Standard type uavcan.protocol.HardwareVersion
  hw_version.major = 1;
  getNode().setHardwareVersion(hw_version);

}

void CanBusMasMacho::setup()
{
  configureNodeInfo();

}

void CanBusMasMacho::loop()
{
  auto& node = getNode();
  const int node_start_res = node.start();
  if (node_start_res < 0) {
    return; //don't loop
  }

  /* Infinite loop */
  for(;;) {
    osDelay(1);
  }
}

void can_reader_task_main(CAN_HandleTypeDef*      canHandle)
{
  CanTxMsgTypeDef        TxMessage;
  CanRxMsgTypeDef        RxMessage;

  canHandle->pTxMsg = &TxMessage;
  canHandle->pRxMsg = &RxMessage;

  CanBusMasMacho macho;

  macho.setCanHandle(canHandle);
  macho.setup();

  macho.loop();



}

