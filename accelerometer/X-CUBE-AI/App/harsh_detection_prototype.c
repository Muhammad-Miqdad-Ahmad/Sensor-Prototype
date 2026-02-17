/**
  ******************************************************************************
  * @file    harsh_detection_prototype.c
  * @author  AST Embedded Analytics Research Platform
  * @date    2026-02-17T23:56:14+0500
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */


#include "harsh_detection_prototype.h"
#include "harsh_detection_prototype_data.h"

#include "ai_platform.h"
#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "core_convert.h"

#include "layers.h"



#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_harsh_detection_prototype
 
#undef AI_HARSH_DETECTION_PROTOTYPE_MODEL_SIGNATURE
#define AI_HARSH_DETECTION_PROTOTYPE_MODEL_SIGNATURE     "0x0567c223e09c17f2e1f5f854ee6bc063"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     ""
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "2026-02-17T23:56:14+0500"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_HARSH_DETECTION_PROTOTYPE_N_BATCHES
#define AI_HARSH_DETECTION_PROTOTYPE_N_BATCHES         (1)

static ai_ptr g_harsh_detection_prototype_activations_map[1] = AI_C_ARRAY_INIT;
static ai_ptr g_harsh_detection_prototype_weights_map[1] = AI_C_ARRAY_INIT;



/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  serving_default_input_layer0_output_array, AI_ARRAY_FORMAT_S8|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 240, AI_STATIC)

/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 1216, AI_STATIC)

/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_2_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 1216, AI_STATIC)

/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_3_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 1216, AI_STATIC)

/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  pool_6_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 608, AI_STATIC)

/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_9_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 1088, AI_STATIC)

/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_10_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 1088, AI_STATIC)

/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_11_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 1088, AI_STATIC)

/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  pool_13_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 64, AI_STATIC)

/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  gemm_14_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 64, AI_STATIC)

/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  gemm_15_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 5, AI_STATIC)

/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  nl_16_output_array, AI_ARRAY_FORMAT_S8|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 5, AI_STATIC)

/* Array#12 */
AI_ARRAY_OBJ_DECLARE(
  tfl_pseudo_qconst9_4D_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 32, AI_STATIC)

/* Array#13 */
AI_ARRAY_OBJ_DECLARE(
  tfl_pseudo_qconst8_4D_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 32, AI_STATIC)

/* Array#14 */
AI_ARRAY_OBJ_DECLARE(
  tfl_pseudo_qconst5_4D_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 64, AI_STATIC)

/* Array#15 */
AI_ARRAY_OBJ_DECLARE(
  tfl_pseudo_qconst4_4D_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 64, AI_STATIC)

/* Array#16 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 576, AI_STATIC)

/* Array#17 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 32, AI_STATIC)

/* Array#18 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_9_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 6144, AI_STATIC)

/* Array#19 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_9_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 64, AI_STATIC)

/* Array#20 */
AI_ARRAY_OBJ_DECLARE(
  gemm_14_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 4096, AI_STATIC)

/* Array#21 */
AI_ARRAY_OBJ_DECLARE(
  gemm_14_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 64, AI_STATIC)

/* Array#22 */
AI_ARRAY_OBJ_DECLARE(
  gemm_15_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 320, AI_STATIC)

/* Array#23 */
AI_ARRAY_OBJ_DECLARE(
  gemm_15_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 5, AI_STATIC)

/* Array#24 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 1672, AI_STATIC)

/* Array#25 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_9_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 6400, AI_STATIC)

/* Array#26 */
AI_ARRAY_OBJ_DECLARE(
  gemm_14_scratch0_array, AI_ARRAY_FORMAT_S16,
  NULL, NULL, 384, AI_STATIC)

/* Array#27 */
AI_ARRAY_OBJ_DECLARE(
  gemm_15_scratch0_array, AI_ARRAY_FORMAT_S16,
  NULL, NULL, 89, AI_STATIC)

/* Array#28 */
AI_ARRAY_OBJ_DECLARE(
  nl_16_scratch0_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 124, AI_STATIC)

