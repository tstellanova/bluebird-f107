//
// Created by Todd Stellanova on 2/12/17.
//

#include <stm32f1xx_hal_can.h>
#include "can_reader_task.h"

#include "stm32f1xx_hal_can.h"

extern void Error_Handler(void);

static void config_can_reader(CAN_HandleTypeDef* canHandle)
{
  /*##-1- Configure the CAN peripheral #######################################*/

  canHandle->Init.TTCM = DISABLE;
  canHandle->Init.ABOM = DISABLE;
  canHandle->Init.AWUM = DISABLE;
  canHandle->Init.NART = DISABLE;
  canHandle->Init.RFLM = DISABLE;
  canHandle->Init.TXFP = DISABLE;
  canHandle->Init.Mode = CAN_MODE_NORMAL;
  canHandle->Init.SJW = CAN_SJW_1TQ;
  canHandle->Init.BS1 = CAN_BS1_6TQ;
  canHandle->Init.BS2 = CAN_BS2_8TQ;
  canHandle->Init.Prescaler = 2;
  if (HAL_OK != HAL_CAN_Init(canHandle)) {
    Error_Handler();
  }
}

void can_reader_task_main(CAN_TypeDef* canRef)
{
  CanTxMsgTypeDef        TxMessage;
  CanRxMsgTypeDef        RxMessage;
  CAN_HandleTypeDef      canHandle;

  canHandle.Instance = canRef;
  canHandle.pTxMsg = &TxMessage;
  canHandle.pRxMsg = &RxMessage;
  config_can_reader(&canHandle);


}

