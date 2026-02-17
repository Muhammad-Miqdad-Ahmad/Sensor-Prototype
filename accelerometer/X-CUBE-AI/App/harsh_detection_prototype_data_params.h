/**
  ******************************************************************************
  * @file    harsh_detection_prototype_data_params.h
  * @author  AST Embedded Analytics Research Platform
  * @date    2026-02-17T23:56:14+0500
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */

#ifndef HARSH_DETECTION_PROTOTYPE_DATA_PARAMS_H
#define HARSH_DETECTION_PROTOTYPE_DATA_PARAMS_H

#include "ai_platform.h"

/*
#define AI_HARSH_DETECTION_PROTOTYPE_DATA_WEIGHTS_PARAMS \
  (AI_HANDLE_PTR(&ai_harsh_detection_prototype_data_weights_params[1]))
*/

#define AI_HARSH_DETECTION_PROTOTYPE_DATA_CONFIG               (NULL)


#define AI_HARSH_DETECTION_PROTOTYPE_DATA_ACTIVATIONS_SIZES \
  { 8096, }
#define AI_HARSH_DETECTION_PROTOTYPE_DATA_ACTIVATIONS_SIZE     (8096)
#define AI_HARSH_DETECTION_PROTOTYPE_DATA_ACTIVATIONS_COUNT    (1)
#define AI_HARSH_DETECTION_PROTOTYPE_DATA_ACTIVATION_1_SIZE    (8096)



#define AI_HARSH_DETECTION_PROTOTYPE_DATA_WEIGHTS_SIZES \
  { 11988, }
#define AI_HARSH_DETECTION_PROTOTYPE_DATA_WEIGHTS_SIZE         (11988)
#define AI_HARSH_DETECTION_PROTOTYPE_DATA_WEIGHTS_COUNT        (1)
#define AI_HARSH_DETECTION_PROTOTYPE_DATA_WEIGHT_1_SIZE        (11988)



#define AI_HARSH_DETECTION_PROTOTYPE_DATA_ACTIVATIONS_TABLE_GET() \
  (&g_harsh_detection_prototype_activations_table[1])

extern ai_handle g_harsh_detection_prototype_activations_table[1 + 2];



#define AI_HARSH_DETECTION_PROTOTYPE_DATA_WEIGHTS_TABLE_GET() \
  (&g_harsh_detection_prototype_weights_table[1])

extern ai_handle g_harsh_detection_prototype_weights_table[1 + 2];


#endif    /* HARSH_DETECTION_PROTOTYPE_DATA_PARAMS_H */