/**  Array metadata declarations section  *************************************/
/* Int quant #0 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_1_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.09834044426679611f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #1 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_1_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 32,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.003916219342499971f, 0.002629362978041172f, 0.002467593178153038f, 0.002413438633084297f, 0.0023465966805815697f, 0.002478384179994464f, 0.002304299268871546f, 0.0021606094669550657f, 0.0024705971591174603f, 0.0021834413055330515f, 0.00223589688539505f, 0.0024956900160759687f, 0.0022861016914248466f, 0.002484699012711644f, 0.0020796400494873524f, 0.0018062148010358214f, 0.0022250330075621605f, 0.0028269460890442133f, 0.0027494127862155437f, 0.0029210515785962343f, 0.0024851153139024973f, 0.002190354047343135f, 0.0027487915940582752f, 0.0030180655885487795f, 0.00216845260001719f, 0.0034254598431289196f, 0.0032848468981683254f, 0.002172184409573674f, 0.002849295036867261f, 0.002089726272970438f, 0.002219308167695999f, 0.0019220776157453656f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #2 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_9_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.08946826308965683f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #3 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_9_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 64,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.002319120801985264f, 0.0025521728675812483f, 0.0021608525421470404f, 0.0017409600550308824f, 0.0023585064336657524f, 0.0025372225791215897f, 0.0025443751364946365f, 0.0020588363986462355f, 0.003073307918384671f, 0.0021270180586725473f, 0.0021963664330542088f, 0.002925719367340207f, 0.001953396014869213f, 0.0027869383338838816f, 0.0024552291724830866f, 0.002270686673000455f, 0.002008582465350628f, 0.0023254663683474064f, 0.0020099044777452946f, 0.0017313228454440832f, 0.002080739475786686f, 0.003695474937558174f, 0.0022898633033037186f, 0.0025552604347467422f, 0.0023357458412647247f, 0.002475527347996831f, 0.0022589510772377253f, 0.002412250963971019f, 0.002042268868535757f, 0.001984083093702793f, 0.0020220535807311535f, 0.002416006289422512f, 0.0023181079886853695f, 0.0018159841420128942f, 0.001926477998495102f, 0.0019513820298016071f, 0.003335509216412902f, 0.0017953944625332952f, 0.0034012100659310818f, 0.0022555566392838955f, 0.002986337523907423f, 0.002595319412648678f, 0.002829245524480939f, 0.002923441817983985f, 0.001988568576052785f, 0.002371225506067276f, 0.003489559981971979f, 0.002800630871206522f, 0.0022045753430575132f, 0.0020310243126004934f, 0.002860801760107279f, 0.0018488260684534907f, 0.0018582850461825728f, 0.0030324633698910475f, 0.002278530038893223f, 0.0021614290308207273f, 0.0022031967528164387f, 0.0026212488301098347f, 0.0023561378475278616f, 0.002476269844919443f, 0.0025917384773492813f, 0.0022251836489886045f, 0.0025081681087613106f, 0.0020222575403749943f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #4 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(eltwise_10_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.09272434562444687f),
    AI_PACK_INTQ_ZP(-119)))

/* Int quant #5 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(eltwise_11_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.09207500517368317f),
    AI_PACK_INTQ_ZP(-119)))

/* Int quant #6 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(eltwise_2_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.10314758867025375f),
    AI_PACK_INTQ_ZP(-116)))

/* Int quant #7 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(eltwise_3_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.10211491584777832f),
    AI_PACK_INTQ_ZP(-116)))

/* Int quant #8 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_14_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.031421687453985214f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #9 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_14_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 64,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.004714144393801689f, 0.0036659543402493f, 0.004489528015255928f, 0.005573638714849949f, 0.004009333439171314f, 0.003985451068729162f, 0.0032934723421931267f, 0.004717106930911541f, 0.004443681333214045f, 0.004965313710272312f, 0.0030865096487104893f, 0.004211679100990295f, 0.004918077494949102f, 0.0042662834748625755f, 0.004214905668050051f, 0.005961775779724121f, 0.003155183745548129f, 0.00298241525888443f, 0.004796170629560947f, 0.003718544729053974f, 0.004913656041026115f, 0.0042207068763673306f, 0.005841763690114021f, 0.003776758210733533f, 0.0031763252336531878f, 0.005358604248613119f, 0.0043677883222699165f, 0.006359319668263197f, 0.004105409607291222f, 0.00360893364995718f, 0.0045850276947021484f, 0.0038462260272353888f, 0.0053301057778298855f, 0.005057900678366423f, 0.0051037585362792015f, 0.006087106186896563f, 0.0032695780973881483f, 0.0031066129449754953f, 0.005805810447782278f, 0.005272009409964085f, 0.00589850964024663f, 0.003887294325977564f, 0.0040661925449967384f, 0.00401102751493454f, 0.006232923828065395f, 0.004642851185053587f, 0.006840630434453487f, 0.0033636274747550488f, 0.005650515202432871f, 0.0029400375206023455f, 0.003597891889512539f, 0.0037058584857732058f, 0.003770197043195367f, 0.003999417647719383f, 0.004573579877614975f, 0.004581402987241745f, 0.0031828510109335184f, 0.0032783772330731153f, 0.002501515904441476f, 0.0033767344430088997f, 0.0034272964112460613f, 0.0029278311412781477f, 0.0050038984045386314f, 0.004138271789997816f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #10 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_15_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.18249505758285522f),
    AI_PACK_INTQ_ZP(-17)))

/* Int quant #11 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_15_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 5,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.005680128466337919f, 0.004843189846724272f, 0.004765069577842951f, 0.005116306245326996f, 0.005327499937266111f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0)))

/* Int quant #12 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(nl_16_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.00390625f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #13 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(pool_13_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.02600458636879921f),
    AI_PACK_INTQ_ZP(-96)))

/* Int quant #14 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(pool_6_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.10211491584777832f),
    AI_PACK_INTQ_ZP(-116)))

/* Int quant #15 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(serving_default_input_layer0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.11971837282180786f),
    AI_PACK_INTQ_ZP(25)))

/* Int quant #16 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(tfl_pseudo_qconst4_4D_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.003256084630265832f),
    AI_PACK_INTQ_ZP(127)))

/* Int quant #17 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(tfl_pseudo_qconst5_4D_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.16391533613204956f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #18 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(tfl_pseudo_qconst8_4D_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.00553410779684782f),
    AI_PACK_INTQ_ZP(94)))

/* Int quant #19 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(tfl_pseudo_qconst9_4D_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.024594133719801903f),
    AI_PACK_INTQ_ZP(-128)))

/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_bias, AI_STATIC,
  0, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &conv2d_1_bias_array, NULL)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_output, AI_STATIC,
  1, 0x1,
  AI_SHAPE_INIT(4, 1, 32, 38, 1), AI_STRIDE_INIT(4, 1, 1, 32, 1216),
  1, &conv2d_1_output_array, &conv2d_1_output_array_intq)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_scratch0, AI_STATIC,
  2, 0x0,
  AI_SHAPE_INIT(4, 1, 1672, 1, 1), AI_STRIDE_INIT(4, 1, 1, 1672, 1672),
  1, &conv2d_1_scratch0_array, NULL)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_weights, AI_STATIC,
  3, 0x1,
  AI_SHAPE_INIT(4, 6, 3, 1, 32), AI_STRIDE_INIT(4, 1, 6, 192, 576),
  1, &conv2d_1_weights_array, &conv2d_1_weights_array_intq)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_9_bias, AI_STATIC,
  4, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &conv2d_9_bias_array, NULL)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_9_output, AI_STATIC,
  5, 0x1,
  AI_SHAPE_INIT(4, 1, 64, 17, 1), AI_STRIDE_INIT(4, 1, 1, 64, 1088),
  1, &conv2d_9_output_array, &conv2d_9_output_array_intq)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_9_scratch0, AI_STATIC,
  6, 0x0,
  AI_SHAPE_INIT(4, 1, 6400, 1, 1), AI_STRIDE_INIT(4, 1, 1, 6400, 6400),
  1, &conv2d_9_scratch0_array, NULL)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_9_weights, AI_STATIC,
  7, 0x1,
  AI_SHAPE_INIT(4, 32, 3, 1, 64), AI_STRIDE_INIT(4, 1, 32, 2048, 6144),
  1, &conv2d_9_weights_array, &conv2d_9_weights_array_intq)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_10_output, AI_STATIC,
  8, 0x1,
  AI_SHAPE_INIT(4, 1, 64, 17, 1), AI_STRIDE_INIT(4, 1, 1, 64, 1088),
  1, &eltwise_10_output_array, &eltwise_10_output_array_intq)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_11_output, AI_STATIC,
  9, 0x1,
  AI_SHAPE_INIT(4, 1, 64, 17, 1), AI_STRIDE_INIT(4, 1, 1, 64, 1088),
  1, &eltwise_11_output_array, &eltwise_11_output_array_intq)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_11_output0, AI_STATIC,
  10, 0x1,
  AI_SHAPE_INIT(4, 1, 64, 1, 17), AI_STRIDE_INIT(4, 1, 1, 64, 64),
  1, &eltwise_11_output_array, &eltwise_11_output_array_intq)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_2_output, AI_STATIC,
  11, 0x1,
  AI_SHAPE_INIT(4, 1, 32, 38, 1), AI_STRIDE_INIT(4, 1, 1, 32, 1216),
  1, &eltwise_2_output_array, &eltwise_2_output_array_intq)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_3_output, AI_STATIC,
  12, 0x1,
  AI_SHAPE_INIT(4, 1, 32, 38, 1), AI_STRIDE_INIT(4, 1, 1, 32, 1216),
  1, &eltwise_3_output_array, &eltwise_3_output_array_intq)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(
  gemm_14_bias, AI_STATIC,
  13, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &gemm_14_bias_array, NULL)

/* Tensor #14 */
AI_TENSOR_OBJ_DECLARE(
  gemm_14_output, AI_STATIC,
  14, 0x1,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 1, 1, 64, 64),
  1, &gemm_14_output_array, &gemm_14_output_array_intq)

