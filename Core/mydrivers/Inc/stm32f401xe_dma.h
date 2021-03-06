/*
 * stm32f401xe_dma.h
 *
 *  Created on: 31 sty 2022
 *      Author: pawel
 */

#ifndef CORE_MYDRIVERS_INC_STM32F401XE_DMA_H_
#define CORE_MYDRIVERS_INC_STM32F401XE_DMA_H_

#include "stm32f401xe.h"

/*
 * @IncrementMode
 */
typedef enum DmaIncrementMode_t
{
	kIncrementDisable, kIncrementEnable,
} DmaIncrementMode_t;

/*
 * @Direction
 */
typedef enum DmaDirection_t
{
	kPeriToMem, kMemToPeri, kMemToMem
} DmaDirection_t;

/*
 * @DoubleBuffer
 */
typedef enum DmaDoubleBuffer_t
{
	kDoubleBufferDisable, kDoubleBufferEnable
} DmaDoubleBuffer_t;

/*
 * @FlowControl - when peripheral flow control is used we do not know how much
 * data will be transfered. It can only be used by peripherals which are able to
 * signal end of transfer (SDIO) Value in SxNDTR doesn't matter when peripheral
 * control is used.
 */
typedef enum DmaFlowControl_t
{
	kDmaControl, kPeripheralControl
} DmaFlowControl_t;
/*
 * @Priority
 */
typedef enum DmaPriority_t
{
	kLow, kMedium, kHigh, kVeryHigh
} DmaPriority_t;

/*
 * @Channel
 */
typedef enum DmaChannel_t
{
	kChannel0, kChannel1, kChannel2, kChannel3, kChannel4, kChannel5, kChannel6, kChannel7
} DmaChannel_t;

/*
 * @FifoThreshold
 */
typedef enum DmaFifoThreshold_t
{
	k14FullFifo, k12FullFifo, k34FullFifo, kFullFifo
} DmaFifoThreshold_t;

/*
 * @DirectMode
 */
typedef enum DmaDirectMode_t
{
	kDirectModeEnable, kDirectModeDisable
} DmaDirectMode_t;

/*
 * @DataWidth
 */
typedef enum DmaDataWidth_t
{
	kByte, kHalfWord, kWord
} DmaDataWidth_t;

/*
 * @CircularMode
 */
typedef enum DmaCircularMode_t
{
	kCircularDisable, kCircularEnable
} DmaCircularMode_t;

/*
 * @Errors
 */
typedef enum DmaError_t
{
	kNoError, kErrWrongStreamNumber
} DmaError_t;

// structure for external peripherals
typedef struct DMA_Stream_Info
{
	DMA_Stream_TypeDef *p_dma_stream_tx;

	DMA_Stream_TypeDef *p_dma_stream_rx;

} DMA_Stream_Info;

typedef struct DMA_Stream_Config_t
{
	DmaChannel_t channel_number;  // @Channel

	DmaPriority_t priority;  // @Priority

	DmaDirection_t direction;  //@Direction

	DmaIncrementMode_t peri_increment;  // @IncrementMode

	DmaIncrementMode_t mem_increment;  // @IncrementMode

	DmaDataWidth_t mem_data_size;  // @DataWidth

	DmaDataWidth_t peri_data_size;  // @DataWidth

	DmaCircularMode_t circular_mode;  // @CircularMode

	uint32_t *p_peri_address;  //  peripheral address to get/put data

	uint32_t *p_mem0_address;  //  memory address 0 to get/put data

	uint32_t *p_mem1_address;  //  memory address 1 to get/put data (used in
							   //  double buffer mode)
	DmaDirectMode_t direct_mode;

	DmaFifoThreshold_t fifo_threshold;

	DmaFlowControl_t flow_control;  // @FlowControl by DMA or peripheral

} DMA_Stream_Config_t;

typedef struct DMA_Handle_t
{
	DMA_TypeDef *p_dmax;  // @address in memory

	DMA_Stream_TypeDef *p_dma_streamx;

	DMA_Stream_Config_t stream_config;

	DmaError_t status_error;

} DMA_Handle_t;


static inline void DMA_EnableDoubleBufferMode(DMA_Stream_TypeDef *p_dma_streamx)
{
	p_dma_streamx->CR |= DMA_SxCR_DBM;
}

static inline void DMA_SetAddresPeri(DMA_Stream_TypeDef *p_dma_streamx,volatile uint32_t *peri_add)
{
	p_dma_streamx->PAR = (uint32_t) peri_add;
}

static inline void DMA_SetAddresMem0(DMA_Stream_TypeDef *p_dma_streamx,uint32_t *mem0_add)
{
	p_dma_streamx->M0AR = (uint32_t) mem0_add;
}

static inline void DMA_SetAddresMem1(DMA_Stream_TypeDef *p_dma_streamx,uint32_t *mem1_add)
{
	p_dma_streamx->M1AR = (uint32_t) mem1_add;
}



void DMA_InitBasicParameters(DMA_Handle_t *p_handle_dma);

#endif /* CORE_MYDRIVERS_INC_STM32F401XE_DMA_H_ */
