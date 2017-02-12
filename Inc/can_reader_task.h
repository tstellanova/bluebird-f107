//
// Created by Todd Stellanova on 2/12/17.
//

#ifndef BLUEBIRD_CANREADERTASK_H
#define BLUEBIRD_CANREADERTASK_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void can_reader_task_main(CAN_TypeDef* canRef);


#ifdef __cplusplus
}
#endif

#endif //BLUEBIRD_CANREADERTASK_H