/* Tensor #15 */
AI_TENSOR_OBJ_DECLARE(
  gemm_14_scratch0, AI_STATIC,
  15, 0x0,
  AI_SHAPE_INIT(4, 1, 384, 1, 1), AI_STRIDE_INIT(4, 2, 2, 768, 768),
  1, &gemm_14_scratch0_array, NULL)

/* Tensor #16 */
AI_TENSOR_OBJ_DECLARE(
  gemm_14_weights, AI_STATIC,
  16, 0x1,
  AI_SHAPE_INIT(4, 64, 64, 1, 1), AI_STRIDE_INIT(4, 1, 64, 4096, 4096),
  1, &gemm_14_weights_array, &gemm_14_weights_array_intq)

/* Tensor #17 */
AI_TENSOR_OBJ_DECLARE(
  gemm_15_bias, AI_STATIC,
  17, 0x0,
  AI_SHAPE_INIT(4, 1, 5, 1, 1), AI_STRIDE_INIT(4, 4, 4, 20, 20),
  1, &gemm_15_bias_array, NULL)

/* Tensor #18 */
AI_TENSOR_OBJ_DECLARE(
  gemm_15_output, AI_STATIC,
  18, 0x1,
  AI_SHAPE_INIT(4, 1, 5, 1, 1), AI_STRIDE_INIT(4, 1, 1, 5, 5),
  1, &gemm_15_output_array, &gemm_15_output_array_intq)

