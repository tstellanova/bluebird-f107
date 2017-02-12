//
// Created by Todd Stellanova on 2/12/17.
//

#include <stm32f1xx_hal_can.h>
#include <cmsis_os.h>

#include "can.h"

#include "can_reader_task.h"


extern void Error_Handler(void);


void can_reader_task_main(CAN_HandleTypeDef*      canHandle)
{
  CanTxMsgTypeDef        TxMessage;
  CanRxMsgTypeDef        RxMessage;

  canHandle->pTxMsg = &TxMessage;
  canHandle->pRxMsg = &RxMessage;

  /* Infinite loop */
  for(;;) {
    osDelay(1);
  }

}

