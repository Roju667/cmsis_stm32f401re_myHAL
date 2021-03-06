/*
 * stm32f401xe_dma.c
 *
 *  Created on: 31 sty 2022
 *      Author: pawel
 */

#include "stm32f401xe_dma.h"

#include "stdint.h"
#include "stm32f401xe.h"
#include "stm32f401xe_rcc.h"

void DMA_ClockEnable(DMA_TypeDef *p_dmax)
{
	if (p_dmax == DMA1)
	{
		RCC_CLOCK_DMA1_ENABLE();
	}
	else if (p_dmax == DMA2)
	{
		RCC_CLOCK_DMA2_ENABLE();
	}

	return;
}

static uint8_t DMA_GetStreamNumber(DMA_Handle_t *p_handle_dma)
{
	if (p_handle_dma->p_dma_streamx == DMA1_Stream0
			|| p_handle_dma->p_dma_streamx == DMA2_Stream0)
	{
		return 0;
	}
	if (p_handle_dma->p_dma_streamx == DMA1_Stream1
			|| p_handle_dma->p_dma_streamx == DMA2_Stream1)
	{
		return 1;
	}
	if (p_handle_dma->p_dma_streamx == DMA1_Stream2
			|| p_handle_dma->p_dma_streamx == DMA2_Stream2)
	{
		return 2;
	}
	if (p_handle_dma->p_dma_streamx == DMA1_Stream3
			|| p_handle_dma->p_dma_streamx == DMA2_Stream3)
	{
		return 3;
	}
	if (p_handle_dma->p_dma_streamx == DMA1_Stream4
			|| p_handle_dma->p_dma_streamx == DMA2_Stream4)
	{
		return 4;
	}
	if (p_handle_dma->p_dma_streamx == DMA1_Stream5
			|| p_handle_dma->p_dma_streamx == DMA2_Stream5)
	{
		return 5;
	}
	if (p_handle_dma->p_dma_streamx == DMA1_Stream6
			|| p_handle_dma->p_dma_streamx == DMA2_Stream6)
	{
		return 6;
	}
	if (p_handle_dma->p_dma_streamx == DMA1_Stream7
			|| p_handle_dma->p_dma_streamx == DMA2_Stream7)
	{
		return 7;
	}

	p_handle_dma->status_error = kErrWrongStreamNumber;
	return 200;
}

static void DMA_ClearAllStreamFlags(DMA_Handle_t *p_handle_dma,
		uint8_t stream_number)
{
	// clear flags
	if (stream_number < 4)
	{
		// clear 5 flags on positions 0,6,16,22 for streams 0-3
		p_handle_dma->p_dmax->LIFCR |= (DMA_LIFCR_CFEIF0 | DMA_LIFCR_CDMEIF0
				| DMA_LIFCR_CTEIF0 |
				DMA_LIFCR_CHTIF0 | DMA_LIFCR_CTCIF0)
				<< (((stream_number / 2) * 16) + (stream_number * 6));
	}
	else if (stream_number >= 4 || stream_number < 8)
	{
		// clear 5 flags on positions 0,6,16,22 for streams 0-3
		p_handle_dma->p_dmax->HIFCR |= (DMA_HIFCR_CFEIF4 | DMA_HIFCR_CDMEIF4
				| DMA_HIFCR_CTEIF4 |
				DMA_HIFCR_CHTIF4 | DMA_HIFCR_CTCIF4)
				<< (((stream_number / 6) * 16) + ((stream_number % 4) * 6));
	}
	else
	{
		// error
		p_handle_dma->status_error = kErrWrongStreamNumber;
		return;
	}
}

void DMA_InitBasicParameters(DMA_Handle_t *p_handle_dma)
{
	// save stream number in uint8
	uint8_t stream_number = DMA_GetStreamNumber(p_handle_dma);
	// enable peripheral clock
	DMA_ClockEnable(p_handle_dma->p_dmax);

	// disable dma to configure new stream
	p_handle_dma->p_dma_streamx->CR &= ~(DMA_SxCR_EN);

	// wait until EN bit is cleared
	while (p_handle_dma->p_dma_streamx->CR & DMA_SxCR_EN)
		;

	// clear flags
	DMA_ClearAllStreamFlags(p_handle_dma, stream_number);

	//** OPTION TO CONFIGURE HERE DOUBLE BUFFER **//
	//** OPTION TO CONFIGURE HERE NO DATA ITEMS TO TRANSFER **//
	//** OPTION TO CONFIGURE MEM/PERI ADDRESSES **//

	// select DMA channel
	p_handle_dma->p_dma_streamx->CR |=
			(p_handle_dma->stream_config.channel_number << DMA_SxCR_CHSEL_Pos);

	// select flow control mode
	p_handle_dma->p_dma_streamx->CR |=
			((p_handle_dma->stream_config.flow_control) << DMA_SxCR_PFCTRL_Pos);

	// configure priority
	p_handle_dma->p_dma_streamx->CR |= ((p_handle_dma->stream_config.priority)
			<< DMA_SxCR_PL_Pos);

	// configure fifo en/dis , thresholds
	p_handle_dma->p_dma_streamx->FCR |=
			((p_handle_dma->stream_config.fifo_threshold) << DMA_SxFCR_FTH_Pos);
	p_handle_dma->p_dma_streamx->FCR |=
			((p_handle_dma->stream_config.direct_mode) << DMA_SxFCR_DMDIS_Pos);

	// configure data transfer direction
	p_handle_dma->p_dma_streamx->CR |= ((p_handle_dma->stream_config.direction)
			<< DMA_SxCR_DIR_Pos);

	// configure increment/fixed mode
	p_handle_dma->p_dma_streamx->CR |=
			((p_handle_dma->stream_config.mem_increment) << DMA_SxCR_MINC_Pos);
	p_handle_dma->p_dma_streamx->CR |=
			((p_handle_dma->stream_config.peri_increment) << DMA_SxCR_PINC_Pos);

	// configure burst modes TO DO
	if (p_handle_dma->stream_config.direct_mode == kDirectModeDisable)
	{
		// check if its possible to configure this burst mode
	}

	// configure data widths
	p_handle_dma->p_dma_streamx->CR |=
			((p_handle_dma->stream_config.mem_data_size) << DMA_SxCR_MSIZE_Pos);
	p_handle_dma->p_dma_streamx->CR |=
			((p_handle_dma->stream_config.peri_data_size) << DMA_SxCR_PSIZE_Pos);

	// configure circular mode
	p_handle_dma->p_dma_streamx->CR |=
			((p_handle_dma->stream_config.circular_mode) << DMA_SxCR_CIRC_Pos);

	// activate the stream by setting the EN bit in the DMA_SxCR register
	// p_handle_dma->p_dma_streamx->CR |= DMA_SxCR_EN;
}