/* Tensor #19 */
AI_TENSOR_OBJ_DECLARE(
  gemm_15_scratch0, AI_STATIC,
  19, 0x0,
  AI_SHAPE_INIT(4, 1, 89, 1, 1), AI_STRIDE_INIT(4, 2, 2, 178, 178),
  1, &gemm_15_scratch0_array, NULL)

/* Tensor #20 */
AI_TENSOR_OBJ_DECLARE(
  gemm_15_weights, AI_STATIC,
  20, 0x1,
  AI_SHAPE_INIT(4, 64, 5, 1, 1), AI_STRIDE_INIT(4, 1, 64, 320, 320),
  1, &gemm_15_weights_array, &gemm_15_weights_array_intq)

/* Tensor #21 */
AI_TENSOR_OBJ_DECLARE(
  nl_16_output, AI_STATIC,
  21, 0x1,
  AI_SHAPE_INIT(4, 1, 5, 1, 1), AI_STRIDE_INIT(4, 1, 1, 5, 5),
  1, &nl_16_output_array, &nl_16_output_array_intq)

/* Tensor #22 */
AI_TENSOR_OBJ_DECLARE(
  nl_16_scratch0, AI_STATIC,
  22, 0x0,
  AI_SHAPE_INIT(4, 1, 124, 1, 1), AI_STRIDE_INIT(4, 4, 4, 496, 496),
  1, &nl_16_scratch0_array, NULL)

/* Tensor #23 */
AI_TENSOR_OBJ_DECLARE(
  pool_13_output, AI_STATIC,
  23, 0x1,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 1, 1, 64, 64),
  1, &pool_13_output_array, &pool_13_output_array_intq)

/* Tensor #24 */
AI_TENSOR_OBJ_DECLARE(
  pool_6_output, AI_STATIC,
  24, 0x1,
  AI_SHAPE_INIT(4, 1, 32, 19, 1), AI_STRIDE_INIT(4, 1, 1, 32, 608),
  1, &pool_6_output_array, &pool_6_output_array_intq)

/* Tensor #25 */
AI_TENSOR_OBJ_DECLARE(
  serving_default_input_layer0_output, AI_STATIC,
  25, 0x1,
  AI_SHAPE_INIT(4, 1, 6, 1, 40), AI_STRIDE_INIT(4, 1, 1, 6, 6),
  1, &serving_default_input_layer0_output_array, &serving_default_input_layer0_output_array_intq)

/* Tensor #26 */
AI_TENSOR_OBJ_DECLARE(
  serving_default_input_layer0_output0, AI_STATIC,
  26, 0x1,
  AI_SHAPE_INIT(4, 1, 6, 40, 1), AI_STRIDE_INIT(4, 1, 1, 6, 240),
  1, &serving_default_input_layer0_output_array, &serving_default_input_layer0_output_array_intq)

/* Tensor #27 */
AI_TENSOR_OBJ_DECLARE(
  tfl_pseudo_qconst4_4D, AI_STATIC,
  27, 0x1,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 1, 1, 64, 64),
  1, &tfl_pseudo_qconst4_4D_array, &tfl_pseudo_qconst4_4D_array_intq)

/* Tensor #28 */
AI_TENSOR_OBJ_DECLARE(
  tfl_pseudo_qconst5_4D, AI_STATIC,
  28, 0x1,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 1, 1, 64, 64),
  1, &tfl_pseudo_qconst5_4D_array, &tfl_pseudo_qconst5_4D_array_intq)

/* Tensor #29 */
AI_TENSOR_OBJ_DECLARE(
  tfl_pseudo_qconst8_4D, AI_STATIC,
  29, 0x1,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 1, 1, 32, 32),
  1, &tfl_pseudo_qconst8_4D_array, &tfl_pseudo_qconst8_4D_array_intq)

/* Tensor #30 */
AI_TENSOR_OBJ_DECLARE(
  tfl_pseudo_qconst9_4D, AI_STATIC,
  30, 0x1,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 1, 1, 32, 32),
  1, &tfl_pseudo_qconst9_4D_array, &tfl_pseudo_qconst9_4D_array_intq)



/**  Layer declarations section  **********************************************/



AI_STATIC_CONST ai_i32 nl_16_nl_params_data[] = { 1567620608, 24, -124 };
AI_ARRAY_OBJ_DECLARE(
    nl_16_nl_params, AI_ARRAY_FORMAT_S32,
    nl_16_nl_params_data, nl_16_nl_params_data, 3, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  nl_16_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_15_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_16_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_16_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  nl_16_layer, 16,
  SM_TYPE, 0x0, NULL,
  sm, forward_sm_integer,
  &nl_16_chain,
  NULL, &nl_16_layer, AI_STATIC, 
  .nl_params = &nl_16_nl_params, 
  .axis = AI_SHAPE_CHANNEL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  gemm_15_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_14_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_15_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &gemm_15_weights, &gemm_15_bias),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_15_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  gemm_15_layer, 15,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense_integer_SSSA_ch,
  &gemm_15_chain,
  NULL, &nl_16_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  gemm_14_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &pool_13_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_14_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &gemm_14_weights, &gemm_14_bias),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_14_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  gemm_14_layer, 14,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense_integer_SSSA_ch,
  &gemm_14_chain,
  NULL, &gemm_15_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  pool_13_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_11_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &pool_13_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  pool_13_layer, 13,
  POOL_TYPE, 0x0, NULL,
  pool, forward_ap_integer_INT8,
  &pool_13_chain,
  NULL, &gemm_14_layer, AI_STATIC, 
  .pool_size = AI_SHAPE_2D_INIT(1, 17), 
  .pool_stride = AI_SHAPE_2D_INIT(1, 17), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  eltwise_11_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &eltwise_10_output, &tfl_pseudo_qconst4_4D),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_11_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  eltwise_11_layer, 11,
  ELTWISE_INTEGER_TYPE, 0x0, NULL,
  eltwise_integer, forward_eltwise_integer_INT8,
  &eltwise_11_chain,
  NULL, &pool_13_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_INT8, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  eltwise_10_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_9_output, &tfl_pseudo_qconst5_4D),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_10_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  eltwise_10_layer, 10,
  ELTWISE_INTEGER_TYPE, 0x0, NULL,
  eltwise_integer, forward_eltwise_integer_INT8,
  &eltwise_10_chain,
  NULL, &eltwise_11_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_INT8, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_9_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &pool_6_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_9_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_9_weights, &conv2d_9_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_9_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_9_layer, 9,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_deep_sssa8_ch,
  &conv2d_9_chain,
  NULL, &eltwise_10_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  pool_6_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_3_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &pool_6_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  pool_6_layer, 6,
  POOL_TYPE, 0x0, NULL,
  pool, forward_mp_integer_INT8,
  &pool_6_chain,
  NULL, &conv2d_9_layer, AI_STATIC, 
  .pool_size = AI_SHAPE_2D_INIT(2, 1), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 1), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  eltwise_3_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &eltwise_2_output, &tfl_pseudo_qconst8_4D),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_3_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  eltwise_3_layer, 3,
  ELTWISE_INTEGER_TYPE, 0x0, NULL,
  eltwise_integer, forward_eltwise_integer_INT8,
  &eltwise_3_chain,
  NULL, &pool_6_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_INT8, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  eltwise_2_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_1_output, &tfl_pseudo_qconst9_4D),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_2_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  eltwise_2_layer, 2,
  ELTWISE_INTEGER_TYPE, 0x0, NULL,
  eltwise_integer, forward_eltwise_integer_INT8,
  &eltwise_2_chain,
  NULL, &eltwise_3_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_INT8, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_1_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &serving_default_input_layer0_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_1_weights, &conv2d_1_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_1_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_1_layer, 1,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_sssa8_ch,
  &conv2d_1_chain,
  NULL, &eltwise_2_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)


#if (AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 11988, 1, 1),
    11988, NULL, NULL),
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 8096, 1, 1),
    8096, NULL, NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_HARSH_DETECTION_PROTOTYPE_IN_NUM, &serving_default_input_layer0_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_HARSH_DETECTION_PROTOTYPE_OUT_NUM, &nl_16_output),
  &conv2d_1_layer, 0xb9250346, NULL)

#else

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 11988, 1, 1),
      11988, NULL, NULL)
  ),
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 8096, 1, 1),
      8096, NULL, NULL)
  ),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_HARSH_DETECTION_PROTOTYPE_IN_NUM, &serving_default_input_layer0_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_HARSH_DETECTION_PROTOTYPE_OUT_NUM, &nl_16_output),
  &conv2d_1_layer, 0xb9250346, NULL)

#endif	/*(AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)*/



/******************************************************************************/
AI_DECLARE_STATIC
ai_bool harsh_detection_prototype_configure_activations(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_activations_map(g_harsh_detection_prototype_activations_map, 1, params)) {
    /* Updating activations (byte) offsets */
    
    serving_default_input_layer0_output_array.data = AI_PTR(g_harsh_detection_prototype_activations_map[0] + 0);
    serving_default_input_layer0_output_array.data_start = AI_PTR(g_harsh_detection_prototype_activations_map[0] + 0);
    conv2d_1_scratch0_array.data = AI_PTR(g_harsh_detection_prototype_activations_map[0] + 240);
    conv2d_1_scratch0_array.data_start = AI_PTR(g_harsh_detection_prototype_activations_map[0] + 240);
    conv2d_1_output_array.data = AI_PTR(g_harsh_detection_prototype_activations_map[0] + 1912);
    conv2d_1_output_array.data_start = AI_PTR(g_harsh_detection_prototype_activations_map[0] + 1912);
    eltwise_2_output_array.data = AI_PTR(g_harsh_detection_prototype_activations_map[0] + 0);
    eltwise_2_output_array.data_start = AI_PTR(g_harsh_detection_prototype_activations_map[0] + 0);
    eltwise_3_output_array.data = AI_PTR(g_harsh_detection_prototype_activations_map[0] + 1216);
    eltwise_3_output_array.data_start = AI_PTR(g_harsh_detection_prototype_activations_map[0] + 1216);
    pool_6_output_array.data = AI_PTR(g_harsh_detection_prototype_activations_map[0] + 0);
    pool_6_output_array.data_start = AI_PTR(g_harsh_detection_prototype_activations_map[0] + 0);
    conv2d_9_scratch0_array.data = AI_PTR(g_harsh_detection_prototype_activations_map[0] + 608);
    conv2d_9_scratch0_array.data_start = AI_PTR(g_harsh_detection_prototype_activations_map[0] + 608);
    conv2d_9_output_array.data = AI_PTR(g_harsh_detection_prototype_activations_map[0] + 7008);
    conv2d_9_output_array.data_start = AI_PTR(g_harsh_detection_prototype_activations_map[0] + 7008);
    eltwise_10_output_array.data = AI_PTR(g_harsh_detection_prototype_activations_map[0] + 0);
    eltwise_10_output_array.data_start = AI_PTR(g_harsh_detection_prototype_activations_map[0] + 0);
    eltwise_11_output_array.data = AI_PTR(g_harsh_detection_prototype_activations_map[0] + 1088);
    eltwise_11_output_array.data_start = AI_PTR(g_harsh_detection_prototype_activations_map[0] + 1088);
    pool_13_output_array.data = AI_PTR(g_harsh_detection_prototype_activations_map[0] + 0);
    pool_13_output_array.data_start = AI_PTR(g_harsh_detection_prototype_activations_map[0] + 0);
    gemm_14_scratch0_array.data = AI_PTR(g_harsh_detection_prototype_activations_map[0] + 64);
    gemm_14_scratch0_array.data_start = AI_PTR(g_harsh_detection_prototype_activations_map[0] + 64);
    gemm_14_output_array.data = AI_PTR(g_harsh_detection_prototype_activations_map[0] + 832);
    gemm_14_output_array.data_start = AI_PTR(g_harsh_detection_prototype_activations_map[0] + 832);
    gemm_15_scratch0_array.data = AI_PTR(g_harsh_detection_prototype_activations_map[0] + 0);
    gemm_15_scratch0_array.data_start = AI_PTR(g_harsh_detection_prototype_activations_map[0] + 0);
    gemm_15_output_array.data = AI_PTR(g_harsh_detection_prototype_activations_map[0] + 180);
    gemm_15_output_array.data_start = AI_PTR(g_harsh_detection_prototype_activations_map[0] + 180);
    nl_16_scratch0_array.data = AI_PTR(g_harsh_detection_prototype_activations_map[0] + 188);
    nl_16_scratch0_array.data_start = AI_PTR(g_harsh_detection_prototype_activations_map[0] + 188);
    nl_16_output_array.data = AI_PTR(g_harsh_detection_prototype_activations_map[0] + 0);
    nl_16_output_array.data_start = AI_PTR(g_harsh_detection_prototype_activations_map[0] + 0);
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_ACTIVATIONS);
  return false;
}




/******************************************************************************/
AI_DECLARE_STATIC
ai_bool harsh_detection_prototype_configure_weights(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_weights_map(g_harsh_detection_prototype_weights_map, 1, params)) {
    /* Updating weights (byte) offsets */
    
    tfl_pseudo_qconst9_4D_array.format |= AI_FMT_FLAG_CONST;
    tfl_pseudo_qconst9_4D_array.data = AI_PTR(g_harsh_detection_prototype_weights_map[0] + 0);
    tfl_pseudo_qconst9_4D_array.data_start = AI_PTR(g_harsh_detection_prototype_weights_map[0] + 0);
    tfl_pseudo_qconst8_4D_array.format |= AI_FMT_FLAG_CONST;
    tfl_pseudo_qconst8_4D_array.data = AI_PTR(g_harsh_detection_prototype_weights_map[0] + 32);
    tfl_pseudo_qconst8_4D_array.data_start = AI_PTR(g_harsh_detection_prototype_weights_map[0] + 32);
    tfl_pseudo_qconst5_4D_array.format |= AI_FMT_FLAG_CONST;
    tfl_pseudo_qconst5_4D_array.data = AI_PTR(g_harsh_detection_prototype_weights_map[0] + 64);
    tfl_pseudo_qconst5_4D_array.data_start = AI_PTR(g_harsh_detection_prototype_weights_map[0] + 64);
    tfl_pseudo_qconst4_4D_array.format |= AI_FMT_FLAG_CONST;
    tfl_pseudo_qconst4_4D_array.data = AI_PTR(g_harsh_detection_prototype_weights_map[0] + 128);
    tfl_pseudo_qconst4_4D_array.data_start = AI_PTR(g_harsh_detection_prototype_weights_map[0] + 128);
    conv2d_1_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_1_weights_array.data = AI_PTR(g_harsh_detection_prototype_weights_map[0] + 192);
    conv2d_1_weights_array.data_start = AI_PTR(g_harsh_detection_prototype_weights_map[0] + 192);
    conv2d_1_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_1_bias_array.data = AI_PTR(g_harsh_detection_prototype_weights_map[0] + 768);
    conv2d_1_bias_array.data_start = AI_PTR(g_harsh_detection_prototype_weights_map[0] + 768);
    conv2d_9_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_9_weights_array.data = AI_PTR(g_harsh_detection_prototype_weights_map[0] + 896);
    conv2d_9_weights_array.data_start = AI_PTR(g_harsh_detection_prototype_weights_map[0] + 896);
    conv2d_9_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_9_bias_array.data = AI_PTR(g_harsh_detection_prototype_weights_map[0] + 7040);
    conv2d_9_bias_array.data_start = AI_PTR(g_harsh_detection_prototype_weights_map[0] + 7040);
    gemm_14_weights_array.format |= AI_FMT_FLAG_CONST;
    gemm_14_weights_array.data = AI_PTR(g_harsh_detection_prototype_weights_map[0] + 7296);
    gemm_14_weights_array.data_start = AI_PTR(g_harsh_detection_prototype_weights_map[0] + 7296);
    gemm_14_bias_array.format |= AI_FMT_FLAG_CONST;
    gemm_14_bias_array.data = AI_PTR(g_harsh_detection_prototype_weights_map[0] + 11392);
    gemm_14_bias_array.data_start = AI_PTR(g_harsh_detection_prototype_weights_map[0] + 11392);
    gemm_15_weights_array.format |= AI_FMT_FLAG_CONST;
    gemm_15_weights_array.data = AI_PTR(g_harsh_detection_prototype_weights_map[0] + 11648);
    gemm_15_weights_array.data_start = AI_PTR(g_harsh_detection_prototype_weights_map[0] + 11648);
    gemm_15_bias_array.format |= AI_FMT_FLAG_CONST;
    gemm_15_bias_array.data = AI_PTR(g_harsh_detection_prototype_weights_map[0] + 11968);
    gemm_15_bias_array.data_start = AI_PTR(g_harsh_detection_prototype_weights_map[0] + 11968);
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_WEIGHTS);
  return false;
}


/**  PUBLIC APIs SECTION  *****************************************************/



AI_DEPRECATED
AI_API_ENTRY
ai_bool ai_harsh_detection_prototype_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_HARSH_DETECTION_PROTOTYPE_MODEL_NAME,
      .model_signature   = AI_HARSH_DETECTION_PROTOTYPE_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 137904,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .params            = AI_STRUCT_INIT,
      .activations       = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0xb9250346,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}



AI_API_ENTRY
ai_bool ai_harsh_detection_prototype_get_report(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_HARSH_DETECTION_PROTOTYPE_MODEL_NAME,
      .model_signature   = AI_HARSH_DETECTION_PROTOTYPE_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 137904,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .map_signature     = AI_MAGIC_SIGNATURE,
      .map_weights       = AI_STRUCT_INIT,
      .map_activations   = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0xb9250346,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}


AI_API_ENTRY
ai_error ai_harsh_detection_prototype_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}


AI_API_ENTRY
ai_error ai_harsh_detection_prototype_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    AI_CONTEXT_OBJ(&AI_NET_OBJ_INSTANCE),
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}


AI_API_ENTRY
ai_error ai_harsh_detection_prototype_create_and_init(
  ai_handle* network, const ai_handle activations[], const ai_handle weights[])
{
  ai_error err;
  ai_network_params params;

  err = ai_harsh_detection_prototype_create(network, AI_HARSH_DETECTION_PROTOTYPE_DATA_CONFIG);
  if (err.type != AI_ERROR_NONE) {
    return err;
  }
  
  if (ai_harsh_detection_prototype_data_params_get(&params) != true) {
    err = ai_harsh_detection_prototype_get_error(*network);
    return err;
  }
#if defined(AI_HARSH_DETECTION_PROTOTYPE_DATA_ACTIVATIONS_COUNT)
  /* set the addresses of the activations buffers */
  for (ai_u16 idx=0; activations && idx<params.map_activations.size; idx++) {
    AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_activations, idx, activations[idx]);
  }
#endif
#if defined(AI_HARSH_DETECTION_PROTOTYPE_DATA_WEIGHTS_COUNT)
  /* set the addresses of the weight buffers */
  for (ai_u16 idx=0; weights && idx<params.map_weights.size; idx++) {
    AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_weights, idx, weights[idx]);
  }
#endif
  if (ai_harsh_detection_prototype_init(*network, &params) != true) {
    err = ai_harsh_detection_prototype_get_error(*network);
  }
  return err;
}


AI_API_ENTRY
ai_buffer* ai_harsh_detection_prototype_inputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    AI_NETWORK_OBJ(network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_inputs_get(network, n_buffer);
}


AI_API_ENTRY
ai_buffer* ai_harsh_detection_prototype_outputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    AI_NETWORK_OBJ(network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_outputs_get(network, n_buffer);
}


AI_API_ENTRY
ai_handle ai_harsh_detection_prototype_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}


AI_API_ENTRY
ai_bool ai_harsh_detection_prototype_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = AI_NETWORK_OBJ(ai_platform_network_init(network, params));
  ai_bool ok = true;

  if (!net_ctx) return false;
  ok &= harsh_detection_prototype_configure_weights(net_ctx, params);
  ok &= harsh_detection_prototype_configure_activations(net_ctx, params);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_harsh_detection_prototype_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}


AI_API_ENTRY
ai_i32 ai_harsh_detection_prototype_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}



#undef AI_HARSH_DETECTION_PROTOTYPE_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

